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
const int MaxWidth = 50;  // col, x
const int MaxHeight = 40; // row, y


BattleField battle;
vector<vector<string>> battlefield(MaxHeight, vector<string>(MaxWidth, "- ")); // row then col then value to insert

// int robotsPositionX= rand() % 50 ; // random num from (0 to 49) because vector indexing starts at 0 //width
// int robotsPositionY = rand() % 40; // random num from (0 to 39) //height
//Robot class 
 Robot::Robot() {} //default constructor
// robotsPositionX= rand() % 50 ; // random num from (0 to 49) because vector indexing starts at 0 //width
// robotsPositionY = rand() % 40; // random num from (0 to 39) //height
// }

int Robot::getPositionX(){
    return robotsPositionX;
}

int Robot::getPositionY(){
    return robotsPositionY;
}

Robot::Robot(string robotName){
    name = robotName;
}


// MovingRobot
void MovingRobot::move(){
  int robotsPositionX= rand() % 50 ; // random num from (0 to 49) because vector indexing starts at 0 //width
int robotsPositionY = rand() % 40; // random num from (0 to 39) //height
int t = -1;
 int u = -1;
     while (t<=1) {
        u = -1;
       while (u<=1) {
         if(robotsPositionY+t<=39 && robotsPositionX+u<=49 && robotsPositionY+t>=0 && robotsPositionY+u>=0){
           cout << t << " " << u << endl;
           //battlefield[robotsPositionY][ robotsPositionX] = "- " ;
           battlefield[robotsPositionY+ t][ robotsPositionX + u] = name ; //battlefield[row][col]
           battle.printBattlefield(battlefield);
         }
           

          u++;
        }
        t++;
    }
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
         if(robotsPositionY+t<=39 && robotsPositionX+u<=49 && robotsPositionY+t>=0 && robotsPositionY+u>=0){

          if(battlefield[robotsPositionY+ t][robotsPositionX + u] != "-" && battlefield[robotsPositionY+ t][robotsPositionX + u] != name ){
            
            cout << "Enemy robot found" ;
          
          }

         }
         else{
            cout <<  robotsPositionY + t << " " << robotsPositionX + u << " out of bounds " ;
         }  

          u++;
        }
        t++;
    }
}
// ThinkingRobot
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