# Hardware & Assembly Architecture {#hardware_arch}

## VHDL Silicon Trigger
The hardware layer is implemented in `hardware/vhdl/signal_trigger.vhd`. It provides:
- **AXI-Stream Interface:** For high-throughput market data ingestion.
- **AXI-Lite Interface:** For runtime configuration of trigger thresholds.
- **Hardware Filtering:** Only price moves exceeding the threshold are forwarded to the CPU.

## x86-64 MMIO Assembly
Located in `hardware/asm/hardware_asm.hpp`, this layer provides the lowest-level interface to the hardware:
- **Memory Barriers:** Using `lfence` to ensure read-after-write consistency.
- **Low-Latency Polling:** Using the `pause` instruction to optimize spin-loops.
