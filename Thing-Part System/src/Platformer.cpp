#include "Platformer.h"

using namespace std;

Platformer::Platformer(float height)
{
    jumpSpeed = sqrt(2 * height);
}

void Platformer::handle()
{
    const mini* keys = SDL_GetKeyboardState(nullptr);

    running = run((keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) - (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]));
}

void Platformer::update()
{
    falling = true;
}

void Platformer::render()
{
    if (!(thing -> get<Texture>()))
        return;

    if (jumping)
        thing -> get<Texture>() -> setFrame(5);
    else if (running)
    {
        if (thing -> get<Motion>() -> getVel()[0] > 0 == thing -> get<Motion>() -> getAcc()[0] > 0) // same direction
        {
            thing -> get<Texture>() -> setFrame(1 + runTimer / 4);
            runTimer += 1 + 1; // isRunning
            runTimer %= 12;
        }
        else
            thing -> get<Texture>() -> setFrame(4); // turn
    }
    else
        thing -> get<Texture>() -> setFrame(0);
}

bool Platformer::run(int dir)
{
    thing -> get<Motion>() -> setAccX(dir);

    if (!dir)
        return false;

    if (thing -> get<Texture>())
        thing -> get<Texture>() -> setFlipH(dir < 0);

    return true;
}

bool Platformer::jump()
{
    if (falling)
        return false;

    jumping = true;

    thing -> get<Audio>() -> playSound();
    thing -> get<Motion>() -> accelerate(0, -jumpSpeed);

    return true;
}

bool Platformer::land()
{
    if (!falling)
        return false;

    jumping = false;
    falling = false;

    return true;
}