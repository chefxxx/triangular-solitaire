//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#include <fstream>
#include <iostream>
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
  const int tournament_size = std::stoi(argv[4]);     // must be power of 2
  const int mutation_size = std::stoi(argv[5]);       // can vary
  const float mutation_strength = std::stof(argv[6]); // in [0,1]

  /* Prepare args */
  std::vector<Chromosome> population;
  population.reserve(init_population_size);

  /* Initial population */
  for (int i = 0; i < init_population_size; i++) {
    population.emplace_back(board_size);
  }

  /* File creation/opening */
  auto outFile = createTimestampedAnalysisFile();

  /* Start evaluation */
  for (int i = 0; i < max_generations && population.size() > MIN_POPULATION_SIZE; i++) {
    evalOneGeneration(population);
    /* Print init population */
    printPopulation(population, outFile);
    population = eliminateWeak(population, tournament_size, false);
    crossAndMutate(population, mutation_size, mutation_strength);
  }

  printPopulation(population, outFile);
  outFile.close();
  return 1;
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