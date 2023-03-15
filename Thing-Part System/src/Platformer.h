#ifndef PLATFORMER
#define PLATFORMER

#include "Motion.h"
#include "Audio.h"

class Platformer : public Part
{
    public:
    Platformer(float height = 144);

    void handle();
    void update();
    void render();

    bool run(int dir);
    bool jump();
    bool land();

    protected:
    float jumpSpeed = sqrt(288);

    bool running = false;
    bool jumping = false;
    bool falling = false;

    int runTimer = 0;
};

#endif