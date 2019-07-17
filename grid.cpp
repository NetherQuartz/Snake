#include "grid.h"
#include "types.h"

#include <iostream>

Grid::Grid(int width, int height)
{
    myGrid = std::vector<std::vector<std::string>>(width, std::vector<std::string>(height, " "));
    this->width = width;
    this->height = height;
}

void Grid::Print()
{
    for (int y = 0; y < height; y++)
    {
        std::cout << BORDER;
        for (int x = 0; x < width; x++)
        {
            std::cout << "\033[32m" << myGrid[x][y] << myGrid[x][y] << "\033[0m";
        }
        std::cout << BORDER << std::endl;
    }
}

void Grid::Place(int x, int y, std::string texture)
{
    myGrid[x][y] = texture;
}

void Grid::PlaceFruit(int x, int y)
{
    myGrid[x][y] = "\033[41m \033[0m";
}