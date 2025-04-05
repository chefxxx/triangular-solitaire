//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#ifndef TRIANGULARSOLITAIRE_BOARD_H
#define TRIANGULARSOLITAIRE_BOARD_H

class board
{
private:
    uint64_t default_state;
    uint64_t board_area_mask;
    int board_size;
    uint64_t generate_board() const;
public:
    explicit board(int size = 5);
    void print_board(uint64_t board_state) const;
    uint64_t get_default_state() const;
    uint64_t get_area_mask() const;
};

#endif //TRIANGULARSOLITAIRE_BOARD_H
