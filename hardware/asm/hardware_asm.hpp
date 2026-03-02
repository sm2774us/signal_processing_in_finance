#pragma once

#include <cstdint>

#if defined(_MSC_VER)
    #include <intrin.h>
    #include <immintrin.h>
#else
    #include <x86intrin.h>
#endif

/**
 * @file hardware_asm.hpp
 * @brief Cross-platform x86-64 assembly/intrinsics for MMIO.
 */

namespace hft::hardware::asm_io {

/**
 * @brief Performs a low-latency 64-bit read with a memory fence.
 */
inline uint64_t mmio_read64(const volatile uint64_t* addr) noexcept {
    #if defined(_MSC_VER)
        _mm_lfence();
        uint64_t res = *addr;
        _mm_lfence();
        return res;
    #else
        uint64_t result;
        __asm__ volatile (
            "lfence\n\t"
            "movq (%1), %0\n\t"
            "lfence\n\t"
            : "=r" (result)
            : "r" (addr)
            : "memory"
        );
        return result;
    #endif
}

/**
 * @brief Emits a PAUSE instruction for spin-loops.
 */
inline void cpu_pause() noexcept {
    #if defined(_MSC_VER)
        _mm_pause();
    #else
        __asm__ volatile ("pause" ::: "memory");
    #endif
}

} // namespace hft::hardware::asm_io
