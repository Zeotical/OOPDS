/**********|**********|**********|
Program: main.cpp ; Robot.cpp / Robot.h ; Simulation.cpp / Simulation.h ; Battlefield.cpp / Battlefield.h ; input.txt ; randomSpawn.txt
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
Group: 8
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
  
BattleField battle;

Simulation sim ;
sim.loadScenario("input.txt",battle);
sim.run(battle);

  return 0;
}
