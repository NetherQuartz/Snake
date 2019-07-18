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

    std::string username;

    private:

    Point newFruit();

    bool isFail;
    int FPS;
    int score;
    int high;

    std::string highName;

    int width;
    int height;

    Grid *grid;
    Player *snake;
    Controls *controls;
};

#endif