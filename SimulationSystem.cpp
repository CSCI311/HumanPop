#include "SimulationSystem.h"
#include <iostream>
#include <stdio.h>

#include "Resource.h"

//Constructor sets up the simulation
SimulationSystem::SimulationSystem(string mapFileName){

    //Initialize the Agent properties.

    _map.load(mapFileName);

    printf("%s Map Loaded!\n", mapFileName.c_str());
}

void SimulationSystem::runStep()
{
    Cell* currentCell = NULL;
    for(int x = 0; x < _map.getWidth(); x++) {
        for(int y = 0; y < _map.getHeight(); y++) {
            currentCell = _map.getCell(x,y);
            if(dynamic_cast<Agent*>(currentCell) != NULL) {
                //Phase 1

                Agent * agent = dynamic_cast<Agent*>(currentCell);

                //Calculate population growth.
                int pop = agent->getPopulation();
                int resourcesAvailable = _map.getResources(x,y);
                float growthRate = (resourcesAvailable/100.0) * 0.019;
                pop += growthRate*pop;

                //Calculate population deaths.
                float tech = agent->getTechnology()/100.0;
                float techFactor = 1/(0.5 + tech);
                pop -= 0.003*pop*techFactor;

                agent->setPopulation(pop);
                cout << "Population: " << agent->getPopulation() << endl;
                agent->update(); //update agent after modification for rendering.

                //Phase 2

                //Phase 3

                //Phase 4,
            }
            if(dynamic_cast<Resource*>(currentCell) != NULL) {
                Resource* resource = dynamic_cast<Resource*>(currentCell);
                int resources = resource->resources();
                //10% resource renewal rate.
                resource->setResources(resources + resources*0.1);


            }
        }
    }
}

Map &SimulationSystem::getMap()
{
    return _map;
}
