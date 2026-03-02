#!/bin/bash
set -e

# Build
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang++-18 -DCMAKE_C_COMPILER=clang-18
cmake --build . --config Release

# Test
ctest --output-on-failure

# Benchmark
./benchmarks/signal_benchmarks

# Documentation
cd ..
doxygen docs/Doxyfile
