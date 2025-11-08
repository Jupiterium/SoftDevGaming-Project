#pragma once

#include <iostream>
using namespace std;

/*
* Purpose of this class:
* Represents a single tile on the map. Acts as a simple data class.
*/

class Tile
{
private:
	char symbol;
	bool walkable;

public:
	Tile(char s = ' ', bool w = false);

	// Getters 
	char getSymbol() const;
	bool isWalkable() const;

	// Setter
	void setTile(char s, bool w);
};