//
// Created by marcin on 11.11.2019.
//

#ifndef STRATA_SOLVER_MOVE_HPP
#define STRATA_SOLVER_MOVE_HPP

#include <cstddef>
#include "Color.hpp"

struct Move {
    Move(std::size_t row, Color color);

    std::size_t row;
    Color color;
};

#endif //STRATA_SOLVER_MOVE_HPP
