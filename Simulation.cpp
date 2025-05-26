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
        cerr << "Error: Could not open input file: " << filename << endl;
        exit(1);
    }

    string dummy;

    // Read "M by N : 40 50"
    file >> dummy >> dummy >> dummy >> dummy >> battlefieldWidth >> battlefieldHeight;

    // Read "steps: 300"
    file >> dummy >> maxTurns;

    // Read "robots: 3"
    file >> dummy >> numRobots;

    // Initialize battlefield with correct dimensions
    battlefield.initialize(battlefieldWidth, battlefieldHeight);

    cout << "Battlefield: " << battlefieldWidth << "x" << battlefieldHeight << endl;
    cout << "Max turns: " << maxTurns << endl;
    cout << "Number of robots: " << numRobots << endl;

    robots.clear();

    for (int i = 0; i < numRobots; i++)
    {
        string type, name, xStr, yStr;
        file >> type >> name >> xStr >> yStr;

        if (type == "GenericRobot")
        {
            GenericRobot *robot = new GenericRobot(name);

            // Handle random position
            if (xStr == "random" || yStr == "random")
            {
                auto pos = battlefield.getRandomEmptyPosition();
                robot->setPosition(pos.first, pos.second);
                cout << "Placed " << name << " at random position (" << pos.first << "," << pos.second << ")" << endl;
            }
            else
            {
                int x = stoi(xStr);
                int y = stoi(yStr);
                robot->setPosition(x, y);
                cout << "Placed " << name << " at position (" << x << "," << y << ")" << endl;
            }

            robots.push_back(robot);
            battlefield.placeRobot(robot->getPositionX(), robot->getPositionY(), robot->getname());
        }
    }

    file.close();
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