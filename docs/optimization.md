# Chapter 5: Execution Layer (Convex Optimization) {#optimization}

[<< Previous Chapter: Signal Layer](signal_processing.html) | [Back to Table of Contents](index.html) | [Next Chapter: Verification >>](verification.html)

## Mean-Variance Optimizer (L3)
The optimizer (`libs/optimizer/convex_optimizer.hpp`) solves for optimal position sizes.

### Mathematical Formulation:
$$ 	ext{maximize } \alpha^T w - \frac{\lambda}{2} w^T \Sigma w $$

### Performance & Safety:
- **C++26 Contracts:** Enforces mathematical invariants using `[[pre]]` and `[[post]]`.
- **Latency:** Targeted at ~350ns for typical portfolio sizes.

---

[<< Previous Chapter: Signal Layer](signal_processing.html) | [Back to Table of Contents](index.html) | [Next Chapter: Verification >>](verification.html)
