#pragma once
#include <vector>
#include <string>
#include "Agent.h"

using namespace std;

//The level stores the data for the level and the agent

class Map
{
public:
    Level();

    void load(string fileName);
    void print();
	
	void updateAgent();

    //Getters
    char getTile(int x, int y);
    //Setters
    void setTile(int x, int y, char tile);
    void setNumPrints(int numPrints) { _numPrints = _numPrints;  }

private:
    void processAgent(int targetX, int targetY);

private:
    // the bottom of the screen with newlines
    int _numPrints; 
    // Stores the level information
    vector <string> _mapData;
    vector <Agent> _agemt;
};

