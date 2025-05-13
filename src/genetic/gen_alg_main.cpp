//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#include <distance_to_center.h>
#include <fstream>
#include <heuristic.h>
#include <iostream>
#include <isolated_pegs.h>
#include <number_of_free_positions.h>
#include <number_of_new_moves.h>
#include <ostream>
#include <string>
#include <vector>
#include "chromosome.h"
#include "eval.h"

constexpr int MIN_POPULATION_SIZE = 10;

int usage(const std::string &pname) {
  std::cout
      << "Usage: " << pname
      << " [population size] [board size] [max generations] [tournament size]"
         " [mutation size] [mutation strength]"
      << std::endl;
  return 0;
}

std::ofstream createTimestampedAnalysisFile();

int main(const int argc, char *argv[]) {
  if (argc < 7)
    return usage(argv[0]);

  /* Read args */
  const int init_population_size = std::stoi(argv[1]);
  const int board_size = std::stoi(argv[2]);
  const int max_generations = std::stoi(argv[3]);
  //const int tournament_size = std::stoi(argv[4]);     // must be power of 2
  int mutation_size = std::stoi(argv[5]);       // can vary
  float mutation_strength = std::stof(argv[6]); // in [0,1]

  /* Prepare args */
  std::vector<Chromosome> population;
  population.reserve(init_population_size);

  /* Initial population */
  for (int i = 0; i < init_population_size; i++) {
    population.emplace_back(board_size);
  }

  /* File creaexprtion/opening */
  auto outFile = createTimestampedAnalysisFile();

  constexpr DistanceToCenterHeuristic disToCenter{};
  constexpr IsolatedPegs isolatedPegs{};
  constexpr NumberOfNewMoves newMoves{};
  constexpr NumberOfFreePositions freePositions{};

  Heuristics h{disToCenter, isolatedPegs, newMoves};
  Heuristics evalFunc{freePositions, disToCenter};

  /* Start evaluation */
  for (int i = 0; i < max_generations && population.size() > MIN_POPULATION_SIZE; i++) {
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
  printPopulation(population, outFile);
  outFile.close();
  return 0;
}

std::ofstream createTimestampedAnalysisFile() {
  auto now = std::chrono::system_clock::now();
  std::time_t timeNow = std::chrono::system_clock::to_time_t(now);

  std::tm* tmNow = std::localtime(&timeNow);
  std::ostringstream oss;
  oss << "Analysis_"
      << std::put_time(tmNow, "%Y-%m-%d__%H:%M:%S")
      << ".txt";

  std::ofstream file(oss.str());
  if (!file) {
    std::cerr << "Failed to create file: " << oss.str() << std::endl;
  } else {
    std::cout << "Created file: " << oss.str() << std::endl;
  }
  return file;
}