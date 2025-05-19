#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream>
#include <vector>
using namespace std;

class BattleField
{
private:
public:
    BattleField() {};
    void printBattlefield(vector<vector<string>> &field)
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
};

#endif