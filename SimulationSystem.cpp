#include "SimulationSystem.h"
#include <iostream>
#include <conio.h>

//Constructor sets up the simulation
SimulationSystem::SimulationSystem(string mapFileName){
    
    //Initialize the Agent properties.
   
  
    system("PAUSE");
}

void SimulationSystem::runSimulation() {

    bool isDone = false;

    while (isDone != true) {
         
		_map.setNumPrints(1);
        //print the map
				
		_map.updateAgents(_agent);

    }
}

