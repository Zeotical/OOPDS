// class Robot Base class 
//***********************************************************
// Below cannot have overlapping public mehtods & data members (Derived classes)
// class MovingRobot: public Robot // handles movement
// class SeeingRobot: public Robot // handles seeing
// class Shooting Robot: public Robot // handles shooting
// class ThinkingRobot:public Robot //handles thinking
//***********************************************************
// Generic Robot using multiple inheritance will inherit all the above

#include "Robot.h" 
#include "Battlefield.h"
#include <iostream>
 

//Robot class 
Robot::Robot() {} //default constructor

Robot::Robot(string robotName){
    name = robotName;
    robotsPositionX= rand() % 30 ; // random num from (0 to 29) because vector indexing starts at 0 //width
    robotsPositionY = rand() % 20; // random num from (0 to 19) //height
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
void SeeingRobot::look(BattleField &battle){
 int t = -1;
 int u = -1;
     while (t<=1) {
      u = -1;
      while (u<=1) {
        if(battle.isInside(getPositionX() + u,getPositionY() + t)){ // can join with the below if? or nvm

          if(battle.isOccupied(getPositionX() + u,getPositionY() + t) && t!=0 && u!=0){  //(width,height) (row,col)
            
            cout << "Enemy robot found at " << getPositionX() + u<<" " << getPositionY() + t <<endl ;
          }
          else if (t!=0 && u!=0) {
            //cout << "Possible positions to move to";
            movePositions.push_back(make_pair(getPositionX() +u,getPositionY() + t));
            //clear vector after moving //everytime I run I get smth diff

          }
        }
        else{
            cout <<  getPositionY() + t << " " << getPositionX() + u << " out of bounds " <<endl ;
         }  
          u++;
        }
        t++;
    }
}

// MovingRobot
void MovingRobot::move(BattleField &battle){ //smth wrong here 

  oldX = getPositionX(); //why not jus use robotpos
  oldY = getPositionY();
  battle.clearPosition(oldX,oldY);
  if (movePositions.size()> 0) {  
    int i =  rand() % movePositions.size();//from the possible to move to positions we pick a random one
    
    battle.placeRobot(movePositions[i].first,movePositions[i].second,getname()); //else statement will not be triggered because movePositions only returns unoccupied positions
    robotsPositionX = movePositions[i].first ;
    robotsPositionY = movePositions[i].second ;
    movePositions.clear();
  }
           
}

// ShootingRobot
void ShootingRobot::fire() {
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