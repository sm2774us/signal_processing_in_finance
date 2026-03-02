# Chapter 6: Signal Layer (State Estimation) {#signal_processing}

[<< Previous Chapter: Network Layer](networking.html) | [Back to Table of Contents](index.html) | [Next Chapter: Execution Layer >>](optimization.html)

## Kalman Filter (L2)
The Kalman filter (`libs/state_estimator/kalman_filter.hpp`) denoises price signals in real-time.

### Implementation Details:
- **Matrix Math:** Built on **Eigen::Dense** for high-performance linear algebra.
- **Numerical Stability:** Designed for LDLT decomposition.
- **C++26 Views:** Uses `std::mdspan` (protected by `__has_include`) to provide standardized data views of the state vector.

\f[
\hat{x}_{k|k} = \hat{x}_{k|k-1} + K_k (z_k - H \hat{x}_{k|k-1})
\f]

## Tick Consumer (L1)
The `libs/tick_consumer/tick_consumer.hpp` provides nano-second parsing logic.
- **Robust CSV Parsing:** Handles malformed input and performs error checking using `std::expected`.
- **Saturation Arithmetic:** Uses `std::add_sat` (or custom fallback) for safe volume accumulation.

---

[<< Previous Chapter: Network Layer](networking.html) | [Back to Table of Contents](index.html) | [Next Chapter: Execution Layer >>](optimization.html)
