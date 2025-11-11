#include "Enemy.h"
#include "Entity.h"
#include <iostream>
#include <string>
using namespace std;

// Enemy's constructor passes data to Entity
Enemy::Enemy(string n, int h, int a, int x, int y) : Entity(n, h, a, x, y) {}