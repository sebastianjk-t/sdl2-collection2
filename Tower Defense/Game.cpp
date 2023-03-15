#include "Game.hpp"
#include "fstream"

bool Game::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) || ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) || TTF_Init())
        return false;

    renderer = SDL_CreateRenderer(SDL_CreateWindow("Tower Defense", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0/*SDL_WINDOW_RESIZABLE*/), -1, 0);
    grid = parseGrid("grid.txt");
    font = TTF_OpenFont("press_start.ttf", 256);

    panels = {{scale, scale * 8, scale * 4, scale * 3}, {scale * 6, scale * 8, scale * 4, scale * 3}, {scale * 11, scale * 8, scale * 4, scale * 3}};

    return true;
}

bool Game::handle()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT: return false;

            case SDL_KEYDOWN:

                keys = SDL_GetKeyboardState(nullptr);

                if (keys[SDL_SCANCODE_ESCAPE])
                    return false;

                if (keys[SDL_SCANCODE_R])
                {                    
                    bloons.clear();
                    towers.clear();
                    
                    lives = 200;
                    money = 200;

                    timer = 0;
                }

                break;

            case SDL_MOUSEBUTTONDOWN:

                int x, y;
                SDL_GetMouseState(&x, &y);

                if (event.button.button != SDL_BUTTON_LEFT)
                {
                    if (x < scale / 2 || x >= width - scale / 2 || y < scale / 2 || y >= height - scale / 2 || grid[y / scale][x / scale])
                        break;

                    if (grid[(y - scale / 2) / scale][(x - scale / 2) / scale] || grid[(y - scale / 2) / scale][(x + scale / 2) / scale] || grid[(y + scale / 2) / scale][(x - scale / 2) / scale] || grid[(y + scale / 2) / scale][(x + scale / 2) / scale])
                        break;
                }

                SDL_Point point = {x, y};
                bool hit = false;

                if (money >= 100)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        if (SDL_PointInRect(&point, &panels[i]))
                        {
                            selected -> buyStat(i);
                            money -= 100;
                            hit = true;
                        }
                    }
                }

                if (hit)
                    break;

                for (Tower* tower : towers)
                {
                    if ((Coords) {(float) x, (float) y} == tower -> getPos())
                    {
                        if (event.button.button == SDL_BUTTON_LEFT)
                            selected = tower;
                        else if (money >= 200)
                        {
                            tower -> levelUp();
                            money -= 200;
                        }

                        hit = true;
                    }
                }

                if (hit)
                    break;

                if (event.button.button == SDL_BUTTON_LEFT)
                    selected = nullptr;
                else if (money >= 200)
                {
                    towers.push_back(new Tower({(float) x, (float) y}));
                    money -= 200;
                }
        }
    }

    return true;
}

void Game::update()
{
    for (int i = 0; i < darts.size(); i++)
    {
        for (int j = 0; j < bloons.size(); j++)
        {
            if (darts[i] -> getPos() == bloons[j] -> getPos())
            {
                money += 2;

                if (bloons[j] -> popLayer())
                {
                    delete bloons[j];
                    bloons.erase(bloons.begin() + j);
                }

                j--;

                if (darts[i] -> usePierce())
                {
                    delete darts[i];
                    darts.erase(darts.begin() + i--);
                    break;
                }
            }
        }
    }

    for (Tower* tower : towers)
        tower -> update();

    for (int i = 0; i < darts.size(); i++)
    {
        if (!darts[i] -> update())
        {
            delete darts[i];
            darts.erase(darts.begin() + i--);
        }
    }

    float xf, yf;
    int x, y;

    for (int i = 0; i < bloons.size(); i++)
    {
        if (bloons[i] -> update())
        {
            xf = (float) (bloons[i] -> getPos().x - scale / 2) / (float) scale;
            yf = (float) (bloons[i] -> getPos().y - scale / 2) / (float) scale;

            if (xf == floor(xf) && yf == floor(yf))
            {
                x = (int) xf;
                y = (int) yf;

                if (y + 1 < 12 && grid[y + 1][x] && bloons[i] -> getDir().x)
                    bloons[i] -> setDir({0, 1});
                else if (x + 1 < 16 && grid[y][x + 1] && bloons[i] -> getDir().y)
                    bloons[i] -> setDir({1, 0});
                else if (x && grid[y][x - 1] && bloons[i] -> getDir().y)
                    bloons[i] -> setDir({-1, 0});
                else if (y && grid[y - 1][x] && bloons[i] -> getDir().x)
                    bloons[i] -> setDir({0, -1});

                bloons[i] -> makeProgress();
            }
        }
        else
        {
            delete bloons[i];
            bloons.erase(bloons.begin() + i--);

            lives--;
        }
        
    }

    timer++;

    if (!(timer % 64))
        bloons.push_back(new Bloon({(float)(-scale / 2), (float) (3 * scale / 2)}, {1, 0}, 1 + rand() % 3));

    std::sort(bloons.begin(), bloons.end(), Bloon::compareProgress);
}

void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, getTexture("background"), nullptr, nullptr);

    for (Dart* dart : darts)
        dart -> render();

    for (int i = bloons.size() - 1; i >= 0; i--)
        bloons[i] -> render();

    for (Tower* tower : towers)
        tower -> render(tower == selected);

    renderText("Lives: " + std::to_string(lives), {8, 10}, {217, 87, 99});
    renderText("Money: " + std::to_string(money), {8, 10}, {251, 242, 54}, true);

    // render panel

    if (selected)
    {
        for (SDL_Rect panel : panels)
            SDL_RenderCopy(renderer, getTexture("panel"), nullptr, &panel);

        for (int i = 3; i < 30; i += 10)
        {
            renderText("Buy", {scale * i / 2, scale * 17 / 2});
            renderText("$100", {scale * i / 2, scale * 10});
        }
        
        renderText("Speed", {scale * 3 / 2, scale * 9});
        renderText("Range", {scale * 13 / 2, scale * 9});
        renderText("Pierce", {scale * 23 / 2, scale * 9});
    }

    SDL_RenderPresent(renderer);
}

SDL_Texture* Game::getTexture(std::string name)
{
    if (!textures.count(name))
        textures[name] = SDL_CreateTextureFromSurface(renderer, IMG_Load((name + ".png").c_str()));

    return textures[name];
}

std::vector<std::vector<bool>> Game::parseGrid(std::string file)
{
    std::vector<std::vector<bool>> grid;

    if (file.find(".txt") != -1)
    {
        std::ifstream fileS(file);
        std::string line;
        int n;

        while (getline(fileS, line))
        {
            n = line.length();
            grid.push_back(std::vector<bool>(n));
            
            for (int i = 0; i < n; i++)
                grid.back()[i] = line[i] - '0';
        }
    }

    return grid;
}

void Game::renderText(std::string text, SDL_Rect rect, SDL_Color colour, bool rightAlign)
{
    TTF_SizeText(font, text.c_str(), &rect.w, &rect.h);

    rect.w /= 8;
    rect.h /= 8;

    if (rightAlign)
        rect.x = width - rect.x - rect.w;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, text.c_str(), colour));
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
}

Game game;