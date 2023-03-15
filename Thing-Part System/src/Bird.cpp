#include "Bird.h"

using namespace std;

Bird::Bird(float height)
{
    flapSpeed = sqrt(2 * height);
}

void Bird::handle()
{
    if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE] && thing -> get<Motion>() -> getVel()[1] >= 0)
        flap();
}

void Bird::render()
{
    if (!(thing -> get<Texture>()))
        return;

    if (thing -> get<Motion>() -> getVel()[1] > 0)
        thing -> get<Texture>() -> setFrame(0);
    else
        thing -> get<Texture>() -> setFrame(1);
}

void Bird::flap()
{
    thing -> get<Audio>() -> playSound();
    thing -> get<Motion>() -> setVelY(-flapSpeed);
}