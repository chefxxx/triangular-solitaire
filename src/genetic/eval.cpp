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

size_t playTournament(const std::vector<chromosome> &players, const size_t start, const size_t end) {
    if (!IsPowerOfTwo(end - start + 1))
        spdlog::error("Tournament size {} is not a power of 2!", end - start + 1);
    if (end - start == 1)
        return std::isless(players[start].score, players[end].score) ? start : end;

    const size_t mid = start + (end - start) / 2;
    const size_t winner1 = playTournament(players, start, mid);
    const size_t winner2 = playTournament(players, mid + 1, end);

    return std::isless(players[winner1].score, players[winner2].score) ? winner1 : winner2;
}

std::vector<chromosome> eliminateWeak(std::vector<chromosome> &generation, const int tournament_size, const bool parallel) {
    const size_t tournament_count = generation.size() / tournament_size;
    if (!IsPowerOfTwo(tournament_size))
        spdlog::error("Tournament (eliminateWeak) size {} is not a power of 2!", tournament_size);

    std::vector<std::vector<chromosome>> tournaments;
    tournaments.reserve(tournament_count);

    for (int i = 0; i < tournament_count; i++) {
        std::vector<chromosome> tr;
        tr.reserve(tournament_size);
        const auto start = generation.begin() + i * tournament_size;
        const auto end = start + tournament_size;
        std::ranges::copy(start, end, std::back_inserter(tr));
        tournaments.emplace_back(tr);
    }

    std::vector<chromosome> winners;
    winners.resize(tournament_count);

    if (parallel) {
        parallelFor(tournament_count, [&](const size_t i) {
            const size_t res = playTournament(tournaments[i], 0, tournaments[i].size() - 1);
            winners[i] = chromosome(tournaments[i][res]);
        });
    }
    else {
        for (int i = 0; i < tournament_count; i++) {
            const size_t res = playTournament(tournaments[i], 0, tournaments[i].size() - 1);
            winners[i] = chromosome(tournaments[i][res]);
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
void evalOneGeneration(std::vector<chromosome> &generation, const bool parallel) {
    if (parallel) {
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