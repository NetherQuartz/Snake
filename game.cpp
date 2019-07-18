#include "game.h"
#include "save.h"

#include <iostream>
#include <unistd.h>
#include <iomanip>

Game::Game(int width, int height)
{
    isFail = false;
    score = 0;
    FPS = 2;
    this->width = width;
    this->height = height;

    toClose = false;

    grid = new Grid(width, height);
    snake = new Player(*grid);
    controls = new Controls();

    Save::record *highRec = Save::readHighScore();
    high = highRec->score;
    highName = highRec->username;
    delete highRec;

    username = getlogin();
}

Game::~Game()
{
    delete grid;
    delete snake;
    delete controls;
}

void Game::Update()
{
    std::string options = "| H-help | L-leaders | N-new name | ESC-exit";

    directions dir = NONE;

    Point fruit = newFruit();

    if (highName.size() == 0)
    {
        highName = username;
    }

    do
    {
        // очистка терминала
        printf("\033c");

        directions new_dir = controls->Input();
        switch (controls->todo)
        {
            case EXIT:
            toClose = true;
            controls->EchoOn();
            return;
            break;

            case LEADERS:
            {
                std::vector<Save::record> leaders = Save::listScores();

                if (leaders.size() == 0)
                {
                    std::cout << "It seems there is no leaders yet, be the first!\n";
                }
                else
                {
                    std::cout << "Current leaderboard:\n";
                    for (Save::record rec : leaders)
                    {
                        std::cout << std::setw(4) << rec.score << std::setw(0) << " - " << rec.username << std::endl;
                    }
                }
                std::cout << "\nPress SPACE to continue...\n";
                while (char c = getchar() != ' ');
                printf("\033c");
                controls->todo = DEFAULT;
            }
            break;

            case CHUSER:
            {
                std::cout << "Enter you name: (SPACE to cancel)\n";
                controls->BufferOff();
                char buf[16];

                *buf = getchar();
                if (buf[0] == ' ')
                {
                    controls->EchoOff();
                    controls->todo = DEFAULT;
                    break;
                }
                scanf("%s", &buf[1]);
                username = buf;

                controls->EchoOff();
                controls->todo = DEFAULT;
            }
            break;

            case HELP:
            {
                std::string helpMsg = "Use WASD or arrows to control the snake. Eat fruits to grow and increase your score. You also can't move backwards. If you bite your tail or bump into a wall, you lose.\n\nWritten by NetherQuartz, follow me on Github: https://github.com/NetherQuartz.";
                std::cout << helpMsg << std::endl;
                std::cout << "\nPress SPACE to continue...\n";
                while (char c = getchar() != ' ');
                printf("\033c");
                controls->todo = DEFAULT;
            }
            break;
        }
        printf("\033c");

        char buf[50];
        sprintf(buf, "\033[100;37mYour score: %d\033[0m", score);
        std::string yourScore = buf;
        sprintf(buf, "High score: %d (%s)", high, highName.c_str());
        std::string highScore = buf;

        std::cout << yourScore;

        // чтобы влезла надпись your score
        for (int i = 0; i < grid->width * 2 - yourScore.size() + 17 - highScore.size(); i++)
        {
            std::cout << "\033[100m \033[0m";
        }
        std::cout << "\033[100;37m" << highScore << "\033[0m" << std::endl;

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
            std::cout << "\033[100;37m" << username << "\033[0m";

            // чтобы влезла надпись options
            for (int i = 0; i < grid->width * 2 - options.size() + 4 - username.size(); i++)
            {
                std::cout << "\033[100;37m \033[0m";
            }
            std::cout << "\033[100;37m" << options << "\033[0m" << std::endl;
        }
        else
        {
            std::string gameOver = "\033[100;37mGAME OVER!!!\033[0m";
            std::cout << gameOver;
            Save::writeHighScore(username, score);

            // чтобы влезли надписи game over и options
            for (int i = 0; i < grid->width * 2 - 8; i++)
            {
                std::cout << "\033[100;37m \033[0m";
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