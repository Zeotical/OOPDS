#include "Battlefield.h"
#include <iostream>
#include <vector>

void BattleField::printBattlefield(vector<vector<string>> &field) {
    for (auto row : field) {
                for (auto col : row)
                {
                    cout << col << " ";
                }
                cout << endl;
            }
            cout << endl;
}

