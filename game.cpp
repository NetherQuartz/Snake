#include "game.h"

#include <iostream>
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

    while (!isFail)
    {
        printf("\033c");
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
        std::cout << "Your score: " << score << std::endl;
        usleep(1E6 / FPS);
    }
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