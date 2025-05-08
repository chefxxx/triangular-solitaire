//
// Created by Mateusz Mikiciuk on 08/05/2025.
//

#ifndef EVAL_H
#define EVAL_H

#include <vector>
#include <thread>
#include "chromosome.h"
#include "move.h"

inline float evaluateHeuristics(const Board& b)
{
    return 0;
}

inline void corssAndMutate(std::vector<chromosome>& population) {

}

inline std::vector<chromosome> eliminateWeak(std::vector<chromosome> &generation) {

}

/* This func performs heuristic search for one chromosome */
inline void performSearch(chromosome &chr)
{
    std::vector<Move> moves = BuildAllMoves(chr.board);
    float best_score = -1;
    Move best_move = moves[0];
    while (moves.empty() == false) {
        for (const auto& m : moves) {
            if (auto mv_res = chr.board.move_peg(m); !mv_res.has_value())
                std::cout << mv_res.error().message();
            if (const float curr_score = evaluateHeuristics(chr.board); std::isgreater(curr_score, best_score)) {
                best_score = curr_score;
                best_move = m;
            }
            if (auto un_res = chr.board.undo_move(m); !un_res.has_value())
                std::cout << un_res.error().message();
        }
        if (auto best_res = chr.board.move_peg(best_move); !best_res.has_value())
            std::cout << best_res.error().message();
        moves.clear();
        moves = BuildAllMoves(chr.board);
    }
}

/* This func evals whole generation */
inline void evalOneGeneration(std::vector<chromosome> &generation) {
    std::vector<std::thread> threads;
    threads.reserve(generation.size());
    for (chromosome &chr : generation) {
        threads.emplace_back([&chr] () {
          performSearch(chr);
        });
    }
    for (auto &thread : threads) {
        thread.join();
    }
}

#endif //EVAL_H
