#include "grid.h"
#include "types.h"

Grid::Grid(int width, int height)
{
    myGrid = std::vector<std::vector<std::string>>(width, std::vector<std::string>(height, " "));
    this->width = width;
    this->height = height;
}

void Grid::Print()
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

void Grid::Place(int x, int y, std::string texture)
{
    myGrid[x][y] = texture;
}

void Grid::PlaceFruit(int x, int y)
{
    myGrid[x][y] = "\033[31m\u2588\033[0m";
}