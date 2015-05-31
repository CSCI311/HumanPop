#include "Map.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string.h>

#include "Cell.h"
#include "Agent.h"
#include "Resource.h"

#include <qmath.h>

using namespace std;
#define NUM_NN 8 //Number of nearest points.
#define MAX_PTS 2048 //Maximum number of data points.

//Constructor
Map::Map() {
    _numPrints = 0;

    _queryPoint = annAllocPt(2);
    _dataPts = annAllocPts(2048, 2);
    _nearestIndex = new ANNidx[NUM_NN];
    _dists = new ANNdist[NUM_NN];

    _resPts = 0;
}

//This loads a map from file

void Map::loadCellData()
{
    char tile;
    //Loop through the map and process chars
    _cellData.resize(_mapData.size());
    for (unsigned int i = 0; i < _mapData.size(); i++) {
        _cellData[i].resize(_mapData[i].size());

        //Loop through each letter in row i
        for (unsigned int j = 0; j < _mapData[i].size(); j++) {
            //This is the current tile we are looking at
            tile = _mapData[i][j];

            //Check the tile to see what we should do
            switch (tile) {

            case 'o': //humans
                _cellData[i][j] = new Agent("Human", 'o', 10, 500, 10, j, i);
                break;
            case 'r': //Resource
                _cellData[i][j] = new Resource(j,i, 80);
                _dataPts[_resPts][0] = ANNcoord(j);
                _dataPts[_resPts][1] = ANNcoord(i);
                _resPts++;
                break;

            case '-':
            case 'x':
            case '.':;
                _cellData[i][j] = new Cell(j,i,tile);
                break;
            default: //If we get here, that means we haven't registered the tile, so print out a warning
                printf("WARNING: Unknown tile %c at x:%d, y:%d\n", tile, j, i);
                _cellData[i][j] = new Cell(j,i,tile);
                break;
            }
        }
    }

    _kdTree = new ANNkd_tree(_dataPts, _resPts, 2);

    //Second pass to set Agent resources
    for (int i = 0; i < _mapData.size(); i++) {
        for (int j = 0; j < _mapData[i].size(); j++) {
            if(_cellData[i][j]->tileType() == 'o') {
                Agent* agentCell = (Agent*)_cellData[i][j];

                agentCell->setResources(getResourceCells(j,i,8));
            }
        }
    }
}

void Map::load(string fileName) {

    //Loads the map
    ifstream file;

    //Open the file and quit if it fails to open
    file.open(fileName.c_str());
    if (file.fail()) {
        perror(fileName.c_str());
    }

    string line;

    //Loop through the entire file, getting each row and
    //putting it in the line string.
    while (getline(file, line)) {
        if(line.size() > 0)
            //Push the current line onto the _mapData array
            _mapData.push_back(line);
    }

    //Close the file so we arent keeping open for longer than we need to
    file.close();
    loadCellData();
}

void Map::load(QImage image)
{
    _mapData.resize(image.height());
    for(int y = 0; y < image.height(); y++) {
        _mapData[y].resize(image.width());
        for(int x =0; x < image.width(); x++) {
            QRgb pixel = image.pixel(x,y);
            if(pixel == QColor(0,0,0).rgb())
                _mapData[y][x] = 'x';
            else if(pixel == QColor(255,255,255).rgb())
                _mapData[y][x] = '.';
            else if(pixel == QColor(0,255,0).rgb())
                _mapData[y][x] = 'r';
            else if(pixel == QColor(255,0,0).rgb())
                _mapData[y][x] = 'o';
            else
                _mapData[y][x] = '#';
        }
    }
    loadCellData();
}

//Prints out the map.
void Map::print() {

    //clear the screen
    printf("%s", string(100, '\n').c_str());

    for (int i = 0; i < _mapData.size(); i++) {
        printf("%s\n", _mapData[i].c_str());
    }

    //This pads the bottom with extra newlines based on how many extra lines
    //have been printed. So for instance, when the player is battling something,
    //the game map doesnt jump around
    if (_numPrints < 5){
        printf("%s", string(5 - _numPrints, '\n').c_str());
    }

    //Set numPrints to zero each time we reprint the screen
    _numPrints = 0;
}

//Gets a tile from the map
char Map::getTile(int x, int y) {
    return _mapData[y][x];
}

Cell *Map::getCell(int x, int y)
{
    return _cellData[y][x];
}

int Map::getWidth()
{
    return _mapData[0].size();
}

int Map::getHeight()
{
    return _mapData.size();
}

//sets a tile on the map
void Map::setTile(int x, int y, char tile) {
    _mapData[y][x] = tile;
}

int Map::getResources(int x, int y)
{
    //3 is range. Should base of tech laters TODO: .

    int resources = 0;
    int range = 10;
    for(int i = x -range; i > 0 && i < x+range && i < getWidth(); i++) {
        if(resources > 100)
            break;
        for(int j = y -range; j > 0 && j < y+range && j < getHeight(); j++) {
            Cell* currentCell = getCell(i,j);
            if(currentCell->tileType() == 'r') {
                if(Resource* currentRCell = (Resource*)currentCell) {
                    float distanceFactor = 1.2 - sqrt(pow(x - i,2) + pow(y-j,2))/range;
                    distanceFactor = distanceFactor < 0 ? 0 : distanceFactor;
                    int cellResources = currentRCell->resources()*distanceFactor;
                    resources += cellResources;

                    if(cellResources > 0) {
                        currentRCell->setResources(currentRCell->resources() - currentRCell->resources()*0.05*distanceFactor);
                        currentRCell->update();
                    }
                    if(resources > 100)
                        break;
                }
            }
        }
    }
    if(resources > 100)
        resources = 100;
    return resources;
}

std::vector<Resource *> Map::getResourceCells(int x, int y, int distance)
{
    vector<Resource *> results;
    _queryPoint[0] = x;
    _queryPoint[1] = y;
    _kdTree->annkSearch(_queryPoint, NUM_NN, _nearestIndex, _dists);
    for(int nnIdx = 0; nnIdx < NUM_NN; nnIdx++) {
        if(_dists[nnIdx] < distance) {
            int rx = _dataPts[_nearestIndex[nnIdx]][0];
            int ry = _dataPts[_nearestIndex[nnIdx]][1];
            results.push_back((Resource*)_cellData[ry][rx]);
        }
    }

//    for(int i = x -distance; i > 0 && i < x+distance && i < getWidth(); i++) {
//        for(int j = y -distance; j > 0 && j < y+distance && j < getHeight(); j++) {
//            Cell* currentCell = getCell(i,j);
//            if(currentCell->tileType() == 'r') {
//                results.push_back((Resource*)currentCell);
//            }
//        }
//    }
    return results;
}

Cell *Map::getMigrationCell(int x, int y, int distance)
{
    vector<Cell*> plausible;
    for(int i = x - distance; i > 0 && i < x+distance && i < getWidth(); i++) {
        for(int j = y -distance; j > 0 && j < y+distance && j < getHeight(); j++) {
            Cell* currentCell = getCell(i,j);
            if(currentCell->tileType() == 'x') {
                plausible.push_back(currentCell);
            }
        }
    }
    if(plausible.size() > 0)
        return plausible.at(rand() % plausible.size());
    else
        return NULL;
}

void Map::setCell(int x, int y, Cell *cell)
{
    _cellData[y][x] = cell;
}
