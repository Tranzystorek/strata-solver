#include "Solver.hpp"

#include <iostream>
#include <set>

Move::Move(int r, Color c)
  : row(r),
    color(c) {
}

void Solver::init_searchspace(const StrataMap& map) {
  int nrows = map.get_nrows();

  for(int i=0;i<nrows;++i) {
    const Color rcolor = map.check_monocolor(i);

    if(rcolor != Color::NONE) {
      Sequence s;
      s.push(Move(i, rcolor));

      searchspace_.push(s);
    }
  }//for
}

void Solver::print_solution(const StrataMap& map,
                            Sequence& solution,
                            const std::set<int>& unused) {
  if(!unused.empty()) {
    std::cout << "ROWS ( ";

    for(auto& r : unused)
      std::cout << r << " ";

    std::cout << "), COLOR *" << std::endl;
  }

  while(!solution.empty()) {
    const Move& m = solution.top();

    std::cout << "ROW " << map.human_readable_rownumber(m.row)
              << ", COLOR " << color_to_string(m.color)
              << std::endl;

    solution.pop();
  }

  std::cout << std::endl;
}

void Solver::revert_moves(StrataMap& map, std::set<int>& unused) {
  while(!revertor_.empty()) {
    const Revertible& r = revertor_.top();
    const Move& m = r.first;
    map.restore_row(m.row, m.color, r.second);
    unused.insert(map.human_readable_rownumber(m.row));

    revertor_.pop();
  }//while
}

void Solver::solve(StrataMap& map) {
  int nrows = map.get_nrows();
  int solution_number = 0;

  std::set<int> unused_rows;

  for(int i=0;i<nrows;++i)
    unused_rows.insert(i);

  //initialize searchspace
  init_searchspace(map);

  //procedurally search for possible moves
  while(!searchspace_.empty()) {
    Sequence& s = searchspace_.front();
    Sequence next = s;

    while(!s.empty()) {
      Move m = s.top();
      s.pop();

      unused_rows.erase(map.human_readable_rownumber(m.row));

      revertor_.push(std::make_pair(m,
                                    map.remove_row(m.row)));
    }//while

    //on finding a solution - print
    if(map.is_empty()) {
      std::cout << "SOLUTION " << ++solution_number << std::endl;
      print_solution(map, next, unused_rows);
    }
    else
      for(int i=0;i<nrows;++i) {
        const Color rcolor = map.check_monocolor(i);

        if(rcolor != Color::NONE) {
          next.push(Move(i, rcolor));
          searchspace_.push(next);
          next.pop();
        }
      }//for

    //revert performed moves
    if(searchspace_.size() > 1)
      revert_moves(map, unused_rows);

    searchspace_.pop();
  }//while
}
