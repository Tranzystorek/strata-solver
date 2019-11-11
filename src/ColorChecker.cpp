//
// Created by marcin on 11.11.2019.
//

#include "ColorChecker.hpp"

ColorChecker::ColorChecker() : currentColor(Color::NONE) {
}

bool ColorChecker::operator()(Color color) {
    if (color == Color::NONE) {
        return true;
    }

    if (currentColor == Color::NONE) {
        currentColor = color;
        return true;
    }

    return currentColor == color;
}

Color ColorChecker::getColor() const {
    return currentColor;
}
