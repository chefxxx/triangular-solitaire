//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "chromosome.h"
#include "distance_to_center.h"
#include "eval.h"
#include "heuristic.h"
#include "isolated_pegs.h"
#include "number_of_free_positions.h"
#include "number_of_new_moves.h"

int usage(const std::string &pname) {
  std::cout << "Usage: " << pname
            << " [population size] [board size] [max generations]"
               " [mutation size] [mutation strength]"
            << "\n";
  return 0;
}

std::ofstream createTimestampedAnalysisFile();

auto main(const int argc, char *argv[]) -> int {
  if (argc < 6)
    return usage(argv[0]);

  /* Read args */
  const int init_population_size = std::stoi(argv[1]);
  const int board_size = std::stoi(argv[2]);
  const int max_generations = std::stoi(argv[3]);
  int mutation_size = std::stoi(argv[4]);
  float mutation_strength = std::stof(argv[5]);

  /* Prepare args */
  std::vector<Chromosome> population;
  population.reserve(init_population_size);

  /* Initial population */
  for (int i = 0; i < init_population_size; i++) {
    population.emplace_back(board_size);
  }

  /* File creaexprtion/opening */
  auto outFile = createTimestampedAnalysisFile();
  outFile << "Program params: \n";
  outFile << "Population size: " << init_population_size << "\n";
  outFile << "Board size: " << board_size << "\n";
  outFile << "Max generations: " << max_generations << "\n";
  outFile << "Mutation size: " << mutation_size << "\n";
  outFile << "Mutation strength: " << mutation_strength << "\n";

  constexpr DistanceToCenterHeuristic disToCenter{};
  constexpr IsolatedPegs isolatedPegs{};
  constexpr NumberOfNewMoves newMoves{};
  constexpr NumberOfFreePositions freePositions{};

  Heuristics h{disToCenter, isolatedPegs, newMoves};
  Heuristics evalFunc{freePositions, disToCenter};

  /* Start evaluation */
  for (int i = 0; i < max_generations; i++) {
    std::cout << i + 1 << " Population is being under evaluation...\n";
    evalOneGeneration(population, h, evalFunc);
    /* Print init population */
    printPopulation(population, outFile);
    population = eliminateWeak2(population);
    crossAndMutate(population, mutation_size, mutation_strength);
    if (i & 1) {
      mutation_size >>= 1;
      mutation_strength -= mutation_strength * 0.2f;
    }
  }

  evalOneGeneration(population, h, evalFunc);
  printPopulation(population, outFile, true);
  outFile.close();
  return 0;
}

std::ofstream createTimestampedAnalysisFile() {
  auto now = std::chrono::system_clock::now();
  std::time_t timeNow = std::chrono::system_clock::to_time_t(now);

  std::tm *tmNow = std::localtime(&timeNow);
  std::ostringstream oss;
  oss << "Analysis_" << std::put_time(tmNow, "%Y-%m-%d__%H:%M:%S") << ".txt";

  std::ofstream file(oss.str());
  if (!file) {
    std::cerr << "Failed to create file: " << oss.str() << std::endl;
  } else {
    std::cout << "Created file: " << oss.str() << std::endl;
  }
  return file;
}