//
// Created by Mateusz Mikiciuk on 09/05/2025.
//

#include "chromosome.h"
#include "distance_to_center.h"
#include "eval.h"
#include "isolated_pegs.h"
#include "number_of_free_positions.h"
#include "number_of_new_moves.h"
#include "threading.h"
#include <gtest/gtest.h>

TEST(Eval, babiesTest) {
  /* Prepare args */
  constexpr size_t measurement_size = 4;
  std::vector<Chromosome> population1;
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
  std::vector<Chromosome> population1;
  population1.reserve(measurement_size);

  /* Initial population */
  for (int i = 0; i < measurement_size; i++) {
    population1.emplace_back(MAX_BOARD_SIDE);
  }

  constexpr DistanceToCenterHeuristic disToCenter{};
  constexpr IsolatedPegs isolatedPegs{};
  constexpr NumberOfNewMoves newMoves{};
  constexpr NumberOfFreePositions freePositions{};

  Heuristics h{disToCenter, isolatedPegs, newMoves};
  Heuristics evalFunc{freePositions, disToCenter};

  evalOneGeneration(population1, h, evalFunc);
  for (const Chromosome &individual : population1) {
    std::cout << "score:" << individual.score << "\n";
  }
  const auto winners1 = eliminateWeak2(population1);
  std::cout << "\nWEENERS \n";
  for (const Chromosome &individual : winners1) {
    std::cout << "score:" << individual.score << "\n";
  }
}
TEST(Eval, ParallelComp) {
  /* Prepare args */
  constexpr size_t measurement_size = 32768;
  std::vector<Chromosome> population1, population2;
  population1.reserve(measurement_size);
  population2.reserve(measurement_size);

  /* Initial population */
  for (int i = 0; i < measurement_size; i++) {
    population1.emplace_back(MAX_BOARD_SIDE);
    population2.push_back(population1.back());
  }

  constexpr DistanceToCenterHeuristic disToCenter{};
  constexpr IsolatedPegs isolatedPegs{};
  constexpr NumberOfNewMoves newMoves{};
  constexpr NumberOfFreePositions freePositions{};

  Heuristics h{disToCenter, isolatedPegs, newMoves};
  Heuristics evalFunc{freePositions, disToCenter};

  ASSERT_EQ(population1.size(), population2.size());

  auto start = std::chrono::high_resolution_clock::now();
  evalOneGeneration(population1, h, evalFunc);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "(Parallel evalGen) Elapsed time: " << duration.count()
            << " ms\n";

  start = std::chrono::high_resolution_clock::now();
  evalOneGeneration(population2, h, evalFunc, false);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "(Simple evalGen) Elapsed time: " << duration.count() << " ms\n";
}