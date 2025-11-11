#pragma once

#include "Enemy.h"

/*
* Purpose of this Abstract Class:
* Base class for all decorators. Provides pass-through implementations for all virtual functions. 
* Allows adding behaviors (i.e. counterattack or fleeing) to existing enemies.
*/

class EnemyDecorator : public Enemy 
{
protected:
    Enemy* wrappedEnemy;

public:
    EnemyDecorator(Enemy* enemy);

    // Pass-through implementations
    virtual void Attack(Entity* target) override;
    virtual void DisplayStatus() const override;
    virtual void takeDamage(int d) override;
};