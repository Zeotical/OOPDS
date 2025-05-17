// class Robot
// Below cannot have overlapping public mehtods & data members
// class MovingRobot: public Robot // handles movement
// class SeeingRobot: public Robot // handles seeing
// class ShootingRobot: public Robot // handles shooting
// class ThinkingRobot:public Robot //handles thinking
//***********************************************************
// Generic Robot using multiple inheritance will inherit all the above

#include "Robot.h" 

//Robot class 
Robot::Robot() {
robotsPositionX= rand() % 50 ; // random num from (0 to 49) because vector indexing starts at 0 //width
robotsPositionY = rand() % 40; // random num from (0 to 39) //height
}

int Robot::getPositionX(){
    return robotsPositionX;
}

int Robot::getPositionY(){
    return robotsPositionY;
}

// MovingRobot

// SeeinngRobot
// ThinkingRobot
// ShootingRobot

