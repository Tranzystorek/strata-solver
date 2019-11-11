//
// Created by marcin on 11.11.2019.
//

#ifndef STRATA_SOLVER_MAP_HPP
#define STRATA_SOLVER_MAP_HPP

#include <valarray>
#include <vector>

#include "Color.hpp"

class Map {
public:
    using SizeType = size_t;

public:
    Map(const std::vector<Color>& map, SizeType width, SizeType height);

    std::valarray<SizeType> removeColor(SizeType number);
    void restoreColor(const std::valarray<SizeType>& indices, Color color);

    Color checkMonocolor(SizeType number) const;

    SizeType getRibbonNumber() const;
    bool isUncolored() const;

private:
    std::slice getSlice(SizeType number) const;

private:
    size_t mWidth;
    size_t mHeight;
    size_t mColoredNumber;
    std::valarray<Color> mMap;
};


#endif //STRATA_SOLVER_MAP_HPP
