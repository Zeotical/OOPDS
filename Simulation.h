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
    BattleField battlefield;
    vector<Robot *> robots;
    int currentTurn;
    int maxTurns;
    int numRobots;
    int battlefieldWidth;
    int battlefieldHeight;

    bool checkGameOver();
    Robot *getWinner();

public:
    Simulation();
    void loadScenario(const string &filename);
    void run();
    void cleanup();
};

#endif