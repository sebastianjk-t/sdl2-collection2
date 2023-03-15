#ifndef PART
#define PART

#include "Thing.h"

class Part
{
    public:
    Part(Thing* t = nullptr);

    virtual void init(Thing* t = nullptr);
    virtual void handle();
    virtual void update();
    virtual void render();

    protected:
    Thing* thing = nullptr;
};

#endif