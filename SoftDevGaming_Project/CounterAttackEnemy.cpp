//Implementation of counter-attacking enemy decorator.
#include "CounterAttackEnemy.h"
#include <iostream> 
using namespace std;

// Forward damage to wrapped enemy and possibly respond with counter-attack.
void CounterAttackEnemy::takeDamage(int d)
{
	// Deal damage to the inner enemy
	wrappedEnemy->takeDamage(d);

	// Sync the wrapper's health so CombatController sees it die!
	this->health = wrappedEnemy->getHealth();

	// If wrapped enemy is still alive, it may counterattack
	if (!wrappedEnemy->isAlive()) // If enemy is dead
	{
		cout << wrappedEnemy->getName() << " has been defeated." << endl;
	}
}

// Attack with a chance to counterattack.
void CounterAttackEnemy::Attack(Entity* target) {
	int chance = rand() % 100;
	if (chance < 60) { // 60% chance to counter-attack
		cout << ">>> " << wrappedEnemy->getName() << " counterattacks in rage!" << endl;
		target->takeDamage(attack);
	}
	else {
		wrappedEnemy->Attack(target); // Normal attack
	}
}