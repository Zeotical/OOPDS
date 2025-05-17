#include <string>
using namespace std; // not recc to use this look into it

// Base Class
class Robot {
    private:
    string name;
    int lives;
    int robotsPositionX; // row
    int robotsPositionY; // col
    int shells; // max 10 

    public:
    Robot ();
    int getPositionX();
    int getPositionY();

};


// Derived Classes
class SeeingRobot: public Robot {
    private:

    public:
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