//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#include <iostream>
#include <sstream>
#include <bitset>
#include <algorithm>
#include "board.h"
#include "bit_operations.h"

constexpr int MAX_SIZE = 64;
constexpr int BOARD_SIDE = 8;

Board::Board(const int size)
    : board_size{size},
      board_area_mask{generate_board()},
      current_state{ClearIntersect(board_area_mask, MaxMsb >> (BOARD_SIDE - 1))},
      current_empty{ClearIntersect(board_area_mask, current_state)},
      pegs_left{CountOnes(current_state)}
{}

tl::expected<void, board_error_info> Board::move_peg(const peg_position &from, const peg_position &to)
{
    if (!CheckBitAtIdx(board_area_mask, peg_to_idx(from)))
        return tl::unexpected{board_error_info(board_error::out_of_bound, from, to)};
    if (!CheckBitAtIdx(board_area_mask, peg_to_idx(to)))
        return tl::unexpected{board_error_info(board_error::out_of_bound, from, to)};
    if (!CheckBitAtIdx(current_state, peg_to_idx(from)))
        return tl::unexpected{board_error_info(board_error::peg_does_not_exist, from, to)};
    if (CheckBitAtIdx(current_state, peg_to_idx(to)))
        return tl::unexpected{board_error_info(board_error::invalid_jump, from, to)};

    const jump_dir dir = calculate_jump_dir(from, to);
    if (dir == jump_dir::INVALID)
        return tl::unexpected{board_error_info(board_error::invalid_jump, from, to)};

    const int erase_idx = peg_to_idx(from) + dir_to_idx(dir) / 2;
    if (!CheckBitAtIdx(current_state, erase_idx))
        return tl::unexpected{board_error_info(board_error::invalid_jump, from, to)};

    const uint64_t erase = MinMsb << erase_idx | MinMsb << peg_to_idx(from);
    current_state = ClearIntersect(current_state,erase);
    current_state |= MinMsb << peg_to_idx(to);

    current_empty = ClearIntersect(board_area_mask, current_state);
    this->pegs_left--;
    return{};
}

tl::expected<void, board_error_info> Board::move_peg(const int from, const int to)
{
    const peg_position p_from{from};
    const peg_position p_to{to};
    return move_peg(p_from, p_to);
}

uint64_t Board::generate_board() const
{
    uint64_t mask = MinMsb << (MAX_SIZE - BOARD_SIDE);
    for (int i = 0; i < board_size - 1; ++i)
    {
        mask = mask | mask >> 7 | mask >> BOARD_SIDE;
    }
    return mask;
}

void print_current_board(const Board &board)
{
    std::cout << "*---CURRENT BOARD---*\n";
    std::cout << "*--a-b-c-d-e-f-g-h--*\n";
    const std::bitset<MAX_SIZE> bin_rep(board.current_state);
    const auto bin_num = bin_rep.to_string();
    std::vector<std::string> tmp;
    tmp.reserve(BOARD_SIDE);
    for (int i = 0; i < BOARD_SIDE; ++i)
    {
        tmp.push_back(bin_num.substr(i * BOARD_SIDE, BOARD_SIDE));
        std::ranges::reverse(tmp[i]);
    }
    int level = 1;
    for (int j = 0; j < board.board_size; ++j)
    {
        const auto& str = tmp[j];
        std::cout << level <<"| ";
        for (int i = 0; i < BOARD_SIDE; ++i) {
            if (i < level)
                std::cout << str[i] << " ";
            else
                std::cout << "  ";
        }
        std::cout << "|" << level++ << "\n";
    }
    std::cout << "*--a-b-c-d-e-f-g-h--*\n";
    std::cout << "*-------------------*\n";
}
