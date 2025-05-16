//class robot
// class MovingRobot: public robot // handles movement
//class SeeingRobot: public robot // handles seeing
//class ShootingRobot: public robot // handles shooting
//class ThinkingRobot:public robot //handles thinking
//Generic robot using multiple inheritance will inherit all the above

#include "Robot.h" 

//Robot class 
Robot::Robot() {
robotsPositionX= rand() % 51 ; // random num from (0 to 50)
robotsPositionY = rand() % 41; // random num from (0 to 40) 
}

int Robot::getPosition(){
    return robotsPositionX, robotsPositionY;
}


