#include <immintrin.h>
#include <vector>
#include <cstddef>

namespace hft::signals::asm_opt {

/**
 * @brief SIMD-optimized normalization using AVX-512.
 * Multiplies an array of prices by a scalar scale factor.
 */
void normalize_prices_avx512(double* prices, size_t count, double scale) {
    if (!prices || count == 0) return;

    size_t i = 0;
#if defined(__AVX512F__)
    __m512d v_scale = _mm512_set1_pd(scale);

    // Process 8 doubles at a time
    for (; i + 8 <= count; i += 8) {
        __m512d v_price = _mm512_loadu_pd(&prices[i]);
        __m512d v_res = _mm512_mul_pd(v_price, v_scale);
        _mm512_storeu_pd(&prices[i], v_res);
    }
#elif defined(__AVX2__)
    __m256d v_scale = _mm256_set1_pd(scale);
    for (; i + 4 <= count; i += 4) {
        __m256d v_price = _mm256_loadu_pd(&prices[i]);
        __m256d v_res = _mm256_mul_pd(v_price, v_scale);
        _mm256_storeu_pd(&prices[i], v_res);
    }
#endif

    // Scalar fallback for remaining elements
    for (; i < count; ++i) {
        prices[i] *= scale;
    }
}

} // namespace hft::signals::asm_opt
