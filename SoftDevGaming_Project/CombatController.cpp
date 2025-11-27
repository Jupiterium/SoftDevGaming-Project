// Implementation of turn-based combat controller.

#include "CombatController.h"
#include <iostream>
#include <conio.h> // For _getch() to pause output
using namespace std;

// Private constructor (empty because this is a static-only utility class)
CombatController::CombatController() {}

// Orchestrates a complete battle sequence between player and enemy.
bool CombatController::StartBattle(Player& p, Enemy& e)
{
	system("cls"); // Clear screen for battle mode
	cout << "==========================================" << endl;
	cout << "COMBAT STARTED!" << endl;
	cout << "You encountered a " << e.getName() << "!" << endl;
	cout << "==========================================" << endl;

	// Main combat loop: alternate turns until one combatant dies
	while (p.isAlive() && e.isAlive())
	{
		// Player Turn
		PlayerTurn(p, e);
		if (!e.isAlive()) break; // Enemy died

		// Enemy Turn
		EnemyTurn(e, p);
		if (!p.isAlive()) break; // Player died
	}

	// Battle Over: display outcome
	if (p.isAlive())
	{
		cout << "\nVictory! You defeated the " << e.getName() << "!" << endl;
		cout << "Press any key to continue..." << endl;
		_getch(); // Wait for keypress
		system("cls");
		return true; // Player won
	}
	else
	{
		cout << "\nDefeat... You have fallen." << endl;
		system("cls");
		return false; // Player lost
	}
}

// Handles player's turn: displays status, prompts for action, executes choice.
void CombatController::PlayerTurn(Player& p, Enemy& e)
{
    cout << "\n--- YOUR TURN ---" << endl;
    p.DisplayStatus();
    e.DisplayStatus();

    cout << "[1] Attack\n[2] Defend\n[3] Use Item" << endl;
    cout << "Choose action: ";

    char choice = _getch();
    cout << choice << endl;

    switch (choice)
    {
    case '1':
        p.Attack(&e);
        break;

    case '2':
        p.defend();
        break;

    case '3':// Use item from inventory
    {
		//If inventory is empty, cannot use item
        if (p.getInventory().empty())
        {
            cout << "You have no items." << endl;
            break;
        }

        cout << "\nYour Items:\n";
        for (int i = 0; i < p.getInventory().size(); i++)
        {
            cout << "[" << i << "] " << p.getInventory()[i].getName() << endl;
        }

        cout << "Choose item slot: ";
        char slotChar = _getch();
        cout << slotChar << endl;

        int slot = slotChar - '0'; // convert char to int
        p.useItem(slot);
        break;
    }

	//If invalid input, lose turn (error handling)
    default:
        cout << "You hesitated and lost your turn!" << endl;
        break;
    }
}

// Executes the enemy's turn: attack the player.
void CombatController::EnemyTurn(Enemy& e, Player& p)
{
	cout << "\n--- ENEMY TURN ---" << endl;
	e.Attack(&p);
}