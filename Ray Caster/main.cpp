#define _USE_MATH_DEFINES
#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

typedef unsigned char mini;

SDL_Window* window;
SDL_Renderer* renderer;
double xPos = 4, yPos = 4, ang = 0;
int width = 1280, height = 800;
int res = width / 8;
bool mm = true;
int size = 16;

void render(map<int, map<int, int>> grid)
{
    SDL_SetRenderDrawColor(renderer, 127, 191, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, new SDL_Rect{0, height / 2, width, height / 2});

    SDL_Rect rect{0, 0, width / res, 0};
    vector<pair<double, double>> points;

    for (double a = ang + M_PI_4 - M_PI_4 / res; a >= ang - M_PI_4; a -= M_PI_2 / res)
    {
        bool isY = false;

        for (double x = xPos + 0.5, y = yPos + 0.5, dist = 0; dist <= 2 * size; x += cos(a) / res, y -= sin(a) / res, dist += 1 / (double) res)
        {
            if (grid[y][x])
            {
                points.push_back({x, y});

                SDL_SetRenderDrawColor(renderer,    (grid[y][x] >= 2 && (grid[y][x] <= 3 || grid[y][x] >= 7)) * 191 + 64 * isY,
                                                    (grid[y][x] >= 3 && grid[y][x] <= 5) * 191 + 64 * isY, 
                                                    (grid[y][x] >= 5 && grid[y][x] <= 7) * 191 + 64 * isY, 255);

                rect.y = height / 2 - height / (2 * dist * cos(ang - a));
                rect.h = height / (dist * cos(ang - a));
                SDL_RenderFillRect(renderer, &rect);

                break;
            }

            if (grid[y][x + cos(a) / res])
                isY = true;
        }

        rect.x += rect.w;
    }

    if (mm)
    {
        rect.w = rect.h = height / 64;
        rect.y = rect.h;

        for (int i = 0; i < size; i++)
        {
            rect.x = rect.w;

            for (int j = 0; j < size; j++)
            {
                if (grid[i][j])
                    SDL_SetRenderDrawColor(renderer,    (grid[i][j] >= 2 && (grid[i][j] <= 3 || grid[i][j] >= 7)) * 255,
                                                        (grid[i][j] >= 3 && grid[i][j] <= 5) * 255, 
                                                        (grid[i][j] >= 5 && grid[i][j] <= 7) * 255, 255);
                else
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

                SDL_RenderFillRect(renderer, &rect);

                rect.x += rect.w;
            }

            rect.y += rect.h;
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        for (auto point : points)
            SDL_RenderDrawLine(renderer, (xPos + 1.5) * rect.w, (yPos + 1.5) * rect.h, (point.first + 1) * rect.w, (point.second + 1) * rect.h);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        rect.x = (xPos + 1) * rect.w;
        rect.y = (yPos + 1) * rect.h;

        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}

void borderify(map<int, map<int, int>>& grid, int n)
{
    for (int i = 0; i < n; i++)
    {
        grid[0][i] = 1;
        grid[n - 1][i] = 1;
        grid[i][0] = 1;
        grid[i][n - 1] = 1;
    }
}

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
        throw SDL_GetError();

    window = SDL_CreateWindow("Ray Caster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;
    const mini* keys;

    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    map<int, map<int, int>> grid;

    borderify(grid, 16);

    grid[4][7] = 4;

    render(grid);

    while (SDL_WaitEvent(&event) || true)
    {
        switch (event.type)
		{
            case SDL_QUIT:
				return 0;
				
			case SDL_KEYDOWN:

				keys = SDL_GetKeyboardState(nullptr);

				if (keys[SDL_SCANCODE_ESCAPE])
					return 0;

                if (keys[SDL_SCANCODE_LEFT])
                    ang += M_PI_4 / 2;

                if (keys[SDL_SCANCODE_RIGHT])
                    ang += 2 * M_PI - M_PI_4 / 2;

                if (ang > 2 * M_PI)
                    ang -= 2 * M_PI;

                if (keys[SDL_SCANCODE_UP] && !grid[yPos - sin(ang) + 0.5][xPos + cos(ang) + 0.5])
                {
                    xPos += cos(ang);
                    yPos -= sin(ang);
                }

                if (keys[SDL_SCANCODE_DOWN] && !grid[yPos + sin(ang) + 0.5][xPos - cos(ang) + 0.5])
                {
                    xPos -= cos(ang);
                    yPos += sin(ang);
                }

                if (keys[SDL_SCANCODE_RIGHTBRACKET])
                    res *= 2;

                if (keys[SDL_SCANCODE_LEFTBRACKET])
                    res /= 2;

                if (keys[SDL_SCANCODE_SPACE])
                    mm = !mm;

                render(grid);

                break;

            case SDL_MOUSEBUTTONDOWN:

                int x, y;
                SDL_GetMouseState(&x, &y);

                x /= height / 64;
                y /= height / 64;

                if (x >= 1 && x < grid[0].size() + 1 && y >= 1 && y < grid.size() + 1)
                    grid[y - 1][x - 1] = (grid[y - 1][x - 1] + 1) % 8;

                render(grid);
        }
    }
}