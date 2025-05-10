//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <chrono>
#include "chromosome.h"
#include "eval.h"

constexpr int MIN_POPULATION_SIZE = 10;

int usage(const std::string& pname) {
    std::cout << "Usage: " << pname << " [population size] [board size] [max generations] [tournament size]"
                                       " [mutation size] [mutation strength]" << std::endl;
    return 0;
}

int main(const int argc, char *argv[]) {
    if (argc < 8)
        return usage(argv[0]);

    /* Read args */
    const int init_population_size = std::stoi(argv[1]);
    const int board_size = std::stoi(argv[2]);
    const int max_generations = std::stoi(argv[3]);
    const int tournament_size = std::stoi(argv[4]);            // must be power of 2
    const int mutation_size = std::stoi(argv[6]);              // can vary
    const int mutation_strength = std::stoi(argv[7]);          // in [0,1]

    /* Prepare args */
    std::vector<chromosome> population;
    population.reserve(init_population_size);

    /* Initial population */
    for (int i = 0; i < init_population_size; i++) {
        population.emplace_back(board_size);
    }

    /* Print init population */
    std::cout << "Firs population of size " << init_population_size << "\n";
    for (chromosome &individual: population) {
        std::cout << individual << "\n";
    }

    for (const chromosome &individual: population) {
        std::cout << "score:"<< individual.score << "\n";
    }

    /* Start evaluation */
    for (int i = 0; i < max_generations || population.size() <= MIN_POPULATION_SIZE; i++) {
        evalOneGeneration(population);
        population = eliminateWeak(population, tournament_size);
        crossAndMutate(population, mutation_size,  mutation_strength);
    }

    return 1;
}