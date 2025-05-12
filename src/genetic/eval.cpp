//
// Created by Mateusz Mikiciuk on 09/05/2025.
//

#include <random>
#include <spdlog/spdlog.h>
#include <vector>

#include "bit_operations.h"
#include "chromosome.h"
#include "threading.h"
#include "heuristic.h"
#include "eval.h"
#include "move.h"


float evaluateHeuristics(const Board &b) {
  return static_cast<float>(std::rand() % 100);
}

// TODO: define real evaluation function
void evaluatePosition(Chromosome &individual) {
  individual.score = static_cast<float>(individual.board.pegs_left);
}

std::vector<Chromosome> crossAndMutate(std::vector<Chromosome> &population,
                                       const int mutSize,
                                       const float mutStrength) {
  population = makeBabies(population);
  mutate(population, mutSize, mutStrength);
  return population;
}

std::vector<Chromosome> makeBabies(std::vector<Chromosome> &parents) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::vector<Chromosome> babiedPopulation;
  while (parents.empty() == false) {
    std::uniform_int_distribution<std::mt19937::result_type> m_idx(
        0, parents.size() - 1);
    const unsigned mother_idx = m_idx(rng);
    Chromosome mother = parents[mother_idx];
    parents.erase(parents.begin() + mother_idx);

    std::uniform_int_distribution<std::mt19937::result_type> f_idx(
        0, parents.size() - 1);
    const unsigned father_idx = f_idx(rng);
    Chromosome father = parents[father_idx];
    parents.erase(parents.begin() + father_idx);

    /* MAKE BABIES */
    const unsigned genesSize = mother.genes.size();
    std::vector<gene> baby1, baby2;
    for (int i = 0; i < genesSize; i++) {
      if (i < (genesSize >> 1)) {
        baby1.push_back(mother.genes[i]);
        baby2.push_back(father.genes[i]);
      } else {
        baby1.push_back(father.genes[i]);
        baby2.push_back(mother.genes[i]);
      }
    }
    babiedPopulation.emplace_back(baby1, mother.board.board_size);
    babiedPopulation.emplace_back(baby2, mother.board.board_size);
  }
  return babiedPopulation;
}

void mutate(std::vector<Chromosome> &population, const int mutSize,
            const float mutStrength) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> chromosome_idx(
      0, population.size() - 1);
  std::uniform_int_distribution<std::mt19937::result_type> gene_idx(
      0, HEURISTIC_COUNT - 1);

  for (int i = 0; i < mutSize; i++) {
    const unsigned chr_idx = chromosome_idx(rng);
    const unsigned g_idx = gene_idx(rng);
    if (i & 1)
      population[chr_idx].genes[g_idx].weight +=
          population[chr_idx].genes[g_idx].weight * mutStrength;
    else
      population[chr_idx].genes[g_idx].weight -=
          population[chr_idx].genes[g_idx].weight * mutStrength;
  }
}

// TODO it can be done without creating a copy
size_t playTournament(const std::vector<Chromosome> &players,
                      const size_t start, const size_t end) {
  if (!IsPowerOfTwo(end - start + 1))
    spdlog::error("Tournament size {} is not a power of 2!", end - start + 1);
  if (end - start == 1)
    return std::isless(players[start].score, players[end].score) ? start : end;

  const size_t mid = start + ((end - start) >> 1);
  const size_t winner1 = playTournament(players, start, mid);
  const size_t winner2 = playTournament(players, mid + 1, end);

  return std::isless(players[winner1].score, players[winner2].score) ? winner1
                                                                     : winner2;
}

std::vector<Chromosome> eliminateWeak(std::vector<Chromosome> &generation,
                                      const int tournament_size,
                                      const bool parallel) {
  const size_t tournament_count = generation.size() / tournament_size;
  if (!IsPowerOfTwo(tournament_size))
    spdlog::error("Tournament (eliminateWeak) size {} is not a power of 2!",
                  tournament_size);

  std::vector<std::vector<Chromosome>> tournaments;
  tournaments.reserve(tournament_count);

  for (int i = 0; i < tournament_count; i++) {
    std::vector<Chromosome> tr;
    tr.reserve(tournament_size);
    const auto start = generation.begin() + i * tournament_size;
    const auto end = start + tournament_size;
    std::ranges::copy(start, end, std::back_inserter(tr));
    tournaments.emplace_back(tr);
  }

  std::vector<Chromosome> winners;
  winners.resize(tournament_count);

  if (parallel) {
    parallelFor(tournament_count, [&](const size_t i) {
      const size_t res =
          playTournament(tournaments[i], 0, tournaments[i].size() - 1);
      winners[i] = Chromosome(tournaments[i][res]);
    });
  } else {
    for (int i = 0; i < tournament_count; i++) {
      const size_t res =
          playTournament(tournaments[i], 0, tournaments[i].size() - 1);
      winners[i] = Chromosome(tournaments[i][res]);
    }
  }

  return winners;
}

/* This func performs heuristic search for one chromosome */
void performSearch(Chromosome &chr) {
  std::vector<Move> moves = BuildAllMoves(chr.board);
  float best_score = -1;
  Move best_move = moves[0];
  while (moves.empty() == false) {
    for (const auto &m : moves) {
      if (auto mv_res = chr.board.move_peg(m); !mv_res.has_value())
        std::cout << mv_res.error().message();
      if (const float curr_score = evaluateHeuristics(chr.board);
          std::isgreater(curr_score, best_score)) {
        best_score = curr_score;
        best_move = m;
      }
      if (auto un_res = chr.board.undo_move(m); !un_res.has_value())
        std::cout << un_res.error().message();
    }
    if (auto best_res = chr.board.move_peg(best_move); !best_res.has_value())
      std::cout << best_res.error().message();
    moves.clear();
    moves = BuildAllMoves(chr.board);
    best_score = -1;
  }
  evaluatePosition(chr);
}

/* This func evals whole generation */
void evalOneGeneration(std::vector<Chromosome> &generation,
                       const bool parallel) {
  if (parallel) {
    parallelFor(generation.size(),
                [&](const size_t i) { performSearch(generation[i]); });
  } else {
    for (Chromosome &individual : generation) {
      performSearch(individual);
    }
  }
}