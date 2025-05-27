#include "Battlefield.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>

BattleField::BattleField() : width(0), height(0)
{
    // Default constructor - field will be initialized when initialize() is called
}

BattleField::BattleField(int w, int h) : width(w), height(h)
{
    field = vector<vector<string>>(height, vector<string>(width, "- "));
}

void BattleField::initialize(int w, int h)
{
    width = w;
    height = h;
    field = vector<vector<string>>(height, vector<string>(width, "- "));
}

void BattleField::printBattlefield()
{
    // Print column numbers header
    cout << "   ";
    for (int i = 0; i < width; i++)
    {
        if (i>9){
        cout  << i << " " << setw(2); //910 issue fix later
    }
        else 
            cout << " " << i << setw(2) ;
    }
    cout << endl;

    // Print battlefield with row numbers
    for (int i = 0; i < height; i++)
    {
        if (i<10){
        cout  << setw(2) << i << "| " ;
    }
    else 
            cout << i << "| ";
        for (int j = 0; j < width; j++)
        {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool BattleField::isInside(int x, int y) const
{
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool BattleField::isOccupied(int x, int y) const
{
    return isInside(x, y) && field[y][x] != "- ";
}

void BattleField::placeRobot(int x, int y, const string &robot)
{
    if (isInside(x, y) && !isOccupied(x, y))
    {
        field[y][x] = robot.substr(0, 2); // Use first 2 characters of robot name
    }
    else
    {
        // Try to find a random empty position (with safety limit)
        int attempts = 0;
        int maxAttempts = width * height; // Prevent infinite loop

        do
        {
            x = rand() % width;
            y = rand() % height;
            attempts++;

            if (attempts > maxAttempts)
            {
                cerr << "Error: Cannot place robot - battlefield may be full!" << endl;
                return;
            }
        } while (isOccupied(x, y));

        field[y][x] = robot.substr(0, 2);
    }
}

void BattleField::clearPosition(int x, int y)
{
    if (isInside(x, y))
    {
        field[y][x] = "- ";
    }
}

pair<int, int> BattleField::getRandomEmptyPosition()
{
    int x, y;
    int attempts = 0;
    int maxAttempts = width * height;

    do
    {
        x = rand() % width;
        y = rand() % height;
        attempts++;

        if (attempts > maxAttempts)
        {
            cerr << "Warning: Could not find empty position after " << maxAttempts << " attempts" << endl;
            // Return a position anyway (might be occupied)
            break;
        }
    } while (isOccupied(x, y));

    return {x, y};
}

void BattleField::moveRobot(int oldX, int oldY, int newX, int newY)
{
    if (isInside(oldX, oldY) && isInside(newX, newY) && !isOccupied(newX, newY))
    {
        string robot = field[oldY][oldX];
        clearPosition(oldX, oldY);
        field[newY][newX] = robot;
    }
}

string BattleField::getCell(int x, int y) const
{
    if (isInside(x, y))
    {
        return field[y][x];
    }
    return "OUT_OF_BOUNDS";
}