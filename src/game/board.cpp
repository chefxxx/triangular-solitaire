//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#include <iostream>
#include <sstream>
#include <bitset>
#include "includes/board.h"
#include "includes/bit_operations.h"

constexpr int MAX_SIZE = 64;
constexpr int BOARD_LENGTH = 8;

board::board(int size)
    : board_size{size},
    current_state{generate_board()},
    board_area_mask{current_state | MaxMsb}
{}

uint64_t board::generate_board() const
{
    uint64_t state = 0;
    uint64_t mask = MinMsb << 6;
    uint64_t tmp = mask | MinMsb << 7;
    for (int level = BOARD_LENGTH - 2; level >= BOARD_LENGTH - this->board_size; --level)
    {
        state = state | tmp << (level * BOARD_LENGTH);
        mask >>= 1;
        tmp |= mask;
    }
    return state;
}

void board::move_peg(PegPositions peg_start, PegPositions peg_dest)
{
    // not implemented

}

void print_current_board(uint64_t state, int b_size)
{
    std::cout << "*---------------------*\n";
    std::cout << "*----CURRENT BOARD----*\n";
    std::cout << "*---a-b-c-d-e-f-g-h---*\n";
    std::stringstream buffer;
    buffer << std::bitset<MAX_SIZE>(state);
    auto str = buffer.str();
    int level = 0;
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (i % BOARD_LENGTH == 0)
            std::cout << level + 1 << " | ";
        if (i < BOARD_LENGTH * b_size)
        {
            if (i % BOARD_LENGTH > level)
                std::cout << "  ";
            else
                std::cout << str[i] << " ";
        }
        else
            std::cout << "  ";
        if ((i + 1) % BOARD_LENGTH == 0)
        {
            std::cout << "| " << level + 1 << "\n";
            level++;
        }
    }
    std::cout << "*---a-b-c-d-e-f-g-h---*\n";
    std::cout << "*---------------------*\n";
}