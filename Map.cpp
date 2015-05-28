#include "Map.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string.h>

#include "Cell.h"
#include "Agent.h"
#include "Resource.h"

using namespace std;

//Constructor
Map::Map() {
    _numPrints = 0;
}

//This loads a map from file

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


    char tile;

    //Loop through the map and process chars
    _cellData.resize(_mapData.size());
    for (int i = 0; i < _mapData.size(); i++) {
        _cellData[i].resize(_mapData[i].size());

        //Loop through each letter in row i
        for (int j = 0; j < _mapData[i].size(); j++) {
            //This is the current tile we are looking at
            tile = _mapData[i][j];

            //Check the tile to see what we should do
            switch (tile) {

            case 'o': //humans
                _cellData[i][j] = new Agent("Human", 'o', 5, 1000, 10, i, j);
                break;
            case 'r': //Resource
                _cellData[i][j] = new Resource(i,j, 80);
                break;

            case '-': //All the tiles that dont need extra processing, in this case, walls and air
            case 'x': //All the tiles that dont need extra processing, in this case, walls and air
            case '.':;
                _cellData[i][j] = new Cell(i,j,tile);
                break;
            default: //If we get here, that means we haven't registered the tile, so print out a warning
                printf("WARNING: Unknown tile %c at %d,%d\n", tile, j, i);
                _cellData[i][j] = new Cell(i,j,tile);
                break;
            }
        }
    }
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
    for(int i = x -3; i > 0 && i < x+3 && i < getWidth(); i++) {
        for(int j = y -3; j > 0 && j < y+3 && j < getHeight(); j++) {
            Cell* currentCell = getCell(i,j);
            if(currentCell->tileType() == 'r') {
                if(Resource* currentRCell = dynamic_cast<Resource*>(currentCell)) {
                    int cellResources = currentRCell->resources();
                    resources += cellResources;

                    if(cellResources > 0) {
                        currentRCell->setResources(currentRCell->resources() - currentRCell->resources()*0.01);
                        currentRCell->update();
                    }
                }
            }
        }
    }
    if(resources > 100)
        resources = 100;
    return resources;
}
