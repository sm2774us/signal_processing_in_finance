#pragma once

#include <vector>
#include <atomic>
#include <cstdint>
#include <memory>
#include <cstring>
#include "hardware/asm/hardware_asm.hpp"

/**
 * @file ef_vi_lite.hpp
 * @brief High-fidelity emulation of the ef_vi kernel-bypass API.
 * 
 * ef_vi (Ethernet Fabric Virtual Interface) is the industry standard for AMD/Solarflare NICs.
 * It provides direct, zero-copy access to the hardware descriptor rings.
 */

namespace hft::net {

/**
 * @struct ef_descriptor
 * @brief Matches the hardware descriptor format for packet ring buffers.
 */
struct alignas(64) ef_descriptor {
    uint64_t addr;      ///< Address of the packet buffer in Host RAM (DMA target)
    uint32_t len;       ///< Length of the packet data
    std::atomic<uint32_t> flags; ///< Ownership flag: 0 = HW, 1 = SW

    ef_descriptor() : addr(0), len(0), flags(0) {}
    
    // std::atomic makes this struct non-copyable and non-movable.
    ef_descriptor(const ef_descriptor&) = delete;
    ef_descriptor& operator=(const ef_descriptor&) = delete;
};

/**
 * @class ef_vi_context
 * @brief Manages a Kernel-Bypass Receive (RX) ring.
 */
class ef_vi_context {
public:
    explicit ef_vi_context(size_t ring_size) 
        : ring_size_(ring_size),
          descriptors_(std::make_unique<ef_descriptor[]>(ring_size)),
          buffers_(ring_size * 2048) // 2KB buffers per descriptor
    {
        for (size_t i = 0; i < ring_size; ++i) {
            descriptors_[i].addr = reinterpret_cast<uint64_t>(&buffers_[i * 2048]);
            descriptors_[i].flags.store(0, std::memory_order_release);
        }
    }

    /**
     * @brief Polls the hardware ring for new packets (Zero-Copy).
     * This is the "Busy-Wait" loop used in HFT.
     * 
     * @return Pointer to packet data or nullptr if none.
     */
    [[nodiscard]] const uint8_t* receive() noexcept {
        ef_descriptor& desc = descriptors_[current_index_];
        
        // Use atomic load to check for "Software Ownership" flag
        if (desc.flags.load(std::memory_order_acquire) == 1) {
            const uint8_t* data = reinterpret_cast<const uint8_t*>(desc.addr);
            
            // Release back to hardware (Simplified for emulation)
            desc.flags.store(0, std::memory_order_release);
            current_index_ = (current_index_ + 1) % ring_size_;
            return data;
        }

        hardware::asm_io::cpu_pause(); // Low-latency hint
        return nullptr;
    }

    /**
     * @brief Emulates the NIC writing a packet via DMA (Internal).
     */
    void simulate_hw_dma(const uint8_t* raw_data, uint32_t len) {
        ef_descriptor& desc = descriptors_[hw_index_];
        std::memcpy(reinterpret_cast<void*>(desc.addr), raw_data, len);
        desc.len = len;
        desc.flags.store(1, std::memory_order_release); // HW -> SW handoff
        hw_index_ = (hw_index_ + 1) % ring_size_;
    }

private:
    size_t ring_size_;
    size_t current_index_ = 0;
    size_t hw_index_ = 0;
    std::unique_ptr<ef_descriptor[]> descriptors_;
    std::vector<uint8_t> buffers_;
};

} // namespace hft::net
