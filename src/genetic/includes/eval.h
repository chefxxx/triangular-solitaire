//
// Created by Mateusz Mikiciuk on 08/05/2025.
//

#ifndef EVAL_H
#define EVAL_H

#include <vector>
#include "chromosome.h"
#include "move.h"

float evaluateHeuristics(const Board &b);
void evaluatePosition(chromosome &individual);
void crossAndMutate(std::vector<chromosome> &population);
size_t playTournament(const std::vector<chromosome> &players, size_t start, size_t end);
std::vector<chromosome> eliminateWeak(std::vector<chromosome> &generation, int , bool parallel = true);
void performSearch(chromosome &chr);
void evalOneGeneration(std::vector<chromosome> &generation, bool parallel = true);

#endif //EVAL_H
