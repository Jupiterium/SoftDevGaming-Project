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

        // Check if enemy died after taking damage
        if (!e.isAlive())
        {
            // Exit the loop so the enemy cannot attack back
            break; 
        }

        // Enemy Turn
        EnemyTurn(e, p);
        if (!p.isAlive()) break; // Player died
    }

    // Battle Over results
    if (p.isAlive())
    {
        cout << "\nVictory! You defeated the " << e.getName() << "!" << endl;
        cout << "Press any key to continue..." << endl;
        _getch();
        return true; // Player won
    }
    else
    {
        cout << "\nDefeat... You have fallen." << endl;
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

    char choice;
    choice = _getch();
    cout << choice << endl;

    switch (choice)
    {
    case '1':
        p.Attack(&e); break;
    case '2':
        p.defend(); break;
    case '3':
        // Simple hardcoded slot 0 for now, or ask for input
        p.useItem(0); break;
    default:
        cout << "You hesitated and lost your turn!" << endl; // Any other input and you're cooked :)
        break;
    }
}

void CombatController::EnemyTurn(Enemy& e, Player& p)
{
    cout << "\n--- ENEMY TURN ---" << endl;
    e.Attack(&p);
}