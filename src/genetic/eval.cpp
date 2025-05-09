//
// Created by Mateusz Mikiciuk on 09/05/2025.
//

#include <vector>
#include <thread>
#include <spdlog/spdlog.h>
#include "threading.h"
#include "chromosome.h"
#include "move.h"
#include "bit_operations.h"
#include "eval.h"

float evaluateHeuristics(const Board& b)
{
    return static_cast<float>(std::rand() % 100);
}

// TODO: define real evaluation function
void evaluatePosition(chromosome &individual) {
    individual.score = static_cast<float>(individual.board.pegs_left);
}

void crossAndMutate(std::vector<chromosome> &population) {

}

chromosome playTournament(std::vector<chromosome> &players) {
    if (!IsPowerOfTwo(players.size()))
        spdlog::error("Tournament size {} is not a power of 2!", players.size());
    if (players.size() == 2)
        return std::isgreater(players[0].score, players[1].score) ? players[0] : players[1];

    /* init variables */
    std::vector<chromosome> pool1;
    std::vector<chromosome> pool2;
    const auto start = players.begin();
    const auto end = players.end();
    const auto mid = start + (end - start) / 2;

    /**/
    std::ranges::copy(start, mid, std::back_inserter(pool1));
    std::ranges::copy(mid, end, std::back_inserter(pool2));

    auto p1 = playTournament(pool1);
    auto p2 = playTournament(pool2);
    return std::isgreater(p1.score, p2.score) ? std::move(p1) : std::move(p2);
}

std::vector<chromosome> eliminateWeak(std::vector<chromosome> &generation, const int tournament_size, bool parallel) {
    const size_t tournament_count = generation.size() / tournament_size;
    if (!IsPowerOfTwo(tournament_size))
        spdlog::error("Tournament size {} is not a power of 2!", tournament_size);

    std::vector<std::vector<chromosome>> tournaments;
    tournaments.reserve(tournament_count);

    for (int i = 0; i < tournament_count; i++) {
        std::vector<chromosome> tr;
        tr.reserve(tournament_size);
        const auto start = generation.begin() + i * tournament_size;
        const auto end = start + tournament_size;
        std::ranges::copy(start, end, std::back_inserter(tr));
        tournaments.emplace_back(std::move(tr));
    }

    std::vector<chromosome> winners;
    winners.reserve(tournament_count);

    if (parallel) {
        parallelFor(tournament_count, [&](const size_t i) {
            winners[i] = playTournament(tournaments[i]);
        });
    }
    else {
        for (int i =0; i < tournament_count; i++) {
            winners[i] = playTournament(tournaments[i]);
        }
    }

    return winners;
}

/* This func performs heuristic search for one chromosome */
void performSearch(chromosome &chr)
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
        best_score = -1;
    }
    evaluatePosition(chr);
}

/* This func evals whole generation */
void evalOneGeneration(std::vector<chromosome> &generation, const bool threads) {
    if (threads) {
        parallelFor(generation.size(), [&](const size_t i) {
           performSearch(generation[i]);
        });
    }
    else {
        for (chromosome &individual: generation) {
            performSearch(individual);
        }
    }
}