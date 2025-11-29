#pragma once

#include "Player.h"
#include "Enemy.h"

/*
* Purpose of this Class:
* CombatController orchestrates the combat loop between a Player and an Enemy.
* It is entirely static—no instances are created. Combat alternates between
* player turns (choices: attack, defend, use item) and enemy turns (always attacks).
*/

class CombatController 
{
private:
    // Private constructor to prevent instance creation
    CombatController();

    // Private helpers for the combat/battle
    // Handle a player turn (display status, prompt for action, execute choice)
    static void PlayerTurn(Player& p, Enemy& e);

    //Handle an enemy turn: execute the enemy's attack on the player.
    static void EnemyTurn(Enemy& e, Player& p);

public:
    // Run a complete turn-based combat sequence until battle is over.
    static bool StartBattle(Player& p, Enemy& e);
};