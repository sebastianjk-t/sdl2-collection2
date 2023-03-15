#ifndef TEXT
#define TEXT

#include <SDL2/SDL_ttf.h>
#include "Box.h"

class Text : public Part
{
    public:
    Text(std::string t, TTF_Font* f);
    Text(std::string t = "", std::string file = "press_start.ttf");

    void render();

    void setText(std::string t);

    void setFont(TTF_Font* f);
    bool setFont(std::string file);

    void resize();

    ~Text();

    protected:
    std::string text = "";

    TTF_Font* font = nullptr;
    bool ownFont = false;
};

#endif