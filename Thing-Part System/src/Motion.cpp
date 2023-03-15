#include "Motion.h"
#include <iostream>

using namespace std;

Motion::Motion(float vx, float vy, float ax, float ay)
{
    setVelX(vx);
    setVelY(vy);
    setAccX(ax);
    setAccY(ay);
}

Motion::Motion(float ms, bool gravity)
{
    setMaxSpeed(ms);

    if (gravity)
        gravitise();
}

void Motion::update()
{
    accelerate(acc[0], acc[1]);
    thing -> get<Core>() -> move(vel[0], vel[1]);

    /*if (acc[1] == 1)
        drag(0.1);*/
}

float Motion::getMaxSpeed()
{
    return maxSpeed;
}

void Motion::setMaxSpeed(float ms)
{
    maxSpeed = ms;
}

std::array<float, 2> Motion::getVel()
{
    return vel;
}

std::array<float, 2> Motion::getAcc()
{
    return acc;
}

void Motion::setVel(float vx, float vy)
{
    setVelX(vx);
    setVelY(vy);
}

void Motion::setVelX(float v)
{
    if (v > 0)
        vel[0] = min(v, maxSpeed);
    else
        vel[0] = max(v, -maxSpeed);
}

void Motion::setVelY(float v)
{
    vel[1] = v;
}

void Motion::setAcc(float ax, float ay)
{
    setAccX(ax);
    setAccY(ay);
}

void Motion::setAccX(float a)
{
    acc[0] = a;
}

void Motion::setAccY(float a)
{
    acc[1] = a;
}

void Motion::accelerate(float vx, float vy)
{
    setVelX(vel[0] + vx);
    setVelY(vel[1] + vy);
}

void Motion::jerk(float ax, float ay)
{
    setAccX(acc[0] + ax);
    setAccY(acc[1] + ay);
}

void Motion::bounce(bool x, bool y, float amt)
{
    if (x)
    {
        if (abs(vel[0]) > 1)
            setVelX(vel[0] * -amt);
        else
            setVelX(0);
    }

    if (y)
    {
        if (abs(vel[1]) > 1)
            setVelY(vel[1] * -amt);
        else
            setVelY(0);
    }
}

void Motion::gravitise()
{
    setAccY(1);
}

void Motion::degravitise()
{
    setAccY(0);
}

mini Motion::uncollide(Thing* other, float amt)
{
    if (!(other -> get<Box>() -> getCamera()))
        return false;

    SDL_Rect rect = thing -> get<Box>() -> getRect();
    SDL_Rect temp = other -> get<Box>() -> getRect(), temp2;

    if (!SDL_IntersectRect(&rect, &temp, &temp2))
        return false;

    if (temp2.w >= temp2.h)
    {
        bounce(false, true, amt);

        if (temp.y - rect.y >= (rect.y + rect.h) - (temp.y + temp.h))
        {
            thing -> get<Core>() -> setPosY(temp.y - rect.h / 2);
            return 1;
        }
        
        thing -> get<Core>() -> setPosY(temp.y + temp.h + rect.h / 2);
        return 3;
    }
    else
    {
        bounce(true, false, amt);

        if (temp.x - rect.x >= (rect.x + rect.w) - (temp.x + temp.w))
        {
            thing -> get<Core>() -> setPosX(temp.x - rect.w / 2);
            return 4;
        }
        
        thing -> get<Core>() -> setPosX(temp.x + temp.w + rect.w / 2);
        return 2;
    }

    return false;
}

void Motion::drag(float amt)
{
    accelerate(vel[0] * -amt, 0);
}