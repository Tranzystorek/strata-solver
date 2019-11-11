//
// Created by marcin on 11.11.2019.
//

#ifndef STRATA_SOLVER_COLORCHECKER_HPP
#define STRATA_SOLVER_COLORCHECKER_HPP

#include "Color.hpp"

class ColorChecker {
public:
    ColorChecker();

    bool operator()(Color color);

    Color getColor() const;

private:
    Color currentColor;
};


#endif //STRATA_SOLVER_COLORCHECKER_HPP
