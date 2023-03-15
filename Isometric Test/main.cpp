#include <SDL2/SDL_image.h>
#include <vector>
#include <array>
#include <string>

using namespace std;

typedef unsigned char mini;

SDL_Rect getRect(array<int, 3> block)
{
    return {((block[0] - block[1]) * 32) + 352, (block[0] + block[1] - block[2] * 2) * 16, 64, 64};
}

bool isNearer(array<int, 3> blockA, array<int, 3> blockB)
{
    return blockA[0] + blockA[1] + blockA[2] < blockB[0] + blockB[1] + blockB[2];
}

bool isSelected(array<int, 3> block, int x, int y)
{
    // top
    if ((x + 2 * y - 384) / 64 == block[0] - block[2] && (2 * y - x + 384) / 64 == block[1] - block[2])
        return true;

    /* left
    if ((x + 2 * y - 448) / 64 == block[0] - block[2] && (2 * y) / 64 == block[1] - block[2])
        return true;
        
    // right*/

    return false;
}

int getSelected(vector<array<int, 3>> blocks) // top
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    for (int i = blocks.size() - 1; i >= 0; i--)
    {
        if (isSelected(blocks[i], x, y))
            return i;
    }

    return -1;
}

void renderBlock(array<int, 3> block, SDL_Texture* texture, SDL_Renderer* renderer)
{
    SDL_Rect box = getRect(block);
    SDL_RenderCopy(renderer, texture, nullptr, &box);
}

void render(vector<array<int, 3>> blocks, SDL_Texture* texture, SDL_Texture* texture2, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < blocks.size(); i++)
    {
        if (i == getSelected(blocks))
            renderBlock(blocks[i], texture2, renderer);
        else
            renderBlock(blocks[i], texture, renderer);
    }

    SDL_RenderPresent(renderer);
}

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) || ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG))
        return 1;

    SDL_Window* window = SDL_CreateWindow("Isometric Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 768, 416, 0);

    SDL_SetWindowIcon(window, IMG_Load("icon.png"));

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;
    const mini* keys;

    bool bordered = false;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("block0.png"));
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, IMG_Load("block02.png"));

    vector<array<int, 3>> blocks;
    
    for (int i = -12; i < 24; i++)
        for (int j = -12; j < 24; j++)
            blocks.push_back({i, j, 0});

    int selected = -1;

    render(blocks, texture, texture2, renderer);

	while (SDL_WaitEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				return 0;
				
			case SDL_KEYDOWN:

				keys = SDL_GetKeyboardState(nullptr);

				if (keys[SDL_SCANCODE_ESCAPE])
					return 0;

				if (keys[SDL_SCANCODE_SPACE])
				{
					SDL_DestroyTexture(texture);
					bordered = !bordered;

					if (bordered)
						texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("block2.png"));
					else
						texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("block0.png"));
				}

				if (keys[SDL_SCANCODE_R])
				{
					blocks.clear();

					for (int i = 0; i < 12; i++)
						for (int j = 0; j < 12; j++)
							blocks.push_back({i, j, 0});
				}

				break;

			case SDL_MOUSEBUTTONDOWN:

				selected = getSelected(blocks);

				if (selected != -1)
				{
					if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_RMASK)
						blocks.erase(blocks.begin() + selected);
					else
					{
						blocks.push_back({blocks[selected][0], blocks[selected][1], blocks[selected][2] + 1});
						sort(blocks.begin(), blocks.end(), isNearer);
					}
				}

			case SDL_MOUSEMOTION:
				render(blocks, texture, texture2, renderer);
		}
	}
}
