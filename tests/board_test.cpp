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

    TEST(BoardTest, pegPosIsOccupiedNorth)
    {
        board board{5};
        auto result1 = board.move_peg(peg_position::a2, peg_position::a4);
        ASSERT_EQ(result1.has_value(), false);
        ASSERT_EQ(result1.error().error_code, board_error::invalid_jump);
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
        ASSERT_EQ(result.has_value(), true);
    }

    // ------------------------------
    // Move to east
    // ------------------------------

    TEST(BoardTest, MoveTest_LegalMoveEast_expectedHasValue)
    {
        board board{5};
        board.current_state = 287003119714304; //    a b c d e
        //                                        1  0 0 0 0 0
        //                                        2  1 0 0 0 0
        //                                        3  1 0 1 0 0
        //                                        4  1 2 1 0 0
        //                                        5  1 1 1 1 1
        board.current_empty = board.current_state ^ board.board_area_mask;
        auto result = board.move_peg(peg_position::b4, peg_position::d4);
        ASSERT_EQ(result.has_value(), true);
    }

    TEST(BoardTest, MoveTest_IlegalMoveEast_expectedHasntValueErrorCodeInvalidJump)
    {
        board board{5};
        board.current_state = 287003119714304  ; //  a b c d e
        //                                       1   0 0 0 0 0
        //                                       2   1 0 0 0 0
        //                                       3   1 0 1 0 0
        //                                       4   2 1 1 0 0
        //                                       5   1 1 1 1 1
        board.current_empty = board.current_state ^ board.board_area_mask;
        auto result = board.move_peg(peg_position::a4, peg_position::c4);
        ASSERT_EQ(result.has_value(), false);
        ASSERT_EQ(result.error().error_code, board_error::invalid_jump);
    }

    TEST(BoardTest, MoveTest_IlegalMoveEast_expectedHasntValueErrorCodeInvalidJump2)
    {
        board board{5};
        board.current_state = 287003102937088  ; //  a b c d e
        //                                       1   0 0 0 0 0
        //                                       2   1 0 0 0 0
        //                                       3   1 0 1 0 0
        //                                       4   1 1 1 0 0
        //                                       5   0 1 1 2 1
        board.current_empty = board.current_state ^ board.board_area_mask;
        auto result = board.move_peg(peg_position::d5, peg_position::a5);
        ASSERT_EQ(result.has_value(), false);
        ASSERT_EQ(result.error().error_code, board_error::invalid_jump);
    }

    TEST(BoardTest, MoveTest_IlegalMoveEastBiggerBoard_expectedHasntValueErrorCodeInvalidJump2)
    {
        board board{8};
        board.current_state = 72344597144571567; //  a b c d e f g h
        //                                       1   1 0 0 0 0 0 0 0
        //                                       2   1 0 0 0 0 0 0 0
        //                                       3   1 0 1 0 0 0 0 0
        //                                       4   1 1 1 0 0 0 0 0
        //                                       5   0 1 1 1 1 0 0 0
        //                                       6   0 0 0 1 1 1 0 0
        //                                       7   1 0 0 0 1 1 1 0
        //                                       8   1 0 1 0 1 1 1 2
        board.current_empty = board.current_state ^ board.board_area_mask;
        auto result = board.move_peg(peg_position::h8, peg_position::a8);
        ASSERT_EQ(result.has_value(), false);
        ASSERT_EQ(result.error().error_code, board_error::invalid_jump);
    }

    TEST(BoardTest, MoveTest_LegalMoveEastBiggerBoard_expectedHasValue)
    {
        board board{8};
        board.current_state = 5510445691027; //      a b c d e f g h
        //                                       1   0 0 0 0 0 0 0 0
        //                                       2   0 0 0 0 0 0 0 0
        //                                       3   1 0 1 0 0 0 0 0
        //                                       4   1 1 0 0 0 0 0 0
        //                                       5   0 0 0 0 0 0 0 0
        //                                       6   0 0 0 1 0 1 0 0
        //                                       7   0 0 0 0 1 1 1 0
        //                                       8   2 1 0 0 1 0 0 1
        board.current_empty = board.current_state ^ board.board_area_mask;
        auto result = board.move_peg(peg_position::a8, peg_position::c8);
        ASSERT_EQ(result.has_value(), true);
    }

    // ------------------------------
    // Move to west
    // ------------------------------
    TEST(BoardTest, MoveTest_LegalMoveWest_expectedHasValue)
    {
        board board{5};
        board.current_state = 286998824747008; //    a b c d e
        //                                        1  0 0 0 0 0
        //                                        2  1 0 0 0 0
        //                                        3  1 0 1 0 0
        //                                        4  0 1 2 0 0
        //                                        5  1 1 1 1 1
        board.current_empty = board.current_state ^ board.board_area_mask;
        auto result = board.move_peg(peg_position::c4, peg_position::a4);
        ASSERT_EQ(result.has_value(), true);
    }

    TEST(BoardTest, MoveTest_LegalMoveWest_expectedHasValue2)
    {
        board board{5};
        board.current_state = 72909728887341056; //  a b c d e
        //                                        1  1 0 0 0 0
        //                                        2  1 1 0 0 0
        //                                        3  1 1 1 0 0
        //                                        4  1 1 0 0 0
        //                                        5  1 1 0 1 2
        board.current_empty = board.current_state ^ board.board_area_mask;
        auto result = board.move_peg(peg_position::e5, peg_position::c5);
        ASSERT_EQ(result.has_value(), true);
    }

    TEST(BoardTest, MoveTest_LegalMoveWest_expectedHasValue3)
    {
        board board{5};
        board.current_state = 569598965448704; //    a b c d e
        //                                        1  0 0 0 0 0
        //                                        2  0 1 0 0 0
        //                                        3  0 1 1 0 0
        //                                        4  0 0 1 2 0
        //                                        5  0 0 0 1 1
        board.current_empty = board.current_state ^ board.board_area_mask;
        auto result = board.move_peg(peg_position::d4, peg_position::b4);
        ASSERT_EQ(result.has_value(), true);
    }

    TEST(BoardTest, MoveTest_IlegalMoveWest_expectedHasntValueErrorCodeInvalidJump)
    {
        board board{5};
        board.current_state = 72909728887341056; //  a b c d e
        //                                        1  1 0 0 0 0
        //                                        2  1 1 0 0 0
        //                                        3  1 1 1 0 0
        //                                        4  1 1 0 0 0
        //                                        5  1 1 0 2 1
        board.current_empty = board.current_state ^ board.board_area_mask;
        auto result = board.move_peg(peg_position::d5, peg_position::b5);
        ASSERT_EQ(result.has_value(), false);
        ASSERT_EQ(result.error().error_code, board_error::invalid_jump);
    }

    TEST(BoardTest, MoveTest_IlegalMoveWest_expectedHasntValueErrorCodeInvalidJump2)
    {
        board board{5};
        board.current_state = 72909728820232192; //  a b c d e
        //                                        1  1 0 0 0 0
        //                                        2  1 1 0 0 0
        //                                        3  1 1 1 0 0
        //                                        4  1 1 0 0 0
        //                                        5  2 1 1 0 1
        board.current_empty = board.current_state ^ board.board_area_mask;
        auto result = board.move_peg(peg_position::a5, peg_position::d5);
        ASSERT_EQ(result.has_value(), false);
        ASSERT_EQ(result.error().error_code, board_error::invalid_jump);
    }

    TEST(BoardTest, MoveTest_IlegalMoveWest_expectedHasntValueErrorCodeInvalidJump3)
    {
        board board{5};
        board.current_state = 7709852172288; //      a b c d e
        //                                        1  0 0 0 0 0
        //                                        2  0 0 0 0 0
        //                                        3  1 1 1 0 0
        //                                        4  1 2 0 0 0
        //                                        5  1 1 1 0 1
        board.current_empty = board.current_state ^ board.board_area_mask;
        auto result = board.move_peg(peg_position::b4, peg_position::d4);
        ASSERT_EQ(result.has_value(), false);
        ASSERT_EQ(result.error().error_code, board_error::invalid_jump);
    }

    TEST(BoardTest, MoveTest_LegalMoveWestBiggerBoard_expectedHasValue)
    {
        board board{8};
        board.current_state = 5510445691027; //      a b c d e f g h
        //                                       1   0 0 0 0 0 0 0 0
        //                                       2   0 0 0 0 0 0 0 0
        //                                       3   1 0 1 0 0 0 0 0
        //                                       4   1 1 0 0 0 0 0 0
        //                                       5   0 0 0 0 0 0 0 0
        //                                       6   0 0 0 1 0 1 0 0
        //                                       7   0 0 0 0 1 2 1 0
        //                                       8   1 1 0 0 1 0 0 1
        board.current_empty = board.current_state ^ board.board_area_mask;
        auto result = board.move_peg(peg_position::f7, peg_position::d7);
        ASSERT_EQ(result.has_value(), true);
    }

    TEST(BoardTest, MoveTest_LegalMoveWestBiggerBoard_expectedHasValue2)
    {
        board board{8};
        board.current_state = 72626093192410815; //  a b c d e f g h
        //                                       1   1 0 0 0 0 0 0 0
        //                                       2   0 1 0 0 0 0 0 0
        //                                       3   1 0 1 0 0 0 0 0
        //                                       4   0 0 1 1 0 0 0 0
        //                                       5   0 1 2 0 0 0 0 0
        //                                       6   0 0 0 1 0 1 0 0
        //                                       7   0 1 1 0 1 1 1 0
        //                                       8   1 1 1 1 1 1 0 1
        board.current_empty = board.current_state ^ board.board_area_mask;
        auto result = board.move_peg(peg_position::c5, peg_position::a5);
        ASSERT_EQ(result.has_value(), true);
    }

    TEST(BoardTest, MoveTest_LegalMoveWestBiggerBoard_expectedHasValue3)
    {
        board board{7};
        board.current_state = 6605763380736; //      a b c d e f g
        //                                       1   0 0 0 0 0 0 0
        //                                       2   0 0 0 0 0 0 0
        //                                       3   0 1 2 0 0 0 0
        //                                       4   0 1 0 0 0 0 0
        //                                       5   0 1 1 0 0 0 0
        //                                       6   0 1 1 1 0 1 0
        //                                       7   0 1 1 0 0 0 0
        board.current_empty = board.current_state ^ board.board_area_mask;
        auto result = board.move_peg(peg_position::c3, peg_position::a3);
        ASSERT_EQ(result.has_value(), true);
    }
