#pragma once

#include <execution> // C++26 Sender/Receiver (P2300)
#include <cstdint>
#include <memory>
#include <debugging> // For std::breakpoint()
#include "hardware/asm/hardware_asm.hpp"

/**
 * @file hardware_trigger.hpp
 * @brief C++26 Asynchronous Hardware Bridge using Senders/Receivers.
 */

namespace hft::hardware {

class HardwareTrigger {
public:
    struct alignas(64) HardwareRegs {
        volatile uint64_t status;
        volatile uint64_t threshold;
        volatile uint64_t last_price;
    };

    explicit HardwareTrigger(uint64_t threshold) 
        : regs_(std::make_unique<HardwareRegs>()) {
        regs_->threshold = threshold;
        regs_->status = 0;
    }

    /**
     * @brief C++26 std::execution (P2300) Sender for Async Event.
     * Replaces raw spin-loops with a composable sender/receiver pattern.
     */
    auto async_wait() {
        return std::execution::just() | std::execution::then([this] {
            while (!(asm_io::mmio_read64(&regs_->status) & 0x1)) {
                asm_io::cpu_pause();
            }
            regs_->status = 0;
        });
    }

    /**
     * @brief Triggers a breakpoint for debugging in error paths.
     */
    void debug_trap() {
        std::breakpoint(); // C++26 standard debugging support
    }

    void simulate_fpga_write(uint64_t price) {
        if (std::abs(static_cast<int64_t>(price - regs_->last_price)) >= static_cast<int64_t>(regs_->threshold)) {
            regs_->last_price = price;
            regs_->status |= 0x1;
        }
    }

private:
    std::unique_ptr<HardwareRegs> regs_;
};

} // namespace hft::hardware
