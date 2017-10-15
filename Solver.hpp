#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "StrataMap.hpp"

#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <utility>

struct Move {
  Move(int, Color);

  int row;
  Color color;
};

class Solver {
public:
  using Revertible = std::pair<Move, std::vector<int>>;
  using Sequence = std::deque<Move>;

public:
  void solve(StrataMap&);

private:
  void init_searchspace(const StrataMap&);
  void print_solution(const StrataMap& map,
                      Sequence& solution,
                      const std::set<int>& unused);
  void revert_moves(StrataMap&,
                    std::set<int>&);

private:
  std::queue<Sequence> searchspace_;
  std::stack<Revertible> revertor_;
};

#endif //SOLVER_HPP
