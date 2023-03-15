#ifndef TETRIS_H
#define TETRIS_H

#include "Piece.h"
#include <vector>
#include <SDL.h>

class Tetris
{
    public:

    Tetris();
    Tetris(int rows, int cols);

    bool tick(); // return false if loss
    bool move(char dir); // return false if couldn't move ye
    void render();
    void render(SDL_Renderer* renderer, int scale);

    private:

    bool checkCollision(); // return false if didn't pass check, also used to check game over
    void solidify();
    void checkClears();

    std::vector<std::vector<bool>> grid;
    Piece* piece;
};

#endif