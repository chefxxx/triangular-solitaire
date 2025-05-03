//
// Created by Mateusz Mikiciuk on 29/04/2025.
//

#include <gtest/gtest.h>
#include "board.h"
#include "move.h"
#include "bit_operations.h"

TEST(Move, MoveSimple) {
    const Board board{5};
    const auto moves = BuildAllMoves(board);
    for (auto move: moves) {
        std::cout << move << std::endl;
    }
}

TEST(Move, MoveNotSimple) {
    Board board{5};
    board.SetState(7709852172288); //            a b c d e
    //                                        1  0
    //                                        2  0 0
    //                                        3  1 1 1
    //                                        4  1 2 0 0
    //                                        5  1 1 1 0 1
    const auto moves = BuildAllMoves(board);
    for (auto move: moves) {
        std::cout << move << std::endl;
    }
}

TEST(Move, MoveNotNotSimple) {
    Board board{8};
    board.SetState(72626093192410815);       //  a b c d e f g h
    //                                       1   1
    //                                       2   0 1
    //                                       3   1 0 1
    //                                       4   0 0 1 1
    //                                       5   0 1 2 0 0
    //                                       6   0 0 0 1 0 1
    //                                       7   0 1 1 0 1 1 1
    //                                       8   1 1 1 1 1 1 0 1
    const auto moves = BuildAllMoves(board);
    for (auto move: moves) {
        std::cout << move << std::endl;
    }
}

TEST(Move, LsbIdxTest) {
    uint64_t test1 = 12;
    const int idx1 = PopLsb(test1);
    EXPECT_EQ(idx1, 2);
    const int idx2 = PopLsb(test1);
    EXPECT_EQ(idx2, 3);
}

TEST(Move, TestAllTreeOfMoves) {
    Board board{5};
    board.SetState(7709852172288); //            a b c d e
    //                                        1  0
    //                                        2  0 0
    //                                        3  1 1 1
    //                                        4  1 2 0 0
    //                                        5  1 1 1 0 1
    perft(board, false);
}