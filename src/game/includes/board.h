//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#ifndef TRIANGULARSOLITAIRE_BOARD_H
#define TRIANGULARSOLITAIRE_BOARD_H

struct board
{
    // ------------------------------
    // Class creation
    // ------------------------------
    explicit board(int size = 5);
    ~board() = default;

    // ------------------------------
    // Fields
    // ------------------------------
    int board_size;
    uint64_t current_state;
    uint64_t board_area_mask;

    // ------------------------------
    // Basic functions
    // ------------------------------
    void print_current_board() const;
    //void move_peg()
private:
    [[nodiscard("Generates starting board and returns it's bitmask.")]] uint64_t generate_board() const;
};

#endif //TRIANGULARSOLITAIRE_BOARD_H
