//
// Created by Mateusz Mikiciuk on 31/03/2025.
//
#include "board.h"
#include <gtest/gtest.h>

TEST(BoardTest, printCurrBoards) {
  const std::vector<Board> boards{Board(5), Board(6), Board(7), Board(8)};

  for (auto const &b : boards) {
    print_current_board(b);
  }
}

TEST(BoardTest, pegPositions) {
  const std::vector<peg_position> peg_positions{
      peg_position::a1, peg_position::a2, peg_position::a3, peg_position::a4,
      peg_position::a5, peg_position::a6, peg_position::a7, peg_position::a8};
  for (int i = 0; i < peg_positions.size(); ++i) {
    ASSERT_EQ(static_cast<int>(peg_positions[i]), 8 * (8 - i - 1));
  }
}

TEST(BoardTest, pegOutOfBounds) {
  Board board{5};
  const auto result1 = board.move_peg(peg_position::b1, peg_position::b2);
  ASSERT_EQ(result1.has_value(), false);
  ASSERT_EQ(result1.error().error_code, board_error::out_of_bound);
}

TEST(BoardTest, pegDoesNotExist) {
  Board board{5};
  auto result1 = board.move_peg(peg_position::a1, peg_position::a4);
  ASSERT_EQ(result1.has_value(), false);
  ASSERT_EQ(result1.error().error_code, board_error::peg_does_not_exist);
}

TEST(BoardTest, pegPosIsOccupiedNorth) {
  Board board{5};
  auto result1 = board.move_peg(peg_position::a2, peg_position::a4);
  ASSERT_EQ(result1.has_value(), false);
  ASSERT_EQ(result1.error().error_code, board_error::invalid_jump);
}

TEST(BoardTest, pegCount) {
  const Board board{5};
  ASSERT_EQ(14, board.pegs_left);
}

TEST(BoardTest, MoveTest1) {
  Board board{5};
  auto result = board.move_peg(peg_position::a3, peg_position::a1);
  ASSERT_EQ(result.has_value(), true);
}
