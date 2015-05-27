#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>

#include "SimulationSystem.h"

using namespace std;

int main()
{

	
	SimulationSystem simulationSystem("map.txt");

    simulationSystem.runSimulation();

    return 0;
}