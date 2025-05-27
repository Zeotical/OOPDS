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

Robot::Robot(string robotName, string robotType){
    name = robotName;
    type = robotType;
    lives = 3;
    numOfRobots ++ ;
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

          if(battle.isOccupied(getPositionX() + u,getPositionY() + t) && (t!=0 || u!=0)){  //(width,height) (row,col) // t!= 0  && u!=0 robot doesn't consider itself an enemy
            
            cout << "Enemy robot found at (" << getPositionY() + t<<" " << getPositionX() + u <<")" <<endl ;
            // 
            enemyPos.push_back(make_pair(getPositionX()+u,getPositionY() + t)) ;
          } // inner if 
          else if (!battle.isOccupied(getPositionX()+u,getPositionY()+t) && (t!=0 || u!=0)) { // don't need the first cond
            cout << "Possible positions to move to";
            movePositions.push_back(make_pair(getPositionX() +u,getPositionY() + t));
            cout <<  getPositionY() + t << " " << getPositionX() + u  <<endl ;

            //clear vector after moving //everytime I run I get smth diff

          } // else if
        } // outer if
        else{
            cout <<  getPositionY() + t << " " << getPositionX() + u << " out of bounds " <<endl ;
         } // outer else 
          u++;
        } // inner while
        t++;
    } // outer while
}

// MovingRobot
void MovingRobot::move(BattleField &battle){  

  oldX = getPositionX(); //why not jus use robotpos ye getpos is for outside methinks
  oldY = getPositionY();
  battle.clearPosition(oldX,oldY);
  if (movePositions.size()> 0) {  
    int i =  rand() % movePositions.size();//from the possible to move to positions we pick a random one
    
    battle.placeRobot(movePositions[i].first,movePositions[i].second,getname()); //else statement will not be triggered because movePositions only returns unoccupied positions
    robotsPositionX = movePositions[i].first ;
    robotsPositionY = movePositions[i].second ;
    movePositions.clear();
  } // if
           
}

// ShootingRobot
void ShootingRobot::fire(BattleField &battle) {
vector <int> values = {1,2,3,4,5,6,7,8,9,10};
int prob = rand() % 10 ; // 0 to 9
cout <<  name  << "used shoot action" << endl;
if (values[prob] <=7 && enemyPos.size()!=0){ //Hit probability 70%
   int i =  rand() % enemyPos.size();
   destroyedRobotName = battle.field[enemyPos[i].second][enemyPos[i].first]; // gets the name of the robot
  // using a map and the name get the object
   GenericRobot destroyedRobot = GenericRobot::robotObjects.at(destroyedRobotName);
  --destroyedRobot.lives; // reduce from the lives  of the loser robot
   battle.clearPosition(enemyPos[i].first,enemyPos[i].second); // x,y == row,col
  cout << name << " hits " << destroyedRobot.name << " at (" << enemyPos[i].second << "," << enemyPos[i].first << ") and destroyed it."  <<endl; 
  // send the loser robot to the backrooms using queue can reneter in next round? 
   if (destroyedRobot.lives > 0){
   GenericRobot::re_enteringRobots.push(destroyedRobot); }
   else {
    cout << destroyedRobotName << " has used up all it's lives and will not be entering again." << endl;
   }
  enemyPos.clear();
  kills ++ ;    // add to the kills of the winner robot
  //updates ++; / call upgragde func    // if kills ++ then choose upgrade 
  } //if
else {
  cout << name << " missed"  ;
} //else
}

//GenericRobot
string GenericRobot::type = "Generic Robot" ; //static variable, shared by all objects
GenericRobot::GenericRobot(string name):Robot(name, GenericRobot::type){}
map<string,GenericRobot> GenericRobot::robotObjects; // static definition
queue <GenericRobot> GenericRobot::re_enteringRobots;

GenericRobot GenericRobot::getRobotByName(string& name) {

  return GenericRobot::robotObjects.at(name) ; }

// do func here ??
// UPGRADES
//There are three possible areas to upgrade. They are moving, shooting and seeing. 
// 1. Moving: HideBot or JumpBot.
//  2. Shooting: LongShotBot, SemiAutoBot or ThirtyShotBot.
// 3. Seeing: ScoutBot or TrackBot
//In each area, a robot can choose only one upgrade. For the next upgrade, the robot
//must choose from the areas not chosen before. After three upgrades, a robot
//cannot be upgraded anymore.