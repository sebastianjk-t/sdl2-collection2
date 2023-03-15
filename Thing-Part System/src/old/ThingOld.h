#ifndef THING
#define THING

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include "Sound.h"

class Thing
{
    public:
    Thing(float x = 0, float y = 0, float w = 0, float h = 0);

    virtual void update();
    bool draw(SDL_Renderer* renderer, SDL_Rect camera);

    std::array<float, 2> getPos();
    std::array<float, 2> getSize();
    SDL_Rect getRect();

    int getState();

    void setPos(float x = 0, float y = 0);
    void setSize(float w = 0, float h = 0);

    void setVel(float x = 0, float y = 0);
    void setAcc(float x = 0, float y = 0);

    void setAngle(float a = 0);
    void setSpin(float s = 0);

    void setFlip(bool h = false, bool v = false);

    void setRGB(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0);

    bool setSprite(std::string file, int tiles = 1);
    bool setState(int i = 0);

    void setSounds(std::vector<Sound*> s);
    void addSound(Sound* s);

    void setUI(bool u = true);

    void move(float x, float y);
    void scale(float w, float h);

    void accelerate(float x, float y);
    void jerk(float x, float y);

    void rotate(float a);
    void whirl(float s);

    void doFlip(bool h, bool v);

    void bounce(bool x, bool y);

    bool uncollide(Thing* other);
    bool isOn(Thing* other);

    bool playSound(int i = 0);

    ~Thing();

    protected:
    std::array<float, 2> pos;
    std::array<float, 2> size;

    std::array<float, 2> vel;
    std::array<float, 2> acc;

    float angle;
    float spin;

    std::array<bool, 2> flip;

    std::array<unsigned char, 3> rgb;

    SDL_Surface* sprite = nullptr;

    int state;
    std::vector<SDL_Rect> srcRects;

    std::vector<Sound*> sounds;

    bool ui;

    // possibly separate sprite, rgb, vel + acc, etc etc - also spin w sprite since u cant rotate rects lol
};

#endif