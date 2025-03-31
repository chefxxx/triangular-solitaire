//
// Created by Mateusz Mikiciuk on 25/03/2025.
//

#include "board.h"

int main()
{
    board B{7};
    B.print_board(B.get_default_state());
    return 0;
}
