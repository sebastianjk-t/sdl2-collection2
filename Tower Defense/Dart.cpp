#include "Dart.hpp"
#include "Game.hpp"

Dart::Dart(Coords pos, Coords dir, int pierce)
{
    this -> pos = pos;
    this -> dir = dir;
    this -> pierce = pierce;
}

bool Dart::update()
{
    pos.x += dir.x * speed;
    pos.y += dir.y * speed;

    return !(pos.x + size.x / 2 < 0 || pos.x - size.x / 2 > game.width || pos.y + size.y / 2 < 0 || pos.y - size.y / 2 > game.height);
}

void Dart::render()
{
    SDL_Rect rect = {(int) (pos.x - size.x / 2), (int) (pos.y - size.y / 2), (int) size.x, (int) size.y};
    SDL_RenderCopyEx(game.renderer, game.getTexture("dart"), nullptr, &rect, atan2(dir.y, dir.x) * 180.0 / M_PI, nullptr, SDL_FLIP_NONE);
}

Coords Dart::getPos()
{
    return pos;
}

bool Dart::usePierce()
{
    return !--pierce;
}
