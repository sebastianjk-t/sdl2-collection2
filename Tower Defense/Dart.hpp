#pragma once
#include "Coords.hpp"

class Dart
{
    Coords pos;
    Coords dir;
    Coords size = {32, 16};

    int pierce;
    int speed = 32;

public:

    Dart(Coords pos, Coords dir, int pierce = 1);
    
    bool update();
    void render();

    Coords getPos();
    bool usePierce();
};