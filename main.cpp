#include "main.h"
#include "game.h"

#include "save.h"

#include <iostream>
#include <stdlib.h>
#include <ctime>

int Width = 30;
int Height = 30;

std::string UserName;

int main()
{
    srand(time(NULL));
    UserName = "";

    while (true)
    {
        Game *game = new Game(Width, Height);
        if (UserName != "")
        {
            game->username = UserName;
        }
        
        game->Update();

        UserName = game->username;
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