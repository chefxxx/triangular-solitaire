//
// Created by Mateusz Mikiciuk on 09/04/2025.
//

#ifndef BOARD_ERROR_H
#define BOARD_ERROR_H

#include <ostream>

enum class board_error
{
    peg_does_not_exist,
    position_is_occupied,
    invalid_jump,
    out_of_bound
};

inline std::ostream& operator<<(std::ostream& os, const board_error& err)
{
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

#endif //BOARD_ERROR_H
