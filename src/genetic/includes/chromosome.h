//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#ifndef TRIANGULARSOLITAIRE_CHROMOSOME_H
#define TRIANGULARSOLITAIRE_CHROMOSOME_H

#include <iostream>
#include <vector>
#include "gene.h"
#include "board.h"

constexpr int HEURISTIC_COUNT = 4;

class chromosome
{
public:
    // ------------------------------
    // Class creation
    // ------------------------------
    explicit chromosome(int b_size);
    ~chromosome() = default;

    // ------------------------------
    // Assignments
    // ------------------------------
    chromosome(chromosome&&) = default;
    chromosome& operator=(chromosome const&&) = default;

    chromosome(chromosome const&) = default;
    chromosome& operator=(chromosome const&) = default;

    // ------------------------------
    // Class members
    // ------------------------------
    std::vector<gene> genes;
    Board board;
    float score;
};

std::ostream& operator<<(std::ostream& os, const chromosome& chromosome);


#endif //TRIANGULARSOLITAIRE_CHROMOSOME_H
