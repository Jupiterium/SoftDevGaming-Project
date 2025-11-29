#pragma once
#include <vector>
#include "Enemy.h"

/*
* Factory for creating enemies with appropriate stats and decorators.
* EnemyFactory uses the Factory design pattern to encapsulate enemy creation logic.
* It supports both creating individual enemies and generating all enemies for a level.
* This separates creation details from the rest of the game system.
*/

class EnemyFactory 
{
private:
	// Private constructor to prevent outside instantiation
    EnemyFactory() {}

public:
    // Helper to create a specific type of enemy at a specific location
    static Enemy* CreateEnemy(int typeId, int x, int y);

    // Generate the enemy list for a specific game level
    static std::vector<Enemy*> CreateEnemiesForLevel(int level);
};