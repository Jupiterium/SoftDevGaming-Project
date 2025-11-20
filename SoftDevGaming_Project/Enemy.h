#pragma once

#include "Entity.h"
#include "Constants.h"
using namespace std;

/*
* Purpose of this Abstract Class:
* Base class for all enemies, supports behavior modification through Decorator pattern. 
* Remains abstract by no implementing Entity’s pure virtual functions.
*/

class Enemy : public Entity
{
public:
	// Constructor passes data to Entity
	Enemy(string n, char c, int h, int a, int x, int y);
	virtual void Attack(Entity* target);
	virtual void DisplayStatus() const;

	virtual ~Enemy() {}
};