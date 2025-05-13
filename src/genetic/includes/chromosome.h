//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#ifndef TRIANGULARSOLITAIRE_CHROMOSOME_H
#define TRIANGULARSOLITAIRE_CHROMOSOME_H

#include <vector>
#include "board.h"

struct Chromosome {
  // ------------------------------
  // Class creation
  // ------------------------------
  Chromosome() : board(MAX_BOARD_SIDE), score(0.0f) {};

  ~Chromosome() = default;

  explicit Chromosome(int b_size);

  explicit Chromosome(const std::vector<float> &genes, int b_size);

  void normalizeGenes();

  // ------------------------------
  // Class members
  // ------------------------------
  std::vector<float> genes;
  Board board;
  float score;
};

void printPopulation(const std::vector<Chromosome> &population, std::ostream &os);
std::ostream &operator<<(std::ostream &os, const Chromosome &chromosome);

#endif // TRIANGULARSOLITAIRE_CHROMOSOME_H
