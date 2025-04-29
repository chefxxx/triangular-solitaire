//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#ifndef TRIANGULARSOLITAIRE_BOARD_H
#define TRIANGULARSOLITAIRE_BOARD_H

#include "tl/expected.hpp"
#include "board_error.h"
#include "peg_position.h"
#include "bit_operations.h"
#include <cstdint>

struct board {
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
    [[nodiscard]] tl::expected<void, board_error_info> move_peg(int from, int to);
private:
    [[nodiscard]] uint64_t generate_board() const;
    [[nodiscard]] constexpr uint64_t generate_start_state(const int size) const
    {
        uint64_t state = MinMsb;
        switch (size)
        {
            case 6: case 8:
                state <<= peg_to_idx(peg_position::c5);
                break;
            case 7:
                state <<= peg_to_idx(peg_position::a3);
                break;
            default:
                state <<= peg_to_idx(peg_position::a1);
        }
        return state;
    }
};

// ------------------------------
// Helper functions
// ------------------------------
void print_current_board(const board &board);

#endif //TRIANGULARSOLITAIRE_BOARD_H
