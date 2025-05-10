//
// Created by Mateusz Mikiciuk on 09/05/2025.
//

#include <gtest/gtest.h>
#include <threading.h>
#include "chromosome.h"
#include "eval.h"

TEST(Eval, babiesTest) {
    /* Prepare args */
    constexpr size_t measurement_size = 4;
    std::vector<chromosome> population1;
    population1.reserve(measurement_size);

    /* Initial population */
    for (int i = 0; i < measurement_size; i++) {
        population1.emplace_back(MAX_BOARD_SIDE);
    }

    std::cout << "Parents: \n";
    for (auto &individual : population1) {
        std::cout << individual << std::endl;
    }

    population1 = makeBabies(population1);

    std::cout << "Babies: \n";
    for (auto &individual : population1) {
        std::cout << individual << std::endl;
    }
}


TEST(Eval, tournamentTest) {
    /* Prepare args */
    constexpr size_t measurement_size = 128;
    constexpr size_t tournament_size = 16;
    std::vector<chromosome> population1;
    population1.reserve(measurement_size);

    /* Initial population */
    for (int i = 0; i < measurement_size; i++) {
        population1.emplace_back(MAX_BOARD_SIDE);
    }

    evalOneGeneration(population1);
    for (const chromosome &individual: population1) {
        std::cout << "score:"<< individual.score << "\n";
    }
    const auto winners1 = eliminateWeak(population1, tournament_size);
    std::cout << "\nWEENERS \n";
    for (const chromosome &individual: winners1) {
        std::cout << "score:"<< individual.score << "\n";
    }
}

TEST(Eval, ParallelComp) {
    /* Prepare args */
    constexpr size_t measurement_size = 32768;
    constexpr size_t tournament_size = 32;
    std::vector<chromosome> population1, population2;
    population1.reserve(measurement_size);
    population2.reserve(measurement_size);

    /* Initial population */
    for (int i = 0; i < measurement_size; i++) {
        population1.emplace_back(MAX_BOARD_SIDE);
        population2.push_back(population1.back());
    }

    ASSERT_EQ(population1.size(), population2.size());

    auto start = std::chrono::high_resolution_clock::now();
    evalOneGeneration(population1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "(Parallel evalGen) Elapsed time: " << duration.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    const std::vector<chromosome> winners1 = eliminateWeak(population1, tournament_size);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "(Parallel eliminateWeak) Elapsed time: " << duration.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    evalOneGeneration(population2, false);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "(Simple evalGen) Elapsed time: " << duration.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    const std::vector<chromosome> winners2 = eliminateWeak(population2, tournament_size, false);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "(Simple eliminateWeak) Elapsed time: " << duration.count() << " ms\n";

    ASSERT_EQ(winners1.size(), winners2.size());
}