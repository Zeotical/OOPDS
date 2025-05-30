#ifndef SIMULATION_H
#define SIMULATION_H

#include "Battlefield.h"
#include "Robot.h"
#include <vector>
#include <string>

using namespace std;

class Simulation
{
private:
public:
    int battlefieldWidth;
    int battlefieldHeight;
    BattleField battlefield;
    vector<GenericRobot *> robots;
    int currentTurn;
    int maxTurns;
    int numRobots;
    Simulation();
    void loadScenario(const string &filename, BattleField &battle);
    void run(BattleField &battle);
    void cleanup();
    bool checkGameOver();
    Robot *getWinner();
};

#endif