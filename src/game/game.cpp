//
// Created by Mateusz Mikiciuk on 28/04/2025.
//

#include "includes/board.h"
#include <iostream>

std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        if (!token.empty()) {  //
            tokens.push_back(token);
        }
    }
    return tokens;
}


int string_to_pos_idx(const std::string &str)
{
    const int col = str[0] - 97;
    int row = str[1] - 49;
    row = 7 - row;
    return row * 8 + col;
}

int main() {
    board board{5};
    std::string buffer;
    buffer.reserve(10);
    const int moves = board.pegs_left;
    for (int i = 0; i < moves; i++)
    {
        print_current_board(board);
        std::cout << "Make a move\n";
        std::getline(std::cin, buffer);
        auto arr = split(buffer, ' ');
        const int from = string_to_pos_idx(arr[0]);
        const int to = string_to_pos_idx(arr[1]);
        auto res = board.move_peg(from, to);
        if (!res.has_value())
            std::cout << res.error().message();
        buffer.clear();
    }
    return 0;
}