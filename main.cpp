/**********|**********|**********|
Program: YOUR_FILENAME.cpp / YOUR_FILENAME.h
Course: Data Structures and Algorithms? oopds
Trimester: 2410
Name: Frank Carrano
ID: 1071001234
Lecture Section: TC101
Tutorial Section: TT1L
Email: abc123@yourmail.com
Phone: 018-1234567
**********|**********|**********/

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <string>

// header files
#include "Robot.h"
#include "Battlefield.h"
#include "Simulation.h"

using namespace std;

int main()
{

  srand(time(0)); // each time program runs get a new random number
  
BattleField battle;
battle.initialize(30,20);

//Initializing robots before turn loop begins, each robot placed in a different random position

   GenericRobot::robotObjects.emplace("R1","R1"); // (key,obj)
  // assign object using key to robot, easier to access methods //auto& == referenced data type (in this case GenericRobot)
  auto& robot =  GenericRobot::robotObjects.at("R1"); // doesn't need a defualt constructor as [] does

   GenericRobot::robotObjects.emplace("R2","R2"); // (key,obj)
  // assign object using key to robot, easier to access methods //auto& == referenced data type (in this case GenericRobot)
  auto& robot2 =  GenericRobot::robotObjects.at("R2"); // doesn't need a defualt constructor as [] does

  // GenericRobot robot3("R3");

    battle.placeRobot(robot.getPositionX(),robot.getPositionY(),robot.getname());
    battle.placeRobot(robot.getPositionX(),robot.getPositionY(),robot2.getname());
  // battle.placeRobot(robot3.getPositionX(),robot3.getPositionY(),robot3.getname());

  
    battle.printBattlefield();
    robot.look(battle); 
  //robot.move(battle); 
       
  battle.printBattlefield();
  //cout << "shelssss " << robot.shells;
cout << GenericRobot::re_enteringRobots.size();
  //robot.fire(battle);
   // cout << "shelssss " << robot.shells;
cout << GenericRobot::re_enteringRobots.size();
robot.semiAutoBot(battle);

  battle.printBattlefield();

//   robot2.look(battle);
//  robot2.move(battle);
// battle.printBattlefield();

//robot.look(battle);



  return 0;
}
