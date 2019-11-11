#include <iostream>

#include "Map.hpp"
#include "Solver.hpp"
#include "Color.hpp"

Color colorFromChar(char choice) {
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

        case '0':
            return Color::NONE;
    }
}

int main() {
    size_t width, height;
    std::cin >> width >> height;

    const int nFields = width * height;
    std::vector<Color> colors; colors.reserve(nFields);
    for(int i=0; i < nFields; ++i) {
        char choice;
        std::cin >> choice;

        Color chosen = colorFromChar(choice);
        colors.push_back(chosen);
    }

    Map map(colors, width, height);
    Solver solver;
    std::vector<Solution> solutions = solver.solve(map);

    int solutionNumber = 1;
    for (auto& s : solutions) {
        std::cout << "SOLUTION " << solutionNumber++ << '\n' << s.toString() << std::endl;
    }

    return 0;
}
