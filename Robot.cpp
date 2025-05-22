// class Robot
// Below cannot have overlapping public mehtods & data members
// class MovingRobot: public Robot // handles movement
// class SeeingRobot: public Robot // handles seeing
// class Shooting Robot: public Robot // handles shooting
// class ThinkingRobot:public Robot //handles thinking
//***********************************************************
// Generic Robot using multiple inheritance will inherit all the above

#include "Robot.h" 
#include "Battlefield.h"
#include <iostream>
 
// int robotsPositionX= rand() % 50 ; // random num from (0 to 49) because vector indexing starts at 0 //width
// int robotsPositionY = rand() % 40; // random num from (0 to 39) //height
//Robot class 
Robot::Robot() {} //default constructor

Robot::Robot(string robotName){
    name = robotName;
    robotsPositionX= rand() % 50 ; // random num from (0 to 49) because vector indexing starts at 0 //width
    robotsPositionY = rand() % 40; // random num from (0 to 39) //height
}

int Robot::getPositionX(){
    return robotsPositionX;
}

int Robot::getPositionY(){
    return robotsPositionY;
}


string Robot::getname(){
    return name;
}
// ThinkingRobot

// SeeinngRobot
// bool SeeingRobot::inBounds(int t, int u){
//   if(getPositionY()+t<=39 && getPositionX()+u<=49 && getPositionY()+t>=0 && getPositionX()+u>=0){
//     return true;
//   }
//   else {
//     return false;
//   }
// }
// bool SeeingRobot::positionTaken(int t, int u){
//   if(BattleField.isOcc[getPositionY()+ t][getPositionX() + u] != "-" && battle.field[getPositionY()+ t][getPositionX() + u] != name ){
//     return true;
//   }
//   else {
//     return false;
//   }
// }
void SeeingRobot::look(BattleField &battle){
 int t = -1;
 int u = -1;
     while (t<=1) {
      u = -1;
      while (u<=1) {
         if(battle.isInside(getPositionY() + t,getPositionX() + u)){

          if(!battle.isOccupied(getPositionY() + t,getPositionX() + u)){
            
            cout << "Enemy robot found at " << getPositionY() + t<<" " << getPositionX() + u <<endl ;
          }
          else {
            cout << " Position possible to move to";
          }

        }
        else{
            cout <<  getPositionY() + t << " " << getPositionX() + u << " out of bounds " ;
         }  
          u++;
        }
        t++;
    }
}

// MovingRobot
void MovingRobot::move(BattleField &battle){
// int t = -1;
//  int u = -1;
//      while (t<=1) {
//         u = -1;
//        while (u<=1) {
//          if(getPositionY()+t<=39 && getPositionX()+u<=49 && getPositionY()+t>=0 && getPositionY()+u>=0){
//            cout << t << " " << u << endl;
           //battlefield[robotsPositionY][ robotsPositionX] = "- " ;
               battle.placeRobot(getPositionX() + u ,getPositionY() + t,getname());

           //battlefield[getPositionY()+ t][getPositionX() + u] = name ; //battlefield[row][col]
           battle.printBattlefield();
        //  }
           

        //   u++;
        // }
        // t++;
    //}
}

// ShootingRobot
void ShootingRobot::shoot() {
vector <int> values = {1,2,3,4,5,6,7,8,9,10};
int prob = rand() % 10 ; // 0 to 9
if (values[prob] <=7){ //Hit probability 70%
  cout << "Hit" ; // + other stuff will add after class 
}
else {
  cout << "Miss" ;
}
}

// GenericRobot later will move to it's own file
GenericRobot::GenericRobot(string name):Robot(name){}