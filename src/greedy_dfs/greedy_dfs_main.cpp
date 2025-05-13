//
// Created by Mykhailo_Shamrai on 12.05.2025.
//
#include <iostream>
#include <heuristic.h>
#include <isolated_pegs.h>
#include <number_of_free_positions.h>
#include <number_of_new_moves.h>
#include <distance_to_center.h>
#include <board.h>
#include <memory>
#include <move.h>
#include <alg_node.h>
#include <float.h>
#include <queue>
#include <unordered_set>

int usage(const std::string &pname) {
    std::cout
        << "Usage: " << pname
        << " [board size] " << "[3 fp values in [0, 1] range]"
        << std::endl;
    return 1;
}

void revert_moves(const std::shared_ptr<AlgNode>& nodeSptr) {
    auto tmpPointer = nodeSptr;
    std::vector<Move> moves{};
    while (tmpPointer->parent != nullptr) {
        auto tmp_move = tmpPointer->move;
        moves.push_back(tmp_move);
        tmpPointer = tmpPointer->parent;
    }
    Board tmp = Board(tmpPointer->board.board_size);
    print_current_board(tmp, std::cout);
    std::ranges::reverse(moves);
    for (auto move: moves) {
        const auto res = tmp.move_peg(move);
        if (!res.has_value())
            std::cerr << res.error().message() << "\n";
        print_current_board(tmp, std::cout);
        std::cout << "Move with parameters: dir:" << move.dir
                  << ", from: " << move.from << ", to: " << move.to << "\n";
    }
}

int main(const int argc, const char *argv[]) {
    if (argc != 5)
        return usage(argv[0]);

    /* Read arguments */
    int boardSize = std::stoi(argv[1]);
    auto weights = std::make_tuple(1.0, std::stod(argv[2]),
                                                        std::stod(argv[3]),
                                                        std::stod(argv[4]));

    /* Init heuristics */
    NumberOfFreePositions number_of_free_positions_heuristic{};
    DistanceToCenterHeuristic dist_to_center_heuristic{};
    IsolatedPegs isolated_pegs_heuristic{};
    NumberOfNewMoves number_of_new_moves_heuristic{};

    /* Heuristic struct initialisation */
    Heuristics heuristics{number_of_free_positions_heuristic,
                            dist_to_center_heuristic,
                            isolated_pegs_heuristic,
                            number_of_new_moves_heuristic};

    Board main_board = Board(boardSize);
    /* Initialisation of priority queue */
    std::priority_queue<std::shared_ptr<AlgNode>, std::vector<std::shared_ptr<AlgNode>>, AlgNodeComparator> pq{};
    pq.emplace(std::make_shared<AlgNode>(nullptr, main_board, DBL_MAX, Move{-1, -1, jump_dir::EAST}));
    std::vector<Move> moves_to_win{};

    /* Unordered set for already visited positions*/
    std::unordered_set<uint64_t> visited_boards;
    visited_boards.insert(main_board.current_state);

    /* Main part of algorithm */
    Board tmp_board = main_board;
    std::vector<Move> moves{};
    while (!pq.empty())
    {
        auto node = pq.top();
        pq.pop();
        if (node->board.pegs_left == 1) {
            // Revert path from start to end
            revert_moves(node);
            break;
        }
        tmp_board = node->board;
        moves = BuildAllMoves(node->board);
        for (auto move : moves)
        {
            auto res_of_move = tmp_board.move_peg(move);
            assert(res_of_move.has_value());
            if (!visited_boards.contains(tmp_board.current_state))
            {
                visited_boards.insert(tmp_board.current_state);
                auto heuristic_value = heuristics.calculate_heuristics(tmp_board);
                auto norm = get_euclidian_norm(heuristic_value);
                auto normalised_values = std::apply([&norm](auto&&... elems) {
                    return std::make_tuple((static_cast<double>(elems) / norm)...);
                }, heuristic_value);

                auto priority = get_euclidian_norm(multiply_two_tuples(normalised_values, weights,
                    std::make_index_sequence<std::tuple_size_v<decltype(weights)>>()));
                assert(priority >= 0);
                pq.emplace(std::make_shared<AlgNode>(node, tmp_board, priority, move));
            }

            auto res_of_undo = tmp_board.undo_move(move);
            assert(res_of_undo.has_value());
        }
    }
    return 0;
}