/**********|**********|**********|
Program: YOUR_FILENAME.cpp / YOUR_FILENAME.h
Course: Data Structures and Algorithms? oopds
Trimester: 2410
Name: Frank Carrano
ID: 1071001234
Lecture Section: TC101
Tutorial Section: TT1L
Email: abc123@yourmail.com
Phone: 018-1234567
**********|**********|**********/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

// header files
#include "Robot.h"


using namespace std;

const int MaxWidth = 50; //col, x
const int MaxHeight = 40; //row, y

class BattleField
{
private:
public:

BattleField(){};
void printBattlefield(vector<vector<string>>& field){
    for (auto row: field) {
        for (auto col: row) {
            cout << col << " ";
        }
        cout << endl;
    }
  	cout << endl;
}
};

int main(){

srand(time(0)); //each time program runs get a new random number
vector <vector<string>> battlefield (MaxHeight, vector<string>(MaxWidth, "- ")); //row then col then value to insert
BattleField battle;
Robot ro;
cout << ro.getPositionY() << " " << ro.getPositionX() << endl; //only main.cpp is comipling need to build executable / use g++ main.cpp Robot.cpp

battle.printBattlefield(battlefield);

 battlefield[ro.getPositionY()][ro.getPositionX()] = "R2"; //battlefield[row][col]
 battle.printBattlefield(battlefield);

// what if two robots get same position? need to implement logic so if positiontaken generte new random num

return 0;
}


