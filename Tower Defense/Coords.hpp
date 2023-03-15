#pragma once
#include <algorithm>

struct Coords
{
    float x;
    float y;

    float operator[](bool i)
    {
        return i ? y : x;
    }

    bool operator==(Coords other)
    {
        return abs(x - other.x) < 32 && abs(y - other.y) < 32;
    }
};