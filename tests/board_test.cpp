//
// Created by Mateusz Mikiciuk on 31/03/2025.
//
#include <gtest/gtest.h>
#include <bitset>
#include "board.h"

TEST(BoardTest, generateDefaultBoard)
{
    board B{5};
    std::cout << "default_state = " << std::bitset<64>(B.get_default_state()) << "\n";
}