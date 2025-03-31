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
    uint64_t tmp = 1;
    int level = BYTE_SIZE;
    for (int i = 1; i < this->board_size; i++)
    {
        state = state | tmp << (level * 8);
        level--;
    }
    return state;
}

void board::print_board(uint64_t board_state) const
{
    for (int i = MAX_SIZE; i > 0; --i)
    {
        if (i > 64 - this->board_size * BYTE_SIZE)
        {
            uint64_t tmp = 1;
            tmp = board_state & (tmp << i);
            tmp = tmp >> i;
            if (tmp == 1)
                std::cout << "1 ";
            else
                std::cout << "0 ";
        }
        else
        {
            std::cout << "x ";
        }
        if (i % BYTE_SIZE == 1)
            std::cout << "\n";
    }
}

uint64_t board::get_default_state() const {
    return default_state;
}
