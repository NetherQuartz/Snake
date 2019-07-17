#include "game.h"

#include <iostream>
//#include <string>
#include <unistd.h>

Game::Game(int width, int height)
{
    isFail = false;
    score = 0;
    FPS = 2;

    grid = new Grid(width, height);
    snake = new Player(*grid);
    controls = new Controls();
}

Game::~Game()
{
    delete grid;
    delete snake;
    delete controls;
}

void Game::Update()
{
    directions dir = NONE;

    Point fruit = newFruit();

    do
    {
        printf("\033c");

        char buf[50];
        sprintf(buf, "\033[100;37mYour score: %d\033[0m", score);
        std::string yourScore = buf;
        std::cout << yourScore;

        // чтобы влезла надпись your score
        for (int i = 0; i < grid->width * 2 - yourScore.size() + 17; i++)
        {
            std::cout << "\033[100m \033[0m";
        }
        std::cout << std::endl;

        directions new_dir = controls->Input();
        if (new_dir != NONE)
        {
            dir = new_dir;
        }
        
        bool movement = snake->Move(dir);
        if (!movement)
        {
            isFail = true;
        }

        if (snake->InTail({snake->x, snake->y}, 1))
        {
            isFail = true;
        }
        
        if (fruit.x == snake->x && fruit.y == snake->y)
        {
            fruit = newFruit();
            snake->Grow();
            FPS += 1;
            score++;
        }

        snake->Print();
        grid->PlaceFruit(fruit.x, fruit.y);
        
        grid->Print();

        if (!isFail)
        {
            for (int i = 0; i < grid->width + 2; i++)
            {
                std::cout << "\033[100;37m  \033[0m";
            }
            std::cout << std::endl;
        }
        else
        {
            std::string gameOver = "\033[100;37mGAME OVER!!!\033[0m";
            std::cout << gameOver;

            // чтобы влезла надпись game over
            for (int i = 0; i < grid->width - 4; i++)
            {
                std::cout << "\033[100;37m  \033[0m";
            }
            std::cout << std::endl;
        }

        usleep(1E6 / FPS);
    } while (!isFail);
}

Point Game::newFruit()
{
    Point fruit;
    do
    {
        int x = rand() % grid->width;
        int y = rand() % grid->height;
        fruit = {x, y};
    } while (snake->InTail(fruit));
    
    return fruit;
}