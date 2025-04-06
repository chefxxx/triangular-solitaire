//
// Created by Mateusz Mikiciuk on 06/04/2025.
//

#ifndef TRIANGULARSOLITAIRE_PEG_H
#define TRIANGULARSOLITAIRE_PEG_H

#include <cstdint>
#include "bit_operations.h"

// BoardPositions define bitshift of a MinMsb value, by which we have to shift it
// to retrieve whether field on the board is occupied or not.
enum class peg_position : int
{
    // First column
    a1 = 63,
    a2 = 55,
    a3 = 47,
    a4 = 39,
    a5 = 31,
    a6 = 23,
    a7 = 15,
    a8 = 7,
    // Second column
    b1 = 62,
    b2 = 54,
    b3 = 46,
    b4 = 38,
    b5 = 30,
    b6 = 22,
    b7 = 14,
    b8 = 6,
    // Third column
    c1 = 61,
    c2 = 53,
    c3 = 45,
    c4 = 37,
    c5 = 29,
    c6 = 21,
    c7 = 13,
    c8 = 5,
    // Fourth column
    d1 = 60,
    d2 = 52,
    d3 = 44,
    d4 = 36,
    d5 = 28,
    d6 = 20,
    d7 = 12,
    d8 = 4,
    // Fifth column
    e1 = 59,
    e2 = 51,
    e3 = 43,
    e4 = 35,
    e5 = 27,
    e6 = 19,
    e7 = 11,
    e8 = 3,
    // Sixth column
    f1 = 58,
    f2 = 50,
    f3 = 42,
    f4 = 34,
    f5 = 26,
    f6 = 18,
    f7 = 10,
    f8 = 2,
    // Seventh column
    g1 = 57,
    g2 = 49,
    g3 = 41,
    g4 = 33,
    g5 = 25,
    g6 = 17,
    g7 = 9,
    g8 = 1,
    // Eighth column
    h1 = 56,
    h2 = 48,
    h3 = 40,
    h4 = 32,
    h5 = 24,
    h6 = 16,
    h7 = 8,
    h8 = 0,
};

struct peg
{
    // ------------------------------
    // Class creation
    // ------------------------------
    constexpr explicit peg(peg_position p) : pos{p} {};

    // ------------------------------
    // Fields
    // ------------------------------
    peg_position pos;

    // ------------------------------
    // Peg functionalities
    // ------------------------------
    [[nodiscard("Returns index of peg position in a unit64_t.")]] constexpr int index() const { return static_cast<int>(pos); }

    [[nodiscard("Returns mask for check if peg is at index().")]] constexpr uint64_t mask() const { return MinMsb << index(); }

    [[nodiscard]] constexpr bool is_peg_on(uint64_t board) const { return board & mask(); }
};

#endif //TRIANGULARSOLITAIRE_PEG_H
