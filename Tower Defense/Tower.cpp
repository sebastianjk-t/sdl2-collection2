#include "Tower.hpp"
#include "Game.hpp"
#include <algorithm>

Tower::Tower(Coords pos)
{
    this -> pos = pos;
}

void Tower::update()
{
    timer++;

    if (!(timer % delay))
        shoot();
}

void Tower::render(bool selected)
{
    SDL_Rect rect;

    if (selected)
    {
        rect = {(int) (pos.x - range), (int) (pos.y - range), (int) (range * 2), (int) (range * 2)};
        SDL_RenderCopy(game.renderer, game.getTexture("range"), nullptr, &rect);
    }

    rect = {(int) (pos.x - size.x / 2), (int) (pos.y - size.y / 2), (int) size.x, (int) size.y};
    SDL_RenderCopy(game.renderer, game.getTexture("monke" + std::to_string(level)), nullptr, &rect);
}

Coords Tower::getPos()
{  
    return pos;
}

void Tower::shoot()
{
    float x, y, mod;
    int n = game.bloons.size();

    for (int i = 0; i < n; i++)
    {
        x = game.bloons[i] -> getPos().x - pos.x;
        y = game.bloons[i] -> getPos().y - pos.y;

        if ((mod = sqrt(x * x + y * y)) < range)
            return game.darts.push_back(new Dart(pos, {x / mod, y / mod}, strength));
    }
}

void Tower::levelUp()
{
    level++;
    delay /= 2;
    range *= 2;
    strength++;
}

void Tower::buyStat(int i)
{
    switch (i)
    {
        case 0: delay /= 2; break;
        case 1: range *= 2; break;
        case 2: strength++; break;
    }
}