#include "Textured.h"
#include <SDL2/SDL_image.h>

using namespace std;

Textured::Textured(float x, float y, float w, float h)// : Thing(x, y, w, h)
{
    cout << "creating textured w values " << x << " " << y << " " << w << " " << h << endl;

    setPos(x, y);
    setSize(w, h);

    setColour();
    setUI(false);

    setFrame();

    setAngle();
    setFlip();
}

bool Textured::draw(SDL_Renderer* renderer, Thing* camera)
{
    if (!sprite)
        return Thing::draw(renderer, camera);
    
    SDL_RendererFlip flag = SDL_FLIP_NONE;

    if (isFlipped[0])
        flag = (SDL_RendererFlip) (flag | SDL_FLIP_HORIZONTAL);

    if (isFlipped[1])
        flag = (SDL_RendererFlip) (flag | SDL_FLIP_VERTICAL);

    SDL_Rect rect = getRect(camera);

    return !SDL_RenderCopyEx(renderer, SDL_CreateTextureFromSurface(renderer, sprite), &(frames[frame]), &rect, angle, nullptr, flag);
}

int Textured::getFrame()
{
    return frame;
}

bool Textured::setSprite(std::string file, int tiles)
{
    SDL_FreeSurface(sprite);

    sprite = IMG_Load(("assets/" + file + ".png").c_str());

    if (!sprite)
        return false;

    int totalWidth = sprite -> w;
    int width = totalWidth / tiles;
    int height = sprite -> h;

    for (int i = 0; i < totalWidth; i += width)
        frames.push_back({i, 0, width, height});

    return true;
}

bool Textured::setFrame(int i)
{
    if (i < 0 || (i && i >= frames.size()))
        return false;

    frame = i;

    return true;
}

void Textured::setAngle(float a)
{
    angle = a;
}

void Textured::setFlip(bool h, bool v)
{
    isFlipped = {h, v};
}

void Textured::rotate(float a)
{
    setAngle(angle + a);
}

void Textured::flip(bool h, bool v)
{
    setFlip((isFlipped[0] + h) % 2, (isFlipped[1] + v) % 2);
}

Textured::~Textured()
{
    SDL_FreeSurface(sprite);
}