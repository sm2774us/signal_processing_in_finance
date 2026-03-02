#pragma once

#include <cstdint>
#include <memory>
#if __has_include(<debugging>)
#include <debugging> // For std::breakpoint()
#endif
#include "hardware/asm/hardware_asm.hpp"

// Mock for C++26 std::execution (P2300) if not available in standard library
#if __has_include(<execution>)
#include <execution>
#endif

namespace hft::hardware {

#if defined(__cpp_lib_execution) && __cpp_lib_execution >= 202311L
namespace execution = std::execution;
#else
namespace execution {
    struct dummy_sender {};

    // Closure for 'then' to support pipe operator: sender | then(func)
    template<typename F>
    struct then_closure {
        F func;
    };

    inline dummy_sender just() { return {}; }

    // Two-argument 'then'
    template<typename F>
    inline dummy_sender then(dummy_sender, F&&) { return {}; }

    // One-argument 'then' (returns a closure)
    template<typename F>
    inline then_closure<F> then(F&& f) { return {std::forward<F>(f)}; }

    // Pipe operator for sender and closure
    template<typename F>
    inline dummy_sender operator|(dummy_sender s, then_closure<F>&& c) { 
        return then(s, std::forward<F>(c.func)); 
    }
}
#endif

/**
 * @file hardware_trigger.hpp
 * @brief C++26 Asynchronous Hardware Bridge using Senders/Receivers.
 */

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
        regs_->last_price = 0;
    }

    /**
     * @brief C++26 std::execution (P2300) Sender for Async Event.
     * Replaces raw spin-loops with a composable sender/receiver pattern.
     */
    auto async_wait() {
        return execution::just() | execution::then([this] {
            wait_for_trigger();
        });
    }

    /**
     * @brief Blocking wait for hardware trigger.
     */
    void wait_for_trigger() {
        while (!(asm_io::mmio_read64(&regs_->status) & 0x1)) {
            asm_io::cpu_pause();
        }
        regs_->status = 0;
    }

    /**
     * @brief Triggers a breakpoint for debugging in error paths.
     */
    void debug_trap() {
#if __has_include(<debugging>)
        std::breakpoint(); // C++26 standard debugging support
#endif
    }

    void on_hardware_tick(uint64_t price) {
        simulate_fpga_write(price);
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
