//
// Created by Mateusz Mikiciuk on 09/05/2025.
//

#include <gtest/gtest.h>
#include "chromosome.h"
#include "eval.h"


TEST(Eval, ParallelComp) {
    /* Prepare args */
    std::vector<chromosome> population;
    population.reserve(32784);

    /* Initial population */
    for (int i = 0; i < 32784; i++) {
        population.emplace_back(8);
    }

    std::vector<chromosome> population2 = population;

    auto start = std::chrono::high_resolution_clock::now();
    evalOneGeneration(population);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "(Parallel) Elapsed time: " << duration.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    evalSimple(population2);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "(Simple) Elapsed time: " << duration.count() << " ms\n";

}