#include "Dynamic.h"

using namespace std;

Dynamic::Dynamic(float x, float y, float w, float h)// : Thing(x, y, w, h)
{
    cout << "creating dynamic w values " << x << " " << y << " " << w << " " << h << endl;

    setPos(x, y);
    setSize(w, h);

    setColour();
    setUI(false);

    setVel();
    setAcc();
}

void Dynamic::update()
{
    move(vel[0], vel[1]);
    accelerate(acc[0], acc[1]);
}

void Dynamic::setVel(float x, float y)
{
    vel = {x, y};
}

void Dynamic::setAcc(float x, float y)
{
    acc = {x, y};
}

void Dynamic::accelerate(float x, float y)
{
    setVel(vel[0] + x, vel[1] + y);
}

void Dynamic::jerk(float x, float y)
{
    setAcc(acc[0] + x, acc[1] + y);
}

bool Dynamic::uncollide(Thing* other)
{
    SDL_Rect rect = getRect();
    SDL_Rect temp = other -> getRect(), temp2;

    if (!SDL_IntersectRect(&rect, &temp, &temp2))
        return false;

    if (temp2.w >= temp2.h)
    {
        setVel(vel[0], 0);

        if (temp.y - rect.y >= (rect.y + rect.h) - (temp.y + temp.h))
            setPos(pos[0], temp.y - size[1] / 2);
        else
            setPos(pos[0], temp.y + temp.h + size[1] / 2);
    }
    else
    {
        setVel(0, vel[1]);

        if (temp.x - rect.x >= (rect.x + rect.w) - (temp.x + temp.w))
            setPos(temp.x - size[0] / 2, pos[1]);
        else
            setPos(temp.x + temp.w + size[0] / 2, pos[1]);
    }

    return true;
}

void Dynamic::bounce(bool x, bool y)
{
    if (x)
        vel[0] *= -0.5;

    if (y)
        vel[1] *= -0.5;
}