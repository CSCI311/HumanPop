#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>


//the following line is necessary for the GetConsoleWindow() function to work!
//it basically says that you are running this program on Windows 2000 or higher

#define _WIN32_WINNT 0x0500
#include <windows.h>

#include "SimulationSystem.h"

using namespace std;

int main()
{

	
	SimulationSystem simulationSystem("map.txt");

    simulationSystem.runSimulation();

    return 0;
}