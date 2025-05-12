//
// Created by Mateusz Mikiciuk on 08/05/2025.
//

#ifndef EVAL_H
#define EVAL_H

#include <vector>
#include "chromosome.h"
#include "move.h"

float evaluateHeuristics(const Board &b);
std::vector<Chromosome> crossAndMutate(std::vector<Chromosome> &population,
                                       int mutSize, float mutStrength);
std::vector<Chromosome> makeBabies(std::vector<Chromosome> &parents);
void mutate(std::vector<Chromosome> &population, int mutSize,
            float mutStrength);
std::vector<Chromosome> eliminateWeak(std::vector<Chromosome> &generation, int,
                                      bool parallel = true);
void evaluatePosition(Chromosome &individual);
void performSearch(Chromosome &chr);
void evalOneGeneration(std::vector<Chromosome> &generation,
                       bool parallel = true);
size_t playTournament(const std::vector<Chromosome> &players, size_t start,
                      size_t end);

#endif // EVAL_H
