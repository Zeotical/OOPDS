#include "Battlefield.h"
#include <iostream>
#include <vector>
#include <string>

int width = 50;  // col, x
  int height = 40 ; // row, y

BattleField::BattleField(){
   field = vector<vector<string>>(height, vector<string>(width, "- "));

}
 
void BattleField::printBattlefield()
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

bool BattleField::isInside(int x, int y)
{
    return x >= 0 && x < width && y >= 0 && y < height; }

bool BattleField::isOccupied(int x, int y)
{
    return field[y][x] != "- ";
}


void BattleField::placeRobot(int x, int y, string robot)
{
    // if (isInside(x, y))
    // {
    //     field[y][x] = symbol;
    // }

    if (!isOccupied(x,y) && isInside(x,y)) {
        field[y][x] = robot;
    }
    else {
        
        x = rand() % 50 ; // random num from (0 to 49) because vector indexing starts at 0 //width
        y = rand() % 40; // random num from (0 to 39) //height
        placeRobot(x, y, robot);
    }
}

void BattleField::clearPosition(int x, int y)
{
    if (isInside(x, y))
    {
        field[y][x] = "-";
    }
}


