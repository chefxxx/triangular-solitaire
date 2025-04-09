//
// Created by Mateusz Mikiciuk on 05/04/2025.
//

#ifndef TRIANGULARSOLITAIRE_BIT_OPERATIONS_H
#define TRIANGULARSOLITAIRE_BIT_OPERATIONS_H

#include <cstdint>

inline constexpr uint64_t min_msb = 1ULL;
inline constexpr uint64_t max_msb = min_msb << 63;

inline constexpr uint64_t notAFile = 0xfefefefefefefefe;
inline constexpr uint64_t notBFile = 0xfefefefefefefeff;

constexpr bool check_bit_at_index(const uint64_t check, const int idx) { return check & (min_msb << idx); }

constexpr uint64_t a_without_b(const uint64_t a, const uint64_t b) { return a ^ (a & b); }

#endif //TRIANGULARSOLITAIRE_BIT_OPERATIONS_H
