#ifndef TYPES_H
#define TYPES_H

enum directions
{
    UP, LEFT, DOWN, RIGHT, NONE
};

enum colors
{
    BLACK, WHITE, GREEN, BLUE, GRAY
};

struct Point
{
    int x, y;
    colors color;
};

// #define SNAKE "\u2588"
#define SNAKE "\033[42m \033[0m"
//#define BORDER "\033[90m\u2588\u2588\033[0m"
#define BORDER "\033[100m  \033[0m"

#endif