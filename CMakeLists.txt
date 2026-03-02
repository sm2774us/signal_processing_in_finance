cmake_minimum_required(VERSION 3.25)
project(SignalProcessingInFinance VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define project-wide warning and optimization flags
add_library(project_options INTERFACE)
if(MSVC)
    target_compile_options(project_options INTERFACE /W4 /WX /Ot /arch:AVX2)
else()
    target_compile_options(project_options INTERFACE -Wall -Wextra -Werror -O3 -march=native)
endif()

# Dependencies
include(FetchContent)

# Eigen: Disable all internal building/testing
set(EIGEN_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "" FORCE)
set(EIGEN_BUILD_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
)
FetchContent_GetProperties(eigen)
if(NOT eigen_POPULATED)
  FetchContent_Populate(eigen)
  add_subdirectory(${eigen_SOURCE_DIR} ${eigen_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Google Benchmark
FetchContent_Declare(
  googlebenchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.tar.gz
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_GetProperties(googlebenchmark)
if(NOT googlebenchmark_POPULATED)
  FetchContent_Populate(googlebenchmark)
  add_subdirectory(${googlebenchmark_SOURCE_DIR} ${googlebenchmark_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Subdirectories
add_subdirectory(libs/tick_consumer)
add_subdirectory(libs/state_estimator)
add_subdirectory(libs/optimizer)

# Header-only libraries (Interface)
add_library(hardware_bridge INTERFACE)
target_include_directories(hardware_bridge INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libs/hardware_bridge)
target_link_libraries(hardware_bridge INTERFACE project_options)

add_library(kernel_bypass INTERFACE)
target_include_directories(kernel_bypass INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libs/kernel_bypass)
target_link_libraries(kernel_bypass INTERFACE project_options)

add_library(dma_engine INTERFACE)
target_include_directories(dma_engine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libs/dma_engine)
target_link_libraries(dma_engine INTERFACE project_options)

# Testing and Benchmarking
enable_testing()
add_subdirectory(tests)
add_subdirectory(benchmarks)
