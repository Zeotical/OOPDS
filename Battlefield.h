#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream>
#include <vector>
using namespace std;

class BattleField
{
private:
public:

    BattleField() = default ;
    void printBattlefield(vector<vector<string>> &field) ;
};
#endif