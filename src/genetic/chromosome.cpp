//
// Created by Mateusz Mikiciuk on 30/03/2025.
//


#include <random>
#include <iomanip>
#include <__random/random_device.h>
#include "heuristic.h"
#include "chromosome.h"

Chromosome::Chromosome(const int b_size) : board{b_size} {
  std::mt19937 rng(std::random_device{}());
  std::uniform_real_distribution<float> dist(0, 100);
  genes.reserve(HEURISTIC_COUNT);
  for (int i = 0; i < HEURISTIC_COUNT; i++) {
    genes.push_back(dist(rng));
  }
  normalizeGenes();
  score = 0.0f;
}

Chromosome::Chromosome(const std::vector<float> &genes, const int b_size)
    : board(b_size) {
  this->genes = genes;
  this->score = 0.0f;
}

void Chromosome::normalizeGenes() {
  auto norm = std::accumulate(genes.begin(), genes.end(), 0.0f,
    [](const float acc, const float x) {
      return acc + x * x;
    });
  norm = std::sqrt(norm);
  for (auto &gene : genes) {
    gene /= norm;
  }
}

void printPopulation(const std::vector<Chromosome> &population, std::ostream &os) {
  for (int i{0}; i < population.size(); ++i) {
    os << i + 1 << "." << population[i] << " ";
    if (i % 3 == 2)
      os << "\n";
  }

  const auto best_individual = std::ranges::min_element(population,
                                                        [](const Chromosome &lhs, const Chromosome &rhs) { return lhs.score < rhs.score; });

  os << "\nBest in population: \n";
  os << *best_individual << "\n";
  print_current_board(best_individual->board, os);
}

std::ostream &operator<<(std::ostream &os, const Chromosome &chromosome) {
  os << std::fixed << std::setprecision(2);
  os << "genes: {";
  for (int i{0}; i < chromosome.genes.size(); ++i) {
    if (i != chromosome.genes.size() - 1)
      os << chromosome.genes[i] << ", ";
    else
      os << chromosome.genes[i];
  }
  os << "} score: " << chromosome.score << " ";
  os << std::setprecision(os.precision());
  return os;
}
