//
// Created by Mykhailo_Shamrai on 10.05.2025.
//

#ifndef NUMBER_OF_FREE_POSITIONS_H
#define NUMBER_OF_FREE_POSITIONS_H

#include <board.h>

struct NumberOfFreePositions {
    int operator()(const Board &board) const {
    const int size = board.board_size;
    return (size * size - (size * size - size) / 2) - board.pegs_left;
  }
};

#endif // NUMBER_OF_FREE_POSITIONS_H
