//
// Created by Mateusz Mikiciuk on 05/04/2025.
//

#ifndef TRIANGULARSOLITAIRE_BIT_OPERATIONS_H
#define TRIANGULARSOLITAIRE_BIT_OPERATIONS_H

#include <cstdint>

// ------------------------------
// Bit specific
// ------------------------------

inline constexpr uint64_t min_msb = 1ULL;
inline constexpr uint64_t max_msb = min_msb << 63;

constexpr bool check_bit_at_index(const uint64_t &a, const int &idx) { return a & (min_msb << idx); }
constexpr uint64_t a_without_b(const uint64_t &a, const uint64_t &b) { return a ^ (a & b); }

// ------------------------------
// Board specific
// ------------------------------

inline constexpr uint64_t notAB_Files = 0x3F3F3F3F3F3F3F3F;
inline constexpr uint64_t notGH_Files = 0xFCFCFCFCFCFCFCFC;

constexpr uint64_t shiftNorth(const uint64_t &a) {return a << 8;}
constexpr uint64_t shiftSouth(const uint64_t &a) {return a >> 8;}

#endif //TRIANGULARSOLITAIRE_BIT_OPERATIONS_H
