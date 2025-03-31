//
// Created by Mateusz Mikiciuk on 31/03/2025.
//
#include <gtest/gtest.h>
#include <bitset>
#include "board.h"

TEST(BoardTest, generateDefaultBoard)
{
    std::vector<board> boards{
            board(5),
            board(6),
            board(7),
            board(8)
    };

    for (int i = 0; i < boards.size(); ++i)
    {
        std::cout << "board " << i << " default_state = " << std::bitset<64>(boards[i].get_default_state()) << "\n";
    }
}