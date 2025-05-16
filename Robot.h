#include <string>
using namespace std;

class Robot {
    private:
    string name;
    int lives;
    int robotsPositionX;
    int robotsPositionY;

    public:
    Robot ();
};

// move the below to robotcpp file

// lives
// position
// type
// name

// basic robot functions etc

// robotsPostionX = rand(0,50) //c++ doesnt really work like this for range
//robotsPositionY = rand(0,40)

//srand(time(0)); //each time program runs get a new random number

//positionforx = rand() % 51 ; //(0 to 50)
//positionfory = rand() % 41; // (0 to 40)