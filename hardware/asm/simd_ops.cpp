#include <immintrin.h>
#include <vector>
#include <cstddef>

namespace hft::signals::asm_opt {

/**
 * @brief SIMD-optimized normalization using AVX-512.
 * Multiplies an array of prices by a scalar scale factor.
 */
void normalize_prices_avx512(double* prices, size_t count, double scale) {
    size_t i = 0;
    __m512d v_scale = _mm512_set1_pd(scale);

    // Process 8 doubles at a time
    for (; i + 8 <= count; i += 8) {
        __m512d v_price = _mm512_loadu_pd(&prices[i]);
        __m512d v_res = _mm512_mul_pd(v_price, v_scale);
        _mm512_storeu_pd(&prices[i], v_res);
    }

    // Scalar fallback for remaining elements
    for (; i < count; ++i) {
        prices[i] *= scale;
    }
}

} // namespace hft::signals::asm_opt
