//
// Created by Mateusz Mikiciuk on 05/04/2025.
//

#ifndef TRIANGULARSOLITAIRE_BIT_OPERATIONS_H
#define TRIANGULARSOLITAIRE_BIT_OPERATIONS_H

#include <cstdint>

// ------------------------------
// Bit specific
// ------------------------------

inline constexpr uint64_t MinMsb = 1ULL;
inline constexpr uint64_t MaxMsb = MinMsb << 63;

/* function checks if bit is set on given idx */
constexpr bool CheckBitAtIdx(const uint64_t a, const int idx) { return a & (MinMsb << idx); }

/* function clears bits intersecting with b from a */
[[nodiscard]] constexpr uint64_t ClearIntersect(const uint64_t a, const uint64_t b) { return a ^ (a & b); }

/* function counts bits set to one in a */
constexpr int CountOnes (const uint64_t a) { return std::popcount(a); }

/* generalized bit shift */
[[nodiscard]] inline uint64_t GenShift(const uint64_t mask, const int shift)
    { return (shift > 0) ? (mask << shift) : (mask >> -shift); }

/* returns index of lsb of given bitmask */
constexpr int GetLbsIdx(const uint64_t a) { return std::countr_zero(a); }

/* retrieves LsbIdx and resets it */
constexpr int PopLsb(uint64_t& a) { const int ret = GetLbsIdx(a); a &= a - 1; return ret; }

// ------------------------------
// Board specific
// ------------------------------

inline constexpr uint64_t notAB_Files = 0xFCFCFCFCFCFCFCFC;
inline constexpr uint64_t notGH_Files = 0x3F3F3F3F3F3F3F3F;

constexpr uint64_t shiftNorth(const uint64_t a) { return a << 8; }
constexpr uint64_t shiftSouth(const uint64_t a) { return a >> 8; }
constexpr uint64_t shiftEast(const uint64_t a) { return a >> 1; }
constexpr uint64_t shiftWest(const uint64_t a) { return a << 1; }
constexpr uint64_t shiftNorthWest(const uint64_t a) { return a << 7; }
constexpr uint64_t shiftSouthEast(const uint64_t a) { return a >> 7; }

#endif //TRIANGULARSOLITAIRE_BIT_OPERATIONS_H
