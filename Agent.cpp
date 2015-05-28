#include "Agent.h"

#include <QPainter>

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

    if(_population < 2000)
        painter->fillRect(QRectF(1, 1, 9, 9), QColor(150,100,100));
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
int Agent::getTechnology() const
{
    return _technology;
}

void Agent::setTechnology(int technology)
{
    _technology = technology;
}


