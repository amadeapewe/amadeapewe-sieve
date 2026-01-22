/**
 * amadeapewe Sieve: Memory-Compressed Wheel Factorization for ARM64
 * ----------------------------------------------------------------
 * Author: Pavlo Kravchuk (amadeapewe)
 * Email: amadeapewe@gmail.com
 * LinkedIn: https://www.linkedin.com/in/amadeapewe/
 * Date: January 22, 2026
 * * Description: 
 * High-performance prime sieve using an 8-pipe wheel (H=30).
 * Optimized for Apple M1/M2/M3/M4 cache lines.
 * Memory compression factor: 3.75x.
 */

#ifndef AMADEAPEWE_SIEVE_HPP
#define AMADEAPEWE_SIEVE_HPP

#include <vector>
#include <cmath>
#include <stdint.h>

namespace amadeapewe_sieve {

    // Мапінг залишків gcd(n, 30) = 1 на біти в байті
    // 1, 7, 11, 13, 17, 19, 23, 29
    const uint8_t BIT_MAP[30] = {
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 3, 0, 0, 0, 4, 0, 5, 0, 0, 0, 6, 0, 0, 0, 0, 0, 7
    };

    const uint8_t RESIDUES[8] = {1, 7, 11, 13, 17, 19, 23, 29};

    /**
     * Головна функція виконання решета
     * @param limit Верхня межа обчислень
     * @return Кількість знайдених простих чисел
     */
    uint64_t execute(uint64_t limit) {
        if (limit < 2) return 0;
        
        // Початкова кількість для 2, 3, 5
        uint64_t count = (limit >= 2) + (limit >= 3) + (limit >= 5);
        
        uint64_t size = (limit / 30) + 1;
        std::vector<uint8_t> sieve(size, 0xFF); // Всі біти встановлені (можливо прості)

        uint64_t sqrt_limit = static_cast<uint64_t>(std::sqrt(limit));

        for (uint64_t i = 0; i <= sqrt_limit / 30; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (sieve[i] & (1 << j)) {
                    uint64_t p = i * 30 + RESIDUES[j];
                    if (p < 7) continue; // Пропускаємо 1
                    
                    // Викреслюємо кратні p
                    for (uint64_t m = p * p; m <= limit; m += p) {
                        uint8_t bit = BIT_MAP[m % 30];
                        if (bit || (m % 30 == 1)) {
                            sieve[m / 30] &= ~(1 << bit);
                        }
                    }
                }
            }
        }

        // Підрахунок результатів
        for (uint64_t i = 0; i < size; ++i) {
            uint64_t base = i * 30;
            for (int j = 0; j < 8; ++j) {
                if (sieve[i] & (1 << j)) {
                    if (base + RESIDUES[j] <= limit && base + RESIDUES[j] > 1) {
                        count++;
                    }
                }
            }
        }

        return count;
    }
}

#endif // AMADEAPEWE_SIEVE_HPP
Add amadeapewe memory-compressed wheel sieve (H=30)
