#include "Agent.h"


// need to define more ints
Agent::Agent(string name, char tile, int technology, int population, int resouces) {
    _name = name;
    _tile = tile;
	_technology = technology;
	_population = population;
}

//Sets the position of the agent
void Agent::setPosition(int x, int y) {
    _x = x;
    _y = y;
}

//Gets the position of the agent using reference variables
void Agent::getPosition(int &x, int &y) {
    x = _x;
    y = _y;
}

//This is the main algorithm for population, technology and migration algarithms 
void Agent::updateAgent(int x, int y) {


}