#pragma once

#include "EnemyDecorator.h"
#include "Map.h"

/*
* Purpose of this Class:
* Adds flee logic to the Attack method.
* (EnemyDecorator2)
*/

class FleeEnemy : public EnemyDecorator {
public:
    // Inherits the constructor
    FleeEnemy(Enemy* enemy) : EnemyDecorator(enemy) {}
    void Flee();
    ~FleeEnemy() override {}
    void takeDamage(int d) override;
};

