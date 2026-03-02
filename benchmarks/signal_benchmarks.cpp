#include <benchmark/benchmark.h>
#include <thread>
#include <atomic>
#include "libs/tick_consumer/tick_consumer.hpp"
#include "libs/state_estimator/kalman_filter.hpp"
#include "libs/optimizer/convex_optimizer.hpp"
#include "libs/kernel_bypass/ef_vi_lite.hpp"
#include "libs/dma_engine/axi_dma_controller.hpp"

using namespace hft::signals;
using namespace hft::net;
using namespace hft::hardware::dma;

/**
 * @brief Production-grade Kernel-Bypass Pipeline Benchmark.
 * 
 * Flow:
 * 1. Hardware: Simulates an FPGA TOE delivering a packet via DMA (ef_vi descriptor).
 * 2. CPU: Busy-polls the ef_vi RX ring (Zero-Copy).
 * 3. On Receive: Tick Parsing -> Kalman Filtering -> Convex Optimization.
 */
static void BM_KernelBypass_SignalPipeline(benchmark::State& state) {
    ef_vi_context net_ctx(1024);
    AxiDmaController dma_ctrl;
    std::atomic<bool> running{true};
    
    // Kalman & Optimizer setup
    KalmanFilter<1, 1> kf; kf.H << 1.0;
    Eigen::MatrixXd cov(1, 1); cov << 0.01;

    // Simulated FPGA/TOE Thread
    std::thread hw_thread([&]() {
        const char* raw_tick = "1709311200,150.25,1000.0";
        while (running) {
            // Simulate packet arrival and DMA transfer to Host RAM
            net_ctx.simulate_hw_dma(reinterpret_cast<const uint8_t*>(raw_tick), 24);
            dma_ctrl.simulate_hw_done();
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
    });

    for (auto _ : state) {
        // 1. Kernel-Bypass Polling (Zero-Copy ef_vi style)
        const uint8_t* packet = nullptr;
        while (!(packet = net_ctx.receive())) {
            // Busy poll
        }

        // 2. Parse from the DMA-delivered buffer
        std::string_view line(reinterpret_cast<const char*>(packet), 24);
        auto tick = TickConsumer::parse_csv(line);
        
        // 3. State Estimation
        kf.predict();
        Eigen::Vector<double, 1> z; z << tick->price;
        kf.update(z);
        
        // 4. Portfolio Optimization
        auto weights = ConvexOptimizer::solve_mean_variance(kf.get_state(), cov, 1.0);
        benchmark::DoNotOptimize(weights);
    }

    running = false;
    hw_thread.join();
}
BENCHMARK(BM_KernelBypass_SignalPipeline);

BENCHMARK_MAIN();
