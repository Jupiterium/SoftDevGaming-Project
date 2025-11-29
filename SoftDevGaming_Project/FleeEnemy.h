#pragma once

#include "EnemyDecorator.h"
#include "Map.h"

/*
* Purpose of this Class:
* Adds flee logic to the Attack method.
* Wraps Enemy objects to make it attempt to flee when its health is low.
* (EnemyDecorator2)
*/

class FleeEnemy : public EnemyDecorator 
{
public:
    // Construct a FleeEnemy by wrapping an existing Enemy
    // The enemy to wrap (will be deleted by this decorator)
    FleeEnemy(Enemy* enemy) : EnemyDecorator(enemy) {}

	// Flee method and overridden method
    void Flee();
    void takeDamage(int d) override;

	// Destructor to clean up the wrapped enemy
    ~FleeEnemy() override {}
};