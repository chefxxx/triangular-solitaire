//
// Created by Mykhailo_Shamrai on 09.05.2025.
//

#ifndef DISTANCE_TO_CENTER_H
#define DISTANCE_TO_CENTER_H

struct DistanceToCenterHeuristic
{
    static int get_distance(uint64_t peg_pos, uint64_t center, int width);
    int operator()(const Board& b) const;
};

#endif //DISTANCE_TO_CENTER_H
