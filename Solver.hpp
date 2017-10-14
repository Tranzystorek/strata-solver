#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "StrataMap.hpp"

#include <vector>
#include <queue>
#include <stack>
#include <utility>

struct Move {
  Move(int, Color);

  int row;
  Color color;
};

class Solver {
public:
  using Revertible = std::pair<Move, std::vector<int>>;
  using Sequence = std::stack<Move>;

public:
  void solve(StrataMap&);

private:
  std::queue<Sequence> searchspace_;
  std::stack<Revertible> revertor_;
};

#endif //SOLVER_HPP
