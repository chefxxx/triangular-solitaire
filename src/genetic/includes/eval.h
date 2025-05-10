//
// Created by Mateusz Mikiciuk on 08/05/2025.
//

#ifndef EVAL_H
#define EVAL_H

#include <vector>
#include "chromosome.h"
#include "move.h"

float evaluateHeuristics(const Board &b);
std::vector<chromosome> crossAndMutate(std::vector<chromosome> &population, int mutSize, float mutStrength);
std::vector<chromosome> makeBabies(std::vector<chromosome> &parents);
void mutate(std::vector<chromosome> &population, int mutSize, float mutStrength);
std::vector<chromosome> eliminateWeak(std::vector<chromosome> &generation, int , bool parallel = true);
void evaluatePosition(chromosome &individual);
void performSearch(chromosome &chr);
void evalOneGeneration(std::vector<chromosome> &generation, bool parallel = true);
size_t playTournament(const std::vector<chromosome> &players, size_t start, size_t end);

#endif //EVAL_H
