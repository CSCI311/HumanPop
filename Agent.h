#pragma once
#include <string>
#include <QGraphicsItem>
#include "Cell.h"

#include "Resource.h"

class Agent : public Cell
{
public:
    //Constructor
    Agent(std::string name, char tile, int technology, unsigned long population, int resources, int x, int y);

    //Getters
    void getPosition(int &x, int &y);

    void updateAgent (int x, int y);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;



    unsigned long getPopulation() const;
    void setPopulation(unsigned long population);

    double getTechnology() const;
    void setTechnology(float technology);

    std::vector<Resource *>* getResources();
    void setResources(std::vector<Resource *> resources);
    float getAvailableResources(int timePeriod = 1);

    int getResRange() const;
    void setResRange(int resRange);

private:
    std::string _name;

    //Properties
    int _map;
    double _technology;
    unsigned long _population;
    int _resRange;

    std::vector<Resource*> _resources;
};

