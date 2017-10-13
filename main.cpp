#include "StrataMap.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

bool next_combination(int* tab, int size, int color_count) {
  bool carry = true;

  for(int i=0;i<size;++i) {
    if(tab[i] == color_count-1) {
      tab[i] = 0;
    } else {
      ++tab[i];
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
  int width, height, ncolors, nfields;

  std::cout << "[W H NCOLORS NFIELDS]: " << std::endl;
  std::cin >> width >> height >> ncolors >> nfields;

  const int nrows = width + height;

  StrataMap map(width, height);

  int* permut = new int[nrows];
  int* colorcomb = new int[nrows];

  for(int i=0;i<nrows;++i) {
    permut[i] = i;
    colorcomb[i] = 0;
  }

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

  int solution_number = 1;
  int comb_number = 1;
  int permutation_number = 1;

  //do the checking
  do {
    do {
      //std::cout << comb_number++ << std::endl;

      for(int i=0;i<nrows;++i) {
        map.add_ribbon(permut[i], colors[colorcomb[i]]);
      }

      if(map.check()) {
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
      }

      map.reset_ribbons();
    } while(next_combination(colorcomb, nrows, ncolors));

    ++permutation_number;
  } while(std::next_permutation(permut, permut+nrows));

  delete[] colorcomb;
  delete[] permut;

  return 0;
}
