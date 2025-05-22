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
#include <cstdlib>
#include <ctime>
#include <string>

// header files
#include "Robot.h"
#include "Battlefield.h"

using namespace std;

int main()
{

srand(time(0)); // each time program runs get a new random number
int robotsPositionX= rand() % 50 ; // random num from (0 to 49) because vector indexing starts at 0 //width
int robotsPositionY = rand() % 40; // random num from (0 to 39) //height



BattleField battle;

//Initializing robots before turn loop begins, each robot placed in a different random position
  GenericRobot robot("R1");
  GenericRobot robot2("R2");
  GenericRobot robot3("R3");



    battle.placeRobot(robotsPositionX,robotsPositionY,robot.getname());
    battle.placeRobot(robotsPositionX,robotsPositionY,robot2.getname()); 
    battle.placeRobot(robotsPositionX,robotsPositionY,robot3.getname()); 

    battle.printBattlefield();


  // robot.move(); // random position not random each time will fix later 
  // robot.look();
  //   robot2.look();
  // robot2.move();

  // what if two robots get same position? need to implement logic so if positiontaken generte new random num

  //Simulation
  // int turn = 0;
  // while (turn <3) {
  //   cout << "Turn " << turn <<endl;

  // }
  return 0;
}
