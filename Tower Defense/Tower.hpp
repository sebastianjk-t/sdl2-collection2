#pragma once
#include "Coords.hpp"
#include "Dart.hpp"

class Tower
{
    Coords pos;
    Coords size = {64, 64};

    int timer = 0;
    int level = 1;

    int delay = 32; // in frames, replace w ms lol
    float range = 128;
    int strength = 2;

public:

    Tower(Coords pos);

    void update();
    void render(bool selected = false);

    Coords getPos();
    void shoot();
    void levelUp();
    void buyStat(int i);
};