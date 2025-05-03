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

    Board board{8};
    perft(board, false);
    return 0;
}