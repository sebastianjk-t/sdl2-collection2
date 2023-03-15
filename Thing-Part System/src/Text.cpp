#include "Text.h"

using namespace std;

Text::Text(std::string t, TTF_Font* f)
{
    setText(t);
    setFont(f);
}

Text::Text(std::string t, std::string file)
{
    setText(t);
    setFont(file);
}

void Text::render()
{
    if (!font)
        return;

    array<mini, 4> colour = thing -> get<Core>() -> getColour();
    SDL_Texture* texture = SDL_CreateTextureFromSurface(thing -> get<Box>() -> getRenderer(), TTF_RenderText_Solid(font, text.c_str(), {colour[0], colour[1], colour[2]}));

    SDL_Rect rect = thing -> get<Box>() -> getRect(true);
    float angle = thing -> get<Texture>() -> getAngle();
    std::array<bool, 2> isFlipped = thing -> get<Texture>() -> getFlip();

    SDL_RenderCopyEx(thing -> get<Box>() -> getRenderer(), texture, nullptr, &rect, angle, nullptr, (SDL_RendererFlip) (isFlipped[0] + 2 * isFlipped[1]));
    SDL_DestroyTexture(texture);
}

void Text::setText(std::string t)
{
    text = t;
}

void Text::setFont(TTF_Font* f)
{
    if (ownFont)
        TTF_CloseFont(font);

    ownFont = false;
    font = f;
}

bool Text::setFont(std::string file)
{
    if (ownFont)
        TTF_CloseFont(font);

    font = TTF_OpenFont(("assets/" + file).c_str(), 256);

    ownFont = font;

    return !font;
}

void Text::resize()
{
    int w, h;

    TTF_SizeText(font, text.c_str(), &w, &h);
    thing -> get<Core>() -> setSizeW(w * (thing -> get<Core>() -> getSize()[1]) / h);
}

Text::~Text()
{
    if (ownFont)
        TTF_CloseFont(font);
}