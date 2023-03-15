#include "Core.h"

using namespace std;

Core::Core(float x, float y, float w, float h)
{
    setPos(x, y);
    setSize(w, h);
}

std::array<float, 2> Core::getPos()
{
    return pos;
}

std::array<float, 2> Core::getSize()
{
    return size;
}

std::array<mini, 4> Core::getColour()
{
    return colour;
}

float Core::getArea()
{
    return size[0] * size[1];
}

float Core::getPerimeter()
{
    return 2 * (size[0] + size[1]);
}

void Core::setPos(float x, float y)
{
    setPosX(x);
    setPosY(y);
}

void Core::setPosX(float x)
{
    pos[0] = x;
}

void Core::setPosY(float y)
{
    pos[1] = y;
}

void Core::setSize(float w, float h)
{
    setSizeW(w);
    setSizeH(h);
}

void Core::setSizeW(float w)
{
    size[0] = w;
}

void Core::setSizeH(float h)
{
    size[1] = h;
}

void Core::setColour(mini r, mini g, mini b, mini a)
{
    colour = {r, g, b, a};
}

void Core::move(float x, float y)
{
    setPosX(pos[0] + x);
    setPosY(pos[1] + y);
}

void Core::scale(float w, float h)
{
    setSizeW(size[0] * w);
    setSizeH(size[1] * h);
}