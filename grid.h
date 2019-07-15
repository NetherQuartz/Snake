#ifndef GRID_H
#define GRID_H

#include <string>
#include <vector>

class Grid
{
    public:

    Grid(int, int);

    void Print();

    void Place(int, int, std::string);

    void PlaceFruit(int, int);

    int width, height;

    private:

    std::vector<std::vector<std::string>> myGrid;
};

#endif