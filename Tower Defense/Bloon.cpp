#include "Bloon.hpp"
#include "Game.hpp"

Bloon::Bloon(Coords pos, Coords dir, int layers)
{
    this -> pos = pos;
    this -> dir = dir;
    this -> layers = layers;
    speed = pow(2, layers);
}

bool Bloon::update()
{
    pos.x += dir.x * speed / 2;
    pos.y += dir.y * speed / 2;

    return !(pos.x + size.x / 2 < 0 || pos.x - size.x / 2 > game.width || pos.y + size.y / 2 < 0 || pos.y - size.y / 2 > game.height);
}

void Bloon::render()
{
    SDL_Rect rect = {(int) (pos.x - size.x / 2), (int) (pos.y - size.y / 2), (int) size.x, (int) size.y};
    SDL_RenderCopy(game.renderer, game.getTexture("bloon" + std::to_string(layers)), nullptr, &rect);
}

Coords Bloon::getPos()
{
    return pos;
}

Coords Bloon::getDir()
{
    return dir;
}

int Bloon::getProgress()
{
    return progress;
}

void Bloon::setDir(Coords dir)
{
    this -> dir = dir;
}

bool Bloon::popLayer()
{
    speed /= 2;
    return !--layers;
}

void Bloon::makeProgress()
{
    progress++;
}

bool Bloon::compareProgress(Bloon* a, Bloon* b)
{
    return a -> progress > b -> progress;
}