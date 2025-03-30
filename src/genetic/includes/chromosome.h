//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#ifndef TRIANGULARSOLITAIRE_CHROMOSOME_H
#define TRIANGULARSOLITAIRE_CHROMOSOME_H

#include <vector>
#include "gene.h"

class chromsome
{
private:
    std::vector<gene> genes;
public:
    explicit chromsome(std::vector<double> const& weights);
};

#endif //TRIANGULARSOLITAIRE_CHROMOSOME_H
