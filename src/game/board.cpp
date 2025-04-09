//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#include <iostream>
#include <sstream>
#include <bitset>
#include <algorithm>
#include "includes/board.h"
#include "includes/bit_operations.h"

constexpr int MAX_SIZE = 64;
constexpr int BOARD_SIDE = 8;

board::board(const int size)
    : board_size{size},
    board_area_mask{generate_board()},
    current_state{a_without_b(board_area_mask, max_msb >> (BOARD_SIDE - 1))}
{}

tl::expected<void, board_error_info> board::move_peg(const peg_position& from, const peg_position& to) const
{
    if (!check_bit_at_index(board_area_mask, static_cast<int>(from)))
        return tl::unexpected{board_error_info(board_error::out_of_bound, from)};
    if (!check_bit_at_index(board_area_mask, static_cast<int>(to)))
        return tl::unexpected{board_error_info(board_error::out_of_bound, to)};
    if (!check_bit_at_index(current_state, static_cast<int>(from)))
        return tl::unexpected{board_error_info(board_error::peg_does_not_exist, from)};
    if (check_bit_at_index(current_state, static_cast<int>(to)))
        return tl::unexpected{board_error_info(board_error::position_is_occupied, to)};
    return{};
}

uint64_t board::generate_board() const
{
    uint64_t mask = (min_msb << 56);
    uint64_t state = mask;
    uint64_t tmp = mask;
    for (int i = 0; i < this->board_size - 1; ++i)
    {
        mask >>= 7;
        tmp = (tmp >> BOARD_SIDE) | mask;
        state = state | tmp;
    }
    return state;
}

void print_current_board(const uint64_t state, const int b_size)
{
    std::cout << "*-------------------*\n";
    std::cout << "*---CURRENT BOARD---*\n";
    std::cout << "*--a-b-c-d-e-f-g-h--*\n";
    const std::bitset<MAX_SIZE> bin_rep(state);
    const auto bin_num = bin_rep.to_string();
    std::vector<std::string> tmp;
    tmp.reserve(BOARD_SIDE);
    for (int i = 0; i < BOARD_SIDE; ++i)
    {
        tmp.push_back(bin_num.substr(i * BOARD_SIDE, BOARD_SIDE));
        std::ranges::reverse(tmp[i]);
    }
    int level = 1;
    for (auto const& str : tmp)
    {
        std::cout << level <<"| ";
        for (const char& i : str)
            std::cout << i << " ";
        std::cout << "|" << level++ << "\n";
    }
    std::cout << "*--a-b-c-d-e-f-g-h--*\n";
    std::cout << "*-------------------*\n";
}