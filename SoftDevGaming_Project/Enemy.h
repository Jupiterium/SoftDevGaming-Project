#pragma once

#include "Entity.h"

/*
* Purpose of this Abstract Class:
* Base class for all enemies, supports behavior modification through Decorator pattern. 
* Remains abstract by no implementing Entity’s pure virtual functions.
*/

class Enemy : public Entity
{
public:
	// Constructor passes data to Entity
	Enemy(string n, int h, int a, int x, int y);

	// This class remains abstract by not implementing Attack() or DisplayStatus() from Entity.
};