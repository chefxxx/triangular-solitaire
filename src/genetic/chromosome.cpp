//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#include "includes/chromosome.h"

chromsome::chromsome(std::vector<double> const& weights)
{
    for (auto const& w : weights)
    {
        gene g{w};
        this->genes.push_back(g);
    }
}
