#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BattleField
{
   
public:
    int width;
    int height;
    vector<vector<string>> field;
    BattleField();
    BattleField(int w, int h);
    void initialize(int w, int h);
    void printBattlefield();
    void placeRobot(int x, int y, const string &robot);
    void clearPosition(int x, int y);
    bool isOccupied(int x, int y) const;
    bool isInside(int x, int y) const;
    pair<int, int> getRandomEmptyPosition();
    void moveRobot(int oldX, int oldY, int newX, int newY);

    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    string getCell(int x, int y) const;
};

#endif