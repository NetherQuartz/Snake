#ifndef GAME_H
#define GAME_H

#include "types.h"
#include "grid.h"
#include "player.h"
#include "controls.h"

class Game
{
    public:

    Game(int, int);

    ~Game();

    void Update();

    bool toClose;

    private:

    Point newFruit();

    bool isFail;
    int FPS;
    int score;

    int width;
    int height;

    Grid *grid;
    Player *snake;
    Controls *controls;
};

#endif