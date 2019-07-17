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

    Game game(Width, Height);
    game.Update();
    //std::cout << "GAME OVER!!!\n";

    return 0;
}