//
// Created by Mykhailo_Shamrai on 09.05.2025.
//

#include <bit_operations.h>
#include <cmath>
#include <cstdint>
#include <utility>

#include "distance_to_center.h"
#include "board.h"

int DistanceToCenterHeuristic::get_distance(const uint64_t peg_pos, const uint64_t center,
                                            const int width) {
  std::tuple<int, int> c = std::make_pair(center / width, center % width);
  std::tuple<int, int> p = std::make_pair(peg_pos / width, peg_pos % width);
  auto [c1, c2] = c;
  auto [p1, p2] = p;
  // Manhattan distance
  return std::abs(c1 - p1) + std::abs(c2 - p2);
}

int DistanceToCenterHeuristic::operator()(const Board &b) const {
  int sum = 0;
  const int size = 2 * b.board_size;
  uint64_t cur_state = b.current_state;
  const int center_idx = peg_to_idx(b.center_of_board());
  while (cur_state) {
    const int index = PopLsb(cur_state);
    sum += size - DistanceToCenterHeuristic::get_distance(index, center_idx,
                                                          MAX_BOARD_SIDE);
  }
  return sum;
}
