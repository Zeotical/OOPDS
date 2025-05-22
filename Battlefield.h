#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BattleField
{
private:
    int width = 50;
    int height = 40;
    vector<vector<string>> field;

public:
    BattleField(); // constructor

    void printBattlefield();
    void placeRobot(int x, int y, string robot);
    void clearPosition(int x, int y);
    bool isOccupied(int x, int y);
    bool isInside(int x, int y);
    pair<int, int> getRandomEmptyPosition();
};

#endif
