#include "StrataMap.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

bool next_combination(std::vector<int>& tab, int color_count) {
  bool carry = true;

  for(auto& n : tab) {
    if(n == color_count-1)
      n = 0;
    else {
      ++n;
      carry = false;
      break;
    }
  }

  return !carry;
}

enum Side {
  A,
  B
};

inline Side get_side(int r, int w) {
  return (r < w) ? Side::A : Side::B;
}

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

  const int nrows = width + height;

  StrataMap map(width, height);

  std::vector<int> permut(nrows);
  std::vector<int> colorcomb(nrows, 0);

  std::generate(permut.begin(), permut.end(),
                [](){static int ret = -1; return ++ret;});

  std::vector<Color> colors;

  int x, y;
  char choice;

  for(int i=0;i<nfields;++i) {
    Color chosen;

    std::cin >> x >> y >> choice;

    chosen = choose_color(choice);

    map.set_field_color(x, y, chosen);

    if(std::none_of(colors.begin(), colors.end(),
                    [chosen](Color c){return chosen == c;}))
      colors.push_back(chosen);
  }

  std::cout << "Solving..." << std::endl;

  const int ncolors = colors.size();
  int solution_number = 1;
  int permutation_number = 1;

  //do the checking
  do {
    do {
      bool failed = false;

      //add all ribbons and verify solution validity
      for(int i=0;i<nrows;++i)
        if(!map.add_ribbon(permut[i], colors[colorcomb[i]])) {
          map.reset_ribbons();
          failed = true;
          break;
        }

      //on finding a solution
      if(!failed) {
        std::cout << "SOLUTION " << solution_number++ << ", PERMUTATION " << permutation_number << std::endl;

        bool is_arbitrary = true;
        Side side = get_side(permut[0], width);

        for(int i=0;i<nrows;++i) {
          const int row = permut[i];

          if(is_arbitrary) {
            if(side == get_side(row, width)) {
              std::cout << "ROW " << ((row < width) ? (width - row - 1) : row)
                        << ", COLOR *" << std::endl;
            } else {
              std::cout << "ROW " << ((row < width) ? (width - row - 1) : row)
                        << ", COLOR " << color_to_string(colors[colorcomb[i]])
                        << std::endl;

              is_arbitrary = false;
            }
          } else {
            std::cout << "ROW " << ((row < width) ? (width - row - 1) : row)
                      << ", COLOR " << color_to_string(colors[colorcomb[i]])
                      << std::endl;
          }//if-else
        }//for

        std::cout << std::endl;

        map.reset_ribbons();
        break;
      }//if
    } while(next_combination(colorcomb, ncolors));

    ++permutation_number;
  } while(std::next_permutation(permut.begin(), permut.end()));

  return 0;
}
