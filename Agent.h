#pragma once
#include <string>

using namespace std;

class Agent
{
public:
    //Constructor
    Agent(string name, char tile, int technology, int population, int resources);

    //Setters
    void setPosition(int x, int y);

    //Getters
    void getPosition(int &x, int &y);
    
	char getTile() { return _tile; }

	void updateAgent (int x, int y);

private:
    string _name;
    char _tile;

    //Properties
    int _map;
	int _technology;
	int _population;
    int _resources;

    //Position
    int _x;
    int _y;
};

