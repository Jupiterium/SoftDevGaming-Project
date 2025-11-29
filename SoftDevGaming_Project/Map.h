#pragma once

#include <vector>
#include <string>
#include "Tile.h"
#include "Item.h"
#include "Constants.h"

using namespace std;

/* 
* The game's 2D grid-based world representation.
* Map manages a 2D array of Tiles and provides methods for checking walkability,
* replacing tiles, and rendering the map to the console with color coding.
*
* The map consists of a 2D array (mapTile) of Tile objects. Each tile stores
* a character representing the terrain, entities, or items at that position.
* The map handles:
* - Walkability checks (prevents movement out of bounds)
* - Tile updates (replacing characters as entities/items move)
* - Rendering with color coding (player=cyan, enemy=brown, treasure=red, etc.)
* 
* Map dimensions are defined in Constants.h (MAP_WIDTH, MAP_HEIGHT).
*/

class Map 
{
	// Private members to encapsulate map properties
private:
	int width, height;
	vector<vector<Tile>> mapTile;
public:
	//Construct a Map with specified dimensions. Initializes the entire grid with empty tiles ('.').
	Map(int width, int height);

	//Validate movement before updating entity positions
	bool isWalkable(int x, int y);

	//Update a specific tile on the map with a new character symbol
	void ReplaceTile(char new_char, int x, int y);

	// Environment generation methods
	void GenerateHiddenGrid();

	// Getter for the tile
	Tile& getTile(int x, int y);

	//Getters for map
	int getWidth();
	int getHeight();

	// Overloaded operator to print the map
	friend ostream& operator<<(ostream& out, const Map& map);
};
