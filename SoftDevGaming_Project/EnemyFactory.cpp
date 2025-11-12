#include "EnemyFactory.h"
#include "CounterAttackEnemy.h"
#include "FleeEnemy.h"
#include <iostream>
using namespace std;

EnemyFactory::EnemyFactory() {}

// Create a single enemy based on level (you can expand this logic easily)
Enemy* EnemyFactory::CreateEnemy(int level) {
    switch (level) {
    case 1:
        return new Enemy("Slime", 10, 3, 1, 1);
    case 2:
        return new FleeEnemy(new Enemy("Goblin", 15, 5, 2, 2));
    case 3:
        return new CounterAttackEnemy(new Enemy("Orc", 25, 7, 3, 3));
    default:
        return new Enemy("Unknown Creature", 5, 2, 1, 1);
    }
}

// Creates predefined enemies with known coordinates
std::vector<EnemySpawnData> EnemyFactory::CreateEnemiesForLevel(int level) {
    std::vector<EnemySpawnData> enemies;

    if (level == 1) {
        enemies.push_back({ 3, 5, CreateEnemy(1) });  // Slime at (3,5)
        enemies.push_back({ 7, 2, CreateEnemy(2) });  // Goblin at (7,2)
        enemies.push_back({ 9, 9, CreateEnemy(3) });  // Orc at (9,9)
    }
    else if (level == 2) {
        enemies.push_back({ 2, 3, CreateEnemy(2) });
        enemies.push_back({ 8, 6, CreateEnemy(3) });
    }

    return enemies;
}
