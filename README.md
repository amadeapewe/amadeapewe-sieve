# amadeapewe Sieve: ARM64-Optimized Prime Search

### What is this?
A high-performance C++ prime number sieve specifically optimized for the **ARM64 architecture (Apple Silicon)**. This project re-thinks memory layout through a geometric lens to maximize cache locality and reduce memory bandwidth pressure.

### The Story: From Paper to Code
I am a **graphic designer and artist**, not a software engineer. My journey began with a sheet of paper, where I drew a grid to visualize the distribution of prime numbers. By mapping "empty zones" where primes cannot exist, I discovered a geometric pattern that allows for extreme memory efficiency.

With the help of **AI (Gemini & ChatGPT)**, I translated this pencil-and-paper logic into optimized C++ code.

### Benchmarks (Apple M1)
The algorithm is designed to be "cache-friendly." It shows peak performance on ranges that fit within the CPU cache hierarchy.

| Range (N) | Standard SOTA (ms) | amadeapewe Sieve (ms) | Speedup | Memory Savings |
| :--- | :--- | :--- | :--- | :--- |
| **10M** | 4.2 ms | **1.3 ms** | **3.13x** | **3.75x** |
| **100M** | 19.8 ms | **17.9 ms** | **1.11x** | **3.75x** |
| **1B** | 114.3 ms | **108.2 ms** | **1.06x** | **3.75x** |

### Performance Visualization
![Benchmark Chart](https://github.com/user-attachments/assets/cb039405-88ac-4104-aa5b-9625a2e67ba4)
### How it works
This is not "new math," but a **new layout**. 
* **Wheel Factorization ($H=30$):** We skip multiples of 2, 3, and 5 automatically.
* **Aggressive Compression:** We pack 30 potential candidates into just 8 bits (1 byte).
* **Hardware First:** The code is structured to minimize "cache misses," which is why it achieves up to **3.13x speedup** on Apple Silicon compared to standard bitset implementations.

### 🛠 How to reproduce
```bash
# Compile with optimization flags
clang++ -O3 sieve_arm64.cpp -o sieve

# Run the benchmark
./sieve
