# Chapter 6: Verification & Coverage Strategy {#verification}

[<< Previous Chapter: Execution Layer](optimization.html) | [Back to Table of Contents](index.html)

## Quality Standards
The HFT Signal Processing Stack is built with a "Verification First" mindset.

### 1. C++ Core Verification
- **Framework:** Google Test (GTest).
- **Coverage:** 100% LCOV coverage target for all libraries.
- **CI Enforcement:** Automated via GitHub Actions with GCC 14.

### 2. Silicon Logic Verification
- **Framework:** GHDL.
- **Simulation:** Timing-accurate testbench (`tests/signal_trigger_tb.vhd`).

### 3. Performance Benchmarking
- **Framework:** Google Benchmark.
- **Target:** Proving sub-microsecond end-to-end performance in a simulated environment.

---

[<< Previous Chapter: Execution Layer](optimization.html) | [Back to Table of Contents](index.html)
