//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#include <random>
#include <__random/random_device.h>
#include "includes/chromosome.h"

chromosome::chromosome(const int b_size) : board{b_size}
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0, 100);
    std::vector<float> weights;
    weights.reserve(HEURISTIC_COUNT);
    for (int i = 0; i < HEURISTIC_COUNT; i++) {
        weights.push_back(dist(rng));
    }
    const float sum = std::accumulate(weights.begin(), weights.end(), 0.0f);
    for (float &weight : weights) {
        weight /= sum;
        genes.emplace_back(weight);
    }
    score = -1;
}

chromosome::chromosome(const std::vector<gene> &genes, const int b_size): board(b_size) {
    this->genes = genes;
    this->score = 0.0f;
}


std::ostream & operator<<(std::ostream &os, const chromosome &chromosome) {
    int i = 1;
    for (const gene &g: chromosome.genes) {
        os << "H" << i++ << ": " << g.weight << " ";
    }
    return os;
}
