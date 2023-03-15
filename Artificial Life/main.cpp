#include <SDL2/SDL.h>
#include <vector>
#include <unordered_map>

#define RES 768
#define SIZE 8

using namespace std;

typedef unsigned char mini;

SDL_Renderer* renderer;

enum Colour 
{
    black,
    red,
    green,
    blue
};

struct Coords
{
    float x;
    float y;

    Coords operator +(Coords other)
    {
        return {x + other.x, y + other.y};
    }

    Coords operator -(Coords other)
    {
        return {x - other.x, y - other.y};
    }

    void operator +=(Coords other)
    {
        x += other.x;
        y += other.y;
    }

    void operator -=(Coords other)
    {
        x -= other.x;
        y -= other.y;
    }

    Coords operator *(float other)
    {
        return {x * other, y * other};
    }

    Coords operator /(float other)
    {
        return {x / other, y / other};
    }

    void operator *=(float other)
    {
        x *= other;
        y += other;
    }

    void operator /=(float other)
    {
        x /= other;
        y /= other;
    }

    float mod()
    {
        return sqrt(x * x + y * y);
    }
};

class Life
{
    public:
    Life(Coords pos, Colour colour = black)
    {
        this -> pos = pos;
        this -> colour = colour;
    }

    Life(Colour colour = black)
    {
        this -> pos = {RES / 2, RES / 2};
        this -> colour = colour;
    }

    bool operator==(Life& other)
    {
        return colour == other.colour;
    }

    Coords operator-(Life& other)
    {
        return pos - other.pos;
    }

    Colour col()
    {
        return colour;
    }

    void accelerate(Coords vel)
    {
        this -> vel += vel / 256;
    }

    void drag()
    {
        vel /= 2;
    }

    void tick()
    {
        //drag(); // also stops chaos lol

        pos += vel;

        if (pos.x < SIZE / 2 || pos.x > RES - SIZE / 2)
        {
            vel.x *= -1;
            pos.x = SDL_clamp(pos.x, SIZE / 2, RES - SIZE / 2);
        }

        if (pos.y < SIZE / 2 || pos.y > RES - SIZE / 2)
        {
            vel.y *= -1;
            pos.y = SDL_clamp(pos.y, SIZE / 2, RES - SIZE / 2);
        }
    }

    void render()
    {
        SDL_SetRenderDrawColor(renderer, 255 * (colour == red), 255 * (colour == green), 255 * (colour == blue), 255);
        SDL_Rect rect = {(int) pos.x - SIZE / 2, (int) pos.y - SIZE / 2, SIZE, SIZE};
        SDL_RenderFillRect(renderer, &rect);
    }

    private:
    Colour colour;
    Coords pos = {0, 0};
    Coords vel = {0, 0};
};

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
        return 1;

    renderer = SDL_CreateRenderer(SDL_CreateWindow("Artificial Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RES, RES, 0), -1, 0);
    SDL_Event event;
    const mini* keys;

    Coords ds;
    float d;

    vector<Life> lives;
    unordered_map<int, unordered_map<int, float>> forces; // how former reacts to latter

    forces[red][red] = 0.1;
    forces[black][green] = 0.2;
    forces[green][green] = 0.32;
    forces[green][red] = 0.17;
    forces[red][green] = 0.34;
    forces[green][black] = -0.34;
    forces[black][black] = 1;

    for (int i = 0; i < 256; i++)
        lives.push_back(Life({(float) (rand() % RES), (float) (rand() % RES)}, Colour(rand() % 3)));

    while (true)
    {
        while(SDL_PollEvent(&event))
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
                        lives.clear();
                        
                        for (int i = 0; i < 1024; i++)
                            lives.push_back(Life({(float) (rand() % RES), (float) (rand() % RES)}, Colour(rand() % 3)));
                    }
            }
        }

        for (int i = 0; i < lives.size(); i++)
        {
            for (int j = i + 1; j < lives.size(); j++)
            {
                ds = lives[i] - lives[j];
                d = ds.mod();

                if (d < 1)
                    ;//lives.erase(lives.begin() + j--);
                else// if (d < RES / 8) // latter stops chaos lol
                {
                    lives[i].accelerate(ds * forces[lives[i].col()][lives[j].col()] / -d);
                    lives[j].accelerate(ds * forces[lives[j].col()][lives[i].col()] / d);
                }
            }
        }

        for (Life& life : lives)
            life.tick();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (Life& life : lives)
            life.render();

        SDL_RenderPresent(renderer);
    }
}