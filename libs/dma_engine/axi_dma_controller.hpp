#pragma once

#include <cstdint>
#include <atomic>
#include "hardware/asm/hardware_asm.hpp"

/**
 * @file axi_dma_controller.hpp
 * @brief C++ Driver for AXI-DMA Hardware Interface.
 */

namespace hft::hardware::dma {

/**
 * @class AxiDmaController
 * @brief Professional AXI-DMA Driver mimicking Xilinx/AMD DMA IP.
 */
class AxiDmaController {
public:
    struct alignas(64) DmaRegisters {
        volatile uint32_t CR;     ///< Control Register (Offset 0x00)
        volatile uint32_t SR;     ///< Status Register (Offset 0x04)
        volatile uint64_t SRADDR; ///< Source/Destination Address (Offset 0x18)
        volatile uint32_t LENGTH; ///< Length of Transfer (Offset 0x28)
    };

    explicit AxiDmaController() : regs_(new DmaRegisters()) {
        regs_->CR = 0x1; // Enable DMA
    }
    
    ~AxiDmaController() { delete regs_; }

    /**
     * @brief High-performance Memory-to-Stream (TX) transfer.
     */
    void start_transfer(void* buffer, size_t length) noexcept {
        // 1. Tell DMA where the data is in Host RAM
        regs_->SRADDR = reinterpret_cast<uint64_t>(buffer);
        
        // 2. Set the length to trigger the transfer (AXI-DMA Standard)
        regs_->LENGTH = static_cast<uint32_t>(length);
    }

    /**
     * @brief Busy-wait for DMA transfer completion (Kernel Bypass style).
     */
    void wait_for_completion() noexcept {
        while (!(regs_->SR & 0x2)) { // Bit 1 is "Done" flag
            asm_io::cpu_pause(); 
        }
        regs_->SR &= ~0x2; // Clear Done flag
    }

    /**
     * @brief Simulates the FPGA logic updating the Status Register.
     */
    void simulate_hw_done() noexcept {
        regs_->SR |= 0x2; // Set Done flag
    }

private:
    DmaRegisters* regs_;
};

} // namespace hft::hardware::dma
