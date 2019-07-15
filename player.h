#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "grid.h"

#include <deque>

class Player
{
    public:

    Player(Grid &);

    void Print();

    bool Move(directions);

    void Grow();

    bool InTail(Point, int pos = 0);

    int x, y;

    private:

    bool toGrow;
    directions cur;
    Grid *grid;

    std::deque<Point> tail;
};

#endif