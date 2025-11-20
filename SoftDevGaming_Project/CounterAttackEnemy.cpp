#include "CounterAttackEnemy.h"
#include <iostream> 
using namespace std;

void CounterAttackEnemy::takeDamage(int d)
{
	// Deal damage to the inner enemy
	wrappedEnemy->takeDamage(d);

	// Sync the wrapper's health so CombatController sees it die!
	this->health = wrappedEnemy->getHealth();

	// Counter-attack Logic
	if (!wrappedEnemy->isAlive()) // If enemy is dead
	{
		cout << wrappedEnemy->getName() << " has been defeated." << endl;
	}
}

void CounterAttackEnemy::Attack(Entity* target) {
	int chance = rand() % 100;
	if (chance < 60) { // 50% chance
		cout << ">>> " << wrappedEnemy->getName() << " counterattacks in rage!" << endl;
		target->takeDamage(attack);
		// TODO: Fix takeDamage by making it accept a pointer (Entity* attacker)
	}
	else {
		wrappedEnemy->Attack(target);
	}
}