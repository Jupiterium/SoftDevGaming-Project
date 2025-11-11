#include "ConcreteEnemy.h"
#include "Enemy.h"
#include <iostream>
using namespace std;

// The ConcreteEnemy's constructor to Enemy
ConcreteEnemy::ConcreteEnemy(string n, int h, int a, int x, int y) : Enemy(n, h, a, x, y) {}

// Implementation of the overridden virtual methods
void ConcreteEnemy::Attack(Entity* target)
{
	cout << "\n" << this->name << " attacks " << target->getName() << "!" << endl;
	target->takeDamage(this->attack);
}

void ConcreteEnemy::DisplayStatus() const
{
	cout << "> Enemy: " << this->name << " | HP: " << this->health << " | ATK: " << this->attack << endl;
}