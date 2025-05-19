#include <string>
using namespace std; // not recc to use this look into it

// Base Class
class Robot {
    private:
    string name;
    string type;
    int lives = 3;
    int shells = 10; // max 10 
    int robotsPositionX; // row
    int robotsPositionY; // col

    public:
    Robot ();
    int getPositionX();
    int getPositionY();

};


// Derived Classes
class SeeingRobot: public Robot {
    private:

    public:
    //bool positionTaken();
    void look();
};
class MovingRobot : public Robot {
    public:
    void move();
};
class ShootingRobot: public Robot {
    public:
    void shoot();
};
class ThinkingRobot:public Robot {
    public:
    void think();
};