#include "Map.h" 
#include <fstream>
#include <iostream>
#include <cstdio>

//Constructor
Map::Map() {
    _numPrints = 0;
}

//This loads a map from file

void Map::load(string fileName) {

    //Loads the map
    ifstream file;

    //Open the file and quit if it fails to open
    file.open(fileName);
    if (file.fail()) {
        perror(fileName.c_str());
        system("PAUSE");
        exit(1);
    }

    string line;

    //Loop through the entire file, getting each row and
    //putting it in the line string.
    while (getline(file, line)) {
        //Push the current line onto the _mapData array
        _mapData.push_back(line);
    }

    //Close the file so we arent keeping open for longer than we need to
    file.close();

   
    char tile;

    //Loop through the map and process chars

    for (int i = 0; i < _mapData.size(); i++) {
        //Loop through each letter in row i
        for (int j = 0; j < _mapData[i].size(); j++) {
            //This is the current tile we are looking at
            tile = _mapData[i][j];

            //Check the tile to see what we should do
            switch (tile) {
            
            case 'o': //humans
                
		/// 		agent.update(Agent("Agent"));

                break;
            
			case '-': //All the tiles that dont need extra processing, in this case, walls and air
           
			case '.': //All the tiles that dont need extra processing, in this case, walls and air
           
			case 'x': //All the tiles that dont need extra processing, in this case, walls and air
           
                //Doesnt need to do anthing, just break.
                break;
            default: //If we get here, that means we haven't registered the tile, so print out a warning
                printf("WARNING: Unknown tile %c at %d,%d", tile, j, i);
                system("Pause");
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

//sets a tile on the map
void Map::setTile(int x, int y, char tile) {
    _mapData[y][x] = tile;
}