#ifndef MARIO
#define MARIO

#include "Dynamic.h"
#include "Textured.h"
#include "Audible.h"

class Mario : public Dynamic, public Textured, public Audible
{
    public:
    Mario(float x = 0, float y = 0, float w = 0, float h = 0);

    void handle(const Uint8* keys);
    void update();

    void run(int dir);
    bool jump();
    void fall();
    bool land();

    ~Mario();

    private:
    int runTimer;
};

#endif