//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#ifndef TRIANGULARSOLITAIRE_BOARD_H
#define TRIANGULARSOLITAIRE_BOARD_H

#include "tl/expected.hpp"
#include "board_error.h"
#include <sstream>

enum class peg_position : int
{
    #define DECLARE_PEG_POS(col, col_offset) \
            col##1 = col_offset + 56, col##2 = col_offset + 48, col##3 = col_offset + 40, col##4 = col_offset + 32, \
            col##5 = col_offset + 24, col##6 = col_offset + 16, col##7 = col_offset + 8, col##8 = col_offset
        DECLARE_PEG_POS(a, 7),
        DECLARE_PEG_POS(b, 6),
        DECLARE_PEG_POS(c, 5),
        DECLARE_PEG_POS(d, 4),
        DECLARE_PEG_POS(e, 3),
        DECLARE_PEG_POS(f, 2),
        DECLARE_PEG_POS(g, 1),
        DECLARE_PEG_POS(h, 0),
    #undef DECLARE_PEG_POS
};

struct board_error_info
{
    board_error error_code;
    std::optional<peg_position> peg_pos;

    board_error_info(const board_error& error_code,const std::optional<peg_position>& peg_pos) : error_code(error_code), peg_pos(peg_pos) {}

    [[nodiscard]] std::string message() const
    {
        std::ostringstream os;
        os << error_code;
        if (peg_pos) os << " on peg: " << static_cast<int>(peg_pos.value());
        return os.str();
    }
};

struct board
{
    // ------------------------------
    // Class creation
    // ------------------------------
    explicit board(int size = 5);
    ~board() = default;

    // ------------------------------
    // Fields
    // ------------------------------
    int board_size;
    uint64_t current_state;
    uint64_t board_area_mask;

    // ------------------------------
    // Basic functions
    // ------------------------------
    [[nodiscard]] tl::expected<void, board_error_info> move_peg(const peg_position& from, const peg_position& to) const;
private:
    [[nodiscard]] uint64_t generate_board() const;
};

// ------------------------------
// Helper functions
// ------------------------------
void print_current_board(uint64_t state, int b_size);

#endif //TRIANGULARSOLITAIRE_BOARD_H
