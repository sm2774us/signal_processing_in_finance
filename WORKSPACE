workspace(name = "signal_processing_in_finance")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Eigen (Header-only Linear Algebra)
http_archive(
    name = "eigen",
    build_file_content = """
cc_library(
    name = "eigen",
    hdrs = glob(["Eigen/**", "unsupported/Eigen/**"]),
    includes = ["."],
    visibility = ["//visibility:public"],
)
    """,
    strip_prefix = "eigen-3.4.0",
    urls = ["https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz"],
)

# Google Test
http_archive(
    name = "com_google_googletest",
    strip_prefix = "googletest-1.14.0",
    urls = ["https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz"],
)

# Google Benchmark
http_archive(
    name = "com_google_benchmark",
    strip_prefix = "benchmark-1.8.3",
    urls = ["https://github.com/google/benchmark/archive/refs/tags/v1.8.3.tar.gz"],
)

# OSQP (Convex Optimization)
# For simplicity in this demo, we'll assume a local or system-provided OSQP 
# or use a simplified implementation if direct Bazel integration is too complex.
# However, a production repo would use a proper build rule.
