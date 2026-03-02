# benchmarks/CMakeLists.txt

add_executable(signal_benchmarks signal_benchmarks.cpp)

# Allow the benchmark to include libraries using relative paths from the root
target_include_directories(signal_benchmarks PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(signal_benchmarks PRIVATE 
    benchmark::benchmark 
    tick_consumer 
    state_estimator 
    optimizer
    kernel_bypass
    dma_engine
    Eigen3::Eigen
    project_options
)

# Ensure it's built with the right flags
if(NOT MSVC)
    target_compile_options(signal_benchmarks PRIVATE -O3 -march=native)
endif()
