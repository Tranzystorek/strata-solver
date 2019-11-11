#include "Solver.hpp"

#include <iostream>

#include "Color.hpp"

void Solver::initializeSearchspace(const Map& map) {
    const size_t nRibbons = map.getRibbonNumber();
    for (size_t i=0; i < nRibbons; ++i) {
        const Color rowColor = map.checkMonocolor(i);
        if (rowColor != Color::NONE) {
            Sequence s;
            s.push_back(Move(i, rowColor));

            mSearchspace.push(s);
        }
    }//for
}

Solution Solver::makeSolution(const Map& map,
                              Sequence& solution) {
    std::vector<size_t> unusedRows; unusedRows.reserve(mUnused.size());
    size_t pos = 0;
    for (auto b : mUnused) {
        if(b)
            unusedRows.push_back(pos);

        ++pos;
    }

    std::vector<Move> moves; moves.reserve(solution.size());
    while (!solution.empty()) {
        Move move = solution.back();
        moves.push_back(move);
        solution.pop_back();
    }

    return Solution(unusedRows, moves);
}

void Solver::revertMoves(Map& map) {
    while (!mRevertor.empty()) {
        const Revertible& r = mRevertor.top();
        const Move& move = r.first;
        map.restoreColor(r.second, move.color);
        mUnused[move.row] = true;

        mRevertor.pop();
    }
}

std::vector<Solution> Solver::solve(Map& map) {
    const size_t nRibbons = map.getRibbonNumber();
    mUnused.resize(nRibbons);
    std::fill(std::begin(mUnused), std::end(mUnused), true);

    // initialize searchspace
    initializeSearchspace(map);

    // procedurally search for possible moves
    std::vector<Solution> solutions;
    while (!mSearchspace.empty()) {
        Sequence& sequence = mSearchspace.front();
        Sequence next = sequence;

        while (!sequence.empty()) {
            const Move& move = sequence.front();

            mUnused[move.row] = false;
            mRevertor.emplace(move, map.removeColor(move.row));

            sequence.pop_front();
        } // while

        // on finding a solution - add to collection
        if (map.isUncolored()) {
            Solution solution = makeSolution(map, next);
            solutions.push_back(solution);
        } else {
            next.emplace_back(0, Color::NONE);
            Move& m = next.back();

            for (size_t i=0; i < nRibbons; ++i) {
                const Color ribbonColor = map.checkMonocolor(i);

                if(ribbonColor != Color::NONE) {
                    m.row = i;
                    m.color = ribbonColor;

                    mSearchspace.push(next);
                }
            } // for
        }

        // revert performed moves
        if (mSearchspace.size() > 1)
            revertMoves(map);

        mSearchspace.pop();
    } // while

    return solutions;
}
