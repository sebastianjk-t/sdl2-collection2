#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <map>

#include "Tower.hpp"
#include "Bloon.hpp"

class Game
{
    SDL_Event event;
    const unsigned char* keys;

    std::map<std::string, SDL_Texture*> textures;
    std::vector<std::vector<bool>> grid;

    int timer = 0;
    int lives = 200;
    int money = 200;

    TTF_Font* font;

    Tower* selected = nullptr;
    std::vector<SDL_Rect> panels;

public:

    SDL_Renderer* renderer;

    std::vector<Tower*> towers;
    std::vector<Bloon*> bloons;
    std::vector<Dart*> darts;

    int width = 1024;
    int height = 768;
    int scale = 64;

    bool init();
    bool handle();
    void update();
    void render();

    SDL_Texture* getTexture(std::string name);
    std::vector<std::vector<bool>> parseGrid(std::string file);

    void renderText(std::string text, SDL_Rect rect, SDL_Color colour = {0, 0, 0}, bool rightAlign = false);
};

extern Game game;