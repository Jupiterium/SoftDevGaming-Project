#include "Enemy.h"
#include "Entity.h"
#include <iostream>
#include <string>
using namespace std;

// Enemy's constructor passes data to Entity
Enemy::Enemy(string n, char c, int h, int a, int x, int y) : Entity(n, c, h, a, x, y) {}

//Attack the target entity, dealing damage equal to this enemy's attack value.
void Enemy::Attack(Entity* target) {
    cout << name << " attacks " << target->getName() << " for " << attack << " damage!\n";
    target->takeDamage(attack);
}

//Display the enemy's current status (name, health, position).
void Enemy::DisplayStatus() const {
    cout << name << " [HP: " << health << "] at (" << x << ", " << y << ")\n";
}