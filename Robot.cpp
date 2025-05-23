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
        if(battle.isInside(getPositionX() + u,getPositionY() + t)){ // can join with the below if? or nvm

          if(battle.isOccupied(getPositionX() + u,getPositionY() + t) && t!=0 && u!=0){  //(width,height) (row,col)
            
            cout << "Enemy robot found at " << getPositionX() + u<<" " << getPositionY() + t <<endl ;
          }
          else {
            //cout << "Possible positions to move to";
            movePositions.push_back(make_pair(getPositionY() + t,getPositionX() +u));
            //clear vector after moving //everytime I run I get smth diff

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
void MovingRobot::move(BattleField &battle){ //smth wrong here 

  oldX = getPositionX();
  oldY = getPositionY();
  //battle.clearPosition(oldX,oldY);
  //if (movePositions.size()> 0) { 
   // int i =  rand() % movePositions.size() + 1;
    for(auto i:movePositions){
      cout << i.second << " " << i.first<<endl;
      battle.placeRobot(i.second,i.first,getname()); //}
      // robotsPositionX = movePositions[i].second ;
      // robotsPositionY = movePositions[i].first ;
  //battle.printBattlefield(); 
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