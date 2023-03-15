#include "Texture.h"

using namespace std;

Texture::Texture(SDL_Texture* tex, int f)
{
    setTexture(tex, f);
}

/*Texture::Texture(string file, int f)
{
    setTexture(file, f);
}*/

void Texture::init(Thing* t)
{
    thing = t;
}

void Texture::render()
{
    if (!texture)
        return;

    SDL_Rect rect = thing -> get<Box>() -> getRect(true);

    SDL_RenderCopyEx(thing -> get<Box>() -> getRenderer(), texture, &(frames[frame]), &rect, angle, nullptr, (SDL_RendererFlip) (isFlipped[0] + 2 * isFlipped[1]));
}

void Texture::setTexture(SDL_Texture* tex, int f)
{
    if (ownTexture)
        SDL_DestroyTexture(texture);

    ownTexture = false;
    texture = tex;

    split(f);
}

bool Texture::setTexture(string file, int f)
{
    if (ownTexture)
        SDL_DestroyTexture(texture);

    ownTexture = true;
    texture = SDL_CreateTextureFromSurface(thing -> get<Box>() -> getRenderer(), IMG_Load(("assets/" + file).c_str()));

    if (!texture)
        return false;

    split(f);

    return true;
}

int Texture::getFrame()
{
    return frame;
}

bool Texture::setFrame(int i)
{
    if (i < 0 || (i && i >= frames.size()))
        return false;

    frame = i;

    return true;
}

float Texture::getAngle()
{
    return angle;
}

std::array<bool, 2> Texture::getFlip()
{
    return isFlipped;
}

void Texture::setAngle(float a)
{
    angle = a;
}

void Texture::setFlipH(bool h)
{
    isFlipped[0] = h;
}

void Texture::setFlipV(bool v)
{
    isFlipped[1] = v;
}

void Texture::rotate(float a)
{
    setAngle(angle + a);
}

void Texture::flip(bool h, bool v)
{
    setFlipH((isFlipped[0] + h) % 2);
    setFlipV((isFlipped[1] + v) % 2);
}

Texture::~Texture()
{
    if (ownTexture)
        SDL_DestroyTexture(texture);
}

void Texture::split(int f)
{
    if (!texture)
        return;

    int totalWidth, width, height;

    SDL_QueryTexture(texture, NULL, NULL, &totalWidth, &height);

    width = totalWidth / f;

    for (int i = 0; i < totalWidth; i += width)
        frames.push_back({i, 0, width, height});
}