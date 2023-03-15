#ifndef BIRD
#define BIRD

#include "Motion.h"
#include "Audio.h"

class Bird : public Part
{
    public:
    Bird(float height = 144);

    void handle();
    void render();

    void flap();

    protected:
    float flapSpeed = 34;
};

#endif