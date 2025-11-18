#pragma once

#include <iostream>
using namespace std;

/*
* Purpose of this class:
* Represents a single tile on the map. Acts as a simple data class.
*/

class Tile {
	int symbol;  // Refer to ASCII table for character

public:
	Tile(char symbol = ' ') {
		this->symbol = symbol;
	}

	char getChar() const {
		return symbol;
	}
};