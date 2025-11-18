#pragma once
#include <vector>
#include "Enemy.h"

/*
* Purpose of this Class:
* Uses the Factory pattern to encapsulate the logic for creating enemies.
* Also promotes Separation of Concerns principle. GameManager manages the game, EnemyFactory creates enemies.
*/

class EnemyFactory 
{
private:
    EnemyFactory() {}

public:
    // Helper to create a specific type of enemy at a specific location
    static Enemy* CreateEnemy(int typeId, int x, int y);

    // Creates the list of enemies for the GameManager
    static std::vector<Enemy*> CreateEnemiesForLevel(int level);
};