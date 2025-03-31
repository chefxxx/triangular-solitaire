//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#include "includes/board.h"


board::board(int size)
{
    this->board_size = size;
    this->default_state = generate_board();
}

uint64_t board::generate_board() const
{
    uint64_t state = 0;
    uint64_t tmp = 128;
    int level = BOARD_LENGTH - 2;
    for (; level >= BOARD_LENGTH - this->board_size ; --level)
    {
        state = state | tmp << (level * BOARD_LENGTH);
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
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (i % BOARD_LENGTH == 0)
            std::cout << "| ";
        if (i < BOARD_LENGTH * this->board_size)
            std::cout << str[i] << " ";
        else
            std::cout << "x ";
        if ((i + 1) % BOARD_LENGTH == 0)
            std::cout << "|\n";
    }
    std::cout << "*-----------------*\n";
}

uint64_t board::get_default_state() const {
    return default_state;
}
