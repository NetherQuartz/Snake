#include <iostream>
#include <vector>
#include <unistd.h>
#include <string>
#include <termios.h>
#include <sys/ioctl.h>
#include <deque>
#include <stdlib.h>
#include <ctime>

#define SNAKE "\u2588"
#define BORDER "\u2592\u2592"

using namespace std;

int Width = 20;
int Height = 20;

enum directions
{
    UP, DOWN, LEFT, RIGHT, NONE
};

class Grid
{
    public:

    Grid(int width, int height)
    {
        myGrid = vector<vector<string>>(width, vector<string>(height, " "));
        this->width = width;
        this->height = height;
    }

    void Print()
    {
        for (int i = 0; i < width + 2; i++)
        {
            printf(BORDER);
        }
        printf("\n");
        for (int y = 0; y < height; y++)
        {
            printf(BORDER);
            for (int x = 0; x < width; x++)
            {
                printf("\033[32m%s%s\033[0m", myGrid[x][y].c_str(), myGrid[x][y].c_str());
            }
            printf("%s\n", BORDER);
        }
        for (int i = 0; i < width + 2; i++)
        {
            printf(BORDER);
        }
        printf("\n");
    }

    void Place(int x, int y, string texture)
    {
        myGrid[x][y] = texture;
    }

    void PlaceFruit(int x, int y)
    {
        myGrid[x][y] = "\033[31m\u2588\033[0m";
    }

    int width, height;

    private:

    vector<vector<string>> myGrid;
};

struct Point
{
    int x, y;
};

class Player
{
    public:

    Player(Grid &grid)
    {
        this->grid = &grid;

        x = grid.width / 2;
        y = grid.height / 2;

        tail = deque<Point>();
        tail.push_back({x, y});

        grid.Place(x, y, SNAKE);

        toGrow = false;
    }

    ~Player()
    {
        
    }

    void Print()
    {
        for (int i = 0; i < tail.size(); i++)
        {
            grid->Place(tail[i].x, tail[i].y, SNAKE);
        }
    }

    int Move(directions dir)
    {
        switch (dir)
        {
            case UP:
            if (y - 1 < 0) return false;
            y--;
            break;

            case DOWN:
            if (y + 1 > grid->height - 1) return false;
            y++;
            break;

            case LEFT:
            if (x - 1 < 0) return false;
            x--;
            break;

            case RIGHT:
            if (x + 1 > grid->width - 1) return false;
            x++;
            break;
        }

        if (dir != NONE)
        {
            grid->Place(tail.back().x, tail.back().y, " ");
            if (!toGrow)
            {
                tail.pop_back();
            }
            else
            {
                toGrow = false;
            }
            
            tail.push_front({x, y});
        }

        if (dir != cur)
        {
            cur = dir;
        }

        return true;
    }

    void Grow()
    {
        toGrow = true;
    }

    bool InTail(Point p, int pos = 0)
    {
        for (int i = pos; i < tail.size(); i++)
        {
            if (tail[i].x == p.x && tail[i].y == p.y)
            {
                return true;
            }
        }
        return false;
    }

    int x, y;

    private:

    bool toGrow;
    directions cur;
    Grid *grid;

    deque<Point> tail;
    
};

class Controls
{
    public:

    Controls()
    {
        tcgetattr(STDIN_FILENO,&old_tio);
        new_tio=old_tio;
        new_tio.c_lflag &= (~ICANON & ~ECHO);
        tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
    }

    ~Controls()
    {
        tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
        tcflush(0, TCIFLUSH);
    }

    directions Input()
    {
        if (!kbhit()) return NONE;

        int c = getchar();
        directions ans = NONE;

        switch (c) {
            case 'w':
            case 'W':
            ans = UP;
            break;

            case 'a':
            case 'A':
            ans = LEFT;
            break;

            case 's':
            case 'S':
            ans = DOWN;
            break;

            case 'd':
            case 'D':
            ans = RIGHT;
            break;

            case '\033':
            getchar();
            c = getchar();
            switch (c)
            {
                case 'A':
                ans = UP;
                break;

                case 'B':
                ans = DOWN;
                break;

                case 'C':
                ans = RIGHT;
                break;

                case 'D':
                ans = LEFT;
                break;
            }
            break;
        }
        tcflush(0, TCIFLUSH);
        return ans;
    }

    private:

    bool kbhit()
    {
        int byteswaiting;
        ioctl(0, FIONREAD, &byteswaiting);
        return byteswaiting > 0;
    }
    
    struct termios old_tio, new_tio;
    unsigned char c;
};

class Game
{
    public:

    Game(int width, int height)
    {
        isFail = false;
        score = 0;
        FPS = 2;

        grid = new Grid(width, height);
        snake = new Player(*grid);
        controls = new Controls();
    }

    ~Game()
    {
        delete grid;
        delete snake;
        delete controls;
    }

    void Update()
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
            int movement = snake->Move(dir);
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
            cout << "Your score: " << score << endl;
            usleep(1E6 / FPS);
        }
    }

    private:

    Point newFruit()
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

    bool isFail;
    int FPS;
    int score;
    Grid *grid;
    Player *snake;
    Controls *controls;
};

int main()
{
    srand(time(NULL));

    Game game(Width, Height);
    game.Update();
    cout << "GAME OVER!!!\n";

    return 0;
}