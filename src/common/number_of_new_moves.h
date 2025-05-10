//
// Created by Mykhailo_Shamrai on 10.05.2025.
//

#ifndef NUMBER_OF_NEW_MOVES_H
#define NUMBER_OF_NEW_MOVES_H
#include <board.h>

struct NumberOfNewMoves {
  inline int operator()(const Board &board) {
    auto moves = BuildAllMoves(board);
    return moves.size();
  };
};

#endif // NUMBER_OF_NEW_MOVES_H
