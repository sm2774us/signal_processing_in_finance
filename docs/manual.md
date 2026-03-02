# HFT Signal Processing Stack: Professional Manual {#mainpage}

Welcome to the official technical documentation for the **HFT Signal Processing Stack**. This manual is structured as a comprehensive guide to the architecture, implementation, and verification of our ultra-low-latency trading system.

## 📖 Table of Contents

1.  @subpage requirements "Engineering Requirements & Specifications"
2.  @subpage hardware_arch "Hardware Layer (VHDL & x86-64 ASM)"
3.  @subpage signal_processing "Signal Processing (Kalman & Optimization)"
4.  @subpage networking "Kernel-Bypass Networking (ef_vi)"
5.  @subpage verification "Verification & Coverage Strategy"

---

## 🚀 Executive Summary
The system implements a co-designed hardware-software pipeline using **C++26**, **Silicon-grade VHDL**, and **x86-64 MMIO Assembly**. It is designed to achieve sub-microsecond "Tick-to-Trade" latency by bypassing traditional OS kernel overheads and performing critical path filtering in FPGA logic.

### Key Technology Stack
- **Standard:** C++26 (Contracts, mdspan, execution)
- **Hardware:** VHDL (AXI-Stream/Lite), AVX-512 SIMD
- **Network:** Zero-Copy ef_vi (Solarflare style)
- **Math:** Eigen3 (LDLT Decomposition)

---

## 🛠️ Developer Quick Start
To get started with the codebase, please refer to the building instructions in the root README or explore the @ref hft namespace documentation.

- **API Reference:** [Modules](modules.html)
- **Class Hierarchy:** [Class Hierarchy](hierarchy.html)
- **File List:** [Files](files.html)
