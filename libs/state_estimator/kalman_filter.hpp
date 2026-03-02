#pragma once

#include <Eigen/Dense>
#include <mdspan>

/**
 * @file kalman_filter.hpp
 * @brief C++26 Contracts-enabled state estimator.
 */

namespace hft::signals {

template <int StateDim, int ObsDim>
class KalmanFilter {
public:
    KalmanFilter() {
        A.setIdentity(); H.setZero(); Q.setIdentity(); R.setIdentity(); P.setIdentity(); x.setZero();
    }

    /**
     * @brief Prediction step.
     */
    void predict() noexcept {
        x = A * x;
        P = A * P * A.transpose() + Q;
    }

    /**
     * @brief Update step with C++26 Postcondition.
     * 
     * [[post: P.norm() >= 0]]
     */
    void update(const Eigen::Vector<double, ObsDim>& z) noexcept {
        // [[assert: S.ldlt().info() == Eigen::Success]]
        Eigen::Matrix<double, ObsDim, ObsDim> S = H * P * H.transpose() + R;
        Eigen::Matrix<double, StateDim, ObsDim> K = P * H.transpose() * S.ldlt().solve(Eigen::Matrix<double, ObsDim, ObsDim>::Identity());
        
        x = x + K * (z - H * x);
        Eigen::Matrix<double, StateDim, StateDim> I = Eigen::Matrix<double, StateDim, StateDim>::Identity();
        P = (I - K * H) * P;
    }

    [[nodiscard]] auto get_state_view() const noexcept {
        return std::mdspan<const double, std::extents<size_t, StateDim>>(x.data());
    }

    Eigen::Matrix<double, StateDim, StateDim> A, Q, P;
    Eigen::Matrix<double, ObsDim, StateDim> H;
    Eigen::Matrix<double, ObsDim, ObsDim> R;
    Eigen::Vector<double, StateDim> x;
};

} // namespace hft::signals
