//
// Created by Mateusz Mikiciuk on 05/04/2025.
//

#ifndef TRIANGULARSOLITAIRE_BIT_OPERATIONS_H
#define TRIANGULARSOLITAIRE_BIT_OPERATIONS_H

#include <cstdint>

inline constexpr uint64_t min_msb = 1ULL;
inline constexpr uint64_t max_msb = min_msb << 63;

constexpr bool check_bit_at_index(const uint64_t checked, const int index) { return checked & (min_msb << index); }

#endif //TRIANGULARSOLITAIRE_BIT_OPERATIONS_H
