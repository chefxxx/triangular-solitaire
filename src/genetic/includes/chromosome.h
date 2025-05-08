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
    Board board;
    std::vector<gene> genes;
    explicit chromosome(int b_size);
};

inline std::ostream& operator<<(std::ostream& os, const chromosome& chromosome) {
    int i = 1;
    for (const gene &g: chromosome.genes) {
        os << "H" << i++ << ": " << g.weight << " ";
    }
    return os;
}


#endif //TRIANGULARSOLITAIRE_CHROMOSOME_H
