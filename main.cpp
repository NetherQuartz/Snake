#include "main.h"
#include "game.h"

#include "save.h"

#include <iostream>
#include <stdlib.h>
#include <ctime>

int Width = 30;
int Height = 30;

int main()
{
    srand(time(NULL));

    while (true)
    {
        Game *game = new Game(Width, Height);
        game->Update();
        if (!game->toClose)
        {
            std::cout << "Press SPACE to continue...\n";
            while (char c = getchar() != ' ');
            delete game;
        }
        else
        {
            delete game;
            break;
        }   
    }

    return 0;
}