#pragma once

#include "Enemy.h"

/*
* Purpose of this Abstract Class:
* Base class for all decorators. Provides pass-through implementations for all virtual functions. 
* Wraps an existing Enemy instance and forwards all virtual calls to it by default. 
* Concrete decorators (CounterAttackEnemy, FleeEnemy) override selected methods 
* to inject new behavior while delegating other calls to the wrapped enemy.
*/

class EnemyDecorator : public Enemy 
{
// Encapsulated wrapped enemy for inheritance by concrete decorators
protected:
    Enemy* wrappedEnemy;

public:
    // The decorator copies the wrapped enemy's properties (name, symbol, health, attack, position)
    // into its own Entity base class so that queries against the decorator return current stats.
    EnemyDecorator(Enemy* enemy);

	// Pass-through implementations that delegate to the wrapped enemy
    virtual void Attack(Entity* target) override;
    virtual void DisplayStatus() const override;
    virtual void takeDamage(int d) override;

	//Clean up wrapped enemy
    virtual ~EnemyDecorator() { delete wrappedEnemy; }
};
