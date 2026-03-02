#include <gtest/gtest.h>
#include <vector>
#include <numeric>
#include <algorithm>
#include "hardware/asm/simd_ops.cpp"

namespace hft::signals::asm_opt::tests {

/**
 * @brief Stress test for SIMD AVX-512 Normalization.
 * Tests varying data sizes to ensure the tail-handling (scalar fallback) is 100% correct.
 */
TEST(AsmSimdTest, FullCoverageStressTest) {
    for (size_t count : {1, 7, 8, 9, 15, 16, 17, 1023, 1024, 1025}) {
        std::vector<double> prices(count);
        std::iota(prices.begin(), prices.end(), 1.0);
        
        std::vector<double> expected(count);
        std::iota(expected.begin(), expected.end(), 1.0);
        const double scale = 3.14159;
        
        // Scalar
        for (auto& p : expected) p *= scale;
        
        // SIMD
        normalize_prices_avx512(prices.data(), count, scale);
        
        for (size_t i = 0; i < count; ++i) {
            ASSERT_NEAR(prices[i], expected[i], 1e-9) << "Failure at count=" << count << " index=" << i;
        }
    }
}

/**
 * @brief Test for null/zero cases.
 */
TEST(AsmSimdTest, ZeroElements) {
    normalize_prices_avx512(nullptr, 0, 1.0); // Should not crash
}

} // namespace hft::signals::asm_opt::tests
