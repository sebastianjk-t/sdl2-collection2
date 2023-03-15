#ifndef TEXTURE
#define TEXTURE

#include <SDL2/SDL_image.h>
#include "Box.h"

class Texture : public Part
{
    public:
    Texture(SDL_Texture* tex = nullptr, int f = 1);
    //Texture(std::string file, int f = 1);

    void init(Thing* t);
    void render();

    void setTexture(SDL_Texture* tex, int f = 1);
    bool setTexture(std::string file, int f = 1);

    int getFrame();
    bool setFrame(int i);

    float getAngle();
    std::array<bool, 2> getFlip();

    void setAngle(float a);
    void setFlipH(bool h);
    void setFlipV(bool v);

    void rotate(float a);
    void flip(bool h, bool v);

    ~Texture();

    protected:
    void split(int f);

    SDL_Texture* texture = nullptr;
    bool ownTexture = false;

    int frame = 0;
    std::vector<SDL_Rect> frames;

    float angle = 0;
    std::array<bool, 2> isFlipped = {false, false};
};

#endif