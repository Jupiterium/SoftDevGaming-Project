#include "CounterAttackEnemy.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void CounterAttackEnemy::takeDamage(int d) {
    // Deal with incoming damage first
    wrappedEnemy->takeDamage(d);

    // If the enemy is still alive after the hit, it has a chance to counterattack
    if (wrappedEnemy->isAlive()) {
        int chance = rand() % 100; // random chance from 0 to 99
        if (chance < 40) { // 40% chance to counterattack
            cout << wrappedEnemy->getName() << " counterattacks in rage!\n";
        }
    }
    else {
        cout << wrappedEnemy->getName() << " has been defeated.\n";
    }
}

void CounterAttackEnemy::Attack(Entity* target) {
    // Attack as usual but maybe with a stronger strike if counter mode triggered
    cout << wrappedEnemy->getName() << " attacks " << target->getName() << "!\n";
    wrappedEnemy->Attack(target);
}
