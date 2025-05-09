//
// Created by Mykhailo_Shamrai on 08.05.2025.
//

#include <gtest/gtest.h>
#include <board.h>

#include "../src/common/distance_to_center.h"
#include "../src/common/heuristic.h"

TEST(Heuristics, LambdaHeuristicCreation_SatisfiesConcept) {
    auto lambda_heuristic = [](Board b) { return static_cast<int>(2); };

    static_assert(Heuristic<decltype(lambda_heuristic)>);
}

TEST(Heuristics, StructHeuristicsCreation_Success)
{
    auto lambda_heuristic1 = [](Board b) { return static_cast<int>(1); };
    auto lambda_heuristic2 = [](Board b) { return static_cast<int>(2); };
    auto lambda_heuristic3 = [](Board b) { return static_cast<int>(3); };

    Heuristics hs{lambda_heuristic1, lambda_heuristic2, lambda_heuristic3};
    Board tmp{5};
    auto res_tuple = hs.calculate_heuristics(tmp);

    ASSERT_EQ(res_tuple, std::make_tuple(1, 2, 3));
}

TEST(Heurisics, MultiplyOfTwoTuples_TwoCorrectTuples)
{
    auto tuple1 = std::make_tuple(1, 2, 3);
    auto tuple2 = std::make_tuple(3, 2, 1);

    auto tuple3 = multiply_two_tuples(tuple1, tuple2, std::make_index_sequence<3>{});

    ASSERT_EQ(tuple3, std::make_tuple(3, 4, 3));
}

TEST(Heuristics, MultiplyOfTwoTuplesInsideStruct_StructWith3HeuristicsAndWeights)
{
    auto weights = std::make_tuple(1, 2, 3);
    auto lambda_heuristic1 = [](Board b) { return static_cast<int>(1); };
    auto lambda_heuristic2 = [](Board b) { return static_cast<int>(1); };
    auto lambda_heuristic3 = [](Board b) { return static_cast<int>(1); };

    Heuristics hs{lambda_heuristic1, lambda_heuristic2, lambda_heuristic3};
    Board tmp{5};

    auto res = hs.multiply_with_weights(weights, tmp);
    ASSERT_EQ(res, std::make_tuple(1, 2, 3));
}

TEST(Heuristcs, UsingHeuristicDistanceToCenter_TwoBoardsOneHasMorePegsInCenter)
{
    Board not_centered{5};
    not_centered.current_state = 72058694069649408; //  a b c d e
    //                                               1  1
    //                                               2  0 0
    //                                               3  1 c 0
    //                                               4  0 0 0 0
    //                                               5  1 1 1 1 1
    not_centered.current_empty = not_centered.current_state ^ not_centered.board_area_mask;

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

TEST(Heuristcs, UsingHeuristicDistanceToCenter_TwoBoardsOneHasMorePegsInCenter2)
{
    Board not_centered{5};
    not_centered.current_state = 72057594323140608; //  a b c d e
    //                                               1  1
    //                                               2  0 0
    //                                               3  0 c 0
    //                                               4  0 0 0 0
    //                                               5  1 0 0 0 1
    not_centered.current_empty = not_centered.current_state ^ not_centered.board_area_mask;

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

TEST(Heuristcs, UsingHeuristicDistanceToCenter_TwoBoardsOneHasMorePegsInCenter_BiggerBoard)
{
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
    not_centered.current_empty = not_centered.current_state ^ not_centered.board_area_mask;

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