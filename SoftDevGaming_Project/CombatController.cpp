// Implementation of turn-based combat controller.

#include "CombatController.h"
#include <iostream>
#include <conio.h> // For _getch() to pause output
using namespace std;

// Private constructor (empty because this is a static-only utility class)
CombatController::CombatController() {}

// Manages a complete battle sequence between player and enemy.
bool CombatController::StartBattle(Player& p, Enemy& e)
{
	system("cls"); // Clear screen for battle mode
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "C O M B A T   S T A R T E D!" << endl;
	cout << "You encountered a " << e.getName() << "!" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	// Main combat loop (alternate turns until one entity dies)
	while (p.isAlive() && e.isAlive())
	{
		// Player Turn
		PlayerTurn(p, e);
		if (!e.isAlive()) break; // Enemy died

		// Enemy Turn
		EnemyTurn(e, p);
		if (!p.isAlive()) break; // Player died
	}

	// Battle Over (display outcome)
	if (p.isAlive())
	{
		cout << "\nVictory! You defeated the " << e.getName() << "!" << endl;
		cout << "Press any key to continue..." << endl;
		(void) _getch(); // Wait for keypress (also explicitly ignore return value)
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

// Handles player's turn  (displays status, prompts for action, executes choice)
void CombatController::PlayerTurn(Player& p, Enemy& e)
{
	// Display status
    cout << "\n~~~ Y O U R   T U R N ~~~" << endl;
    p.DisplayStatus();
    e.DisplayStatus();

	// Prompt for action
    cout << "[1] Attack\n[2] Defend\n[3] Use Item" << endl;
    cout << "Choose action: ";

	// Get player choice (without needing Enter key)
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

    case '3': // Use item from inventory
    {
		// If inventory is empty, cannot use item
        if (p.getInventory().empty())
        {
            cout << "You have no items." << endl;
            break;
        }

		// Display inventory with item descriptions provided by Item
        cout << "\nYour Items:\n";
        for (int i =0; i < (int)p.getInventory().size(); i++) // Int casting because size() returns size_t
        {
            const Item& it = p.getInventory()[i];
            cout << "[" << i << "] " << it.getName() << " (" << it.getItemDescription() << ")" << endl;
        }

		// Prompt for item slot
        cout << "Choose item slot: ";
        char slotChar = _getch();
        cout << slotChar << endl;

		// Validate slot input and call useItem only if valid
        int slot = slotChar - '0'; // Convert char to int
		if (slot >= 0 && slot < (int)p.getInventory().size()) 
        {
          p.useItem(slot);
        }
        else
        {
          cout << "Invalid slot selected. Turn wasted." << endl;
        }
        break;
    }

	//If invalid input, lose turn 
    default:
        cout << "You hesitated and lost your turn!" << endl;
        break;
    }
}

// Executes the enemy's turn: attack the player.
void CombatController::EnemyTurn(Enemy& e, Player& p)
{
	cout << "\n~ E N E M Y   T U R N ~~~";
	e.Attack(&p);
}