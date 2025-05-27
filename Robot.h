#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <queue>
#include "Battlefield.h"

using namespace std; // not recc to use this look into it

class GenericRobot;

// Base Class
class Robot {
    private:
    string type;
    int shells; // max 10 // can jus put this in shoot func why here?
    int upgrades; // max 3
    protected:
    int lives; // max 3
    int robotsPositionX; // row
    int robotsPositionY; // col
    int kills;


    public:
    string name;
    int numOfRobots;
    Robot () ;
    Robot (string robotName,string robotType);
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
class MovingRobot: virtual public Robot {
    public: 
    MovingRobot():Robot(){};
    int oldX;
    int oldY;
    void move(BattleField &battle);
};
class ShootingRobot: virtual public Robot {
    public:
    void fire(BattleField &battle);
    string destroyedRobotName ;
    GenericRobot* destroyedRobot ;

};
class ThinkingRobot: virtual public Robot {
    public:
    void think();
};

// Multiple inheritance
class GenericRobot : public MovingRobot, public SeeingRobot, public ShootingRobot, public ThinkingRobot {
public:
GenericRobot(string name);
static map<string, GenericRobot> robotObjects; //can jus use emplace to construct diretly in here instead of pointers==getting the address 

static string type; //all objects from this class share the same type
static GenericRobot getRobotByName(string& name) ;
static queue <GenericRobot> re_enteringRobots;


};
#endif
