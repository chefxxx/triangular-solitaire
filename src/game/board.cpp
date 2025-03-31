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
    uint64_t state;
    int level = 7;
    for (int i = 1; i < this->board_size; i++)
    {
        state = state | 1 << (level * 8);
        level--;
    }
    return state;
}

void board::print_board(uint64_t board_state) const
{
    for (int i = 64; i > 0; --i)
    {
        uint64_t tmp = 1;
        tmp = board_state & (tmp << i);
        tmp = tmp >> i;
        if (tmp == 1)
            std::cout << "1 ";
        else
            std::cout << "0 ";
        if (i % 8 == 1)
            std::cout << "\n";
    }
}

uint64_t board::get_default_state() const {
    return default_state;
}
