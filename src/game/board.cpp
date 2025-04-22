//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#include <iostream>
#include <sstream>
#include <bitset>
#include <algorithm>
#include <numeric>
#include "board.h"
#include "bit_operations.h"

constexpr int MAX_SIZE = 64;
constexpr int BOARD_SIDE = 8;

board::board(const int size)
    : board_size{size},
      board_area_mask{generate_board()},
      current_state{a_without_b(board_area_mask, max_msb >> (BOARD_SIDE - 1))},
      current_empty{a_without_b(board_area_mask, current_state)},
      pegs_left{init_pegs_left()}
{}

tl::expected<void, board_error_info> board::move_peg(const peg_position &from, const peg_position &to)
{
    if (!check_bit_at_index(board_area_mask, peg_to_idx(from)))
        return tl::unexpected{board_error_info(board_error::out_of_bound, from, to)};
    if (!check_bit_at_index(board_area_mask, peg_to_idx(to)))
        return tl::unexpected{board_error_info(board_error::out_of_bound, from, to)};
    if (!check_bit_at_index(current_state, peg_to_idx(from)))
        return tl::unexpected{board_error_info(board_error::peg_does_not_exist, from, to)};
    // I think that this not necessary
#if 0
    if (check_bit_at_index(current_state, peg_to_idx(to)))
        return tl::unexpected{board_error_info(board_error::position_is_occupied, from, to)};
#endif
    // Find if given jump qualifies as a valid jump
    uint64_t mask = find_all_valid_jumps(from);
    if (!check_bit_at_index(mask, peg_to_idx(to)))
        return tl::unexpected{board_error_info(board_error::invalid_jump, from, to)};

    // Update board variables
    current_empty = a_without_b(board_area_mask, current_state);
    this->pegs_left--;
    return{};
}

// TODO: attack mask?
// TODO: how to know what peg to erase!!!
// ANS: I think it is possible to decide which peg to erase in checking which side was using in jump;
// TODO: finding all possible attack moves??

uint64_t board::find_all_valid_jumps(const peg_position &from) const
{
    const uint64_t from_mask = min_msb << peg_to_idx(from); //TODO: it may be a good idea to store those masks
    // TODO: Check and choose version
    // Mateusz version:
#if 0
     const uint64_t north_mask = a_without_b(shiftNorth(a_without_b(shiftNorth(from_mask), current_empty)),
                                             current_state) & board_area_mask;
     const uint64_t south_mask = a_without_b(shiftSouth(a_without_b(shiftSouth(from_mask), current_empty)),
                                             current_state) & board_area_mask;
#endif
    // Mykhailo version:
    const uint64_t north_mask = shiftNorth(shiftNorth(from_mask) & current_state) & current_empty & board_area_mask;
    const uint64_t south_mask = shiftSouth(shiftSouth(from_mask) & current_state) & current_empty & board_area_mask;
    const uint64_t east_mask = shiftEast(shiftEast(from_mask) & current_state) & current_empty & board_area_mask;
    const uint64_t west_mask = shiftWest(shiftWest(from_mask) & current_state) & current_empty & board_area_mask;
    return north_mask | south_mask | east_mask | west_mask;
}

uint64_t board::generate_board() const
{
    uint64_t mask = min_msb << (MAX_SIZE - BOARD_SIDE);
    for (int i = 0; i < board_size - 1; ++i)
    {
        mask = mask | mask >> 7 | mask >> BOARD_SIDE;
    }
    return mask;
}

int board::init_pegs_left() const
{
    std::vector<int> pl(board_size);
    std::iota(pl.begin(), pl.end(), 1);
    return std::accumulate(pl.begin(), pl.end(), 0) - 1;
}

void print_current_board(const uint64_t &state)
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
    for (auto const &str : tmp)
    {
        std::cout << level <<"| ";
        for (const char &i : str)
            std::cout << i << " ";
        std::cout << "|" << level++ << "\n";
    }
    std::cout << "*--a-b-c-d-e-f-g-h--*\n";
    std::cout << "*-------------------*\n";
}
