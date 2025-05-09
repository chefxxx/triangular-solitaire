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
chromosome playTournament(std::vector<chromosome> &players);
std::vector<chromosome> eliminateWeak(std::vector<chromosome> &generation, int tournament_size);
void performSearch(chromosome &chr);
void evalSimple(std::vector<chromosome> &population);
void evalOneGeneration(std::vector<chromosome> &generation);

#endif //EVAL_H
