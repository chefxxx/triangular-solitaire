//
// Created by Mateusz Mikiciuk on 31/03/2025.
//
#include <gtest/gtest.h>
#include "board.h"

TEST(BoardTest, printCurrBoards)
{
    const std::vector<board> boards{
            board(5),
            board(6),
            board(7),
            board(8)
    };

    for (auto const& b: boards)
    {
        print_current_board(b.current_state);
    }
}

TEST(BoardTest, pegPositions)
{
    const std::vector<peg_position> peg_positions{peg_position::a1, peg_position::a2, peg_position::a3, peg_position::a4,
                                            peg_position::a5, peg_position::a6, peg_position::a7, peg_position::a8};
    for (int i = 0; i < peg_positions.size(); ++i) {
        ASSERT_EQ(static_cast<int>(peg_positions[i]), 8 * (8 - i - 1));
    }
}

TEST(BoardTest, pegOutOfBounds)
{
    board board{5};
    const auto result1 = board.move_peg(peg_position::b1, peg_position::b2);
    ASSERT_EQ(result1.has_value(), false);
    ASSERT_EQ(result1.error().error_code, board_error::out_of_bound);
}

TEST(BoardTest, pegDoesNotExist)
{
    board board{5};
    auto result1 = board.move_peg(peg_position::a1, peg_position::a4);
    ASSERT_EQ(result1.has_value(), false);
    ASSERT_EQ(result1.error().error_code, board_error::peg_does_not_exist);
}

TEST(BoardTest, pegPosIsOccupied)
{
    board board{5};
    auto result1 = board.move_peg(peg_position::a2, peg_position::a4);
    ASSERT_EQ(result1.has_value(), false);
    ASSERT_EQ(result1.error().error_code, board_error::position_is_occupied);
}

TEST(BoardTest, pegCount)
{
    const board board{5};
    ASSERT_EQ(14, board.pegs_left);
}

TEST(BoardTest, MoveTest1)
{
    board board{5};
    auto result = board.move_peg(peg_position::a3, peg_position::a1);
}


// TODO: change in tests, something here is wrong!!!
TEST(BoardTest, MoveTest2)
{
    board board{8};
    board.current_state = 36205685112832000; // 0 0 0 0 0 0 0 0
    //                                          1 0 0 0 0 0 0 0
    //                                          1 0 1 0 0 0 0 0
    //                                          1 2 1 0 0 0 0 0
    //                                          1 1 1 1 1 0 0 0
    board.current_empty = board.current_state ^ board.board_area_mask;
    auto result = board.move_peg(peg_position::b4, peg_position::d4);
}

TEST(BoardTest, MoveTest3)
{
    board board{8};
    board.current_state = 36205685112832000; // 0 0 0 0 0 0 0 0
    //                                          1 0 0 0 0 0 0 0
    //                                          1 0 1 0 0 0 0 0
    //                                          2 1 1 0 0 0 0 0
    //                                          1 1 1 1 1 0 0 0
    board.current_empty = board.current_state ^ board.board_area_mask;
    auto result = board.move_peg(peg_position::a4, peg_position::g4);
}