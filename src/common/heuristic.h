//
// Created by Mykhailo_Shamrai on 07.05.2025.
//

#ifndef HEURISTIC_H
#define HEURISTIC_H
#include <complex>
#include <../includes/board.h>
#include <concepts>

constexpr int HEURISTIC_COUNT = 4;

template<typename T>
concept Heuristic = requires(T t, const Board& b)
{
    { t(b) } -> std::convertible_to<int>;
};

// ------------------------------
// Helper functions
// ------------------------------
template<std::size_t... Is, typename... A, typename... B>
requires ((std::convertible_to<A, double> && ...)
    && (std::convertible_to<B, double> && ...)
    && (sizeof...(A) == sizeof...(B)))
static auto multiply_two_tuples(const std::tuple<A...>& a, const std::tuple<B...>& b, std::index_sequence<Is...>)
{
    return std::make_tuple((std::get<Is>(a) * std::get<Is>(b))...);
}

template<typename... TupleArgs>
requires (std::convertible_to<TupleArgs, double> && ...)
static double get_sum_of_tuple_elements(const std::tuple<TupleArgs...>& tuple)
{
    return std::apply([](auto&& ... args)
    {
        return (0.0 + ... + static_cast<double>(args));
    }, tuple);
}

template<typename... TupleArgs>
requires (std::convertible_to<TupleArgs, double> && ...)
static double get_euclidian_norm(const std::tuple<TupleArgs...>& tuple)
{
    return std::apply([](auto&& ... args)
    {
        return std::sqrt((0.0 + ... + (static_cast<double>(args) * static_cast<double>(args))));
    }, tuple);
}

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

    template<typename... Weights, typename... Values>
    requires ((std::convertible_to<Weights, double> && ...)
        && (std::convertible_to<Values, double> && ...)
        && (sizeof...(Weights) == sizeof...(Values)))
    auto multiply_with_weights(const std::tuple<Weights...>& weights, const std::tuple<Values...>& values)
    {
        return multiply_two_tuples(weights, values, std::index_sequence_for<Weights...>{});
    }

    template<typename... Weights>
    requires (std::convertible_to<Weights, double> && ... && (sizeof...(Weights) == sizeof...(Hs)))
    auto multiply_with_weights(const std::tuple<Weights...>& weights, const Board& b)
    {
        auto values = calculate_heuristics(b);
        return multiply_two_tuples(weights, values, std::index_sequence_for<Weights...>{});
    }

    private:
    std::tuple<Hs...> heuristic_functions;
};
#endif //HEURISTIC_H
