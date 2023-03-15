#ifndef TEXT
#define TEXT

#include <SDL2/SDL_ttf.h>
#include "Textured.h"

class Text : public Textured
{
    public:
    Text(std::string t = "", float x = 0, float y = 0, float h = 0);

    void setFont(TTF_Font* f);
    bool setFont(std::string file = "courier");

    void setText(std::string t = "");

    void resize(float h = 0);

    void setColour(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0);

    ~Text();

    protected:
    TTF_Font* font = nullptr;
    std::string text;
};

#endif