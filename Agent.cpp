#include "Agent.h"

#include <QPainter>
#include <qmath.h>

using namespace std;

// need to define more ints
Agent::Agent(string name, char tile, int technology, int population, int resouces, int x, int y) :
    Cell(x,y,tile)
{
    _name = name;
    _technology = technology;
    _population = population;
}


//This is the main algorithm for population, technology and migration algarithms
void Agent::updateAgent(int x, int y) {


}

void Agent::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(item);

    if(_population < 200)
        painter->fillRect(QRectF(1, 1, 9, 9), QColor(25,0,0));
    else if(_population < 500)
        painter->fillRect(QRectF(1, 1, 9, 9), QColor(50,0,0));
    else if(_population < 1000)
        painter->fillRect(QRectF(1, 1, 9, 9), QColor(100,0,0));
    else if(_population < 2000)
        painter->fillRect(QRectF(1, 1, 9, 9), QColor(150,0,0));
    else if(_population < 5000)
        painter->fillRect(QRectF(1, 1, 9, 9), QColor(200,0,0));
    else if(_population < 10000)
        painter->fillRect(QRectF(1, 1, 9, 9), QColor(255,0,0));
    else if(_population < 100000)
        painter->fillRect(QRectF(1, 1, 9, 9), QColor(255,100,0));
}

int Agent::getPopulation() const
{
    return _population;
}

void Agent::setPopulation(int population)
{
    _population = population;
}
float Agent::getTechnology() const
{
    return _technology;
}

void Agent::setTechnology(float technology)
{
    _technology = technology;
}

void Agent::setResources(std::vector<Resource *> resources)
{
    _resources = resources;
}

float Agent::getAvailableResources()
{
    float resources = 0;
    for(int i = 0; i < _resources.size(); i++) {
        Resource* resCell = _resources[i];
        float distanceFactor = 1.2 - sqrt(pow(getX() - resCell->getX(),2) + pow(getY()-resCell->getY(),2))/15.0; //15.0 is range, need to create variable for it.
        distanceFactor = distanceFactor < 0 ? 0 : distanceFactor;
        float cellResources = resCell->resources()*distanceFactor;
        resources += cellResources;

        if(cellResources > 0) {
            resCell->setResources(resCell->resources() - resCell->resources()*0.05*distanceFactor);
            resCell->update();
        }
        if(resources > 100)
            break;
    }
    if(resources > 100)
        resources = 100;
    return resources;
}

std::vector<Resource *> *Agent::getResources()
{
    return &_resources;
}

