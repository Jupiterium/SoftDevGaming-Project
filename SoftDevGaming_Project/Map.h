#pragma once

#include <vector>
#include <string>
#include "Tile.h"
#include "Item.h"
#include "Constants.h"

using namespace std;

/* 
* Purpose of this class: 
* Manages the grid-based world (ASCII map, which is composed of Tile objects )
*/

class Map 
{
private:
	int width, height;
	vector<vector<Tile>> mapTile;

public:
	Map(int width, int height);
	//void loadFromFile(string filename);

	bool isWalkable(int x, int y);

	void ReplaceTile(char new_char, int x, int y);

	// Environment generation methods
	void GenerateHiddenGrid();
	
	// Overloaded operator to print the map
	friend ostream& operator<<(ostream& out, const Map& map);

	// Getter for the tile
	Tile& getTile(int x, int y);

	//Getters for map
	int getWidth();
	int getHeight();
};
