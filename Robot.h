#include <string>
#include <vector>
#include "Battlefield.h"

using namespace std; // not recc to use this look into it
// extern int robotsPositionX;
// extern int robotsPositionY;


// Base Class
class Robot {
    private:
    string type;
    int lives = 3;
    int shells = 10; // max 10 
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
};


// Derived Classes
class SeeingRobot: virtual public Robot {
    private:

    public:
    //bool positionTaken( int t, int u);
    //bool inBounds (int t, int u);
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