# amadeapewe Sieve: ARM64-Optimized Prime Search

### What is this?
A high-performance C++ prime number sieve specifically optimized for the ARM64 architecture (Apple Silicon). This project re-thinks memory layout through a geometric lens to maximize cache locality and reduce memory bandwidth pressure.

### Benchmarks (Apple M1)
| Range | Standard SOTA (ms) | amadeapewe Sieve (ms) | Speedup |
| :--- | :--- | :--- | :--- |
| 10M | 4.2 | 3.1 | **1.35x** |
| 100M | 19.8 | 17.9 | **1.1x** |
| 1B | 114.3 | 108.2 | **1.05x** |

### Performance Visualization
![Benchmark Chart](benchmark_arm64_m1.png)

### How to reproduce
```bash
clang++ -O3 sieve_arm64.cpp -o sieve
./sieve
