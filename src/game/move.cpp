//
// Created by Mateusz Mikiciuk on 29/04/2025.
//

#include "includes/move.h"
#include <bit_operations.h>
#include "board.h"

Move::Move(const int from, const int to, const jump_dir dir) {
    this->from = IdxToPos(from);
    this->to = IdxToPos(to);
    this->dir = dir;
}

std::vector<Move> BuildAllMoves(const Board &board)
{
    std::vector<Move> moves;
    const uint64_t current = board.current_state;
    const uint64_t empty = board.current_empty;
    const uint64_t area = board.board_area_mask;

    /* prepare masks in all directions */
    const uint64_t north = shiftNorth(shiftNorth(current) & current & area) & empty & area;
    const uint64_t south = shiftSouth(shiftSouth(current) & current & area) & empty & area;
    const uint64_t west = shiftWest(shiftWest(current & notAB_Files) & current & area) & empty & area;
    const uint64_t east = shiftEast(shiftEast(current & notGH_Files) & current & area) & empty & area;
    const uint64_t northWest = shiftNorthWest(shiftNorthWest(current & notAB_Files) & current & area) & empty & area;
    const uint64_t southEast = shiftSouthEast(shiftSouthEast(current & notGH_Files) & current & area) & empty & area;

    /* Fill possible moves list */
    MakeMoves(north, jump_dir::NORTH, moves);
    MakeMoves(south, jump_dir::SOUTH, moves);
    MakeMoves(west, jump_dir::WEST, moves);
    MakeMoves(east, jump_dir::EAST, moves);
    MakeMoves(northWest, jump_dir::NORTH_WEST, moves);
    MakeMoves(southEast, jump_dir::SOUTH_EAST, moves);

    return moves;
}

void MakeMoves(uint64_t attacks, const jump_dir offset, std::vector<Move> &moves)
{
    while (attacks)
    {
        int to_idx = PopLsb(attacks);
        moves.emplace_back(to_idx - dir_to_idx(offset), to_idx, offset);
    }
}