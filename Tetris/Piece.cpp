#include "Piece.h"

using namespace std;

Piece::Piece()
{
    switch (rand() % 3)
    {
        case 0:
        type = 'I';
        break;

        case 1:
        type = 'O';
        break;

        case 2:
        type = 'T';
        break;

        case 3:
        type = 'S';
        break;

        case 4:
        type = 'Z';
        break;

        case 5:
        type = 'J';
        break;

        case 6:
        type = 'L';
    }

    rotation = 0;
    pos = {0, 4};
}

Piece::Piece(char t)
{
    type = t;
    rotation = 0;
    pos = {0, 4};
}

void Piece::rotate(bool isClockwise = true)
{
    if (isClockwise)
        rotation++;
    else
        rotation += 3;

    rotation %= 4;
}

vector<vector<int>> Piece::getCells()
{
    vector<vector<int>> cells;

    switch (type)
    {
        case 'I':

        switch (rotation)
        {
            case 0:
            case 2:

            cells.push_back({pos[0], pos[1] + 1});
            cells.push_back({pos[0] + 1, pos[1] + 1});
            cells.push_back({pos[0] + 2, pos[1] + 1});
            cells.push_back({pos[0] + 3, pos[1] + 1});

            break;

            case 1:
            case 3:

            cells.push_back({pos[0] + 1, pos[1] - 1});
            cells.push_back({pos[0] + 1, pos[1]});
            cells.push_back({pos[0] + 1, pos[1] + 1});
            cells.push_back({pos[0] + 1, pos[1] + 2});
        }

        break;

        case 'O':

        cells.push_back({pos[0], pos[1]});
        cells.push_back({pos[0], pos[1] + 1});
        cells.push_back({pos[0] + 1, pos[1]});
        cells.push_back({pos[0] + 1, pos[1] + 1});

        break;

        case 'T':

        switch (rotation)
        {
            case 0:

            cells.push_back({pos[0], pos[1] + 1});
            cells.push_back({pos[0] + 1, pos[1]});
            cells.push_back({pos[0] + 1, pos[1] + 1});
            cells.push_back({pos[0] + 1, pos[1] + 2});

            break;

            case 1:

            cells.push_back({pos[0], pos[1] + 1});
            cells.push_back({pos[0] + 1, pos[1] + 1});
            cells.push_back({pos[0] + 1, pos[1] + 2});
            cells.push_back({pos[0] + 2, pos[1] + 1});

            break;

            case 2:

            cells.push_back({pos[0] + 1, pos[1]});
            cells.push_back({pos[0] + 1, pos[1] + 1});
            cells.push_back({pos[0] + 1, pos[1] + 2});
            cells.push_back({pos[0] + 2, pos[1] + 1});

            break;

            case 3:

            cells.push_back({pos[0], pos[1] + 1});
            cells.push_back({pos[0] + 1, pos[1] + 1});
            cells.push_back({pos[0] + 1, pos[1]});
            cells.push_back({pos[0] + 2, pos[1] + 1});
        }

        break;
    }

    return cells;
}