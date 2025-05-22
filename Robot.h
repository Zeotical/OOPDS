#include <string>
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

};


// Derived Classes
class SeeingRobot: virtual public Robot {
    private:

    public:
    bool positionTaken( int t, int u);
    bool inBounds (int t, int u);
    void look();
};
class MovingRobot : virtual public Robot {
    public: 
    MovingRobot():Robot(){};
    void move();
};
class ShootingRobot: virtual public Robot {
    public:
    void shoot();
};
class ThinkingRobot: virtual public Robot {
    public:
    void think();
};

// Multiple inheritance
class GenericRobot : public MovingRobot, public SeeingRobot, public ShootingRobot, public ThinkingRobot {
public:
GenericRobot(string name);
};