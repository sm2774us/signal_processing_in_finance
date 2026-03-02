# Chapter 3: Hardware Layer (Silicon & ASM) {#hardware_arch}

[<< Previous Chapter: Getting Started](getting_started.html) | [Back to Table of Contents](index.html) | [Next Chapter: Network Layer >>](networking.html)

## VHDL Silicon Trigger
The hardware layer (`hardware/vhdl/signal_trigger.vhd`) implements a simple signal trigger based on price jumps.
- **Active-High Reset:** Matches standard FPGA design patterns.
- **Synchronous Logic:** Processes price data on each clock edge.
- **Threshold Comparison:** Only triggers `trigger_out` when the absolute price change exceeds the `threshold`.

## x86-64 MMIO Assembly
Located in `hardware/asm/hardware_asm.hpp`, this layer provides cross-platform x86-64 assembly/intrinsics for MMIO.
- **mmio_read64:** Performs a low-latency 64-bit read with `lfence` memory fences.
- **cpu_pause:** Emits a `pause` instruction to optimize spin-loops.

## SIMD Optimization
The `hardware/asm/simd_ops.cpp` file provides AVX-512 and AVX2 optimized normalization:
- **AVX-512:** Processes 8 doubles per iteration.
- **AVX2:** Processes 4 doubles per iteration (fallback).
- **Scalar:** Standard C++ fallback for tail elements.

---

[<< Previous Chapter: Getting Started](getting_started.html) | [Back to Table of Contents](index.html) | [Next Chapter: Network Layer >>](networking.html)
