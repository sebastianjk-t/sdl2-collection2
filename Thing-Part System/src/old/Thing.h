#ifndef THING
#define THING

#include <SDL2/SDL.h>
#include <array>
#include <iostream>

class Thing
{
    public:
    Thing(float x = 0, float y = 0, float w = 0, float h = 0);

    virtual bool draw(SDL_Renderer* renderer, Thing* camera);

    std::array<float, 2> getPos();
    std::array<float, 2> getSize();
    
    SDL_Rect getRect();
    SDL_Rect getRect(Thing* camera);

    void setPos(float x = 0, float y = 0);
    void setSize(float w = 0, float h = 0);
    virtual void setColour(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0);
    void setUI(bool u = true);

    void move(float x, float y);
    void scale(float w, float h);

    bool isOn(Thing* other);

    protected:
    std::array<float, 2> pos;
    std::array<float, 2> size;
    std::array<unsigned char, 3> colour;
    bool isUI;
};

#endif