// Implementation of enemy factory: creates enemies and level spawn lists.

#include "EnemyFactory.h"
#include "ConcreteEnemy.h" 
#include "CounterAttackEnemy.h"
#include "FleeEnemy.h"   
using namespace std;

// Creates a specific type of enemy at the given coordinates.
Enemy* EnemyFactory::CreateEnemy(int typeId, int x, int y) 
{
    switch (typeId) {
    case 1: // Slime (Weak)
        return new ConcreteEnemy("Slime", 'E', 100, 5, x, y);

    case 2: // Goblin (Fleeing)
        // Note: Decorator takes a pointer to the concrete enemy
        return new FleeEnemy(new ConcreteEnemy("Goblin", 'E', 95, 8, x, y));

    case 3: // Orc (Counter-Attacking)
        return new CounterAttackEnemy(new ConcreteEnemy("Orc", 'E', 80, 11, x, y));

    default: // Default fallback
        return new ConcreteEnemy("Unknown", 'E', 5, 1, x, y);
    }
}

// Generates the list for the level
vector<Enemy*> EnemyFactory::CreateEnemiesForLevel(int level) 
{
    vector<Enemy*> enemies;

    if (level == 1) 
    {
        // Level 1: Simple mix
        // API usage: CreateEnemy(TypeID, X, Y)
        enemies.push_back(CreateEnemy(1, 3, 5));  // Slime at 3,5
        enemies.push_back(CreateEnemy(2, 7, 2));  // Goblin at 7,2
        enemies.push_back(CreateEnemy(3, 9, 9));  // Orc at 9,9
    }
    else if (level == 2) 
    {
        // Level 2: Harder mix
        enemies.push_back(CreateEnemy(2, 2, 3));
        enemies.push_back(CreateEnemy(2, 8, 6));
        enemies.push_back(CreateEnemy(3, 12, 4));
    }
    else if (level >= 3)
    {
        // Level 3: Harder mix
        enemies.push_back(CreateEnemy(3, 5, 5));
        enemies.push_back(CreateEnemy(3, 5, 2));
        enemies.push_back(CreateEnemy(3, 12, 6));
    }
    return enemies;
}