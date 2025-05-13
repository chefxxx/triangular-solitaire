//
// Created by Mateusz Mikiciuk on 29/04/2025.
//

#include "bit_operations.h"
#include "board.h"
#include "move.h"
#include <gtest/gtest.h>

TEST(Move, MoveSimple) {
  const Board board{5};
  const auto moves = BuildAllMoves(board);
  for (auto move : moves) {
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
  for (auto move : moves) {
    std::cout << move << std::endl;
  }
}

TEST(Move, MoveNotNotSimple) {
  Board board{8};
  board.SetState(72626093192410815); //  a b c d e f g h
  //                                       1   1
  //                                       2   0 1
  //                                       3   1 0 1
  //                                       4   0 0 1 1
  //                                       5   0 1 2 0 0
  //                                       6   0 0 0 1 0 1
  //                                       7   0 1 1 0 1 1 1
  //                                       8   1 1 1 1 1 1 0 1
  const auto moves = BuildAllMoves(board);
  for (auto move : moves) {
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

// ------------------------------
// Move to east
// ------------------------------

TEST(Move, MoveTest_LegalMoveEast_expectedHasValue) {
  Board board{5};
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

TEST(Move, MoveTest_IlegalMoveEast_expectedHasntValueErrorCodeInvalidJump) {
  Board board{5};
  board.current_state = 287003119714304; //  a b c d e
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

TEST(Move, MoveTest_IlegalMoveEast_expectedHasntValueErrorCodeInvalidJump2) {
  Board board{5};
  board.current_state = 287003102937088; //  a b c d e
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

TEST(
    Move,
    MoveTest_IlegalMoveEastBiggerBoard_expectedHasntValueErrorCodeInvalidJump2) {
  Board board{8};
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

TEST(Move, MoveTest_LegalMoveEastBiggerBoard_expectedHasValue) {
  Board board{8};
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
TEST(Move, MoveTest_LegalMoveWest_expectedHasValue) {
  Board board{5};
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

TEST(Move, MoveTest_LegalMoveWest_expectedHasValue2) {
  Board board{5};
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

TEST(Move, MoveTest_LegalMoveWest_expectedHasValue3) {
  Board board{5};
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

TEST(Move, MoveTest_IlegalMoveWest_expectedHasntValueErrorCodeInvalidJump) {
  Board board{5};
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

TEST(Move, MoveTest_IlegalMoveWest_expectedHasntValueErrorCodeInvalidJump2) {
  Board board{5};
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

TEST(Move, MoveTest_IlegalMoveWest_expectedHasntValueErrorCodeInvalidJump3) {
  Board board{5};
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

TEST(Move, MoveTest_LegalMoveWestBiggerBoard_expectedHasValue) {
  Board board{8};
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

TEST(Move, MoveTest_LegalMoveWestBiggerBoard_expectedHasValue2) {
  Board board{8};
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

TEST(Move, MoveTest_LegalMoveWestBiggerBoard_expectedHasValue3) {
  Board board{7};
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

TEST(Move, Perft) {
  Board board{5};
  perft(board, false);
}