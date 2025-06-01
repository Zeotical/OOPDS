/**********|**********|**********|
Program: YOUR_FILENAME.cpp / YOUR_FILENAME.h
Course: CCP6124-OOPDS
Trimester: 2510
Name: BASMALA MOHAMMED ALI ELIMAM
ID: 243UC247PF
Email: BASMALA.MOHAMED.ALI@student.mmu.edu.my
Phone: +966 50 8493218 (whatsapp)
Name: LEE KAH WAI
ID: 243UC247K0
Email: LEE.KAH.WAI@STUDENT.MMU.EDU.MY
Phone: 011-11173393
Name: YAP HUI CHI
ID: 242UC244M6
Email: YAP.HUI.CHI@STUDENT.MMU.EDU.MY
Phone: 016-3225726
Lecture Section: TC101
Tutorial Section: T10L 
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

  //srand(time(0)); // each time program runs get a new random number
  
BattleField battle;
//battle.initialize(40,50);

//Initializing robots before turn loop begins, each robot placed in a different random position

   //GenericRobot::robotObjects.emplace("R1","R1"); // (key,obj)
  // assign object using key to robot, easier to access methods //auto& == referenced data type (in this case GenericRobot)
  //auto& robot =  GenericRobot::robotObjects.at("R1"); // doesn't need a defualt constructor as [] does

   //GenericRobot::robotObjects.emplace("R2","R2"); // (key,obj)
  // assign object using key to robot, easier to access methods //auto& == referenced data type (in this case GenericRobot)
  //auto& robot2 =  GenericRobot::robotObjects.at("R2"); // doesn't need a defualt constructor as [] does

  // GenericRobot::robotObjects.emplace("R3","R3"); // (key,obj)
  // // assign object using key to robot, easier to access methods //auto& == referenced data type (in this case GenericRobot)
  // auto& robot3 =  GenericRobot::robotObjects.at("R3"); // doesn't need a defualt constructor as [] does
  // // GenericRobot robot3("R3");
  // GenericRobot::robotObjects.emplace("R4","R4"); // (key,obj)
  // // assign object using key to robot, easier to access methods //auto& == referenced data type (in this case GenericRobot)
  // auto& robot4 =  GenericRobot::robotObjects.at("R4"); // doesn't need a defualt 

    //battle.placeRobot(robot.getPositionX(),robot.getPositionY(),robot.getname());
   // battle.placeRobot(robot2.getPositionX(),robot2.getPositionY(),robot2.getname());
  //  battle.placeRobot(robot3.getPositionX(),robot3.getPositionY(),robot3.getname());

  //    battle.placeRobot(robot4.getPositionX(),robot4.getPositionY(),robot4.getname());

    //battle.printBattlefield();
   // robot.look(battle); 
  //robot.move(battle); 
       
  //battle.printBattlefield();
  //cout << "shelssss " << robot.shells;
//cout << GenericRobot::re_enteringRobots.size();
  //robot.fire(battle);
  //cout << robot2.lives << "ACTUAL lives" <<endl ;
   // cout << "shelssss " << robot.shells;
//cout << GenericRobot::re_enteringRobots.size();
//   robot.thirtyShotBot();

// //robot.semiAutoBot(battle);

//battle.printBattlefield();
//     robot.look(battle); 

//   robot.semiAutoBot(battle);

//     battle.printBattlefield();


//   robot2.look(battle);
//  robot2.move(battle);
// battle.printBattlefield();

//robot.look(battle);

Simulation sim ;
sim.loadScenario("input.txt",battle);
sim.run(battle);

  return 0;
}
