//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <bitset>
#include "includes/board.h"


#define MAX_SIZE 64
#define BOARD_LENGTH 8


board::board(int size)
{
    this->board_size = size;
    this->default_state = generate_board();
}

uint64_t board::generate_board() const
{
    uint64_t state = 0;
    uint64_t mask = 64;
    uint64_t tmp = 192;
    for (int level = BOARD_LENGTH - 2; level >= BOARD_LENGTH - this->board_size; --level)
    {
        state = state | tmp << (level * BOARD_LENGTH);
        mask /= 2;
        tmp += mask;
    }
    return state;
}

void board::print_board(uint64_t board_state) const
{
    std::cout << "*-----------------*\n";
    std::cout << "*--CURRENT BOARD--*\n";
    std::cout << "*-----------------*\n";
    std::stringstream buffer;
    buffer << std::bitset<64>(board_state);
    auto str = buffer.str();
    int level = 0;
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (i % BOARD_LENGTH == 0)
            std::cout << "| ";
        if (i < BOARD_LENGTH * this->board_size)
        {
            if (i % BOARD_LENGTH > level)
                std::cout << "x ";
            else
                std::cout << str[i] << " ";
        }
        else
            std::cout << "x ";
        if ((i + 1) % BOARD_LENGTH == 0)
        {
            level++;
            std::cout << "|\n";
        }
    }
    std::cout << "*-----------------*\n";
}

uint64_t board::get_default_state() const {
    return default_state;
}
