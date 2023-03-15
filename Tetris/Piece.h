#ifndef PIECE_H
#define PIECE_H

#include <vector>

class Piece
{
    public:

    Piece();
    Piece(char t);

    void rotate(bool isClockwise);
    std::vector<std::vector<int>> getCells();

    private:

    char type;
    int rotation;
    std::vector<int> pos;

    friend class Tetris;
};

#endif