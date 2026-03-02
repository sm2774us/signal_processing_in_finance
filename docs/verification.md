# Verification & Coverage Strategy {#verification}

## C++ Unit Verification
- **Framework:** Google Test (GTest)
- **Coverage Target:** 100% LCOV coverage for all signal logic.

## VHDL Silicon Simulation
- **Toolchain:** GHDL
- **Testbench:** Timing-accurate simulation of AXI-Stream bus transactions.

## Performance Benchmarking
- **Framework:** Google Benchmark
- **Latency Targets:** Sub-microsecond end-to-end tick-to-trade.
