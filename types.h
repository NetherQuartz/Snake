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

#define SNAKE "\u2588"
#define BORDER "\u2592\u2592"

#endif