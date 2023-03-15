#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <array>
#include <unordered_set>
#include <string>
#include <queue>

#define RES 768
#define SIZE 16
#define SCALE RES / SIZE
typedef unsigned char mini;

using namespace std;

SDL_Renderer* renderer;

class Tile
{
    public:
    Tile(array<string, 4> sides, string file)
    {
        image = SDL_CreateTextureFromSurface(renderer, IMG_Load(file.c_str()));
        this -> sides = sides;

        this -> revSides = this -> sides;
        for (auto& revSide : revSides)
            reverse(revSide.begin(), revSide.end());
    };

    Tile(Tile* other, mini rotation = 0, bool hFlip = false, bool vFlip = false)
    {
        image = other -> image;
        this -> rotation = (other -> rotation + rotation) % 4;
        this -> hFlip = (other -> hFlip + hFlip) % 2;
        this -> vFlip = (other -> vFlip + vFlip) % 2;
        sides = other -> sides;

        for (int i = 0; i < rotation; i++)
            for (int j = 3; j > 0; j--)
                swap(sides[j], sides[j - 1]);

        this -> revSides = this -> sides;
        for (auto& revSide : revSides)
            reverse(revSide.begin(), revSide.end());
    };

    void render(SDL_Rect rect)
    {
        SDL_RenderCopyEx(renderer, image, nullptr, &rect, 90 * rotation, nullptr, (SDL_RendererFlip) (hFlip | (2 * vFlip)));
    };

    string getUp()
    {
        return sides[0];
    };

    string getRight()
    {
        return sides[1];
    };

    string getDown()
    {
        return sides[2];
    };

    string getLeft()
    {
        return sides[3];
    };

    string getRevUp()
    {
        return revSides[0];
    };

    string getRevRight()
    {
        return revSides[1];
    };

    string getRevDown()
    {
        return revSides[2];
    };

    string getRevLeft()
    {
        return revSides[3];
    };

    ~Tile()
    {
        SDL_DestroyTexture(image);
    };
    
    private:
    SDL_Texture* image;

    mini rotation = 0;
    bool hFlip = false;
    bool vFlip = false;

    array<string, 4> sides;
    array<string, 4> revSides;
};

void render(array<array<unordered_set<Tile*>, SIZE>, SIZE> grid)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect;

    rect.w = SCALE;
    rect.h = SCALE;
    rect.y = 0;

    for (auto row : grid)
    {
        rect.x = 0;

        for (auto cell : row)
        {
            if (cell.size() == 1)
                for (auto tile : cell)
                    tile -> render(rect);

            rect.x += SCALE;
        }

        rect.y += SCALE;
    }

    SDL_RenderPresent(renderer);
}

array<array<unordered_set<Tile*>, SIZE>, SIZE> collapse(array<array<unordered_set<Tile*>, SIZE>, SIZE> grid, int i = 0, int j = 0)
{
    queue<array<int, 2>> q;
    q.push({i, j});

    unordered_set<string> up, right, down, left;
    bool changed = false;

    q.push({i, j});

    while (!q.empty())
    {
        i = q.front()[0];
        j = q.front()[1];
        q.pop();

        if (grid[i][j].empty())
            return {{{}}};

        up.clear();
        right.clear();
        down.clear();
        left.clear();

        for (Tile* tile : grid[i][j])
        {
            up.insert(tile -> getRevUp());
            right.insert(tile -> getRevRight());
            down.insert(tile -> getRevDown());
            left.insert(tile -> getRevLeft());
        }

        if (i)
        {
            changed = false;

            for (auto it = grid[i - 1][j].begin(); it != grid[i - 1][j].end();)
            {
                if (!up.count((*it) -> getDown()))
                {
                    it = grid[i - 1][j].erase(it);
                    changed = true;
                }
                else
                    it++;
            }

            if (changed)
                q.push({i - 1, j});
        }

        if (j + 1 < grid[i].size())
        {
            changed = false;

            for (auto it = grid[i][j + 1].begin(); it != grid[i][j + 1].end();)
            {
                if (!right.count((*it) -> getLeft()))
                {
                    it = grid[i][j + 1].erase(it);
                    changed = true;
                }
                else
                    it++;
            }

            if (changed)
                q.push({i, j + 1});
        }

        if (i + 1 < grid.size())
        {
            changed = false;

            for (auto it = grid[i + 1][j].begin(); it != grid[i + 1][j].end();)
            {
                if (!down.count((*it) -> getUp()))
                {
                    it = grid[i + 1][j].erase(it);
                    changed = true;
                }
                else
                    it++;
            }

            if (changed)
                q.push({i + 1, j});
        }

        if (j)
        {
            changed = false;

            for (auto it = grid[i][j - 1].begin(); it != grid[i][j - 1].end();)
            {
                if (!left.count((*it) -> getRight()))
                {
                    it = grid[i][j - 1].erase(it);
                    changed = true;
                }
                else
                    it++;
            }

            if (changed)
                q.push({i, j - 1});
        }
    }

    for (int i2 = 0; i2 < grid.size(); i2++)
    {
        for (int j2 = 0; j2 < grid[i2].size(); j2++)
        {
            if (grid[i][j].size() <= 1 || (grid[i2][j2].size() > 1 && grid[i2][j2].size() < grid[i][j].size()))
            {
                i = i2;
                j = j2;
            }
        }
    }

    if (grid[i][j].size() <= 1)
        return grid;

    vector<Tile*> possible(grid[i][j].begin(), grid[i][j].end());
    array<array<unordered_set<Tile*>, SIZE>, SIZE> temp = {{{}}};
    int t;

    while (temp[i][j].empty())
    {
        t = rand() % possible.size();
        possible.erase(possible.begin() + t);

        grid[i][j] = {possible[t]};
        render(grid);
    
        temp = collapse(grid, i, j);
    }

    return temp;
}

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) || ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG))
        return 1;

    SDL_Window* window = SDL_CreateWindow("Wave Function Collapse", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RES, RES, 0);
    SDL_SetWindowIcon(window, IMG_Load("tiles/tile4.png"));

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;
    const mini* keys;

    SDL_PollEvent(&event);

    srand(time(nullptr));

    vector<Tile*> tiles;

    tiles.push_back(new Tile({"l", "l", "l", "l"}, "tiles/land0.png"));
    tiles.push_back(new Tile({"lww", "wwl", "l", "l"}, "tiles/land2.png"));
    tiles.push_back(new Tile({"lww", "w", "wwl", "l"}, "tiles/land3.png"));
    tiles.push_back(new Tile({"w", "w", "w", "w"}, "tiles/land4.png"));

    for (int i = 1; i < 3; i++)
        for (int j = 1; j < 4; j++)
            tiles.push_back(new Tile(tiles[i], j));

    array<array<unordered_set<Tile*>, SIZE>, SIZE> grid;

    for (auto& row : grid)
        row.fill(unordered_set<Tile*>(tiles.begin(), tiles.end()));

    grid = collapse(grid);
    render(grid);

    while (true)
    {
        while(SDL_WaitEvent(&event))
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
                        for (auto& row : grid)
                            row.fill(unordered_set<Tile*>(tiles.begin(), tiles.end()));

                        grid = collapse(grid);
                        render(grid);
                    }

                    break;

                case SDL_MOUSEBUTTONDOWN:

                    for (auto& row : grid)
                        row.fill(unordered_set<Tile*>(tiles.begin(), tiles.end()));

                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    
                    grid = collapse(grid, y / (SCALE), x / (SCALE));
                    render(grid);
            }
        }
    }
}
