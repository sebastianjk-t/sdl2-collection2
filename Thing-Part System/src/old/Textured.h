#ifndef TEXTURED
#define TEXTURED

#include "Thing.h"
#include <vector>
#include <string>

class Textured : virtual public Thing
{
    public:
    Textured(float x = 0, float y = 0, float w = 0, float h = 0);

    bool draw(SDL_Renderer* renderer, Thing* camera);

    int getFrame();

    bool setSprite(std::string file, int tiles = 1);
    bool setFrame(int i = 0);

    void setAngle(float a = 0);
    void setFlip(bool h = false, bool v = false);

    void rotate(float a);
    void flip(bool h, bool v);

    ~Textured();

    protected:
    SDL_Surface* sprite = nullptr;

    int frame;
    std::vector<SDL_Rect> frames;

    float angle;
    std::array<bool, 2> isFlipped;
};

#endif