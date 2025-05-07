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