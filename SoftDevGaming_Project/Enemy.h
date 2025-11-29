#pragma once

#include "Entity.h"
#include "Constants.h"
using namespace std;

/*
* Enemy extends Entity for inherited attributes and methods.
* Remains abtract so it can be extended by ConcreteEnemy and Decorators without losing design consistency.
* Base class for all enemies, supports behavior modification through Decorator pattern. 
* Remains abstract by not implementing Entity’s pure virtual functions.
*/

class Enemy : public Entity
{
public:
	// Constructor passes data to Entity (name, char, health, attack, x coordinate, y coordinate)
	Enemy(string n, char c, int h, int a, int x, int y);
	virtual void Attack(Entity* target);

	//Display enemy status
	virtual void DisplayStatus() const;

	// Virtual destructor for proper cleanup in derived classes
	virtual ~Enemy() {}
};