//
// Created by Mateusz Mikiciuk on 09/04/2025.
//

#ifndef BOARD_ERROR_H
#define BOARD_ERROR_H

#include "peg_position.h"
#include <ostream>
#include <sstream>

enum class board_error {
  peg_does_not_exist,
  position_is_occupied,
  invalid_jump,
  out_of_bound
};

inline std::ostream &operator<<(std::ostream &os, const board_error &err) {
  switch (err) {
  case board_error::invalid_jump:
    os << "invalid_jump";
    break;
  case board_error::out_of_bound:
    os << "out_of_bound";
    break;
  case board_error::peg_does_not_exist:
    os << "peg_does_not_exist";
    break;
  case board_error::position_is_occupied:
    os << "position_is_occupied";
    break;
  default:
    os << "unknown error";
    break;
  }
  return os;
}

struct board_error_info {
  board_error error_code;
  peg_position from;
  peg_position to;

  board_error_info(const board_error &error_code, const peg_position &from,
                   const peg_position &to)
      : error_code{error_code}, from{from}, to{to} {}

  ~board_error_info() = default;

  [[nodiscard]] std::string message() const {
    std::ostringstream os;
    os << error_code;
    os << " from peg: " << peg_to_idx(from);
    os << " to peg: " << peg_to_idx(to) << "\n";
    return os.str();
  }
};

#endif // BOARD_ERROR_H
