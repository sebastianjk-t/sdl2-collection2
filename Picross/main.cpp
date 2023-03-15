#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

SDL_Renderer* renderer;
SDL_Event event;
const unsigned char* keys;
TTF_Font* font;
SDL_Rect rect;

vector<vector<bool>> parseGrid(string file)
{
    vector<vector<bool>> grid;

    if (file.find(".txt") != -1)
    {
        ifstream fileS(file);
        string line;
        int n;

        while (getline(fileS, line))
        {
            n = line.length();
            grid.push_back(vector<bool>(n));
            
            for (int i = 0; i < n; i++)
                if (line[i] == 'X')
                    grid.back()[i] = true;
        }
    }

    return grid;
}

void render(vector<vector<bool>> orig, vector<vector<bool>> grid, vector<vector<SDL_Texture*>> rowNums, vector<vector<SDL_Texture*>> colNums, int scale)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    rect.y = 768 - scale * 2;

    for (int i = grid.size() - 1; i >= 0; i--)
    {
        rect.x = 768 - scale * 2;

        for (int j = grid[i].size() - 1; j >= 0; j--)
        {
            if (grid[i][j])
                SDL_SetRenderDrawColor(renderer, 255 * !orig[i][j], 0, 0, 255);
            else
                SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);

            SDL_RenderFillRect(renderer, &rect);

            rect.x -= scale;
        }

        for (int j = rowNums[i].size() - 1; j >= 0; j--)
        {
            SDL_RenderCopy(renderer, rowNums[i][j], nullptr, &rect);
            rect.x -= scale;
        }

        rect.y -= scale;
    }

    rect.x = 768 - scale * 2;

    for (int j = grid[0].size() - 1; j >= 0; j--)
    {
        rect.y = 768 - scale * (2 + grid.size());

        for (int i = colNums[j].size() - 1; i >= 0; i--)
        {
            SDL_RenderCopy(renderer, colNums[j][i], nullptr, &rect);
            rect.y -= scale;
        }

        rect.x -= scale;
    }

    SDL_RenderPresent(renderer);
}

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) || TTF_Init())
        return 1;

    renderer = SDL_CreateRenderer(SDL_CreateWindow("Picross", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 768, 768, 0/*SDL_WINDOW_RESIZABLE*/), -1, 0);
    font = TTF_OpenFont("press_start.ttf", 256);

    vector<vector<bool>> orig = parseGrid("grid.txt");
    int rows = orig.size(), cols = orig[0].size();

    // number stuff

    vector<vector<SDL_Texture*>> rowNums(rows), colNums(cols);
    int prev;

    for (int i = 0; i < rows; i++)
    {
        prev = 0;

        for (int j = 0; j < cols; j++)
        {
            if (orig[i][j])
            {
                if (prev == -1)
                    prev = 1;
                else
                    prev++;
            }
            else if (prev != -1 && prev)
            {
                rowNums[i].push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, to_string(prev).c_str(), {0, 0, 0, 255})));
                prev = -1;
            }
        }

        if (prev != -1)
            rowNums[i].push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, to_string(prev).c_str(), {0, 0, 0, 255})));
    }

    for (int j = 0; j < cols; j++)
    {
        prev = 0;

        for (int i = 0; i < rows; i++)
        {
            if (orig[i][j])
            {
                if (prev == -1)
                    prev = 1;
                else
                    prev++;
            }
            else if (prev != -1 && prev)
            {
                colNums[j].push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, to_string(prev).c_str(), {0, 0, 0, 255})));
                prev = -1;
            }
        }

        if (prev != -1)
            colNums[j].push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, to_string(prev).c_str(), {0, 0, 0, 255})));
    }

    int height = 1, width = 1;

    for (vector<SDL_Texture*> nums : rowNums)
        height = max(height, (int) nums.size());

    for (vector<SDL_Texture*> nums : colNums)
        width = max(width, (int) nums.size());

    height += rows;
    width += cols;

    vector<vector<bool>> main(rows, vector<bool>(cols));

    int scale = 768 / (max(width, height) + 2);
    rect.w = rect.h = scale;

    render(orig, main, rowNums, colNums, scale);

    while (SDL_WaitEvent(&event) || true)
    {
        switch (event.type)
        {
            case SDL_QUIT: return 0;

            case SDL_KEYDOWN:

                keys = SDL_GetKeyboardState(nullptr);

                if (keys[SDL_SCANCODE_ESCAPE])
                    return 0;

            case SDL_MOUSEBUTTONDOWN:

                int x, y;
                SDL_GetMouseState(&x, &y);

                x /= scale;
                y /= scale;

                x -= (width - cols + 1);
                y -= (height - rows + 1);

                if (x >= 0 && y >= 0 && x < cols && y < rows)
                {
                    if (event.button.button == SDL_BUTTON_LEFT) // fill
                        main[y][x] = !main[y][x];
                    // else // x
                    
                    render(orig, main, rowNums, colNums, scale);
                }

        }
    }
}