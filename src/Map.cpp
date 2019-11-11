//
// Created by marcin on 11.11.2019.
//

#include "Map.hpp"

#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>

#include "ColorChecker.hpp"

Map::Map(const std::vector<Color>& map, Map::SizeType width, Map::SizeType height)
        : mWidth(width),
          mHeight(height),
          mColoredNumber(0),
          mMap(width * height) {
    auto transformator = [this](Color c) {
        if (c != Color::NONE) {
            ++mColoredNumber;
        }
        return c;
    };

    std::transform(std::begin(map), std::end(map), std::begin(mMap), transformator);
}

Color Map::checkMonocolor(Map::SizeType number) const {
    ColorChecker checker;
    auto slice = getSlice(number);
    const std::valarray<Color> checkedSlice = mMap[slice];
    const bool isMonocolor = std::all_of(std::begin(checkedSlice), std::end(checkedSlice), std::ref(checker));

    return isMonocolor ? checker.getColor() : Color::NONE;
}

std::slice Map::getSlice(Map::SizeType number) const {
    if (number >= mWidth) {
        const size_t startPos = number - mWidth;
        return std::slice(startPos, mHeight, mWidth);
    }

    return std::slice(number * mWidth, mWidth, 1);
}

std::valarray<Map::SizeType> Map::removeColor(Map::SizeType number) {
    auto slice = getSlice(number);

    const Map::SizeType end = slice.start() + slice.size() * slice.stride();
    std::vector<Map::SizeType> indices;
    for (Map::SizeType i = slice.start(); i < end; i += slice.stride()) {
        Color& fieldColor = mMap[i];

        if (fieldColor != Color::NONE) {
            indices.push_back(i);
            fieldColor = Color::NONE;
        }
    }

    std::valarray<Map::SizeType> ret(indices.size());
    std::copy(std::begin(indices), std::end(indices), std::begin(ret));
    mColoredNumber -= indices.size();
    return ret;
}

void Map::restoreColor(const std::valarray<SizeType>& indices, Color color) {
    mMap[indices] = color;
    mColoredNumber += indices.size();
}

Map::SizeType Map::getRibbonNumber() const {
    return mWidth + mHeight;
}

bool Map::isUncolored() const {
    return mColoredNumber == 0;
}
