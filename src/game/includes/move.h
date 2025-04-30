//
// Created by Mateusz Mikiciuk on 29/04/2025.
//

#ifndef MOVE_H
#define MOVE_H

#include <board.h>

#include "peg_position.h"
#include <vector>

struct Move
{
    peg_position from;
    peg_position to;

    Move(int from, int to);
    ~Move() = default;

};

inline std::ostream& operator<<(std::ostream& os, const Move& move) {
    os << "Move from:" << static_cast<int>(move.from) << " to:" << static_cast<int>(move.to);
    return os;
};

std::vector<Move> BuildAllMoves(const Board &board);
void MakeMoves(uint64_t attacks, int offset, std::vector<Move> &moves);


#endif //MOVE_H
