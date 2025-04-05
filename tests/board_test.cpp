//
// Created by Mateusz Mikiciuk on 31/03/2025.
//
#include <gtest/gtest.h>
#include <bitset>
#include "board.h"

TEST(BoardTest, printBoards)
{
    std::vector<board> boards{
            board(5),
            board(6),
            board(7),
            board(8)
    };

    for (auto const& b: boards)
    {
        print_current_board(b.current_state, b.board_size);
    }
}