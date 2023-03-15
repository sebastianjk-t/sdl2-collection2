#ifndef DYNAMIC
#define DYNAMIC

#include "Thing.h"

class Dynamic : virtual public Thing
{
    public:
    Dynamic(float x = 0, float y = 0, float w = 0, float h = 0);

    virtual void update();

    void setVel(float x = 0, float y = 0);
    void setAcc(float x = 0, float y = 0);

    void accelerate(float x, float y);
    void jerk(float x, float y);

    bool uncollide(Thing* other);
    void bounce(bool x, bool y);

    protected:
    std::array<float, 2> vel;
    std::array<float, 2> acc;
};

#endif