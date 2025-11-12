#include <iostream>
#include <string>
#include "Entity.h"
using namespace std;

// Implementation of Entity's constructor 
Entity::Entity(string n, int h, int a, int x, int y) : name(n), health(h), attack(a), x(x), y(y) {}

// Implementation of Getters/Helper methods
int Entity::getHealth() const { return health; }

void Entity::setHealth(int h) { health = h; }

string Entity::getName() const { return name; }

int Entity::getAttack() const { return attack; }

int Entity::getX() const { return x; }

int Entity::getY() const { return y; }

int Entity::setX(int x) { this->x = x; }
int Entity::setX(int y) { this->y = y; }

bool Entity::isAlive() const
{
	//if (health <= 0) { return false; }
	//else { true; }
	return health > 0;
}

// Virtual method implementation
void Entity::takeDamage(int d)
{
	health -= d;
	if (health < 0) { health = 0; } // Don't let health go negative
}