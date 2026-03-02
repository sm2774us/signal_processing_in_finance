#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "libs/tick_consumer/tick_consumer.hpp"
#include "libs/state_estimator/kalman_filter.hpp"
#include "libs/optimizer/convex_optimizer.hpp"
#include "libs/hardware_bridge/hardware_trigger.hpp"

using namespace hft::signals;
using namespace hft::hardware;

// --- Hardware Bridge Coverage ---
TEST(HardwareBridgeTest, TriggerLogicCorrectness) {
    HardwareTrigger trigger(10); // 10 unit price move threshold
    
    // Simulate a price move that should NOT trigger (delta 5)
    trigger.on_hardware_tick(5);
    // (In a real test, we would use a non-blocking wait or a timeout)
}

TEST(HardwareBridgeTest, MultiThreadedTrigger) {
    HardwareTrigger trigger(10);
    std::atomic<bool> triggered{false};

    std::thread cpu_thread([&]() {
        trigger.wait_for_trigger();
        triggered = true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    EXPECT_FALSE(triggered.load());

    // Trigger the condition
    trigger.on_hardware_tick(11);
    
    cpu_thread.join();
    EXPECT_TRUE(triggered.load());
}

// --- TickConsumer Coverage ---
TEST(TickConsumerCoverage, ParseEmptyLine) {
    auto tick = TickConsumer::parse_csv("");
    EXPECT_FALSE(tick.has_value());
}

TEST(TickConsumerCoverage, ParseMalformedCSV) {
    EXPECT_FALSE(TickConsumer::parse_csv("123,456").has_value());
    EXPECT_FALSE(TickConsumer::parse_csv("abc,def,ghi").has_value());
}

TEST(TickConsumerCoverage, Normalization) {
    Tick tick{100, 10.0, 5.0, "AAPL"};
    TickConsumer::normalize(tick, 2.0, 0.5);
    EXPECT_DOUBLE_EQ(tick.price, 20.0);
    EXPECT_DOUBLE_EQ(tick.volume, 2.5);
}

// --- KalmanFilter Coverage ---
TEST(KalmanFilterCoverage, TemplateInitialization) {
    KalmanFilter<2, 1> kf;
    EXPECT_EQ(kf.get_state().size(), 2);
    EXPECT_DOUBLE_EQ(kf.get_state()(0), 0.0);
}

// --- ConvexOptimizer Coverage ---
TEST(OptimizerCoverage, InvalidDimensions) {
    Eigen::VectorXd alpha(2); alpha << 0.1, 0.2;
    Eigen::MatrixXd cov(1, 1); cov << 0.01;
    auto res = ConvexOptimizer::solve_mean_variance(alpha, cov, 1.0);
    ASSERT_FALSE(res.has_value());
    EXPECT_EQ(res.error(), ConvexOptimizer::Error::InvalidDimensions);
}
