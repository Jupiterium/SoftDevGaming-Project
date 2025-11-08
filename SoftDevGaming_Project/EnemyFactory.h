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
    // Private constructor so there's no acces to it by others
    EnemyFactory();

public:
    // Static methods to create enemies
    static Enemy* CreateEnemy(int level);
    static vector<Enemy*> CreateEnemiesForLevel(int level);
};
