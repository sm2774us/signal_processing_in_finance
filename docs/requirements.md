# Chapter 1: Engineering Requirements & Specifications {#requirements}

[<< Back to Table of Contents](index.html)

This chapter outlines the formal functional and non-functional requirements for the HFT Signal Processing Stack.

---

## 1. Project Overview
The **HFT Signal Processing Stack** is a low-latency, production-grade monorepo designed to process market data at sub-microsecond speeds. The solution implements a co-designed hardware-software pipeline mirroring elite industry architectures (Citadel, Jane Street, HRT).

## 2. Functional Requirements
- **FR-01: Market Data Parsing (L1):** Parse raw CSV/Binary L1/L2 market ticks without heap allocations.
- **FR-02: State Estimation (L2):** Kalman Filter to denoise price signals in real-time.
- **FR-03: Portfolio Optimization (L3):** Mean-Variance optimizer for optimal position sizes.
- **FR-04: Hardware-Software Bridge:** Low-level interface (ASM MMIO) between host CPU and simulated FPGA.
- **FR-05: Kernel Bypass:** Zero-copy, descriptor-based networking layer (ef_vi style).
- **FR-06: AXI-DMA Interface:** DMA controller to move data between FPGA stream and host memory.

## 3. Non-Functional Requirements
- **NFR-01: Latency (Performance):** End-to-end "Tick-to-Trade" latency under **1,000 nanoseconds**.
- **NFR-02: Portability:** Build and run on **Windows 11 (MSVC)**, **Ubuntu (GCC 14)**, and **macOS**.
- **NFR-03: Quality Standards:** 
    - 100% Code Coverage for all C++ logic.
    - Verified mathematical correctness (Unit Tests).
- **NFR-04: Scalability:** Support both **Bazel** and **CMake** build systems.

## 4. Hardware/Firmware Requirements
- **HW-01: VHDL Implementation:** Top-level silicon processor with AXI-Lite and AXI-Stream.
- **HW-02: SIMD Acceleration:** Critical hot-paths (normalization) using **AVX-512** intrinsics.
- **HW-03: Low-Level IO:** x86-64 assembly (`lfence`, `pause`) for direct PCIe MMIO polling.

---

[<< Back to Table of Contents](index.html) | [Next Chapter: Hardware Layer >>](hardware_arch.html)
