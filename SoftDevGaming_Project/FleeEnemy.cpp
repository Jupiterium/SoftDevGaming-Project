#include "FleeEnemy.h"
#include <iostream>
using namespace std;

void FleeEnemy::Flee(int mapWidth, int mapHeight) {
    if (wrappedEnemy->getHealth() < 10) {
        int dx = (rand() % 3 - 1) * 2; // -2, 0, or +2
        int dy = (rand() % 3 - 1) * 2;

        int newX = wrappedEnemy->getX() + dx;
        int newY = wrappedEnemy->getY() + dy;

        // Clamp to map boundaries
        if (newX < 0) newX = 0;
        if (newX >= mapWidth) newX = mapWidth - 1;
        if (newY < 0) newY = 0;
        if (newY >= mapHeight) newY = mapHeight - 1;

        wrappedEnemy->setX(newX);
        wrappedEnemy->setY(newY);

        cout << wrappedEnemy->getName() << " flees to (" << newX << ", " << newY << ")!\n";
    }
}
