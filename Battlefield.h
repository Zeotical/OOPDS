#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream>
#include<string>
#include <vector>
using namespace std;

class BattleField
{
// private:
//     vector<vector<string>> field;
//     int width = 50;
//     int height = 40;

public:
 int width = 30;  // col, x
  int height = 20 ; // row, y

    vector<vector<string>> field ;
    

    BattleField();
    void printBattlefield();
    void placeRobot(int x, int y, string robot);
    void clearPosition(int x, int y);
    bool isOccupied(int x, int y);
    bool isInside(int x, int y);
};
#endif
