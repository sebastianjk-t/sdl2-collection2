#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Mario.h"
#include "Counter.h"
#include <array>
#include <vector>

using namespace std;

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) || ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) || TTF_Init())
        return 1;

    Thing* camera = new Thing(512, 384, 1024, 768);
    camera -> setColour(191, 223, 255);

    SDL_Renderer* renderer = SDL_CreateRenderer(SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, camera -> getSize()[0], camera -> getSize()[1], 0), -1, 0);
    SDL_Event event;
    const Uint8* keys;

    cout << "mario" << endl;

    Mario* mario = new Mario(camera -> getPos()[0], camera -> getPos()[1], 48, 48);
    mario -> setSprite("mario", 6);
    mario -> setAcc(0, 0.1);
    mario -> addSound("jump");

    cout << "floor" << endl;

    vector<Textured*> blocks;
    blocks.push_back(new Textured(camera -> getPos()[0], camera -> getSize()[1] - 24, camera -> getSize()[0], 48)); // floor

    cout << "coins" << endl;

    Counter<int>* coins = new Counter<int>("coins?: ", 0, camera -> getPos()[0], camera -> getPos()[1] / 4, camera -> getPos()[1] / 8);
    coins -> setFont("press_start");
    coins -> setUI();

    while (true)
    {
        keys = SDL_GetKeyboardState(nullptr);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
					return 0;
                    
                case SDL_KEYDOWN:

                    if (keys[SDL_SCANCODE_ESCAPE])
						return 0;

                    if (keys[SDL_SCANCODE_SPACE])
                        mario -> jump();

                    if (keys[SDL_SCANCODE_R])
                    {
                        mario -> setPos(camera -> getSize()[0] / 2, camera -> getSize()[1] / 2); // not pos
                        mario -> setVel();
                    }

                    break;

                case SDL_MOUSEBUTTONDOWN:

                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    blocks.push_back(new Textured(x + camera -> getRect().x, y + camera -> getRect().y, 48, 48)); // block
                    blocks.back() -> setSprite("brick", 2);
                    //blocks.back() -> addSound("smash");
            }
        }

        mario -> handle(keys);

        mario -> update();

        for (Textured* block : blocks)
            mario -> uncollide(block);

        for (Textured* block : blocks)
        {
            if (mario -> isOn(block))
            {
                mario -> land();
                break;
            }
        }

        for (Textured* block : blocks)
        {
            if (!(block -> getFrame()) && block -> isOn(mario))
            {
                block -> setFrame(1);
                //block -> playSound(0);
                coins -> add();
            }
        }

        camera -> setPos(mario -> getPos()[0], camera -> getPos()[1]);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        camera -> draw(renderer, camera);

        mario -> draw(renderer, camera);

        for (Thing* block : blocks)
            block -> draw(renderer, camera);

        coins -> draw(renderer, camera);

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
}