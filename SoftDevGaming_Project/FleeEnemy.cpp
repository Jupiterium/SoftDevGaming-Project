#include "FleeEnemy.h"
#include <iostream>
using namespace std;

void FleeEnemy::Flee() {
    if (wrappedEnemy->getHealth() < 10) {
        int dx = (rand() % 3 - 1) * 2; // -2, 0, or +2
        int dy = (rand() % 3 - 1) * 2;

        int newX = wrappedEnemy->getX() + dx;
        int newY = wrappedEnemy->getY() + dy;

        // Clamp to map boundaries
        if (newX < 0) newX = 0;
        if (newX >= MAP_WIDTH) newX = MAP_WIDTH - 1;
        if (newY < 0) newY = 0;
        if (newY >= MAP_HEIGHT) newY = MAP_HEIGHT - 1;

        wrappedEnemy->setX(newX);
        wrappedEnemy->setY(newY);

        cout << wrappedEnemy->getName() << " flees to (" << newX << ", " << newY << ")!\n";
    }
}

void FleeEnemy::takeDamage(int d) {
    // Deal damage to the inner enemy
    wrappedEnemy->takeDamage(d);

    // Sync the wrapper's health so CombatController sees it die!
    this->health = wrappedEnemy->getHealth();

    // Fleeing Logic
    if (!wrappedEnemy->isAlive()) // If enemy is dead
    {
        cout << wrappedEnemy->getName() << " has been defeated." << endl;
    }
    else {
        Flee();
    }
}