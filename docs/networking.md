# Chapter 5: Network Layer (Kernel-Bypass) {#networking}

[<< Previous Chapter: Hardware Layer](hardware_arch.html) | [Back to Table of Contents](index.html) | [Next Chapter: Signal Layer >>](signal_processing.html)

## ef_vi-lite Stack
The kernel-bypass layer (`libs/kernel_bypass/ef_vi_lite.hpp`) provides a high-fidelity emulation of the **Ethernet Fabric Virtual Interface (ef_vi)**.

### Key Features:
- **Zero-Copy Architecture:** Packets are parsed directly from DMA-mapped buffers.
- **Descriptor Rings:** Managed using `std::unique_ptr<ef_descriptor[]>` to handle non-movable atomic flags.
- **Ownership Handoff:** Uses `memory_order_acquire/release` for low-latency HW/SW synchronization.

---

[<< Previous Chapter: Hardware Layer](hardware_arch.html) | [Back to Table of Contents](index.html) | [Next Chapter: Signal Layer >>](signal_processing.html)
