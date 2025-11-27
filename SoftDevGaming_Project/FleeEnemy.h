#pragma once

#include "EnemyDecorator.h"
#include "Map.h"

/*
* Purpose of this Class:
* Adds flee logic to the Attack method.
* (EnemyDecorator2)
* Wraps Enemy objects to make it attempt to flee when its health is low.
*/

class FleeEnemy : public EnemyDecorator {
public:
    // Construct a FleeEnemy by wrapping an existing Enemy.
    //The enemy to wrap (will be deleted by this decorator).
    FleeEnemy(Enemy* enemy) : EnemyDecorator(enemy) {}
    void Flee();
    ~FleeEnemy() override {}
    void takeDamage(int d) override;
};

