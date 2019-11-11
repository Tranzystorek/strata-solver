#ifndef STRATA_SOLVER_SOLVER_HPP
#define STRATA_SOLVER_SOLVER_HPP

#include <valarray>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <utility>

#include "Move.hpp"
#include "Solution.hpp"
#include "Map.hpp"

class Solver {
public:
    using Revertible = std::pair<Move, std::valarray<size_t>>;
    using Sequence = std::deque<Move>;

public:
    std::vector<Solution> solve(Map& map);

private:
    void initializeSearchspace(const Map& map);
    Solution makeSolution(const Map& map,
                          Sequence& solution);
    void revertMoves(Map& map);

private:
    std::queue<Sequence> mSearchspace;
    std::stack<Revertible> mRevertor;
    std::vector<bool> mUnused;
};

#endif //STRATA_SOLVER_SOLVER_HPP
