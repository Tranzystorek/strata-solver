//
// Created by marcin on 11.11.2019.
//

#include "Solution.hpp"

#include <sstream>

#include "Color.hpp"

Solution::Solution(const std::vector<size_t>& unused, const std::vector<Move>& moves) : mUnusedRows(unused), mMoves(moves) {
}

std::string Solution::toString() const {
    std::ostringstream output;

    output << "ROWS ( ";
    for (auto row : mUnusedRows) {
        output << row << ' ';
    }

    output << "), COLOR *\n";

    for (auto move : mMoves) {
        output << "ROW " << move.row
               << ", COLOR " << colorToString(move.color)
               << '\n';
    }

    return output.str();
}
