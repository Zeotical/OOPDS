#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <queue>
#include "Battlefield.h"

class GenericRobot;

// Base Class
class Robot {
    private:
    string type;
    protected:
    int lives; // max 3
    int robotsPositionX; // row
    int robotsPositionY; // col
    int kills;
    int shells; // max 10
    int upgrades; // max 3


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
    string robottotrackName ;
    GenericRobot* robottotrack ;
    vector <GenericRobot> trackedrobots;
    void trackbot(BattleField &battle);

};
class MovingRobot: virtual public Robot {
    public: 
    MovingRobot():Robot(), jumpUsesLeft(3){};
    int oldX;
    int oldY;
    void move(BattleField &battle);
    int jumpUsesLeft; // Declaration of jumpUsesLeft
    void jumpBot(BattleField &battle);

};
class ShootingRobot: virtual public Robot {
    public:
    vector <int> values;
    int probability ;
    string destroyedRobotName ;
    GenericRobot* destroyedRobot ;
    void fire(BattleField &battle);
    void semiAutoBot(BattleField &battle);
    void thirtyShotBot () ; // add var from cpp here 
   

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
static queue <GenericRobot*> re_enteringRobots;


};
#endif
