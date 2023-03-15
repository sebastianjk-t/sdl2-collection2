#include "Tetris.h"
#include <iostream>

using namespace std;

Tetris::Tetris()
{
    grid = std::vector<std::vector<bool>>(20, std::vector<bool>(10, false));
    piece = new Piece();
}

Tetris::Tetris(int rows, int cols)
{
    grid = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
    piece = new Piece();
}

bool Tetris::tick()
{
    if (!move('D'))
    {
        solidify();
        checkClears();

        delete piece;
        piece = new Piece();

        if (!checkCollision())
            return false;
    }

    return true;
}

bool Tetris::move(char dir)
{
    switch (dir)
    {
        case 'L':

        (piece -> pos[1])--;

        if (!checkCollision())
        {
            (piece -> pos[1])++;
            return false;
        }

        return true;

        case 'R':

        (piece -> pos[1])++;

        if (!checkCollision())
        {
            (piece -> pos[1])--;
            return false;
        }

        return true;

        case 'C':

        piece -> rotate(true);

        if (!checkCollision())
        {
            piece -> rotate(false);
            return false;
        }

        return true;

        case 'A':

        piece -> rotate(false);

        if (!checkCollision())
        {
            piece -> rotate(true);
            return false;
        }

        return true;

        case 'D':

        (piece -> pos[0])++;

        if (!checkCollision())
        {
            (piece -> pos[0])--;
            return false;
        }

        return true;
    }

    return false;
}

void Tetris::render()
{
    vector<vector<bool>> tempGrid = grid;
    vector<vector<int>> cells = piece -> getCells();
    string line;

    for (vector<int> cell : cells)
        tempGrid[cell[0]][cell[1]] = true;

    for (int i = 0; i < grid[0].size() + 2; i++)
        line += "[]";

    cout << line << endl;

    for (vector<bool> row : tempGrid)
    {
        line.clear();

        line += "[]";

        for (bool cell : row)
        {
            if (cell)
                line += "[]";
            else
                line += "  ";
        }

        line += "[]";

        cout << line << endl;
    }

    line.clear();

    for (int i = 0; i < grid[0].size() + 2; i++)
        line += "[]";

    cout << line << endl;
}

void Tetris::render(SDL_Renderer* renderer, int scale)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

    SDL_Rect rect;

    rect.w = scale;
    rect.h = scale;

    rect.y = 0;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (vector<bool> row : grid)
    {
        rect.x = 0;

        for (bool cell : row)
        {
            if (cell)
                SDL_RenderFillRect(renderer, &rect);

            rect.x += scale;
        }

        rect.y += scale;
    }

    vector<vector<int>> cells = piece -> getCells();

    SDL_SetRenderDrawColor(renderer, 0, 127, 255, 255);

    for (vector<int> cell : cells)
    {
        rect.y = cell[0] * scale;
        rect.x = cell[1] * scale;

        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}

bool Tetris::checkCollision()
{
    vector<vector<int>> cells = piece -> getCells();

    for (vector<int> cell : cells)
        if (cell[0] < 0 || cell[0] >= grid.size() || cell[1] < 0 || cell[1] >= grid[0].size() || grid[cell[0]][cell[1]])
            return false;

    return true;
}

void Tetris::solidify()
{
    vector<vector<int>> cells = piece -> getCells();

    for (vector<int> cell : cells)
        grid[cell[0]][cell[1]] = true;
}

void Tetris::checkClears()
{
    int width = grid[0].size();
    int count;

    for (int i = grid.size() - 1; i >= 0; i--)
    {
        for (count = 0; count < width; count++)
            if (!grid[i][count])
                break;

        if (count == width)
        {
            for (int j = i; j > 0; j--)
                grid[j] = grid[j - 1];

            grid[0].clear();
            grid[0].resize(grid[1].size(), false);
            
            i++;
        }
    }
}