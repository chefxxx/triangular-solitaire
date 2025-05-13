//
// Created by Mateusz Mikiciuk on 09/04/2025.
//
#ifndef PEG_POSITION_H
#define PEG_POSITION_H

#include <map>
#include <ostream>

enum class peg_position : int {
#define DECLARE_PEG_POS(col, col_offset)                                       \
  col##1 = col_offset + 56, col##2 = col_offset + 48,                          \
  col##3 = col_offset + 40, col##4 = col_offset + 32,                          \
  col##5 = col_offset + 24, col##6 = col_offset + 16, col##7 = col_offset + 8, \
  col##8 = col_offset
  DECLARE_PEG_POS(a, 0),
  DECLARE_PEG_POS(b, 1),
  DECLARE_PEG_POS(c, 2),
  DECLARE_PEG_POS(d, 3),
  DECLARE_PEG_POS(e, 4),
  DECLARE_PEG_POS(f, 5),
  DECLARE_PEG_POS(g, 6),
  DECLARE_PEG_POS(h, 7),
#undef DECLARE_PEG_POS
};

inline std::ostream &operator<<(std::ostream &os, const peg_position &pos) {
  static const std::map<peg_position, std::string> peg_position_names = {
#define CREATE_MAP_TO_STRING(col)                                              \
  {peg_position::col##1, #col "1"}, {peg_position::col##2, #col "2"},          \
      {peg_position::col##3, #col "3"}, {peg_position::col##4, #col "4"},      \
      {peg_position::col##5, #col "5"}, {peg_position::col##6, #col "6"},      \
      {peg_position::col##7, #col "7"}, {peg_position::col##8, #col "8"}

      CREATE_MAP_TO_STRING(a), CREATE_MAP_TO_STRING(b), CREATE_MAP_TO_STRING(c),
      CREATE_MAP_TO_STRING(d), CREATE_MAP_TO_STRING(e), CREATE_MAP_TO_STRING(f),
      CREATE_MAP_TO_STRING(g), CREATE_MAP_TO_STRING(h),
#undef CREATE_MAP_TO_STRING
  };

  static const std::string unknown = "unknown";
  const auto it = peg_position_names.find(pos);
  it != peg_position_names.end() ? os << it->second : os << unknown;
  return os;
}

/* like vectors in linear algebra */
enum class jump_dir : int {
  INVALID = 0,
  NORTH = 16,
  SOUTH = -16,
  WEST = -2,
  EAST = 2,
  NORTH_WEST = 14,
  SOUTH_EAST = -14,
};

/* debugging utility */
inline std::ostream &operator<<(std::ostream &os, const jump_dir &dir) {
  switch (dir) {
  case jump_dir::NORTH:
    os << "NORTH";
    break;
  case jump_dir::SOUTH:
    os << "SOUTH";
    break;
  case jump_dir::WEST:
    os << "WEST";
    break;
  case jump_dir::EAST:
    os << "EAST";
    break;
  case jump_dir::NORTH_WEST:
    os << "NORTH_WEST";
    break;
  case jump_dir::SOUTH_EAST:
    os << "SOUTH_EAST";
    break;
  default:
    os << "INVALID";
    break;
  }
  return os;
}

inline peg_position IdxToPos(const int idx) {
  return static_cast<peg_position>(idx);
}
inline int peg_to_idx(const peg_position pos) { return static_cast<int>(pos); }
inline int dir_to_idx(const jump_dir dir) { return static_cast<int>(dir); }
inline jump_dir idx_to_dir(const int idx) { return static_cast<jump_dir>(idx); }

inline jump_dir calculate_jump_dir(const peg_position &from,
                                   const peg_position &to) {
  switch (int delta = peg_to_idx(to) - peg_to_idx(from)) {
  case 16:
    return jump_dir::NORTH;
  case -16:
    return jump_dir::SOUTH;
  case -2:
    return jump_dir::WEST;
  case 2:
    return jump_dir::EAST;
  case 14:
    return jump_dir::NORTH_WEST;
  case -14:
    return jump_dir::SOUTH_EAST;
  default:
    return jump_dir::INVALID;
  }
}

#endif // PEG_POSITION_H
