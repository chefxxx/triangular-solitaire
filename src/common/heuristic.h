//
// Created by Mykhailo_Shamrai on 07.05.2025.
//

#ifndef HEURISTIC_H
#define HEURISTIC_H
#include <board.h>
#include <cstdint>
#include <concepts>

template<typename T>
concept Heuristic = requires(T t, const Board& b)
{
    { t(b) } -> std::convertible_to<int>;
};

#endif //HEURISTIC_H
