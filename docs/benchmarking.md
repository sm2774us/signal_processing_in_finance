# Chapter 10: Performance Benchmarking {#benchmarking}

[<< Previous Chapter: Verification](verification.html) | [Back to Table of Contents](index.html) | [Next Chapter: Citations >>](citations.html)

---

## 📊 Performance Budgets

The system is measured using **Google Benchmark** in a simulated production environment with CPU pinning and frequency locking.

| Stage | Mechanism | Target Latency | C++26 Feature |
| :--- | :--- | :--- | :--- |
| **Trigger** | ASM MMIO Poll | ~30 ns | `std::atomic::wait` |
| **Parse** | Kernel Bypass | ~70 ns | `std::expected` |
| **Filter** | Kalman (LDLT) | ~120 ns | `std::mdspan` |
| **Optimize** | LLT Solution | ~350 ns | `std::println` |

### Benchmark Results (Example)
```text
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_TickProcessing/1            72 ns           71 ns     9823421
BM_KalmanFilter/6x6           118 ns          118 ns     5923122
BM_PortfolioOptimization      342 ns          341 ns     2012399
```

---

[<< Previous Chapter: Verification](verification.html) | [Back to Table of Contents](index.html) | [Next Chapter: Citations >>](citations.html)
