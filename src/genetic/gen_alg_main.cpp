//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "chromosome.h"

int usage(const std::string& pname) {
    std::cout << "Usage: " << pname << " [population size] [board size]" << std::endl;
    return 0;
}

int main(const int argc, char *argv[]) {
    if (argc < 3)
        return usage(argv[0]);

    /* Read args */
    const int population_size = std::stoi(argv[1]);
    const int board_size = std::stoi(argv[2]);
    std::vector<chromosome> population;
    population.reserve(population_size);

    /* Initial population */
    for (int i = 0; i < population_size; i++) {
        population.emplace_back(board_size);
    }

    /* Print init population */
    std::cout << "Firs population of size " << population_size << "\n";
    for (chromosome &individual: population) {
        std::cout << individual << "\n";
    }

    return 1;
}