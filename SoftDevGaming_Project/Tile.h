#pragma once

#include <iostream>
using namespace std;

/*
* Purpose of this class:
* Represents a single tile on the map. Acts as a simple data class.
*/

class Tile {
private:
	int symbol;  // Refer to ASCII table for character

public:
	//Construct a Tile with an optional character symbol.
	//@param symbol The ASCII character to display for this tile
	Tile(char symbol = ' ') {
		this->symbol = symbol;
	}

	//Getter for the tile's character symbol.
	char getChar() const {
		return symbol;
	}
};