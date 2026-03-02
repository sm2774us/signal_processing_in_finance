# Chapter 7: Execution Layer (Convex Optimization) {#optimization}

[<< Previous Chapter: Signal Layer](signal_processing.html) | [Back to Table of Contents](index.html) | [Next Chapter: C++26 Features >>](cpp26_features.html)

## Mean-Variance Optimizer (L3)
The optimizer (`libs/optimizer/convex_optimizer.hpp`) solves for optimal portfolio weights.

### Mathematical Formulation:
\f[
\max_{w} \left( \alpha^T w - \frac{\lambda}{2} w^T \Sigma w \right)
\f]

### Performance & Safety:
- **C++26 Contracts:** Enforces mathematical invariants using `[[pre]]` and `[[post]]`.
- **Latency:** Targeted at ~350ns for typical portfolio sizes.

---

[<< Previous Chapter: Signal Layer](signal_processing.html) | [Back to Table of Contents](index.html) | [Next Chapter: C++26 Features >>](cpp26_features.html)
