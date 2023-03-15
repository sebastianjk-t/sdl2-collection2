#include <iostream>
#include <SDL.h>
#include "Tetris.h"
#include "Piece.h" // sdlify everything

using namespace std;

int main()
{
    srand(time(nullptr));
    vector<int> size = {20, 10};
    int scale = 768 / max(size[0], size[1]);

    SDL_Init(SDL_INIT_VIDEO);
	SDL_Renderer* renderer = SDL_CreateRenderer(SDL_CreateWindow("tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size[1] * scale, size[0] * scale, 0), -1, 0);
	SDL_Event event;
    const Uint8* keys;

    Tetris* tetris = new Tetris(size[0], size[1]);
    int tickTimer = 0;

    while (true)
    {
        while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					return 0;
					
				case SDL_KEYDOWN:

					keys = SDL_GetKeyboardState(NULL);

					if (keys[SDL_SCANCODE_ESCAPE])
						return 0;

                    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT])
                        tetris -> move('L');

                    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT])
                        tetris -> move('R');

                    if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN])
                        tetris -> move('D');

                    if (keys[SDL_SCANCODE_SPACE])
                        tetris -> move('C');

                    if (keys[SDL_SCANCODE_BACKSPACE])
                        tetris -> move('A');
			}
		}

        if (tickTimer >= 8)
        {
            if (!(tetris -> tick()))
                return 0;

            tickTimer = 0;
        }

        tickTimer++;

        tetris -> render(renderer, scale);
        SDL_Delay(32);
    }
}