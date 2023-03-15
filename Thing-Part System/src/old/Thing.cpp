#include "Thing.h"

using namespace std;

Thing::Thing(float x, float y, float w, float h)
{
    cout << "creating thing w values " << x << " " << y << " " << w << " " << h << endl;

    setPos(x, y);
    setSize(w, h);

    setColour();
    setUI(false);
}

bool Thing::draw(SDL_Renderer* renderer, Thing* camera)
{
    SDL_Rect rect = getRect(camera);

    SDL_SetRenderDrawColor(renderer, colour[0], colour[1], colour[2], 255);
    return !SDL_RenderFillRect(renderer, &rect);
}

std::array<float, 2> Thing::getPos()
{
    return pos;
}

std::array<float, 2> Thing::getSize()
{
    return size;
}

SDL_Rect Thing::getRect()
{
    return SDL_Rect{(int) (pos[0] - size[0] / 2), (int) (pos[1] - size[1] / 2), (int) size[0], (int) size[1]};
}

SDL_Rect Thing::getRect(Thing* camera)
{
    return SDL_Rect{(int) (pos[0] - size[0] / 2) - (camera -> getRect().x * !isUI), (int) (pos[1] - size[1] / 2) - (camera -> getRect().y * !isUI), (int) size[0], (int) size[1]};
}

void Thing::setPos(float x, float y)
{
    pos = {x, y};
}

void Thing::setSize(float w, float h)
{
    size = {w, h};
}

void Thing::setColour(unsigned char r, unsigned char g, unsigned char b)
{
    colour = {r, g, b};
}

void Thing::setUI(bool u)
{
    isUI = u;
}

void Thing::move(float x, float y)
{
    setPos(pos[0] + x, pos[1] + y);
}

void Thing::scale(float w, float h)
{
    setSize(size[0] * w, size[1] * h);
}

bool Thing::isOn(Thing* other)
{
    array<float, 2> otherPos = other -> getPos();
    array<float, 2> otherSize = other -> getSize();

    if (pos[0] + size[0] / 2 < otherPos[0] - otherSize[0] / 2 + 1 || pos[0] - size[0] / 2 > otherPos[0] + otherSize[0] / 2 - 1)
        return false;

    return pos[1] + size[1] / 2 >= otherPos[1] - otherSize[1] / 2 && pos[1] - size[1] / 2 < otherPos[1] - otherSize[1] / 2;
}