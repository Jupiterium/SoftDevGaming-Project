#pragma once

#include <iostream>
#include <string>
using namespace std;

/*
* Purpose of this Abstract Class:
* Provides a base class for all living beings (Player, Enemy).
* Defines common attributes and properties for all entities.
* Cannot be instantiated
*/

class Entity 
{
// Protected members accessible by derived classes
protected:
    string name;
    char symbol;
    int health;
    int attack;
    int x, y; // Position on the map

public:
	// Constructor
    Entity(string n, char c, int h, int a, int x, int y);
    virtual ~Entity() {}

    // Getters/Helpers
    string getName() const;
    char getSymbol() const;
    int getHealth() const;
    void setHealth(int h);
    int getAttack() const;
    bool isAlive() const;
    int getX() const;
    int getY() const;

    //Setters
    int setX(int x);
    int setY(int y);
    void setAttack(int a);

    // Pure virtual, abstract methods (must be overridden)
    virtual void Attack(Entity* target) = 0;
    virtual void DisplayStatus() const = 0;

    // Virtual method (can be overridden)
    virtual void takeDamage(int d);

    // Set entity's position on the map
	//Use for level transition or respawn
    void setPosition(int newX, int newY);
};
