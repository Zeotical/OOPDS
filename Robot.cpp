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
#include <cstdlib> 
#include <vector>
#include <algorithm>

 
queue <Robot*> re_enteringRobots;


//Robot class 
Robot::Robot() {} //default constructor

Robot::Robot(string robotName, string robotType){
    name = robotName;
    type = robotType;
    lives = 3;
    shells = 10;
    upgrades = 0;
    numOfRobots ++ ;
    //robotsPositionX= rand() % 30; // random num from (0 to 29) because vector indexing starts at 0 //width
    //robotsPositionY = rand() % 20; // random num from (0 to 19) //height
}

void Robot::setPositionX(int posx){
  robotsPositionX = posx ;
}

void Robot::setPositionY(int posy){
  robotsPositionY = posy ;
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

bool Robot::isAlive(){
if(lives != 0 && shells > 0 ){
  return true;
}
return false;
}
 string Robot::handle_upgrades(){
  scout_bot_uses = 0;
  track_bot_uses = 0;
  hide_bot_uses = 0;
  jump_bot_uses = 0;
  long_shot_bot_uses = 0;
  semi_auto_bot_uses = 0;
  thirty_shot_uses = 0;
  //Seeing ScoutBot or TrackBot
if (see!=1 || see < 1){ // To force it to choose from another area
  if(shells < 4 ){ //|| enemyPos.size() == 0
    see++;
    return "ScoutBot" ;
  }
  else {
    see++;
    return "TrackBot" ;
  }
}
  //Moving HideBot or JumpBot.
else if (move!=1 || move < 1){
    if((shells < 4 || lives == 1) && move == 0) {
    move++;
    return "HideBot" ; }
    
   else if (enemyPos.size() > 4 || lives==1 && move == 0) {
     move++;
     return "JumpBot" ; 
    }
   else {
        random = rand() % 10;
        if (random%2){
          move++;
          return "HideBot" ;
        }
        else {
          move++;
          return "JumpBot" ;
          }

      }
    }
  //Shooting LongShotBot, SemiAutoBot or ThirtyShotBot.
  else if (shoot != 1 || shoot < 1){
    if( shells>4 ){ //|| enemyPos.size() == 0 
      shoot++;
      return "LongShotBot" ;
    }
    else if(lives > 4 || enemyPos.size() > 4) {
      shoot++;
      return "SemiAutoBot";
  }

    else if(shells < 4 || enemyPos.size() != 0){
      shoot++;
      return "ThirtyShotBot";

  }
    else {
        random = rand() % 10;
        if (0 <= random && random < 3){
          shoot++;
          return "LongShotBot" ;
        }
        else if (3 <= random && random < 6) {
          shoot++;
          return "SemiAutoBot" ;
          }
        else {
          shoot++;
          return "ThirtyShotBot";
        }  

      }

  }//shoot else if
return "None" ;
}

// ThinkingRobot
int ThinkingRobot::think(){
cout << "*" << name << " is thinking*" <<endl;
if (lives == 1 || shells < 4){
  //look
  //move
  return 1; //defense
}

else if (shells>4){
  //look
  //shoot
  return 2; //offense
}

return 0;
//upgrades

}

// SeeinngRobot
void SeeingRobot::look(BattleField &battle){
 int t = -1;
 int u = -1;
   enemyPos.clear();
   movePositions.clear();
     while (t<=1) {
      u = -1;
      while (u<=1) {
        if(battle.isInside(getPositionX() + u,getPositionY() + t)){ // can join with the below if? or nvm

          if(battle.isOccupied(getPositionX() + u,getPositionY() + t) && (t!=0 || u!=0)){  //(width,height) (row,col) // t!= 0  && u!=0 robot doesn't consider itself an enemy
            
            cout << "Enemy robot found at (" << getPositionX() + u<<"," << getPositionY() + t <<")" <<endl ;
            // 
            enemyPos.push_back(make_pair(getPositionY()+t,getPositionX() + u)) ; //y,x
          } // inner if 
          else if (!battle.isOccupied(getPositionX()+u,getPositionY()+t) && (t!=0 || u!=0)) { // don't need the first cond
            cout << "Possible positions to move to ";
            movePositions.push_back(make_pair(getPositionX() +u,getPositionY() + t));
            cout << "(" << getPositionX() + u << "," << getPositionY() + t  << ")" << endl ;

            //clear vector after moving //everytime I run I get smth diff

          } // else if
        } // outer if
        else{
            cout << "(" << getPositionX() + u << "," << getPositionY() + t << ") is out of bounds " <<endl ;
         } // outer else 
          u++;
        } // inner while
        t++;
    } // outer while
}


void SeeingRobot::TrackBot(BattleField &battle){
  look(battle) ;
  if(enemyPos.size()!=0) {
  int i =  rand() % enemyPos.size();
  robottotrackName = battle.field[enemyPos[i].first][enemyPos[i].second]; // gets the name of the robot //use y,x
  for (auto pair: GenericRobot::robotObjects){

    if(pair.first.substr(0, 2) == robottotrackName) {
      robottotrackName = pair.first ;
    }
  }
  robottotrack =  &GenericRobot::robotObjects.at(robottotrackName); //enemyPos uses y,x and so does field[y][x]
  robotIsTracked = find(trackedrobots.begin(),trackedrobots.end(),robottotrack);
   if (robotIsTracked==trackedrobots.end() && trackedrobots.size() < 3){

  trackedrobots.push_back(robottotrack); } }
// ranomd pos1
// random pos2
// posx = robotTotrack.robotposx
// pos y = robottotrack.posy
// pass pos to a make pair vector 
}

 void  SeeingRobot::ScoutBot(BattleField &battle){
  for ( auto row =0 ; row < battle.height ; row++) {
      for (auto col=0 ; col < battle.width; col++) {
        if(battle.isInside(col,row)){ // can join with the below if? or nvm

          if(battle.isOccupied(col,row) && battle.field[row][col] != name.substr(0, 2)){  //(width,height) (row,col) // t!= 0  && u!=0 robot doesn't consider itself an enemy
            
            cout << "Enemy robot found at (" << col <<"," << row <<")" <<endl ; //for the above name.substr(0,2) since only the first 2 charas of robots name is placed
            // 
            enemyPos.push_back(make_pair(col,row)) ;
          } // inner if 
          else if (!battle.isOccupied(col,row) ) { // don't need the first cond
            cout << "Possible positions to move to ";
            movePositions.push_back(make_pair(col,row));
            cout << "(" << col << "," << row << ")" << endl ;

            //clear vector after moving //everytime I run I get smth diff

          } // else if
        } // outer if
        else{
            cout << "(" << col << "," << row << ") is out of bounds " <<endl ;
         } // outer else

        } 
    }
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
    cout << name << " moved to (" << movePositions[i].first << "," << movePositions[i].second << ") from (" <<oldX << "," <<oldY <<")" <<endl ;
    movePositions.clear();
  } else {
    cout << getname() << " found no possible moves." << endl;
    battle.placeRobot(oldX, oldY, getname()); // Place robot back if no move was made
  } 
           
}

void MovingRobot::JumpBot(BattleField &battle){
  if (jumpUsesLeft > 0) {
    // Remove robot from current position on battlefield
    // Assuming battle.removeRobot exists and takes robot's name.
    // If not, use battle.clearPosition(robotsPositionX, robotsPositionY)
    battle.clearPosition(robotsPositionX, robotsPositionY);
    oldX = robotsPositionX;
    oldY = robotsPositionY;
    // Generate new random coordinates within battlefield bounds
    // Assuming battle.width and battle.height are accessible (e.g., public members or getters).
    auto pos = battle.getRandomEmptyPosition();
    // Update robot's internal position
    robotsPositionX = pos.first;
    robotsPositionY = pos.second;
    // Place robot at new position on battlefield
    // Assuming battle.placeRobot takes robot's name.
    battle.placeRobot(pos.first,pos.second,name);

    jumpUsesLeft--; // Decrement remaining jumps

    std::cout << getname() << " jumped to (" << pos.first << ", " << pos.second << ") from (" << oldX << ", " << oldY << ") <<. Jumps left: " << jumpUsesLeft << std::endl;
    } else {
    std::cout << getname() << " has no jumps left!" << std::endl;
    }
  }

// ShootingRobot

void ShootingRobot::self_destruction(BattleField &battle) {
if (shells == 0){
  cout <<  name  << " has run out of shells." << endl;
  cout <<  name  << " *self-destructs*" << endl;
  cout <<  name  << " has died and will not be entering again" << endl;

  battle.clearPosition(robotsPositionX,robotsPositionY); // x,y == row,col
  GenericRobot::robotObjects.erase(name) ; //
}
}

void ShootingRobot::fire(BattleField &battle) {
values = {1,2,3,4,5,6,7,8,9,10};
probability = rand() % 10 ; // 0 to 9
cout <<  name  << " used fire action" << endl;
if (values[probability] <=7 && enemyPos.size()!=0){ //Hit probability 70%
   --shells;
    int i =  rand() % enemyPos.size();
   destroyedRobotName = battle.field[enemyPos[i].first][enemyPos[i].second]; // gets the name of the robot
  // using a map and the name get the object
  for (auto pair: GenericRobot::robotObjects){

    if(pair.first.substr(0, 2) == destroyedRobotName) {
      destroyedRobotName = pair.first ;
    }
  }
  destroyedRobot = &GenericRobot::robotObjects.at(destroyedRobotName);
   // using the object we can acccess lives,name etc
  --destroyedRobot->lives; // reduce from the lives  of the loser robot
   battle.clearPosition(enemyPos[i].second,enemyPos[i].first); // x,y == row,col
  cout << name << " hits " << destroyedRobot->name << " at (" << enemyPos[i].second << "," << enemyPos[i].first << ") and destroys it."  <<endl; 
  // send the loser robot to the backrooms using queue can reneter in next round? 
  cout << "Lives left for " << destroyedRobot->name << ": " << destroyedRobot->lives << endl;
   if (destroyedRobot->lives > 0){
   cout << "*" <<destroyedRobot->name<< " goes into the queue*" <<endl;
   destroyedRobot->re_enteringRobots.push(destroyedRobot); 
   destroyedRobot->cooldown = 1;
  }
   else {
    cout << destroyedRobotName << " has used up all it's lives and will not be entering again." << endl;
    battle.clearPosition(enemyPos[i].second,enemyPos[i].first); // x,y == row,col
    GenericRobot::robotObjects.erase(destroyedRobotName) ; //of o delte from here will pointer disappear also?
   }
  enemyPos.clear();
  kills++ ;    // add to the kills of the winner robot
  self_destruction(battle); //check if it has to self destruct, if yes no need for upgrades
  if (kills < 4) { //after 3 no more upgrades possible
  ++upgrades; // call upgragde func    // if kills ++ then choose upgrade 
   string choice = handle_upgrades();
   choices.push_back(choice); 
  cout << "*" << name << " is picking an upgrade*" << endl ;
  cout << name << " picked " << choice << endl;
  }
  } //if
else if(values[probability] > 7 && enemyPos.size()!=0) {
  --shells;
  cout << name << " missed" << endl;
  self_destruction(battle);
} //else 

else {
  cout <<"There are no enemies nearby " << name << " will not fire" << endl;
}
}

void ShootingRobot::SemiAutoBot(BattleField &battle){
  current_kills = kills;
  tries = 0; //max 3
  actual_shell_num = shells;
  while (tries < 3 && current_kills == kills){
    cout << "SemiAutoBot " <<endl;
    fire(battle);
    ++tries ;
    //cout << "THIS IS" <<current << "this " << kills <<endl ;
        //cout << "THIS IS" <<cshells << "this " << shells <<endl ;

  }
shells = --actual_shell_num;
    //cout << "THIS IS" <<shells << "this skibidi"  <<endl ;

  
}

void ShootingRobot::ThirtyShotBot(){
  shells = 30 ;
}

void ShootingRobot::LongShotBot(BattleField &battle){
  shoot++;
for ( auto row =0 ; row < battle.height ; row++) {
      for (auto col=0 ; col < battle.width; col++) {
        if(battle.isInside(col,row)){ // can join with the below if? or nvm

          if(battle.isOccupied(col,row) && battle.field[row][col] != name.substr(0, 2) && (abs(col - robotsPositionX) + abs(row - robotsPositionY) <=3)){  //(width,height) (row,col) // t!= 0  && u!=0 robot doesn't consider itself an enemy
            
            cout << "Enemy robot found at (" << col <<"," << row <<")" <<endl ; //for the above name.substr(0,2) since only the first 2 charas of robots name is placed
            // 
            enemyPos.clear(); //in case other funcs already filled it
            enemyPos.push_back(make_pair(col,row)) ;
          } // inner if 
        } //outer if
      } //inner for
} // outer for
      fire(battle);

}
//GenericRobot
string GenericRobot::type = "Generic Robot" ; //static variable, shared by all objects
GenericRobot::GenericRobot(string name) : Robot(name, GenericRobot::type) {}
map<string,GenericRobot> GenericRobot::robotObjects; // static definition

GenericRobot GenericRobot::getRobotByName(string& name) {

  return GenericRobot::robotObjects.at(name) ; }

// do func here ?? no in sub-classes
// UPGRADES
// There are three possible areas to upgrade. They are moving, shooting and seeing. 
// 1. Moving: HideBot or JumpBot.
//  2. Shooting: LongShotBot, SemiAutoBot or ThirtyShotBot.
// 3. Seeing: ScoutBot or TrackBot
// In each area, a robot can choose only one upgrade. For the next upgrade, the robot
// must choose from the areas not chosen before. After three upgrades, a robot
// cannot be upgraded anymore.

// The capabilites of the upgrades are as follow:
//MOVING

// HideBot : The robot can hide three times in a match. When the robot hides, it
// cannot be hit by other robots

// SHOOTING

// SEEING

//Doing/Done

// SemiAutoBot : Each shell the robot fires is now considered as three consecutive
// shots into one location and each shot has a 70% probability to hit and destroy
// another robot. (shooting)

// TrackBot : The robot can plant a tracker on another robot it can see. The location
// of the targetted robot will be known to the robot until the end of a match. The
// robot has three trackers. (seeing)

// ThirtyShotBot : The robot now has a fresh load of 30 shells replacing its current 
// load of shells. (shooting)

// JumpBot : The robot can jump to a new location anywhere in the map. It can
// jump three times in a match. (moving)

// ScoutBot : Instead of look(x, y) The robot can see the entire battlefield for one
// turn. This ability can be used three times in a match. (seeing)

// LongShotBot : The robot can fire up to three unit distance away from its location.
// It means the robot can fire(x, y) where x + y <= 3. (shooting)
