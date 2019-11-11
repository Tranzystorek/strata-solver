//
// Created by marcin on 11.11.2019.
//

#include "Color.hpp"

const char* colorToString(Color c) {
    switch(c) {
        case Color::YELLOW:
            return "Yellow";

        case Color::RED:
            return "Red";

        case Color::GREEN:
            return "Green";

        case Color::PURPLE:
            return "Purple";

        case Color::ORANGE:
            return "Orange";
    }
}
