# Chapter 2: Getting Started & Build Instructions {#getting_started}

[<< Previous Chapter: Introduction](introduction.html) | [Back to Table of Contents](index.html) | [Next Chapter: Requirements >>](requirements.html)

---

## 🛠️ Environment Setup

The stack is designed for cross-platform compatibility but requires a modern toolchain to support C++26 features.

### 🪟 Windows 11 (MSVC 17.10+)
- **Prerequisites:** Visual Studio 2022 (latest), CMake 3.28+.
- **Build:** 
  ```powershell
  cmake -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_CXX_STANDARD=26
  cmake --build build --config Release
  ```
- **Test:** `ctest -C Release --output-on-failure`

### 🐧 Ubuntu 24.04 (Clang 18+)
- **Prerequisites:** `clang-18`, `libstdc++-14-dev`, `cmake`, `ghdl`, `doxygen`.
- **Build:** 
  ```bash
  chmod +x ./scripts/build.sh
  ./scripts/build.sh
  ```
- **Verify VHDL:** `./scripts/run_vhdl_tests.sh`

### 🍎 MacOS (Sonoma+)
- **Prerequisites:** Homebrew, LLVM 18, Eigen.
- **Run:** 
  ```bash
  cmake -B build -DCMAKE_CXX_COMPILER=$(brew --prefix llvm)/bin/clang++
  ```

### 🐳 Docker (Recommended)
A `Dockerfile` is provided for a reproducible Ubuntu 24.04 environment:
```bash
docker build -t hft-stack .
docker run -it hft-stack /bin/bash
```

---

[<< Previous Chapter: Introduction](introduction.html) | [Back to Table of Contents](index.html) | [Next Chapter: Requirements >>](requirements.html)
