#pragma once

#include <Eigen/Dense>
#include <expected>
#include <string>

/**
 * @file convex_optimizer.hpp
 * @brief C++26 Contracts-enabled Convex Optimization.
 */

namespace hft::signals {

class ConvexOptimizer {
public:
    enum class Error {
        OptimizationFailed,
        InvalidDimensions,
        MatrixNotPD
    };

    /**
     * @brief Unconstrained Mean-Variance Solution.
     * 
     * [[pre: alpha.size() == covariance.rows()]]
     * [[pre: covariance.rows() == covariance.cols()]]
     * [[pre: risk_aversion > 0.0]]
     * [[post: result.has_value() -> result.value().size() == alpha.size()]]
     */
    [[nodiscard]] static std::expected<Eigen::VectorXd, Error> solve_mean_variance(
        const Eigen::VectorXd& alpha,
        const Eigen::MatrixXd& covariance,
        double risk_aversion) noexcept {
        
        if (alpha.size() != covariance.rows() || covariance.rows() != covariance.cols()) [[unlikely]] {
            return std::unexpected(Error::InvalidDimensions);
        }

        if (risk_aversion <= 0.0) [[unlikely]] {
            return std::unexpected(Error::OptimizationFailed);
        }

        Eigen::LLT<Eigen::MatrixXd> llt(covariance);
        if (llt.info() == Eigen::Success) {
            Eigen::VectorXd weights = (1.0 / risk_aversion) * llt.solve(alpha);
            return weights;
        } else {
            return std::unexpected(Error::MatrixNotPD);
        }
    }
};

} // namespace hft::signals
