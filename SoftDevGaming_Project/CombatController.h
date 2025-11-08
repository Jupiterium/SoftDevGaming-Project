#pragma once

#include "Player.h"
#include "Enemy.h"

/*
* Purpose of this Class:
* A static helper class that handles the turn-based combat loop.
*/

class CombatController 
{
private:
    // Private constructor to prevent instance creation
    CombatController();

    // Private helpers for the combat/battle
    static void PlayerTurn(Player& p, Enemy& e);
    static void EnemyTurn(Enemy& e, Player& p);

public:
    // Runs a loop until the battle is over
    static bool StartBattle(Player& p, Enemy& e);
};
