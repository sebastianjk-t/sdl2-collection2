#include "Thing.h"

using namespace std;

Thing::Thing(float x, float y, float w, float h)
{
    setPos(x, y);
    setSize(w, h);

    setVel();
    setAcc();

    setAngle();
    setSpin();

    setFlip();

    setRGB();
    setState();

    setUI(false);
}

void Thing::update()
{
    move(vel[0], vel[1]);
    accelerate(acc[0], acc[1]);
    rotate(spin);
}

bool Thing::draw(SDL_Renderer* renderer, SDL_Rect camera)
{
    SDL_Rect rect = getRect();

    if (!ui)
    {
        SDL_Rect temp;

        if (!SDL_IntersectRect(&rect, &camera, &temp))
            return false;

        rect.x -= camera.x;
        rect.y -= camera.y;
    }

    if (sprite != nullptr)
    {
        SDL_RendererFlip flippiness = SDL_FLIP_NONE;

        if (flip[0])
            flippiness = (SDL_RendererFlip) (flippiness | SDL_FLIP_HORIZONTAL);

        if (flip[1])
            flippiness = (SDL_RendererFlip) (flippiness | SDL_FLIP_VERTICAL);

        SDL_RenderCopyEx(renderer, SDL_CreateTextureFromSurface(renderer, sprite), &(srcRects[state]), &rect, angle, nullptr, flippiness);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    return true;
}

std::array<float, 2> Thing::getPos()
{
    return pos;
}

std::array<float, 2> Thing::getSize()
{
    return size;
}

SDL_Rect Thing::getRect()
{
    return SDL_Rect{(int) (pos[0] - size[0] / 2), (int) (pos[1] - size[1] / 2), (int) size[0], (int) size[1]};
}

int Thing::getState()
{
    return state;
}

void Thing::setPos(float x, float y)
{
    pos[0] = x;
    pos[1] = y;
}

void Thing::setSize(float w, float h)
{
    size[0] = w;
    size[1] = h;
}

void Thing::setVel(float x, float y)
{
    vel[0] = x;
    vel[1] = y;
}

void Thing::setAcc(float x, float y)
{
    acc[0] = x;
    acc[1] = y;
}

void Thing::setAngle(float a)
{
    angle = a;
}

void Thing::setSpin(float s)
{
    spin = s;
}

void Thing::setFlip(bool h, bool v)
{
    flip[0] = h;
    flip[1] = v;
}

void Thing::setRGB(unsigned char r, unsigned char g, unsigned char b)
{
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
}

bool Thing::setSprite(std::string file, int tiles)
{
    SDL_FreeSurface(sprite);

    sprite = IMG_Load(("assets/" + file + ".png").c_str());

    if (!sprite)
        return false;

    int totalWidth = sprite -> w;
    int width = totalWidth / tiles;
    int height = sprite -> h;

    for (int i = 0; i < totalWidth; i += width)
        srcRects.push_back({i, 0, width, height});

    return true;
}

bool Thing::setState(int i)
{
    if (i < 0 || (i && i >= srcRects.size()))
        return false;

    state = i;

    return true;
}

void Thing::setSounds(std::vector<Sound*> s)
{
    sounds = s;
}

void Thing::addSound(Sound* s)
{
    sounds.push_back(s);
}

void Thing::setUI(bool u)
{
    ui = u;
}

void Thing::move(float x, float y)
{
    pos[0] += x;
    pos[1] += y;
}

void Thing::scale(float w, float h)
{
    size[0] *= w;
    size[1] *= h;
}

void Thing::accelerate(float x, float y)
{
    vel[0] += x;
    vel[1] += y;
}

void Thing::jerk(float x, float y)
{
    acc[0] += x;
    acc[1] += y;
}

void Thing::rotate(float a)
{
    angle += a;
}

void Thing::whirl(float s)
{
    spin += s;
}

void Thing::doFlip(bool h, bool v)
{
    if (h)
        flip[0] = !flip[0];

    if (v)
        flip[1] = !flip[1];
}

void Thing::bounce(bool x, bool y)
{
    if (x)
        vel[0] *= -0.5;

    if (y)
        vel[1] *= -0.5;

    // add change in spin
}

bool Thing::uncollide(Thing* other)
{
    SDL_Rect rect = getRect();
    SDL_Rect temp = other -> getRect(), temp2;

    if (!SDL_IntersectRect(&rect, &temp, &temp2))
        return false;

    // could also do bounce

    if (temp2.w >= temp2.h) // push up or down
    {
        setVel(vel[0], 0);

        if (temp.y - rect.y >= (rect.y + rect.h) - (temp.y + temp.h))
            setPos(pos[0], temp.y - size[1] / 2); // is on
        else
            setPos(pos[0], temp.y + temp.h + size[1] / 2);
    }
    else // push left or right
    {
        setVel(0, vel[1]);

        if (temp.x - rect.x >= (rect.x + rect.w) - (temp.x + temp.w))
            setPos(temp.x - size[0] / 2, pos[1]);
        else
            setPos(temp.x + temp.w + size[0] / 2, pos[1]);
    }

    return true;
}

bool Thing::isOn(Thing* other)
{
    array<float, 2> otherPos = other -> getPos();
    array<float, 2> otherSize = other -> getSize();

    if (pos[0] + size[0] / 2 < otherPos[0] - otherSize[0] / 2 + 1 || pos[0] - size[0] / 2 > otherPos[0] + otherSize[0] / 2 - 1)
        return false;

    return pos[1] + size[1] / 2 >= otherPos[1] - otherSize[1] / 2 && pos[1] - size[1] / 2 < otherPos[1] - otherSize[1] / 2;
}

bool Thing::playSound(int i)
{
    if (i < 0 || (i && i >= sounds.size()))
        return false;

    sounds[i] -> play();

    return true;
}

Thing::~Thing()
{
    SDL_FreeSurface(sprite);
}