# Kernel-Bypass Networking {#networking}

## ef_vi-lite Stack
The kernel-bypass layer (`libs/kernel_bypass/ef_vi_lite.hpp`) emulates the AMD/Solarflare hardware interface.
- **Zero-Copy Architecture:** Packets are parsed directly from DMA-mapped memory.
- **Spin-Polling:** Descriptor rings are polled with minimum latency using ASM MMIO hints.
