#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream>
#include <vector>
using namespace std;

class BattleField
{
private:
    vector<vector<string>> field;
    int width, height;

public:
    BattleField() = default;
    void printBattlefield(vector<vector<string>> &field);
    void placeRobot(int x, int y, string symbol);
    void clearPosition(int x, int y);
    bool isOccupied(int x, int y);
    bool isInside(int x, int y);
};
#endif
