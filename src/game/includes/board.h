//
// Created by Mateusz Mikiciuk on 30/03/2025.
//

#ifndef TRIANGULARSOLITAIRE_BOARD_H
#define TRIANGULARSOLITAIRE_BOARD_H

#include <cstdint>
#include <tl/expected.hpp>
#include "board_error.h"
#include "move.h"
#include "peg_position.h"

constexpr int MAX_SIZE = 64;
constexpr int MAX_BOARD_SIDE = 8;

struct Move;

struct Board {
  // ------------------------------
  // Class creation
  // ------------------------------
  explicit Board(int size);
  ~Board() = default;

  // ------------------------------
  // Fields
  // ------------------------------
  int board_size;
  uint64_t board_area_mask;
  uint64_t current_state;
  uint64_t current_empty;
  int pegs_left;

  // ------------------------------
  // Basic functions
  // ------------------------------
  [[nodiscard]] tl::expected<jump_dir, board_error_info>
  move_peg(const peg_position &from, const peg_position &to);
  [[nodiscard]] tl::expected<jump_dir, board_error_info> move_peg(int from,
                                                                  int to);
  [[nodiscard]] tl::expected<jump_dir, board_error_info>
  move_peg(const Move &move);
  [[nodiscard]] tl::expected<void, board_error_info>
  undo_move(const peg_position &from, const peg_position &to,
            const jump_dir &dir);
  [[nodiscard]] tl::expected<void, board_error_info>
  undo_move(int from, int to, const jump_dir &dir);
  [[nodiscard]] tl::expected<void, board_error_info>
  undo_move(const Move &move);
  // ------------------------------
  // Useful helpers
  // ------------------------------
  void SetState(uint64_t state);
  [[nodiscard]] uint64_t generate_board() const;
  [[nodiscard]] uint64_t generate_start_state() const;
  [[nodiscard]] peg_position center_of_board() const;
};

// ------------------------------
// Helper functions
// ------------------------------
void print_current_board(const Board &board, std::ostream &os);
void perft(Board &board, bool debug);

#endif // TRIANGULARSOLITAIRE_BOARD_H
