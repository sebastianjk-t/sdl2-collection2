#include "Box.h"

using namespace std;

Box::Box(SDL_Renderer* ren, Thing* cam)
{
    setRenderer(ren);
    setCamera(cam);
}

void Box::render()
{
    if (thing -> get<Texture>())
        return;
        
    SDL_Rect rect = getRect(true);
    array<mini, 4> colour = thing -> get<Core>() -> getColour();

    SDL_SetRenderDrawColor(renderer, colour[0], colour[1], colour[2], colour[3]);
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Rect Box::getRect(bool useCameraX, bool useCameraY)
{
    array<float, 2> pos = thing -> get<Core>() -> getPos();
    array<float, 2> size = thing -> get<Core>() -> getSize();

    if (camera && useCameraX)
        pos[0] -= camera -> get<Core>() -> getPos()[0] - 384;
    
    if (camera && useCameraY)
        pos[1] -= camera -> get<Core>() -> getPos()[1] - 576;

    return {(int) (pos[0] - size[0] / 2), (int) (pos[1] - size[1] / 2), (int) size[0], (int) size[1]};
}

SDL_Renderer* Box::getRenderer()
{
    return renderer;
}

void Box::setRenderer(SDL_Renderer* ren)
{
    renderer = ren;
}

Thing* Box::getCamera()
{
    return camera;
}

void Box::setCamera(Thing* cam)
{
    camera = cam;
}