#include "Text.h"

using namespace std;

Text::Text(string t, float x, float y, float h) : Textured(x, y, 0, h)
{
    cout << "creating text w values " << t << " " << x << " " << y << " " << h << endl;

    setFont();
    setText(t);
}

void Text::setFont(TTF_Font* f)
{
    if (!font)
        TTF_CloseFont(font);

    font = f;
    setText(text);
}

bool Text::setFont(string file)
{
    if (!font)
        TTF_CloseFont(font);

    font = TTF_OpenFont(("assets/" + file + ".ttf").c_str(), size[1]);
    setText(text);

    return !font;
}

void Text::setText(string t)
{
    if (!sprite)
        SDL_FreeSurface(sprite);

    text = t;
    sprite = TTF_RenderText_Solid(font, text.c_str(), {colour[0], colour[1], colour[2]});

    resize(size[1]);
}

void Text::resize(float h)
{
    int w;

    TTF_SizeText(font, text.c_str(), &w, nullptr);

    setSize(w, h);
}

void Text::setColour(unsigned char r, unsigned char g, unsigned char b)
{
    Thing::setColour(r, g, b);
    setText(text);
}

Text::~Text()
{
    SDL_FreeSurface(sprite);
    TTF_CloseFont(font);
}