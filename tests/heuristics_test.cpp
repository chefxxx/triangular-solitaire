//
// Created by Mykhailo_Shamrai on 08.05.2025.
//

#include <gtest/gtest.h>
#include <board.h>
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