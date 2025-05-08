//
// Created by Mykhailo_Shamrai on 07.05.2025.
//

#ifndef HEURISTIC_H
#define HEURISTIC_H
#include <board.h>
#include <concepts>

template<typename T>
concept Heuristic = requires(T t, const Board& b)
{
    { t(b) } -> std::convertible_to<int>;
};

template<Heuristic... Hs>
struct Heuristics
{
    // ------------------------------
    // Class creation
    // ------------------------------
    explicit Heuristics(Hs... heuristics): heuristic_functions(std::make_tuple(std::move(heuristics)...)) {};
    ~Heuristics() = default;

    // ------------------------------
    // Basic functions
    // ------------------------------
    auto calculate_heuristics(const Board& b)
    {
        return std::apply
        ([&b](auto&&... hs)
            {
                return std::make_tuple(hs(b)...);
            }, heuristic_functions
        );
    }
    private:
    std::tuple<Hs...> heuristic_functions;
};


#endif //HEURISTIC_H
