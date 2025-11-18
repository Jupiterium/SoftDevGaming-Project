#include "EnemyDecorator.h"
#include "Enemy.h"
#include <string> 
using namespace std;

// This has to do two jobs:
// 1. Call its parent (Enemy) constructor
// 2. Set its own wrappedEnemy member
EnemyDecorator::EnemyDecorator(Enemy* enemy) : Enemy(enemy->getName(), enemy->getHealth(), enemy->getAttack(), enemy->getX(), enemy->getY()), wrappedEnemy(enemy) {}

// Implementation for the overridden methods
// These pass the call to the wrapped enemy
void EnemyDecorator::Attack(Entity* target)
{
    wrappedEnemy->Attack(target);
}

void EnemyDecorator::DisplayStatus() const
{
    wrappedEnemy->DisplayStatus();
}

void EnemyDecorator::takeDamage(int d)
{
    wrappedEnemy->takeDamage(d);

    // This ensures CombatController sees the correct HP when checking isAlive()
    this->health = wrappedEnemy->getHealth();
}