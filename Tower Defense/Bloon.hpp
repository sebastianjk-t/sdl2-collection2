#pragma once
#include "Coords.hpp"

class Bloon
{
    Coords pos;
    Coords dir;
    Coords size = {64, 64};

    int progress = 0;
    int layers;
    int speed = 1;

public:

    Bloon(Coords pos, Coords dir = {0, 0}, int layers = 1);

    bool update();
    void render();

    Coords getPos();
    Coords getDir();
    int getProgress();

    void setDir(Coords dir);

    bool popLayer();
    void makeProgress();

    static bool compareProgress(Bloon* a, Bloon* b);
};