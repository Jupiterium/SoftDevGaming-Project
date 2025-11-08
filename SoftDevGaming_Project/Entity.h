#pragma once

#include <iostream>
using namespace std;

/*
* Purpose of this Abstract Class:
* Provides a base class for all living beings (Player, Enemy).
*/

class Entity {
protected:
    string name;
    int health;
    int attack;
    int x, y; // Position on the map

public:
    Entity(string n, int h, int a, int x, int y);
    virtual ~Entity() {}

    // Getters/Helpers
    int getHealth() const;
    void setHealth(int h);
    string getName() const;
    bool isAlive() const;

    // Pure virtual, abstract methods (must be overridden)
    virtual void Attack(Entity* target) = 0;
    virtual void DisplayStatus() const = 0;

    // Virtual methods (can be overridden)
    virtual void takeDamage(int d);
};
