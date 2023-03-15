#include "Game.hpp"

int main()
{
    if (!game.init())
        return 0;

    while (game.handle())
    {
        game.update();
        game.render();
    }
}