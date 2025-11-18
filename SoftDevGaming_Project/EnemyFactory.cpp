#include "EnemyFactory.h"
#include "ConcreteEnemy.h" 
#include "CounterAttackEnemy.h"
#include "FleeEnemy.h"   
using namespace std;

// Helper method implementation which creates 
// a specific enemy type at specific coordinates.
Enemy* EnemyFactory::CreateEnemy(int typeId, int x, int y) 
{
    switch (typeId) {
    case 1: // Slime (Weak)
        return new ConcreteEnemy("Slime", 10, 3, x, y);

    case 2: // Goblin (Fleeing)
        // Note: Decorator takes a pointer to the concrete enemy
        return new FleeEnemy(new ConcreteEnemy("Goblin", 15, 5, x, y));

    case 3: // Orc (Counter-Attacking)
        return new CounterAttackEnemy(new ConcreteEnemy("Orc", 25, 7, x, y));

        // TODO: Add more enemies

    default: // Default fallback
        return new ConcreteEnemy("Unknown", 5, 1, x, y);
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
        enemies.push_back(CreateEnemy(3, 8, 6));
        enemies.push_back(CreateEnemy(3, 12, 4));
    }
    // TODO: Add more levels
    return enemies;
}