#pragma once

#include "EnemyDecorator.h"

/*
* Purpose of this Class:
* Adds counter-attack logic to the takeDamage method.
* (EnemyDecorator1)
*/

class CounterAttackEnemy : public EnemyDecorator {
public:
    // Inherits the constructor
    using EnemyDecorator::EnemyDecorator;

    // Overridden method
    void takeDamage(int d) override;
    
    void Attack(Entity* target) override;
    ~CounterAttackEnemy() override {}
};
