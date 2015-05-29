#include "SimulationSystem.h"
#include <iostream>
#include <stdio.h>

#include <Mainwindow.h>

#include "Resource.h"

//Constructor sets up the simulation
SimulationSystem::SimulationSystem(string mapFileName, MainWindow* main){

    //Initialize the Agent properties.

    QImage image;
    image.load(mapFileName.c_str());
    _map.load(image);
    _app = main;

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
                int resourcesAvailable = _map.getResources(x,y)*(0.5 + agent->getTechnology()/100.0);
                float growthRate = (resourcesAvailable/100.0) * 0.019;
                pop += growthRate*pop;

                //Calculate population deaths.
                float tech = agent->getTechnology()/100.0;
                float techFactor = 1.0/(0.5 + tech);
                float resourceFactor = 1.1 - resourcesAvailable/100.0;
                pop -= 0.003*pop*techFactor + 0.003*pop*resourceFactor;

                agent->setPopulation(pop);
                //cout << "Population: " << agent->getPopulation() << endl;
                agent->update(); //update agent after modification for rendering.

                //Phase 2
                //Population limits and migration
                int limit = 500*(1.3 + resourcesAvailable/100.0);
                if(pop > limit) {
                    Cell* target = _map.getMigrationCell(x,y,8);
                    if(target != NULL) {
                        int target_x = target->getX();
                        int target_y = target->getY();
                        _app->deleteCell(target);
                        delete target;
                        target = NULL;

                        Agent* replacement = new Agent("human2", 'o', agent->getTechnology()/2, pop/4, 200, target_x, target_y);
                        _app->addCell(replacement);
                        _map.setCell(target_x, target_y, replacement);
                        agent->setPopulation(pop*(3.0/4.0));
                        agent->update();
                    }
                }

                //Phase 3
                agent->setTechnology(agent->getTechnology()*1.0005);

                //Phase 4,
                if(pop <= 1) {
                    int old_x = agent->getX();
                    int old_y = agent->getY();
                    _app->deleteCell(agent);
                    delete agent;
                    agent = NULL;

                    Cell* emptyLand = new Cell(old_x, old_y, 'x');
                    _app->addCell(emptyLand);
                    _map.setCell(old_x, old_y, emptyLand);
                    emptyLand->update();

                }
            }
            else if(dynamic_cast<Resource*>(currentCell) != NULL) {
                Resource* resource = dynamic_cast<Resource*>(currentCell);
                int resources = resource->resources();
                //10% resource renewal rate.
                resource->setResources(resources + resources*0.1 + 3);
                resource->update();


            }
        }
    }
}

Map &SimulationSystem::getMap()
{
    return _map;
}
