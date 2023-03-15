#include "Platformer.h"
#include "Bird.h"
#include "Text.h"

using namespace std;

int main()
{
    srand(time(nullptr));

    if (SDL_Init(SDL_INIT_EVERYTHING) || ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) || TTF_Init())
        return 1;

    array<int, 2> res = {768, 768};

    SDL_Renderer* renderer = SDL_CreateRenderer(SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, res[0], res[1], 0), -1, 0);
    SDL_Event event;
    const mini* keys;

    /*Thing* mario = new Thing({new Core(res[0] / 2, 0, 48, 48), new Box(renderer), new Texture(), new Motion(32, true), new Platformer(144), new Audio("jump")});
    mario -> get<Texture>() -> setTexture("mario", 6);
    mario -> get<Box>() -> setCamera(mario);*/

    Thing* bird = new Thing({new Core(res[0] / 2, res[1] / 2, 48, 48), new Box(renderer), new Texture(), new Motion(8, 0, 0, 1), new Bird(), new Audio("jump.wav")});
    bird -> get<Texture>() -> setTexture("bird.png", 2);
    bird -> get<Box>() -> setCamera(bird);

    Thing* camera = bird;

    Thing* ground = new Thing({new Core(res[0] / 2, res[1] + 24, 48, 48), new Box(renderer, camera)});

    vector<Thing*> pipes;

    pipes.push_back(nullptr); // left1
    pipes.push_back(nullptr); // left2
    pipes.push_back(nullptr); // mid1
    pipes.push_back(nullptr); // mid2

    int hole = 192 + rand() % 384;
    int diff;

    // right1 and right2
    pipes.push_back(new Thing({new Core(res[0], (hole - 96) / 2, 96, hole - 96), new Box(renderer, camera)/*, new Texture()*/}));
    pipes.push_back(new Thing({new Core(res[0], res[1] - (res[1] - 96 - hole) / 2, 96, res[1] - 96 - hole), new Box(renderer, camera)/*, new Texture()*/}));

    int score = 0;

    Thing* scoreText = new Thing({new Core(res[0] / 2, res[1] / 8, 0, 48), new Box(renderer), new Texture(), new Text("Score: " + to_string(score))});
    scoreText -> get<Core>() -> setColour(255, 0, 255);
    scoreText -> get<Text>() -> resize();

    int timeout = SDL_GetTicks() + 24;
    bool alive = true;

    while (true)
    {
        keys = SDL_GetKeyboardState(nullptr);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
					return 0;
                    
                case SDL_KEYDOWN:

                    if (keys[SDL_SCANCODE_ESCAPE])
						return 0;

                    /*if (keys[SDL_SCANCODE_SPACE])
                        bird -> get<Bird>() -> flap();*/

                    /*if (keys[SDL_SCANCODE_R])
                    {
                        mario -> get<Core>() -> setPos(384, 384);
                        mario -> get<Motion>() -> setVel(0, 0);
                    }

                    break;*/

                /*case SDL_MOUSEBUTTONDOWN:

                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    things.push_back(new Thing({new Core(x, y, 48, 48), new Box(renderer, camera), new Texture()}));
                    things.back() -> get<Core>() -> move(camera -> get<Core>() -> getPos()[0] - res[0] / 2, 0);
                    things.back() -> get<Texture>() -> setTexture("brick", 2);*/
            }
        }

        bird -> handle();
        bird -> update();

        for (Thing* pipe : pipes)
            if (pipe)
                pipe -> update();

        diff = pipes[4] -> get<Core>() -> getPos()[0] - bird -> get<Core>() -> getPos()[0];

        if (diff <= pipes[4] -> get<Core>() -> getSize()[0] / 2)
        {
            if (pipes[0])
                delete pipes[0];

            if (pipes[1])
                delete pipes[1];

            pipes[0] = pipes[2];
            pipes[1] = pipes[3];

            pipes[2] = pipes[4];
            pipes[3] = pipes[5];

            hole = 192 + rand() % 384;
            pipes[4] = new Thing({new Core(res[0] + diff + camera -> get<Core>() -> getPos()[0] - res[0] / 2, (hole - 96) / 2, 96, hole - 96), new Box(renderer, camera)/*, new Texture()*/});
            pipes[5] = new Thing({new Core(res[0] + diff + camera -> get<Core>() -> getPos()[0] - res[0] / 2, res[1] - (res[1] - 96 - hole) / 2, 96, res[1] - 96 - hole), new Box(renderer, camera)/*, new Texture()*/});

            score++;
            scoreText -> get<Text>() -> setText("Score: " + to_string(score));
            scoreText -> get<Text>() -> resize();
        }

        for (Thing* pipe : pipes)
            if (pipe)
                if (bird -> get<Motion>() -> uncollide(pipe))
                    alive = false;

        if (bird -> get<Motion>() -> uncollide(ground))
            alive = false;

        if (!alive)
        {
            Sound* slay = new Sound("smash.wav");
            slay -> play();

            bird -> get<Motion>() -> setVelX(0);

            while (!slay -> play())
            {
                bird -> update();

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);

                for (Thing* pipe : pipes)
                    if (pipe)
                        pipe -> render();

                bird -> render();

                scoreText -> render();

                SDL_RenderPresent(renderer);

                while (SDL_GetTicks() < timeout);
                timeout = SDL_GetTicks() + 24;
            }

            timeout = SDL_GetTicks() + 250;
            while (SDL_GetTicks() < timeout);

            return 0;
        }

        /*for (Thing* thing : things)
        {
            if (thing)
            {
                if (bird -> get<Motion>() -> uncollide(thing))
                return 0;

                switch (mario -> get<Motion>() -> uncollide(thing))
                {
                    case 1: // above
                        mario -> get<Platformer>() -> land();
                        break;

                    case 3: // below
                        things[i] -> get<Texture>() -> setFrame(1);
                }
            }
        }*/

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (Thing* pipe : pipes)
            if (pipe)
                pipe -> render();

        bird -> render();

        scoreText -> render();

        SDL_RenderPresent(renderer);

        while (SDL_GetTicks() < timeout);
        timeout = SDL_GetTicks() + 24;
    }
}