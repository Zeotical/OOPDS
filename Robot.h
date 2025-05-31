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
    int robotsPositionX; // row
    int robotsPositionY; // col
    int kills;
    int shells; // max 10


    public:
    int lives; // max 3
    int upgrades; // max 3
    string name;
    int numOfRobots;
    Robot () ;
    Robot (string robotName,string robotType);
    void setPositionX(int posx);
    void setPositionY(int posy);
    int getPositionX();
    int getPositionY();
    string getname();
    vector <pair<int,int>> movePositions ; //use std::pair stores safe to move to positions
    vector <pair<int,int>> enemyPos ; //use std::pair stores enemy positions in surrounding area
    string handle_upgrades();
    int see = 0;
    int move = 0;
    int shoot = 0;
    int random ;
    int scout_bot_uses;
    int track_bot_uses;
    int hide_bot_uses;
    int jump_bot_uses;
    int long_shot_bot_uses;
    int semi_auto_bot_uses;
    int thirty_shot_uses;
    bool isAlive();
};


// Derived Classes
class SeeingRobot: virtual public Robot {
    private:

    public:
    void look(BattleField &battle);
    string robottotrackName ;
    GenericRobot* robottotrack ;
    vector <GenericRobot*> trackedrobots;
    vector <GenericRobot*>::iterator robotIsTracked; //std::vector for all
    void TrackBot(BattleField &battle);
    void ScoutBot(BattleField &battle);
};
class MovingRobot: virtual public Robot {
    public: 
    MovingRobot():Robot(), jumpUsesLeft(3){};
    int oldX;
    int oldY;
    void move(BattleField &battle);
    int jumpUsesLeft; // Declaration of jumpUsesLeft
    void JumpBot(BattleField &battle);

};
class ShootingRobot: virtual public Robot {
    public:
    vector <int> values;
    int probability ;
    string destroyedRobotName ;
    GenericRobot* destroyedRobot ;
    void fire(BattleField &battle);
    void SemiAutoBot(BattleField &battle);
    void ThirtyShotBot () ; // add var from cpp here 
    void LongShotBot(BattleField &battle);
    vector<string> choices;
    int current_kills;
    int tries ;
    int actual_shell_num;
   

};
class ThinkingRobot: virtual public Robot {
    public:
    int think();
};

// Multiple inheritance
class GenericRobot : public MovingRobot, public SeeingRobot, public ShootingRobot, public ThinkingRobot {
public:
GenericRobot(string name);
static map<string, GenericRobot> robotObjects; //can jus use emplace to construct diretly in here instead of pointers==getting the address 

static string type; //all objects from this class share the same type
static GenericRobot getRobotByName(string& name) ;
queue <GenericRobot*> re_enteringRobots;


};
#endif
