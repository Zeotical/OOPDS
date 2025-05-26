#include "Simulation.h"
#include "Battlefield.h"
#include "Robot.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

Simulation::Simulation() : currentTurn(0)
{
    // Initialize random seed
    srand(time(0));
}

void Simulation::loadScenario(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not open input file!" << endl;
        exit(1);
    }

    string dummy;
    file >> dummy >> dummy >> dummy >> battlefieldWidth >> battlefieldHeight;
    file >> dummy >> maxTurns;
    file >> dummy >> numRobots;

    robots.clear();
    for (int i = 0; i < numRobots; i++)
    {
        string type, name;
        int x, y;
        file >> type >> name >> x >> y;

        if (type == "GenericRobot")
        {
            GenericRobot *robot = new GenericRobot(name);
            if (x == -1 && y == -1)
            { // Random position
                auto pos = battlefield.getRandomEmptyPosition();
                robot->setPosition(pos.first, pos.second);
            }
            else
            {
                robot->setPosition(x, y);
            }
            robots.push_back(robot);
            battlefield.placeRobot(robot->getPositionX(), robot->getPositionY(), robot->getname());
        }
    }
}

void Simulation::run()
{
    ofstream logfile("simulation_log.txt");

    for (currentTurn = 0; currentTurn < maxTurns; currentTurn++)
    {
        logfile << "=== Turn " << currentTurn << " ===" << endl;
        cout << "=== Turn " << currentTurn << " ===" << endl;

        // Process each robot's turn
        for (Robot *robot : robots)
        {
            if (!robot->isAlive())
                continue;

            // Robot actions
            robot->look(battlefield);
            robot->think();
            robot->move(battlefield);
            robot->fire(battlefield);

            // Log robot status
            logfile << robot->getname() << " at ("
                    << robot->getPositionX() << ","
                    << robot->getPositionY() << ")" << endl;
        }

        // Print battlefield state
        battlefield.printBattlefield();

        // Check for game over condition
        if (checkGameOver())
        {
            logfile << "Game over! Winner: " << getWinner()->getname() << endl;
            cout << "Game over! Winner: " << getWinner()->getname() << endl;
            break;
        }
    }

    logfile.close();
}

bool Simulation::checkGameOver()
{
    int aliveCount = 0;
    Robot *lastAlive = nullptr;

    for (Robot *robot : robots)
    {
        if (robot->isAlive())
        {
            aliveCount++;
            lastAlive = robot;
        }
    }

    return aliveCount <= 1;
}

Robot *Simulation::getWinner()
{
    for (Robot *robot : robots)
    {
        if (robot->isAlive())
        {
            return robot;
        }
    }
    return nullptr;
}

void Simulation::cleanup()
{
    for (Robot *robot : robots)
    {
        delete robot;
    }
    robots.clear();
}