#ifndef MOTION
#define MOTION

#include "Texture.h"

class Motion : public Part
{
    public:
    Motion(float ms = 4, bool gravity = false);
    Motion(float vx, float vy, float ax = 0, float ay = 0);

    void update();

    float getMaxSpeed();
    void setMaxSpeed(float ms);

    std::array<float, 2> getVel();
    std::array<float, 2> getAcc();

    void setVel(float vx, float vy);
    void setVelX(float v);
    void setVelY(float v);

    void setAcc(float ax, float ay);
    void setAccX(float a);
    void setAccY(float a);

    void accelerate(float vx, float vy);
    void jerk(float ax, float ay);

    void bounce(bool x, bool y, float amt = 0.5);

    void gravitise();
    void degravitise();

    mini uncollide(Thing* other, float amt = 0);

    void drag(float amt);

    protected:
    std::array<float, 2> vel = {0, 0};
    std::array<float, 2> acc = {0, 0};
    float maxSpeed = 16;
};

#endif