#pragma once

#include <vector>
#include "Tile.h"
using namespace std;

/* 
* Purpose of this class: 
* Manages the grid-based world (ASCII map, which is composed of Tile objects 
*/

class Map 
{
private:
	int width, height;
	vector<vector<Tile>> mapTile;


public:
	Map();
	void loadFromFile(string filename);

	// Getters
	Tile& getTile(int x, int y);
	bool isWalkable(int x, int y);
	
	// Overloaded operator to print the map
	friend ostream& operator<<(ostream& out, const Map& map);
};


