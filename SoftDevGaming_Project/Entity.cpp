#include <iostream>
#include <string>
#include "Entity.h"
#include "Constants.h"
using namespace std;

// Implementation of Entity's constructor 
Entity::Entity(string n, char c, int h, int a, int x, int y) : name(n), symbol(c), health(h), attack(a), x(x), y(y) {}

// Implementation of Getters/Helper methods
int Entity::getHealth() const { return health; }

void Entity::setHealth(int h) { health = h; }

string Entity::getName() const { return name; }

char Entity::getSymbol() const { return symbol; }

int Entity::getAttack() const { return attack; }

int Entity::getX() const { return x; }

int Entity::getY() const { return y; }

// Implementation of Setters
int Entity::setX(int newX) { return this->x = newX; return this->x; }
int Entity::setY(int newY) { return this->y = newY; return this->y; }
void Entity::setAttack(int a) { (this->attack) += a; }


bool Entity::isAlive() const
{
	return health > 0;
}

// Virtual method implementation
// Apply damage to the entity by subtracting from health
void Entity::takeDamage(int d)
{
	health -= d;
	if (health < 0) { health = 0; } // Don't let health go negative
}

// Method to move the player for level changes
void Entity::setPosition(int newX, int newY) 
{
	x = newX;
	y = newY;
}