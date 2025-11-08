#pragma once

#include "Enemy.h"
using namespace std;

/*
* Purpose of this class:
* The default, concrete implementation of an enemy. 
* This is the "core" enemy object that the Decorator pattern will wrap to add new behaviours.
*/

class ConcreteEnemy : public Enemy
{
public:
	ConcreteEnemy(string n, int h, int a, int x, int y);

	// Concrete implementation of the virtual methods 
	void Attack(Entity* target) override;
	void DisplayStatus() const override;
};