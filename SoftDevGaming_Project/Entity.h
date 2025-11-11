#pragma once

#include <iostream>
#include <string>
using namespace std;

/*
* Purpose of this Abstract Class:
* Provides a base class for all living beings (Player, Enemy).
*/

class Entity 
{
protected:
    string name;
    int health;
    int attack;
    int x, y; // Position on the map

public:
    Entity(string n, int h, int a, int x, int y);
    virtual ~Entity() {}

    // Getters/Helpers
    string getName() const;
    int getHealth() const;
    void setHealth(int h);
    int getAttack() const;
    bool isAlive() const;
    int getX() const; 
    int getY() const; 

    // Pure virtual, abstract methods (must be overridden)
    virtual void Attack(Entity* target) = 0;
    virtual void DisplayStatus() const = 0;

    // Virtual method (can be overridden)
    virtual void takeDamage(int d);
};