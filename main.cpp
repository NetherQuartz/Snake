#include "main.h"
#include "game.h"

#include <iostream>
#include <stdlib.h>
#include <ctime>

int Width = 30;
int Height = 30;

int main()
{
    srand(time(NULL));

    Game *game = new Game(Width, Height);

    while (true)
    {
        game->Update();
        if (!game->toClose)
        {
            std::cout << "Press any key to continue...\n";
            getchar();
            delete game;
            game = new Game(Width, Height);
        }
        else
        {
            break;
        }   
    }

    return 0;
}