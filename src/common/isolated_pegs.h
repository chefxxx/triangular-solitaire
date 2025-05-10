//
// Created by Mykhailo_Shamrai on 10.05.2025.
//

#ifndef ISOLATED_PEGS_H
#define ISOLATED_PEGS_H
#include <board.h>

struct IsolatedPegs {
  int operator()(const Board &b) const;
  static uint64_t find_neighbours(int index, const Board &board);
};

#endif // ISOLATED_PEGS_H
