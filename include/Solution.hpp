//
// Created by marcin on 11.11.2019.
//

#ifndef STRATA_SOLVER_SOLUTION_HPP
#define STRATA_SOLVER_SOLUTION_HPP

#include <string>
#include <vector>

#include "Move.hpp"

class Solution {
public:
    Solution(const std::vector<size_t>& unused, const std::vector<Move>& moves);

    std::string toString() const;

private:
    std::vector<size_t> mUnusedRows;
    std::vector<Move> mMoves;
};


#endif //STRATA_SOLVER_SOLUTION_HPP
