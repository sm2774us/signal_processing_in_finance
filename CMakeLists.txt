cmake_minimum_required(VERSION 3.25)
project(SignalProcessingInFinance VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Handle platform-specific optimization flags
if(MSVC)
    add_compile_options(/W4 /WX /Ot /arch:AVX2)
else()
    add_compile_options(-Wall -Wextra -Werror -O3 -march=native)
endif()

# Dependencies
# In a real monorepo, use FetchContent or find_package
include(FetchContent)

# Eigen
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(eigen)

# Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Google Benchmark
FetchContent_Declare(
  googlebenchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.tar.gz
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googlebenchmark)

# Subdirectories
add_subdirectory(libs/tick_consumer)
add_subdirectory(libs/state_estimator)
add_subdirectory(libs/optimizer)

# Header-only libraries (Interface)
add_library(hardware_bridge INTERFACE)
target_include_directories(hardware_bridge INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libs/hardware_bridge)

add_library(kernel_bypass INTERFACE)
target_include_directories(kernel_bypass INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libs/kernel_bypass)

add_library(dma_engine INTERFACE)
target_include_directories(dma_engine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libs/dma_engine)

# Testing and Benchmarking
enable_testing()
add_subdirectory(tests)
add_subdirectory(benchmarks)
