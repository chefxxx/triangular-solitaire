//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#include <iostream>
#include <sstream>
#include <bitset>
#include <algorithm>
#include "board.h"

#include <stack>
#include <tuple>
#include <unordered_set>

#include "bit_operations.h"
#include "move.h"

Board::Board(const int size)
    : board_size{size},
      board_area_mask{generate_board()},
      current_state{ClearIntersect(board_area_mask, generate_start_state())},
      current_empty{ClearIntersect(board_area_mask, current_state)},
      pegs_left{CountOnes(current_state)}
{}

void Board::SetState(const uint64_t state)
{
    current_state = state;
    current_empty = ClearIntersect(board_area_mask, current_state);
    pegs_left = CountOnes(current_state);
}

uint64_t Board::generate_start_state() const
{
    uint64_t state = MinMsb;
    switch (board_size)
    {
        case 6: case 8:
            state <<= peg_to_idx(peg_position::c5);
        break;
        case 7:
            state <<= peg_to_idx(peg_position::a3);
        break;
        default:
            state <<= peg_to_idx(peg_position::a1);
    }
    return state;
}

peg_position Board::center_of_board() const
{
    peg_position center = peg_position::c3;
    switch (board_size)
    {
        case 5: case 6:
            center = peg_position::b2;
            break;
        case 7: case 8:
            center = peg_position::c3;
            break;
        default:
            center = peg_position::c3;
    }
    return center;
}

tl::expected<jump_dir, board_error_info> Board::move_peg(const peg_position &from, const peg_position &to)
{
    if (!CheckBitAtIdx(board_area_mask, peg_to_idx(from)))
        return tl::unexpected{board_error_info(board_error::out_of_bound, from, to)};
    if (!CheckBitAtIdx(board_area_mask, peg_to_idx(to)))
        return tl::unexpected{board_error_info(board_error::out_of_bound, from, to)};
    if (!CheckBitAtIdx(current_state, peg_to_idx(from)))
        return tl::unexpected{board_error_info(board_error::peg_does_not_exist, from, to)};
    if (CheckBitAtIdx(current_state, peg_to_idx(to)))
        return tl::unexpected{board_error_info(board_error::invalid_jump, from, to)};

    const jump_dir dir = calculate_jump_dir(from, to);
    if (dir == jump_dir::INVALID)
        return tl::unexpected{board_error_info(board_error::invalid_jump, from, to)};

    const int erase_idx = peg_to_idx(from) + (dir_to_idx(dir) >> 1);
    if (!CheckBitAtIdx(current_state, erase_idx))
        return tl::unexpected{board_error_info(board_error::invalid_jump, from, to)};

    const uint64_t erase = MinMsb << erase_idx | MinMsb << peg_to_idx(from);
    current_state = ClearIntersect(current_state,erase);
    current_state |= MinMsb << peg_to_idx(to);

    current_empty = ClearIntersect(board_area_mask, current_state);
    --this->pegs_left;
    return{dir};
}

tl::expected<jump_dir, board_error_info> Board::move_peg(const int from, const int to)
{
    const peg_position p_from{from};
    const peg_position p_to{to};
    return move_peg(p_from, p_to);
}

tl::expected<jump_dir, board_error_info> Board::move_peg(const Move &move)
{
    const peg_position from{move.from};
    const peg_position to{move.to};
    const jump_dir dir{move.dir};

    if (!CheckBitAtIdx(board_area_mask, peg_to_idx(from)))
        return tl::unexpected{board_error_info(board_error::out_of_bound, from, to)};
    if (!CheckBitAtIdx(board_area_mask, peg_to_idx(to)))
        return tl::unexpected{board_error_info(board_error::out_of_bound, from, to)};
    if (!CheckBitAtIdx(current_state, peg_to_idx(from)))
        return tl::unexpected{board_error_info(board_error::peg_does_not_exist, from, to)};
    if (CheckBitAtIdx(current_state, peg_to_idx(to)))
        return tl::unexpected{board_error_info(board_error::invalid_jump, from, to)};

    const int erase_idx = peg_to_idx(from) + (dir_to_idx(dir) >> 1);
    if (!CheckBitAtIdx(current_state, erase_idx))
        return tl::unexpected{board_error_info(board_error::invalid_jump, from, to)};

    const uint64_t erase = MinMsb << erase_idx | MinMsb << peg_to_idx(from);
    current_state = ClearIntersect(current_state,erase);
    current_state |= MinMsb << peg_to_idx(to);

    current_empty = ClearIntersect(board_area_mask, current_state);
    --this->pegs_left;
    return{dir};
}

tl::expected<void, board_error_info> Board::undo_move(const peg_position &from, const peg_position &to, const jump_dir &dir) {
    // Same checks as in move_peg function, but in reversed order, now it's necessary that from is free
    // and to is occupied
    if (!CheckBitAtIdx(board_area_mask, peg_to_idx(from)))
        return tl::unexpected{board_error_info(board_error::out_of_bound, from, to)};
    if (!CheckBitAtIdx(board_area_mask, peg_to_idx(to)))
        return tl::unexpected{board_error_info(board_error::out_of_bound, from, to)};
    if (CheckBitAtIdx(current_state, peg_to_idx(from)))
        return tl::unexpected{board_error_info(board_error::invalid_jump, from, to)};
    if (!CheckBitAtIdx(current_state, peg_to_idx(to)))
        return tl::unexpected{board_error_info(board_error::peg_does_not_exist, from, to)};

    const int add_idx = peg_to_idx(from) + (dir_to_idx(dir) >> 1);
    if (CheckBitAtIdx(current_state, add_idx))
        return tl::unexpected{board_error_info(board_error::invalid_jump, from, to)};

    const uint64_t add = MinMsb << add_idx | MinMsb << peg_to_idx(from);
    current_state |= add;
    current_state = ClearIntersect(current_state, MinMsb << peg_to_idx(to));

    current_empty = ClearIntersect(board_area_mask, current_state);
    ++this->pegs_left;
    return {};
}

tl::expected<void, board_error_info> Board::undo_move(int from, int to, const jump_dir &dir)
{
    const peg_position p_from{from};
    const peg_position p_to{to};
    return undo_move(p_from, p_to, dir);
}

tl::expected<void, board_error_info> Board::undo_move(const Move &move)
{
    return undo_move(move.from, move.to, move.dir);
}

uint64_t Board::generate_board() const
{
    uint64_t mask = MinMsb << (MAX_SIZE - BOARD_SIDE);
    for (int i = 0; i < board_size - 1; ++i)
    {
        mask = mask | mask >> 7 | mask >> BOARD_SIDE;
    }
    return mask;
}

void print_current_board(const Board &board)
{
    std::cout << "*---CURRENT BOARD---*\n";
    std::cout << "*--a-b-c-d-e-f-g-h--*\n";
    const std::bitset<MAX_SIZE> bin_rep(board.current_state);
    const auto bin_num = bin_rep.to_string();
    std::vector<std::string> tmp;
    tmp.reserve(BOARD_SIDE);
    for (int i = 0; i < BOARD_SIDE; ++i)
    {
        tmp.push_back(bin_num.substr(i * BOARD_SIDE, BOARD_SIDE));
        std::ranges::reverse(tmp[i]);
    }
    int level = 1;
    for (int j = 0; j < board.board_size; ++j)
    {
        const auto& str = tmp[j];
        std::cout << level <<"| ";
        for (int i = 0; i < BOARD_SIDE; ++i) {
            if (i < level)
                std::cout << str[i] << " ";
            else
                std::cout << "  ";
        }
        std::cout << "|" << level++ << "\n";
    }
    std::cout << "*--a-b-c-d-e-f-g-h--*\n";
    std::cout << "*-------------------*\n";
}

void perft(Board& board, bool debug)
{
    std::unordered_set<uint64_t> visited_boards;
    std::stack<std::tuple<Move, bool>> moves_stack{};
    auto moves = BuildAllMoves(board);
    for (const auto& m : moves)
        moves_stack.push(std::make_tuple(m, false));

    visited_boards.emplace(board.current_state);

    while (!moves_stack.empty())
    {
        print_current_board(board);
        if (debug)
            getchar();

        const auto [move, state] = moves_stack.top();
        moves_stack.pop();
        // If the move is made for the first time
        if (!state)
        {
            moves_stack.push(std::make_tuple(move, true));
            auto dir = board.move_peg(move);
            if (!dir.has_value())
                std::cout <<  dir.error().message() << " in move from " << move.from << "to "
                            << move.to <<"\n";
            else
                std::cout <<  "Move with parameters: dir:"<< move.dir << ", from: "
                << move.from << ", to: " << move.to << "\n";
            if (board.pegs_left == 1) {
                std::cout << "GRATS you win" << "\n";
                break;
            }
            if (std::get<1>(visited_boards.emplace(board.current_state)))
            {
                moves = BuildAllMoves(board);
                for (const auto& m : moves)
                    moves_stack.push(std::make_tuple(m, false));
            }
            else
            {
                std::cout << "This position already was searched!" << "\n";
            }
        }
        else
        {
            auto exp = board.undo_move(move);
            if (!exp.has_value())
                std::cout << exp.error().message() << " in undo move from " << move.from << "to "
                            << move.to <<"\n";
            else
                std::cout << "Return to state before move from:" << move.from << " to " << move.to << "\n";
        }
    }
}
