#include "CombatController.h"
#include <iostream>
#include <conio.h> // For _getch() to pause output
using namespace std;

// Private constructor (empty because it's static)
CombatController::CombatController() {}

bool CombatController::StartBattle(Player& p, Enemy& e)
{
	system("cls"); // Clear screen for battle mode
	cout << "==========================================" << endl;
	cout << "COMBAT STARTED!" << endl;
	cout << "You encountered a " << e.getName() << "!" << endl;
	cout << "==========================================" << endl;

	while (p.isAlive() && e.isAlive())
	{
		// Player Turn
		PlayerTurn(p, e);
		if (!e.isAlive()) break; // Enemy died

		// Enemy Turn
		EnemyTurn(e, p);
		if (!p.isAlive()) break; // Player died
	}

	// Battle Over results
	if (p.isAlive())
	{
		cout << "\nVictory! You defeated the " << e.getName() << "!" << endl;
		cout << "Press any key to continue..." << endl;
		_getch(); // Grab the character pressed
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

    case '3':
    {
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

    default:
        cout << "You hesitated and lost your turn!" << endl;
        break;
    }
}


void CombatController::EnemyTurn(Enemy& e, Player& p)
{
	cout << "\n--- ENEMY TURN ---" << endl;
	e.Attack(&p);
}