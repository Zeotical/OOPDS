#include "Simulation.h"
#include "Battlefield.h"
#include "Robot.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>



Simulation::Simulation() : currentTurn(0)
{
    // Initialize random seed
    srand(time(0));
}

void Simulation::loadScenario(const string &filename, BattleField &battle)
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
    battle.initialize(battlefieldWidth, battlefieldHeight);

    cout << "Battlefield: " << battlefieldWidth << "x" << battlefieldHeight << endl;
    cout << "Max turns: " << maxTurns << endl;
    cout << "Number of robots: " << numRobots << endl;

    robots.clear();

    for (int i = 0; i < numRobots; i++)
    {
        string type, name, xStr, yStr;
        file >> type >> name >> xStr >> yStr;

        //if (type == "GenericRobot")
        //{
            //GenericRobot *robot = new GenericRobot(name);
               GenericRobot::robotObjects.emplace(name,name); // (key,obj)
                 auto& robot =  GenericRobot::robotObjects.at(name); // doesn't need a defualt constructor as [] does


            //Handle random position
            if (xStr == "random" || yStr == "random")
            {
                auto pos = battle.getRandomEmptyPosition();
                //robot->setPosition(pos.first, pos.second);
                robot.setPositionX(pos.first);
                robot.setPositionY(pos.second);
                cout << "Placed " << name << " at random position (" << pos.first << "," << pos.second << ")" << endl;
                battle.placeRobot(pos.first,pos.second,robot.getname());

            }
             else
            {
                int x = stoi(xStr);
                int y = stoi(yStr);
                robot.setPositionX(y);
                robot.setPositionY(x);   

                battle.placeRobot(robot.getPositionX(),robot.getPositionY(),robot.getname());

                cout << "Placed " << name << " at position (" << y << "," << x << ")" << endl;
            }

            robots.push_back(&robot);
            //battlefield.placeRobot(robot->getPositionX(), robot->getPositionY(), robot->getname());
        //}
    }
    battle.printBattlefield();

    file.close();
}

void Simulation::run(BattleField &battle)
{
    ofstream logfile("simulation_log.txt");
    currentTurn = -1;
    GenericRobot* robot = nullptr;
    int action =0;
    int random_spawn = rand() % maxTurns ;
    int random_spawn_times = 0; // make func if random_spawn is b/w so so maxturns then gen robot,name and push to vector shall i make a new inout file for this?
     while ( currentTurn < maxTurns)
    {    

        // Process each robot's turn
        for (int i = 0; i < robots.size();)
        { 
             robot = robots[i];
            ++currentTurn;      

            logfile << "=== Turn " << currentTurn << " ===" << endl;
            cout << "=== Turn " << currentTurn << " (" << robot->name <<") ===" << endl;

        //Handle dead Robots
        if (!robot->isAlive()) {
                for(int i =0 ; i< robots.size();i++) {
                    if(robots[i] == robot) {
                    robots.erase(robots.begin() + i);
                    cout << "#### " << robot->name << " is dead #### (╥‸╥)" <<endl;  
                    logfile << robot->name << " is dead" <<endl; 
                    }
                 continue; } }
        //Handle cooldown for re-entering Robots
        else if (robot->re_enteringRobots.size() > 0 && robot->cooldown == 1) {
            cout << "|||| " << robot->name << " will respawn in it's next turn ||||" <<endl ;
            logfile << robot->name << " will respawn in it's next turn" <<endl ;
            --robot->cooldown ;
            i++;
            continue;
        } 
        //Handle re-entering Robots
        else if(robot->re_enteringRobots.size() > 0  && robot->cooldown == 0)
            {  
                cout << robot->name << " is re-entering" << endl;
                robot->re_enteringRobots.pop();
                auto pos = battle.getRandomEmptyPosition();
                //robot->setPosition(pos.first, pos.second);
                robot->setPositionX(pos.first);
                robot->setPositionY(pos.second);
                cout << "Placed " << robot->name << " at random position (" << pos.first << "," << pos.second << ")" << endl;
                battle.placeRobot(pos.first,pos.second,robot->name);
                robot->choices.clear(); //robot re enters as a generic robot with 0 upgrades
                robot->re_entryReset();
            // Robot actions
            action = robot->think();

            if (robot->upgrades == 0 || robot->choices.size() == 0) {
                if (action == 1) {
                    robot->look(battle);
                    robot->move(battle);
                }
                else if (action == 2) {
                    robot->look(battle);
                    robot->fire(battle);
                }
                else {
                    // optional fallback, maybe just look? or upgrades?
                    robot->look(battle);
                }
            }

            else {

                int idx = rand() % robot->choices.size();
                string choice = robot->choices[idx];

                if (choice=="ScoutBot" && robot->scout_bot_uses < 3) {
                    ++robot->scout_bot_uses ;
                    cout << robot->name <<" is using " << choice << " upgrade" << endl;
                    robot->ScoutBot(battle);
                    if(robot->scout_bot_uses == 3) {
                        robot->choices.erase(robot->choices.begin() + idx);
                    }
                }
                else if (choice== "TrackBot" && robot->track_bot_uses < 3) {
                    ++robot->track_bot_uses;
                    cout << robot->name <<" is using " << choice << " upgrade" << endl;
                    robot->TrackBot(battle); //cout the robots being tracked and their pos, kill them if near and lives r high else move away from them
                    if(robot->track_bot_uses == 3) {
                        robot->choices.erase(robot->choices.begin() + idx);
                    }
                }
                else if (choice=="HideBot") {} //TBD
                else if (choice=="JumpBot" && robot->jump_bot_uses < 3) {
                    ++robot->jump_bot_uses;
                    cout << robot->name <<" is using " << choice << " upgrade" << endl;
                    robot->JumpBot(battle);
                    if(robot->jump_bot_uses == 3) {
                        robot->choices.erase(robot->choices.begin() + idx);
                    }
                }
                else if (choice=="LongShotBot" && robot->long_shot_bot_uses < 3) {
                    ++robot->long_shot_bot_uses;
                    cout << robot->name <<" is using " << choice << " upgrade" << endl;
                    robot->LongShotBot(battle);
                    if(robot->long_shot_bot_uses == 3) {
                        robot->choices.erase(robot->choices.begin() + idx);
                    }
                }
                else if (choice=="SemiAutoBot" && robot->semi_auto_bot_uses < 3) {
                    ++robot->semi_auto_bot_uses;
                    cout << robot->name <<" is using " << choice << " upgrade" << endl;
                    robot->SemiAutoBot(battle);
                    if(robot->semi_auto_bot_uses == 3) {
                        robot->choices.erase(robot->choices.begin() + idx);
                    }
                }
                else if (choice=="ThirtyShotBot" && robot->thirty_shot_uses < 3) {
                    ++robot->thirty_shot_uses;
                    cout << robot->name <<" is using " << choice << " upgrade" << endl;
                    robot->ThirtyShotBot();
                    if(robot->thirty_shot_uses == 3) {
                        robot->choices.erase(robot->choices.begin() + idx);
                    }
               }
           }

            // Log robot status
            logfile << robot->getname() << " at ("
                    << robot->getPositionX() << ","
                    << robot->getPositionY() << ")" << endl;

            }
        //Handle still alive robots
        else if (robot->lives == 3 || (robot->lives <= 3 && robot->re_enteringRobots.size() == 0)) {
            // Robot actions
            action = robot->think();
            if (robot->upgrades == 0 || robot->choices.size() == 0) {
                if (action == 1) {
                    robot->look(battle);
                    robot->move(battle);
                }
                else if (action == 2) {
                    robot->look(battle);
                    robot->fire(battle);
                }
                else {
                    // optional fallback, maybe just look? or upgrades?
                    robot->look(battle);
                }
            }

            else {

                int idx = rand() % robot->choices.size();
                string choice = robot->choices[idx];

                if (choice=="ScoutBot" && robot->scout_bot_uses < 3) {
                    ++robot->scout_bot_uses ;
                    cout << robot->name <<" is using " << choice << " upgrade" << endl;
                    robot->ScoutBot(battle);
                    if(robot->scout_bot_uses == 3) {
                        robot->choices.erase(robot->choices.begin() + idx);
                    }
                }
                else if (choice== "TrackBot" && robot->track_bot_uses < 3) {
                    ++robot->track_bot_uses;
                    cout << robot->name <<" is using " << choice << " upgrade" << endl;
                    robot->TrackBot(battle);
                    if(robot->track_bot_uses == 3) {
                        robot->choices.erase(robot->choices.begin() + idx);
                    }
                }
                else if (choice=="HideBot") {} //TBD
                else if (choice=="JumpBot" && robot->jump_bot_uses < 3) {
                    ++robot->jump_bot_uses;
                    cout << robot->name <<" is using " << choice << " upgrade" << endl;
                    robot->JumpBot(battle);
                    if(robot->jump_bot_uses == 3) {
                        robot->choices.erase(robot->choices.begin() + idx);
                    }
                }
                else if (choice=="LongShotBot" && robot->long_shot_bot_uses < 3) {
                    ++robot->long_shot_bot_uses;
                    cout << robot->name <<" is using " << choice << " upgrade" << endl;
                    robot->LongShotBot(battle);
                    if(robot->long_shot_bot_uses == 3) {
                        robot->choices.erase(robot->choices.begin() + idx);
                    }
                }
                else if (choice=="SemiAutoBot" && robot->semi_auto_bot_uses < 3) {
                    ++robot->semi_auto_bot_uses;
                    cout << robot->name <<" is using " << choice << " upgrade" << endl;
                    robot->SemiAutoBot(battle);
                    if(robot->semi_auto_bot_uses == 3) {
                        robot->choices.erase(robot->choices.begin() + idx);
                    }
                }
                else if (choice=="ThirtyShotBot" && robot->thirty_shot_uses < 3) {
                    ++robot->thirty_shot_uses;
                    cout << robot->name <<" is using " << choice << " upgrade" << endl;
                    robot->ThirtyShotBot();
                    if(robot->thirty_shot_uses == 3) {
                        robot->choices.erase(robot->choices.begin() + idx);
                    }
               }
           }

            // Log robot status
            logfile << robot->getname() << " at ("
                    << robot->getPositionX() << ","
                    << robot->getPositionY() << ")" << endl;

            }
            i++;
            battle.printBattlefield();
        }
            
        // Print battlefield state
        // battle.printBattlefield();

        // Check for game over condition
        if (checkGameOver())
        {
            logfile << "Game over! Winner: " << getWinner()->getname() << endl;
            cout << "Game over! Winner: " << getWinner()->getname()  <<" ୧(๑•̀ヮ•́)૭ LET'S GO!" << endl;
            break;
        }
        else if (currentTurn >= maxTurns){
            cout << "No one won, game time has run out " << "( ˶°ㅁ°) !!" << endl;
            break; //needed? if turn over it will just break already..
        }

    }

    logfile.close();
}

bool Simulation::checkGameOver()
{
    int aliveCount = 0;
    Robot *lastAlive = nullptr;

    for (GenericRobot* robot : robots)
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
    for (GenericRobot* robot : robots)
    {
        if (robot->isAlive())
        {
            return robot;
            }
    }
    return nullptr;
}

// void Simulation::cleanup()
// {
//     for (GenericRobot* robot : robots) //no need for this
//     {
//         delete robot;
//     }
//     robots.clear();
// }