FROM ubuntu:24.04

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    clang-18 \
    libeigen3-dev \
    python3-pip \
    doxygen \
    && rm -rf /var/lib/apt/lists/*

# Set Clang 18 as the default compiler
ENV CC=clang-18
ENV CXX=clang++-18

WORKDIR /app
COPY . .

# Build the project
RUN mkdir build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    cmake --build .

# Run tests
CMD ["./build/tests/signal_tests"]
