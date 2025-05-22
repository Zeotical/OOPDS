#include "Battlefield.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // for rand()

int width = 50;  // col, x
  int height = 40 ; // row, y

BattleField::BattleField(){
   field = vector<vector<string>>(height, vector<string>(width, "- "));

}
 
void BattleField::printBattlefield()
{
    for (const auto &row : field)
    {
        for (const auto &col : row)
        {
            cout << col << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool BattleField::isInside(int x, int y)
{
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool BattleField::isOccupied(int x, int y)
{
    return isInside(x, y) && field[y][x] != "- ";
}

void BattleField::placeRobot(int x, int y, string robot)
{
    if (!isOccupied(x, y) && isInside(x, y))
    {
        field[y][x] = robot;
    }
    else
    {
        // Retry at a new random position
        auto [newX, newY] = getRandomEmptyPosition();
        placeRobot(newX, newY, robot);
    }
}

void BattleField::clearPosition(int x, int y)
{
    if (isInside(x, y))
    {
        field[y][x] = "- ";
    }
}

pair<int, int> BattleField::getRandomEmptyPosition()
{
    int x, y;
    do
    {
        x = rand() % width;
        y = rand() % height;
    } while (isOccupied(x, y));
    return {x, y};
}
