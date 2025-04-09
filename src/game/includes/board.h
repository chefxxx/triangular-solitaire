//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#ifndef TRIANGULARSOLITAIRE_BOARD_H
#define TRIANGULARSOLITAIRE_BOARD_H

#include "tl/expected.hpp"
#include "board_error.h"
#include "peg_position.h"

struct board
{
    // ------------------------------
    // Class creation
    // ------------------------------
    explicit board(int size);
    ~board() = default;

    // ------------------------------
    // Fields
    // ------------------------------
    const int board_size;
    const uint64_t board_area_mask;
    uint64_t current_state;
    uint64_t current_empty;
    int pegs_left;

    // ------------------------------
    // Basic functions
    // ------------------------------
    [[nodiscard]] tl::expected<void, board_error_info> move_peg(const peg_position &from, const peg_position &to);
    [[nodiscard]] uint64_t find_all_valid_jumps(const peg_position &from) const;
private:
    [[nodiscard]] uint64_t generate_board() const;
    [[nodiscard]] int init_pegs_left() const;
};

// ------------------------------
// Helper functions
// ------------------------------
void print_current_board(const uint64_t &state);

#endif //TRIANGULARSOLITAIRE_BOARD_H
