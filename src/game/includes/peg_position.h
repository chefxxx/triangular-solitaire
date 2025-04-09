//
// Created by Mateusz Mikiciuk on 09/04/2025.
//

#ifndef PEG_POSITION_H
#define PEG_POSITION_H

enum class peg_position : int
{
#define DECLARE_PEG_POS(col, col_offset) \
col##1 = col_offset + 56, col##2 = col_offset + 48, col##3 = col_offset + 40, col##4 = col_offset + 32, \
col##5 = col_offset + 24, col##6 = col_offset + 16, col##7 = col_offset + 8, col##8 = col_offset
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

constexpr int peg_to_idx(const peg_position &pos) { return static_cast<int>(pos); }

#endif //PEG_POSITION_H
