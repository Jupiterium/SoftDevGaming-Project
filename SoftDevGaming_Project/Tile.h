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
	int symbol; // Refer to ASCII table for character

public:
	// Constructor with optional symbol parameter (default is space character)
	Tile(char symbol = ' ') { this->symbol = symbol; }

	// Getter for the tile's character symbol
	char getChar() const { return symbol; }
};