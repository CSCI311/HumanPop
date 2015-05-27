#pragma once
#include "Agent.h"
#include "Map.h"
#include <string>

using namespace std;

class SimulationSystem
{
public:
    SimulationSystem(string mapFileName);

    void runSimulation();

private:
    Map _map;
};

