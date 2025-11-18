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
	if (wrappedEnemy->isAlive()) // If enemy is alive
	{
		int chance = rand() % 100;
		if (chance < 40) { // 40% chance
			cout << ">>> " << wrappedEnemy->getName() << " counterattacks in rage!" << endl;

			// We need a target for the counter-attack. 
			// ideally, takeDamage should accept an (Entity* attacker)
			// For now, we just print the message, or you could add logic here if you had the pointer.
		}
	}
	// If enemy is dead
	else { cout << wrappedEnemy->getName() << " has been defeated." << endl; }
}

void CounterAttackEnemy::Attack(Entity* target) { wrappedEnemy->Attack(target); }