#include "Mario.h"

using namespace std;

Mario::Mario(float x, float y, float w, float h) : Dynamic(x, y, w, h), Textured(x, y, w, h)
{
    cout << "creating mario w values " << x << " " << y << " " << w << " " << h << endl;

    runTimer = 0;
    acc[1] = 0.1;
}
    
void Mario::handle(const Uint8* keys)
{
    if (frame != 5)
        setFrame(0);

    run((keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) - (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]));
}

void Mario::update()
{
    Dynamic::update();

    if (vel[0] >= 0.05)
        accelerate(-0.05, 0);
    else if (vel[0] <= -0.05)
        accelerate(0.05, 0);
    else
        setVel(0, vel[1]);
}

void Mario::run(int dir)
{
    if (!dir)
        return;

    accelerate(dir * 0.1, 0);

    if (vel[0] > 4)
        setVel(4, vel[1]);
    else if (vel[0] < -4)
        setVel(-4, vel[1]);

    setFlip(dir < 0, isFlipped[1]);

    if (frame != 5)
    {
        if (dir * vel[0] > 0) // same direction
        {
            setFrame(runTimer / 8 + 1);
            runTimer += 2;
            runTimer %= 24;
        }
        else
            setFrame(4); // turn
    }
}

bool Mario::jump()
{
    if (frame == 5)
        return false;
    
    playSound(0);
    setVel(vel[0], -6);
    setFrame(5);

    return true;
}

bool Mario::land()
{
    if (frame != 5)
        return false;

    setVel(vel[0], 0);
    setFrame(0);

    return true;
}