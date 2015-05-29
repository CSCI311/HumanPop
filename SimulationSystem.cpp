#include "SimulationSystem.h"
#include <iostream>
#include <stdio.h>
#include <qmath.h>

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
    int width = _map.getWidth();
    int height = _map.getHeight();
    long int totalPop = 0;
    static int year = 0;
    year++;
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            currentCell = _map.getCell(x,y);
            if(currentCell->tileType() == 'o') {
                //Phase 1

                Agent * agent = (Agent*)currentCell;

                //Calculate population growth.
                int pop = agent->getPopulation();
                int resourcesAvailable = agent->getAvailableResources()*(0.5 + agent->getTechnology()/100.0);
                float growthRate = (resourcesAvailable/100.0) * 0.019;
                pop += growthRate*pop;

                //Calculate population deaths.
                float tech = agent->getTechnology()/100.0;
                float techFactor = 1.0/(0.5 + tech);
                float resourceFactor = 1.1 - resourcesAvailable/100.0;
                pop -= 0.002*pop*techFactor + 0.002*pop*resourceFactor;

                agent->setPopulation(pop);
                //cout << "Population: " << agent->getPopulation() << endl;
                agent->update(); //update agent after modification for rendering.

                //Phase 2
                //Population limits and migration
                int limit = pow((1+tech),10)*500*(1.3 + resourcesAvailable/100.0);
                if(pop > limit) {
                    Cell* target = _map.getMigrationCell(x,y,10);
                    if(target != NULL) {
                        int target_x = target->getX();
                        int target_y = target->getY();
                        _app->deleteCell(target);
                        delete target;
                        target = NULL;

                        Agent* replacement = new Agent("human2", 'o', agent->getTechnology(), pop/4, 200, target_x, target_y);
                        replacement->setResources(_map.getResourceCells(target_x, target_y, 15));
                        _app->addCell(replacement);
                        _map.setCell(target_x, target_y, replacement);
                        agent->setPopulation(pop*(3.0/4.0));
                        agent->update();
                        totalPop += pop*(3.0/4.0);
                    }
                }
                else
                    totalPop += pop;

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
            else if(currentCell->tileType() == 'r') {
                Resource* resource = (Resource*)currentCell;
                int resources = resource->resources();
                //15% resource renewal rate.
                resource->setResources(resources + resources*0.15 + 3);
                resource->update();
            }
        }
    }
    cout << "Year: " << year << " Total Population: " << totalPop << endl;
}

Map &SimulationSystem::getMap()
{
    return _map;
}
