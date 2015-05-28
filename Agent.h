#pragma once
#include <string>
#include <QGraphicsItem>
#include "Cell.h"

class Agent : public Cell
{
public:
    //Constructor
    Agent(std::string name, char tile, int technology, int population, int resources, int x, int y);

    //Getters
    void getPosition(int &x, int &y);

    void updateAgent (int x, int y);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;



    int getPopulation() const;
    void setPopulation(int population);

    float getTechnology() const;
    void setTechnology(float technology);

private:
    std::string _name;

    //Properties
    int _map;
    float _technology;
    int _population;
    int _resources;
};

