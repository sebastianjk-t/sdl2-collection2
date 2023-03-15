#ifndef BOX
#define BOX

#include <SDL2/SDL.h>
#include "Core.h"
#include "Texture.h"

class Box : public Part
{
    public:
    Box(SDL_Renderer* ren = nullptr, Thing* cam = nullptr);

    void render();

    SDL_Rect getRect(bool useCameraX = false, bool useCameraY = false);

    SDL_Renderer* getRenderer();
    void setRenderer(SDL_Renderer* ren);

    Thing* getCamera();
    void setCamera(Thing* cam);

    protected:
    SDL_Renderer* renderer = nullptr;
    Thing* camera = nullptr;
};

#endif