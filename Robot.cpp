// class Robot
// Below cannot have overlapping public mehtods & data members
// class MovingRobot: public Robot // handles movement
// class SeeingRobot: public Robot // handles seeing
// class ShootingRobot: public Robot // handles shooting
// class ThinkingRobot:public Robot //handles thinking
//***********************************************************
// Generic Robot using multiple inheritance will inherit all the above

#include "Robot.h" 
#include "Battlefield.h"
#include <iostream>

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
 void MovingRobot::move(){
// int t = -1;
//  int u = -1;
//      while (t<=1) {
//         u = -1;
//         while (u<=1) {
//          if(ro.getPositionY()+t<=39 && ro.getPositionX()+u<=49 && ro.getPositionY()+t>=0 &&  ro.getPositionX()+u>=0){
//            cout << t << " " << u << endl;
//            battlefield[ro.getPositionY()+ t][ro.getPositionX() + u] = "R2"; //battlefield[row][col]
//            battle.printBattlefield(battlefield);
//          }
           

//           u++;
//         }
//         t++;
//     }
}
// SeeinngRobot
// void SeeingRobot::positionTaken(){

// }
void SeeingRobot::look(){
 int t = -1;
 int u = -1;
     while (t<=1) {
        u = -1;
        while (u<=1) {
         if(getPositionY()+t<=39 && getPositionX()+u<=49 && getPositionY()+t>=0 && getPositionX()+u>=0){
            //if(battlefield[getPositionY()+ t][getPositionX() + u] != "-" ){}

         }
         else{
            cout << getPositionY() + t << " " << getPositionX() + u << "out of bounds" ;
         }  

          u++;
        }
        t++;
    }
}
// ThinkingRobot
// ShootingRobot

