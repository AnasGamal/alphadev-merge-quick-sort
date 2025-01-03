# alphadev-merge-quick-sort

## Introduction

This project improves Merge Sort and Quick Sort performance by using optimized sorting networks, discovered by AlphaDev, as base cases for small subarrays.

## Requirements

- Linux system or WSL Ubuntu
- Bazel version 7.4.1
- Clang compiler

## Build Instructions

To build the project, run the following command:

```bash
CC=clang bazel build -c opt --cxxopt='-std=c++17' :benchmark
```

## Running the Benchmark

To execute the benchmark and generate CSV output:

```bash
./bazel-bin/benchmark --benchmark_format=console --benchmark_out_format=csv --benchmark_out=results/benchmark_$(date +%Y%m%d_%H%M%S).csv
```

This command generates CSV files with timestamps in their names, facilitating easy data analysis.

## Results

- **Location**: `results` directory
- **Format**: CSV files with timestamped names
- **Content**: Benchmark results for analysis