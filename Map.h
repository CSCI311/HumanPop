#pragma once
#include <vector>
#include <string>
#include "Agent.h"
#include "Resource.h"

#include <QVector2D>

#include "ANN/ANN.h"


//The level stores the data for the level and the agent

class Map
{
public:
    Map();

    void load(std::string fileName);
    void load(QImage image);
    void print();

    //Getters
    char getTile(int x, int y);
    Cell* getCell(int x, int y);
    int getWidth();
    int getHeight();
    //Setters
    void setTile(int x, int y, char tile);
    void setNumPrints(int numPrints) { this->_numPrints = numPrints;  }

    int getResources(int x, int y);
    std::vector<Resource*> getResourceCells(int x, int y, int distance);
    Cell* getMigrationCell(int x, int y, int distance);

    void setCell(int x, int y, Cell*);

    void loadCellData();
private:
    void processAgent(int targetX, int targetY);

private:
    // the bottom of the screen with newlines
    int _numPrints;
    int _width;
    int _height;
    // Stores the level information
    std::vector<std::string> _mapData;
    std::vector<std::vector<Cell*> > _cellData;
    int _resPts; // actual number resource points.
    ANNpointArray _dataPts;
    ANNpoint _queryPoint;
    ANNidxArray _nearestIndex;
    ANNdistArray _dists;
    ANNkd_tree* _kdTree;
};

