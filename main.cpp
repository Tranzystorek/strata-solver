#include "StrataMap.hpp"
#include "Solver.hpp"

#include <iostream>

inline Color choose_color(char choice) {
  switch(choice) {
  case 'y':
  case 'Y':
    return Color::YELLOW;

  case 'r':
  case 'R':
    return Color::RED;

  case 'g':
  case 'G':
    return Color::GREEN;

  case 'p':
  case 'P':
    return Color::PURPLE;

  case 'o':
  case 'O':
    return Color::ORANGE;
  }
}

int main() {
  int width, height, nfields;

  std::cout << "[W H NFIELDS]: " << std::endl;
  std::cin >> width >> height >> nfields;

  StrataMap map(width, height);

  int x, y;
  char choice;

  for(int i=0;i<nfields;++i) {
    Color chosen;

    std::cin >> x >> y >> choice;

    chosen = choose_color(choice);

    map.set_field(x, y, chosen);
  }

  std::cout << "Solving..." << std::endl;

  Solver solver;
  solver.solve(map);

  return 0;
}
