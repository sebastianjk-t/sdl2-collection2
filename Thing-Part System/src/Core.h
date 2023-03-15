#ifndef CORE
#define CORE

#include <array>
#include "Part.h"

typedef unsigned char mini;

class Core : public Part
{
    public:
    Core(float x = 0, float y = 0, float w = 0, float h = 0);

    std::array<float, 2> getPos();
    std::array<float, 2> getSize();
    std::array<mini, 4> getColour();

    float getArea();
    float getPerimeter();

    void setPos(float x, float y);
    void setPosX(float x);
    void setPosY(float y);

    void setSize(float w, float h);
    void setSizeW(float w);
    void setSizeH(float h);

    void setColour(mini r, mini g, mini b, mini a = 255);

    void move(float x, float y);
    void scale(float w, float h);

    private:
    std::array<float, 2> pos = {0, 0};
    std::array<float, 2> size = {0, 0};
    std::array<mini, 4> colour = {0, 0, 0, 255};
};

#endif