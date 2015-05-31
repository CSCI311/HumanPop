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
    _timeStep = 1;
    _birthRate = 0.0019;
    _deathRate = 0.0009;
    _total = 0;
}

void SimulationSystem::runStep()
{
    Cell* currentCell = NULL;
    int width = _map.getWidth();
    int height = _map.getHeight();
    unsigned long int totalPop = 0;
    static unsigned long long int year = 0;
    year += _timeStep;
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            currentCell = _map.getCell(x,y);
            if(currentCell->tileType() == 'o') {
                //Phase 1

                Agent * agent = (Agent*)currentCell;

                //Calculate population growth.
                long long int pop = agent->getPopulation();
                long long int prevPop = agent->getPopulation();
                double resourcesAvailable = agent->getAvailableResources(_timeStep)*(0.49 + agent->getTechnology()/200.0);
                double growthRate = (2.0*resourcesAvailable/100.0) * _birthRate;
                pop += prevPop*pow(1.0+growthRate,_timeStep);
                if(pop/prevPop > 2)
                    cout <<"Doubling in pop" << endl;

                //Calculate population deaths.
                double tech = agent->getTechnology()/100.0;
                double techFactor = 1.0 - tech;
                double resourceFactor = 1.0 - resourcesAvailable/100.0;
                double deathrate = _deathRate*(techFactor + resourceFactor);
                pop -= prevPop*pow(1.0+deathrate,_timeStep);
                if(pop < 0)
                    pop = 0;

                agent->setPopulation(pop);
                //cout << "Population: " << agent->getPopulation() << endl;
                agent->update(); //update agent after modification for rendering.

                //Phase 2
                //Population limits and migration
                double limit = pow((1.0+tech),13.0)*300.0*(1.3 + resourcesAvailable/100.0);
                if(pop > limit) {
                    Cell* target = _map.getMigrationCell(x,y,16);
                    if(target != NULL) {
                        int target_x = target->getX();
                        int target_y = target->getY();
                        _app->deleteCell(target);
                        delete target;
                        target = NULL;

                        Agent* replacement = new Agent("human2", 'o', agent->getTechnology(), pop*0.5, 200, target_x, target_y);
                        replacement->setResources(_map.getResourceCells(target_x, target_y, 4));
                        replacement->setResRange(8);
                        _app->addCell(replacement);
                        _map.setCell(target_x, target_y, replacement);
                        agent->setPopulation(pop*0.5);
                        agent->update();
                        totalPop += pop*0.5;
                    }
                    agent->setPopulation(pop*0.5);
                }
                else
                    totalPop += pop;

                //Phase 3
                agent->setTechnology(agent->getTechnology()*pow((1+0.00005),_timeStep));

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
                //20% resource renewal rate.
                resources += (resources*0.2 + 5)*_timeStep;
                resource->setResources(resources);
                resource->update();
            }
        }
    }
    _total = totalPop;
}

Map &SimulationSystem::getMap()
{
    return _map;
}
int SimulationSystem::getTimeStep() const
{
    return _timeStep;
}

void SimulationSystem::setTimeStep(int timeStep)
{
    _timeStep = timeStep;
}
double SimulationSystem::getBirthRate() const
{
    return _birthRate;
}

void SimulationSystem::setBirthRate(double birthRate)
{
    _birthRate = birthRate;
}
double SimulationSystem::getDeathRate() const
{
    return _deathRate;
}

void SimulationSystem::setDeathRate(double deathRate)
{
    _deathRate = deathRate;
}
unsigned long SimulationSystem::getTotal() const
{
    return _total;
}



