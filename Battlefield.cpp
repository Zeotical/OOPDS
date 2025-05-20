#include "Battlefield.h"
#include <iostream>
#include <vector>

void BattleField::printBattlefield(vector<vector<string>> &field)
{
    for (auto row : field)
    {
        for (auto col : row)
        {
            cout << col << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void BattleField::placeRobot(int x, int y, string symbol)
{
    if (isInside(x, y))
    {
        field[y][x] = symbol;
    }
}

void BattleField::clearPosition(int x, int y)
{
    if (isInside(x, y))
    {
        field[y][x] = ".";
    }
}

bool BattleField::isOccupied(int x, int y)
{
    return isInside(x, y) && field[y][x] != ".";
}

bool BattleField::isInside(int x, int y)
{
    return x >= 0 && x < width && y >= 0 && y < height;