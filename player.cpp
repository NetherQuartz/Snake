#include "player.h"

Player::Player(Grid &grid)
{
    this->grid = &grid;

    x = grid.width / 2;
    y = grid.height / 2;

    tail = std::deque<Point>();
    tail.push_back({x, y});

    grid.Place(x, y, SNAKE);
    cur = NONE;

    toGrow = false;
}

void Player::Print()
{
    for (int i = 0; i < tail.size(); i++)
    {
        grid->Place(tail[i].x, tail[i].y, SNAKE);
    }
}

bool Player::Move(directions dir)
{
    // нельзя ползти в обратную сторону
    if (cur != NONE && (int)dir % 2 == (int)cur % 2)
    {
        dir = cur;
    }
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

void Player::Grow()
{
    toGrow = true;
}

bool Player::InTail(Point p, int pos)
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