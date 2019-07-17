#ifndef TYPES_H
#define TYPES_H

enum directions
{
    UP, LEFT, DOWN, RIGHT, NONE
};

struct Point
{
    int x, y;
};

#define SNAKE "\033[42m \033[0m"
#define BORDER "\033[100m  \033[0m"

#endif