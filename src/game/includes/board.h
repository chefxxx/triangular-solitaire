//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#ifndef TRIANGULARSOLITAIRE_BOARD_H
#define TRIANGULARSOLITAIRE_BOARD_H

class board
{
private:
    int board_size;
    uint64_t current_state;
    uint64_t board_area_mask;
    [[nodiscard("Generates starting board and returns it's bitmask.")]] uint64_t generate_board() const;
public:
    explicit board(int size = 5);
    void print_current_board() const;
};

#endif //TRIANGULARSOLITAIRE_BOARD_H
