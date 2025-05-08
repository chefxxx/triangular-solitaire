//
// Created by Mykhailo_Shamrai on 09.05.2025.
//

#include <cstdint>
#include "heuristic.h"

unsigned int DistanceToCenterHeuristic::get_distance(uint64_t peg_pos, uint64_t center, int width)
{
    auto [c1, c2] = std::make_pair(center / width, center % width);
    auto [p1, p2] = std::make_pair(peg_pos / width, peg_pos % width);
    // Manhattan distance
    return std::abs(c1 - p1) + std::abs(c2 - p2);
}

int DistanceToCenterHeuristic::operator()(const Board& b) const
{
    uint64_t cur_state = b.current_state;
    int distance = get_distance(b.)
}

