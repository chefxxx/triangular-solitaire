//
// Created by Mykhailo_Shamrai on 08.05.2025.
//

#include <board.h>
#include <gtest/gtest.h>

#include "../src/common/distance_to_center.h"
#include "../src/common/heuristic.h"
#include "../src/common/isolated_pegs.h"
#include "../src/common/number_of_free_positions.h"
#include "../src/common/number_of_new_moves.h"

TEST(Heuristics, LambdaHeuristicCreation_SatisfiesConcept) {
  auto lambda_heuristic = [](Board b) { return static_cast<int>(2); };

  static_assert(Heuristic<decltype(lambda_heuristic)>);
}

TEST(Heuristics, StructHeuristicsCreation_Success) {
  auto lambda_heuristic1 = [](Board b) { return static_cast<int>(1); };
  auto lambda_heuristic2 = [](Board b) { return static_cast<int>(2); };
  auto lambda_heuristic3 = [](Board b) { return static_cast<int>(3); };

  Heuristics hs{lambda_heuristic1, lambda_heuristic2, lambda_heuristic3};
  Board tmp{5};
  auto res_tuple = hs.calculate_heuristics(tmp);

  ASSERT_EQ(res_tuple, std::make_tuple(1, 2, 3));
}

TEST(Heurisics, MultiplyOfTwoTuples_TwoCorrectTuples) {
  auto tuple1 = std::make_tuple(1, 2, 3);
  auto tuple2 = std::make_tuple(3, 2, 1);

  auto tuple3 =
      multiply_two_tuples(tuple1, tuple2, std::make_index_sequence<3>{});

  ASSERT_EQ(tuple3, std::make_tuple(3, 4, 3));
}

TEST(Heuristics,
     MultiplyOfTwoTuplesInsideStruct_StructWith3HeuristicsAndWeights) {
  auto weights = std::make_tuple(1, 2, 3);
  auto lambda_heuristic1 = [](Board b) { return static_cast<int>(1); };
  auto lambda_heuristic2 = [](Board b) { return static_cast<int>(1); };
  auto lambda_heuristic3 = [](Board b) { return static_cast<int>(1); };

  Heuristics hs{lambda_heuristic1, lambda_heuristic2, lambda_heuristic3};
  Board tmp{5};

  auto res = hs.multiply_with_weights(weights, tmp);
  ASSERT_EQ(res, std::make_tuple(1, 2, 3));
}

TEST(Heuristcs,
     UsingHeuristicDistanceToCenter_TwoBoardsOneHasMorePegsInCenter) {
  Board not_centered{5};
  not_centered.current_state = 72058694069649408; //  a b c d e
  //                                               1  1
  //                                               2  0 0
  //                                               3  1 c 0
  //                                               4  0 0 0 0
  //                                               5  1 1 1 1 1
  not_centered.current_empty =
      not_centered.current_state ^ not_centered.board_area_mask;

  Board centered{5};
  centered.current_state = 849982617812992; //        a b c d e
  //                                               1  0
  //                                               2  1 1
  //                                               3  1 c 1
  //                                               4  0 1 1 1
  //                                               5  0 0 0 0 0
  centered.current_empty = centered.current_state ^ centered.board_area_mask;

  DistanceToCenterHeuristic dhs{};
  int h1 = dhs(not_centered);
  int h2 = dhs(centered);

  ASSERT_TRUE(h1 < h2);
}

TEST(Heuristcs,
     UsingHeuristicDistanceToCenter_TwoBoardsOneHasMorePegsInCenter2) {
  Board not_centered{5};
  not_centered.current_state = 72057594323140608; //  a b c d e
  //                                               1  1
  //                                               2  0 0
  //                                               3  0 c 0
  //                                               4  0 0 0 0
  //                                               5  1 0 0 0 1
  not_centered.current_empty =
      not_centered.current_state ^ not_centered.board_area_mask;

  Board centered{5};
  centered.current_state = 564058054983680; //        a b c d e
  //                                               1  0
  //                                               2  0 1
  //                                               3  1 c 0
  //                                               4  0 1 0 0
  //                                               5  0 0 0 0 0
  centered.current_empty = centered.current_state ^ centered.board_area_mask;

  DistanceToCenterHeuristic dhs{};
  int h1 = dhs(not_centered);
  int h2 = dhs(centered);

  ASSERT_TRUE(h1 < h2);
}

TEST(
    Heuristcs,
    UsingHeuristicDistanceToCenter_TwoBoardsOneHasMorePegsInCenter_BiggerBoard) {
  Board not_centered{8};
  not_centered.current_state = 72057594324260097; //  a b c d e f g h
  //                                               1  1
  //                                               2  0 0
  //                                               3  0 0 0
  //                                               4  0 0 0 0
  //                                               5  1 0 c 0 1
  //                                               6  1 0 0 0 1 0
  //                                               7  1 0 1 0 1 0 0
  //                                               8  1 0 0 0 0 0 0 0
  not_centered.current_empty =
      not_centered.current_state ^ not_centered.board_area_mask;

  Board centered{8};
  centered.current_state = 564049499394580; //        a b c d e f g h
  //                                               1  0
  //                                               2  0 1
  //                                               3  1 0 0
  //                                               4  0 0 0 0
  //                                               5  0 1 c 0 0
  //                                               6  0 0 1 1 0 0
  //                                               7  0 1 0 0 1 0 0
  //                                               8  0 0 1 0 1 0 0 0

  centered.current_empty = centered.current_state ^ centered.board_area_mask;

  DistanceToCenterHeuristic dhs{};
  int h1 = dhs(not_centered);
  int h2 = dhs(centered);

  ASSERT_TRUE(h1 < h2);
}

TEST(Heuristcs, UsingHeuristicNumberOfFreePostions_TestOnlyAFunctor) {
  NumberOfFreePositions nofph{};

  Board board{8};
  board.current_state = 564049499394580; //           a b c d e f g h
  //                                               1  0
  //                                               2  0 1
  //                                               3  1 0 0
  //                                               4  0 0 0 0
  //                                               5  0 1 c 0 0
  //                                               6  0 0 1 1 0 0
  //                                               7  0 1 0 0 1 0 0
  //                                               8  0 0 1 0 1 0 0 0

  board.current_empty = board.current_state ^ board.board_area_mask;
  int res = 27;
  board.pegs_left = 9;

  ASSERT_EQ(nofph(board), res);
}

TEST(
    Heuristcs,
    UsingHeuristicNumberOfFreePostions_TestWithTwoBoardsWithTheSameNumberOfPegs) {
  NumberOfFreePositions nofph{};

  Board first{8};
  first.current_state = 564049499394580; //           a b c d e f g h
  //                                               1  0
  //                                               2  0 1
  //                                               3  1 0 0
  //                                               4  0 0 0 0
  //                                               5  0 1 c 0 0
  //                                               6  0 0 1 1 0 0
  //                                               7  0 1 0 0 1 0 0
  //                                               8  0 0 1 0 1 0 0 0

  first.current_empty = first.current_state ^ first.board_area_mask;
  first.pegs_left = 9;

  Board second{8};
  second.current_state = 72057594324260097; //        a b c d e f g h
  //                                               1  1
  //                                               2  0 0
  //                                               3  0 0 0
  //                                               4  0 0 0 0
  //                                               5  1 0 c 0 1
  //                                               6  1 0 0 0 1 0
  //                                               7  1 0 1 0 1 0 0
  //                                               8  1 0 0 0 0 0 0 0
  second.current_empty = second.current_state ^ second.board_area_mask;

  second.pegs_left = 9;

  ASSERT_EQ(nofph(first), nofph(second));
}

TEST(
    Heuristics,
    UsingHeuristicNumberOfFreePostions_TestWithTwoBoardsWithDifferentNumberOfPegs) {
  Board first{5};
  first.current_state = 72057594054705152; //         a b c d e
  //                                               1  1
  //                                               2  0 0
  //                                               3  0 c 0
  //                                               4  0 0 0 0
  //                                               5  1 0 0 0 0
  first.current_empty = first.current_state ^ first.board_area_mask;
  first.pegs_left = 2;

  Board second{5};
  second.current_state = 564058054983680; //        a b c d e
  //                                               1  0
  //                                               2  0 1
  //                                               3  1 c 0
  //                                               4  0 1 0 0
  //                                               5  0 0 0 0 0
  second.current_empty = second.current_state ^ second.board_area_mask;
  second.pegs_left = 3;
  NumberOfFreePositions nofph{};
  ASSERT_TRUE(nofph(first) > nofph(second));
}

TEST(Heuristic, FindNeighborsForAPeg) {
  Board board{8};
  board.current_state = 72057594324260097; //        a b c d e f g h
  //                                               1  1
  //                                               2  0 0
  //                                               3  0 0 0
  //                                               4  0 0 0 0
  //                                               5  1 0 0 0 1
  //                                               6  1 0 0 0 1 0
  //                                               7  1 0 1 0 1 0 0
  //                                               8  1 0 0 0 0 0 0 0
  board.current_empty = board.current_state ^ board.board_area_mask;
  int index = 8;
  auto res = IsolatedPegs::find_neighbours(index, board);
  uint64_t correct_answ = 65537;
  ASSERT_EQ(correct_answ, res);
}

TEST(Heuristic, FindNeighborsForAPeg_PegWithOneNeighbor) {
  Board board{8};
  board.current_state = 72057594324260289; //        a b c d e f g h
  //                                               1  1
  //                                               2  0 0
  //                                               3  0 0 0
  //                                               4  0 0 0 0
  //                                               5  1 0 0 0 1
  //                                               6  1 0 0 0 1 0
  //                                               7  1 0 1 0 1 0 0
  //                                               8  1 0 0 0 0 0 1 1
  board.current_empty = board.current_state ^ board.board_area_mask;
  int index = 7;
  auto res = IsolatedPegs::find_neighbours(index, board);
  uint64_t correct_answ = 64;
  ASSERT_EQ(correct_answ, res);
}

TEST(Heuristic, FindNeighborsForAPeg_PegWithTwoNeighbors) {
  Board board{8};
  board.current_state = 72057594324260289; //        a b c d e f g h
  //                                               1  1
  //                                               2  0 0
  //                                               3  0 0 0
  //                                               4  0 0 0 0
  //                                               5  1 0 0 0 1
  //                                               6  1 0 0 0 1 0
  //                                               7  1 0 1 0 1 0 0
  //                                               8  1 0 0 0 0 0 1 1
  board.current_empty = board.current_state ^ board.board_area_mask;
  int index = 20;
  auto res = IsolatedPegs::find_neighbours(index, board);
  uint64_t correct_answ = 268439552;
  ASSERT_EQ(correct_answ, res);
}

TEST(Heuristic,
     IsolatedPegsHeuristic_CheckIfNumberOfPegsWithNeighborsIsTheSame) {
  Board first{5};

  first.current_state = 520093696; //          a b c d e
  //                                               1  0
  //                                               2  0 0
  //                                               3  0 0 0
  //                                               4  0 0 0 0
  //                                               5  1 1 1 1 1
  first.current_empty = first.current_state ^ first.board_area_mask;

  Board second{5};

  second.current_state = 72624976666034176; //         a b c d e
  //                                               1  1
  //                                               2  0 1
  //                                               3  0 0 1
  //                                               4  0 0 0 1
  //                                               5  0 0 0 0 1

  second.current_empty = second.current_state ^ second.board_area_mask;

  IsolatedPegs iph{};
  ASSERT_EQ(iph(first), iph(second));
}

TEST(Heuristic,
     IsolatedPegsHeuristic_CheckIfNumberOfPegsWithNeighborsIsDifferent) {
  Board first{5};

  first.current_state = 72057594524467200; //          a b c d e
  //                                               1  1
  //                                               2  0 0
  //                                               3  0 0 0
  //                                               4  0 0 0 0
  //                                               5  1 0 1 1 1
  first.current_empty = first.current_state ^ first.board_area_mask;

  Board second{5};

  second.current_state = 72627141128224768; //         a b c d e
  //                                               1  1
  //                                               2  0 1
  //                                               3  0 1 1
  //                                               4  0 0 0 0
  //                                               5  0 0 1 0 0

  second.current_empty = second.current_state ^ second.board_area_mask;

  IsolatedPegs iph{};
  ASSERT_TRUE(iph(first) < iph(second));
}

TEST(Heuristic, NumberOfNewMoves_OneBoardWithKnownNumberOfMoves) {
  Board board{8};
  board.current_state = 72057594324260289; //         a b c d e f g h
  //                                               1  1
  //                                               2  0 0
  //                                               3  0 0 0
  //                                               4  0 0 0 0
  //                                               5  1 0 0 0 1
  //                                               6  1 0 0 0 1 0
  //                                               7  1 0 1 0 1 0 0
  //                                               8  1 0 0 0 0 0 1 1
  board.current_empty = board.current_state ^ board.board_area_mask;

  int number_of_moves = 3;
  NumberOfNewMoves nonmh{};
  ASSERT_EQ(nonmh(board), number_of_moves);
}

TEST(Heuristic, NumberOfNewMoves_FirstBoardHasLessMovesThanSecond) {
  Board first{6};
  first.current_state = 72059801738346496; //         a b c d e f // 5
  //                                               1  1
  //                                               2  0 0
  //                                               3  0 1 0
  //                                               4  0 1 0 0
  //                                               5  1 0 1 0 0
  //                                               6  1 1 0 0 1 1
  first.current_empty = first.current_state ^ first.board_area_mask;

  Board second{6};
  second.current_state = 72058702526480384; //         a b c d e f // 3
  //                                               1  1
  //                                               2  0 0
  //                                               3  1 0 0
  //                                               4  0 1 0 0
  //                                               5  1 1 1 0 1
  //                                               6  1 0 0 0 1 0
  second.current_empty = second.current_state ^ second.board_area_mask;

  NumberOfNewMoves nonmh{};
  ASSERT_TRUE(nonmh(first) > nonmh(second));
}

TEST(Heuristic, NumberOfNewMoves_BoardHasntMoves) {
  Board board{7};
  board.current_state = 72059793130459648; //         a b c d e f g // 0
  //                                               1  1
  //                                               2  0 0
  //                                               3  0 1 0
  //                                               4  0 0 0 0
  //                                               5  0 0 1 0 0
  //                                               6  1 0 0 0 0 1
  //                                               6  0 1 0 0 1 0 0
  board.current_empty = board.current_state ^ board.board_area_mask;

  NumberOfNewMoves nonmh{};
  ASSERT_EQ(0, nonmh(board));
}

TEST(Heristic, SumOfATuple) {
  auto t = std::make_tuple(1, 2, 3, 10, 11);
  auto res = get_sum_of_tuple_elements(t);
  std::cout << res << std::endl;
}

TEST(Heuristic, EuqlidianNormOfATuple) {
  auto t = std::make_tuple(1, 2, 3, 10, 11);
  auto res = get_euclidian_norm(t);
  std::cout << res << std::endl;
}

TEST(Heuristic, TestAllHeuristicsAtOneInOneHeuristicsStructure) {
  Board board{8};
  board.current_state = 72057594324260289; //         a b c d e f g h
  //                                               1  1
  //                                               2  0 0
  //                                               3  0 0 0
  //                                               4  0 0 0 0
  //                                               5  1 0 0 0 1
  //                                               6  1 0 0 0 1 0
  //                                               7  1 0 1 0 1 0 0
  //                                               8  1 0 0 0 0 0 1 1
  board.current_empty = board.current_state ^ board.board_area_mask;
  board.pegs_left = 11;
  DistanceToCenterHeuristic dtch{};
  IsolatedPegs iph{};
  NumberOfNewMoves nonmh{};
  NumberOfFreePositions nofp{};

  Heuristics h{dtch, iph, nonmh, nofp};
  auto evaluation = h.calculate_heuristics(board);
  std::cout << std::get<0>(evaluation) << " " << std::get<1>(evaluation) << " "
            << std::get<2>(evaluation) << " " << std::get<3>(evaluation)
            << std::endl;
  auto sum = get_sum_of_tuple_elements(evaluation);
  std::cout << sum << std::endl;
  auto norm = get_euclidian_norm(evaluation);
  std::cout << norm << std::endl;
}
