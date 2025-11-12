#pragma once

#include <vector>
#include "Enemy.h"

/*
* Purpose of this Class:
* Uses the Factory pattern to encapsulate the logic for creating enemies.
* Also promotes Separation of Concerns principle. GameManager manages the game, EnemyFactory creates enemies.
*/

struct EnemySpawnData {
    int x;
    int y;
    Enemy* enemy;
};

class EnemyFactory {
private:
    EnemyFactory(); // private to prevent instantiation

public:
    // Creates a single enemy type based on level or type ID
    static Enemy* CreateEnemy(int level);

    // Creates and returns all enemies for a level with fixed coordinates
    static std::vector<EnemySpawnData> CreateEnemiesForLevel(int level);
};