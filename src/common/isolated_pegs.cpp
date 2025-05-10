//
// Created by Mykhailo_Shamrai on 10.05.2025.
//

#include <bit_operations.h>
#include "isolated_pegs.h"


uint64_t IsolatedPegs::find_neighbours(int index, const Board &board) {
  const uint64_t current_peg = MinMsb << index;

  const uint64_t current = board.current_state;
  const uint64_t area = board.board_area_mask;

  const uint64_t north = shiftNorth(current_peg) & area & current;
  const uint64_t south = shiftSouth(current_peg) & area & current;
  const uint64_t west = shiftWest(current_peg & notA_Files) & area & current;
  const uint64_t east = shiftEast(current_peg & notH_Files) & area & current;
  const uint64_t northWest =
      shiftNorthWest(current_peg & notA_Files) & area & current;
  const uint64_t southEast =
      shiftSouthEast(current_peg & notH_Files) & area & current;

  return north | south | east | west | northWest | southEast;
}

int IsolatedPegs::operator()(const Board &board) const {
  int sum = 0;
  uint64_t current_state = board.current_state;
  while (current_state) {
    int index = PopLsb(current_state);
    sum += find_neighbours(index, board) > 0 ? 1 : 0;
  }
  return sum;
}
