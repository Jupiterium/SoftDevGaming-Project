#pragma once

#include "EnemyDecorator.h"

/*
* Purpose of this Class:
* Adds flee logic to the Attack method.
* (EnemyDecorator2)
*/

class FleeEnemy : public EnemyDecorator {
public:
    // Inherits the constructor
    using EnemyDecorator::EnemyDecorator;

    // Overridden method
    void Attack(Entity* target) override;
};

