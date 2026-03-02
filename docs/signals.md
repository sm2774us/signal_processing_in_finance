# Signal Processing Logic {#signal_processing}

## Kalman Filter (L2)
The Kalman filter (`libs/state_estimator/kalman_filter.hpp`) provides real-time state estimation of noisy market data.
- **Mathematical Core:** Eigen3 LDLT for numerical stability.
- **C++26 Views:** `std::mdspan` is used to provide non-owning views of the state vector.

## Convex Optimization (L3)
The optimizer (`libs/optimizer/convex_optimizer.hpp`) calculates optimal portfolio weights.
- **Contract Enforcement:** Uses C++26 `[[pre]]` and `[[post]]` to ensure mathematical invariants.
