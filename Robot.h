#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <vector>
#include "Battlefield.h"

using namespace std; // not recc to use this look into it

// Base Class
class Robot {
    private:
    string type;
    int lives; // max 3
    int shells; // max 10 
    int kills;
    int upgrades; // max 3
    protected:
    int robotsPositionX; // row
    int robotsPositionY; // col

    public:
    string name;
    Robot () ;
    Robot (string robotName);
    int getPositionX();
    int getPositionY();
    string getname();
    vector <pair<int,int>> movePositions ; //use std::pair stores safe to move to positions
    vector <pair<int,int>> enemyPos ; //use std::pair stores enemy positions in surrounding area
};


// Derived Classes
class SeeingRobot: virtual public Robot {
    private:

    public:
    void look(BattleField &battle);

};
class MovingRobot : virtual public Robot {
    public: 
    MovingRobot():Robot(){};
    int oldX;
    int oldY;
    void move(BattleField &battle);
};
class ShootingRobot: virtual public Robot {
    public:
    void fire();
};
class ThinkingRobot: virtual public Robot {
    public:
    void think();
};

// Multiple inheritance
class GenericRobot : public MovingRobot, public SeeingRobot, public ShootingRobot, public ThinkingRobot {
public:
GenericRobot(string name);
//vector <pair<int,int>> movePositions ; //use std::pair stores safe to move to positions

};
#endif
