#include <iostream>
#include <vector>
#include <unistd.h>
#include <string>
#include <termios.h>
#include <sys/ioctl.h>

#define SNAKE "\u2588"
#define BORDER "\u2592\u2592"

using namespace std;

int Width = 20;
int Height = 20;
int FPS = 2;

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
                printf("%s%s", myGrid[x][y].c_str(), myGrid[x][y].c_str());
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

    int width, height;

    private:

    vector<vector<string>> myGrid;
};

class Player
{
    public:

    Player(Grid &grid)
    {
        this->grid = &grid;

        x = grid.width / 2;
        y = grid.height / 2;

        grid.Place(x, y, SNAKE);
    }

    int Move(directions dir)
    {
        switch (dir)
        {
            case UP:
            if (y - 1 < 0) return false;
            clear_pos();
            grid->Place(x, y - 1, SNAKE);
            y--;
            break;

            case DOWN:
            if (y + 1 > grid->height - 1) return false;
            clear_pos();
            grid->Place(x, y + 1, SNAKE);
            y++;
            break;

            case LEFT:
            if (x - 1 < 0) return false;
            clear_pos();
            grid->Place(x - 1, y, SNAKE);
            x--;
            break;

            case RIGHT:
            if (x + 1 > grid->width - 1) return false;
            clear_pos();
            grid->Place(x + 1, y, SNAKE);
            x++;
            break;
        }
        if (dir != cur)
        {
            cur = dir;
        }
        return true;
    }

    int x, y;

    private:

    void clear_pos()
    {
        grid->Place(x, y, " ");
    }

    directions cur;
    Grid *grid;
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
        
        switch (c) {
            case 'w':
            case 'W':
            return UP;
            break;

            case 'a':
            case 'A':
            return LEFT;
            break;

            case 's':
            case 'S':
            return DOWN;
            break;

            case 'd':
            case 'D':
            return RIGHT;
            break;
        }
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
        isWin = false;
        score = 0;

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
        while (!isWin && !isFail)
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
            grid->Print();
            usleep(1E6 / FPS);
        }
        if (isFail)
        {
            cout << "YOU LOSE!!!\n";
        }
    }

    private:

    bool isFail, isWin;
    int score;
    Grid *grid;
    Player *snake;
    Controls *controls;
};

int main()
{
    Game game(Width, Height);
    game.Update();
    cout << "Game over\n";
    return 0;
}