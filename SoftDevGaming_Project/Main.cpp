#include "GameManager.h"
#include "Constants.h"
#include <iostream>
#include <conio.h> // For _getch()
using namespace std;

int main()
{
    try 
    {
        // Game Manager instance creation
        // This calls the constructor, which sets up the Player and Map sizing
        GameManager game;
        cout << "Welcome to the Terminal Forest Adventure!" << endl;
        cout << "Find the treasure in the forest, but be careful, it is dangerous!" << endl;

        cout << "\nLegend: " << endl;
        cout << CYAN << "P = Player" << RESET << endl;
        cout << BROWN << "X = Treasure" << RESET << endl;
        cout << GREEN << "K = Key" << RESET << endl;
        cout << RED << "E = Enemy" << RESET << endl;
        cout << BLUE << "Others = Collectables" << RESET << endl;

        cout << "\nWhile playing, press K to save the game, and Q to quit." << endl;
        cout << "-------------------------------------------------------" << endl;

        // Menu for the player to choose to continue playing or not
        cout << "So, would you like to continue or start a new adventure?" << endl;
        cout << "Any Key = Continue\tN = New Game\tQ = Quit" << endl;

        char choice = _getch();
        if (choice == 'q' || choice == 'Q')
        {
            cout << "Game Over! Thank you for playing!\n";
            // Exit straightaway to avoid initializing the map
            return 0;
        }
        else if (choice == 'n' || choice == 'N')
        {
            cout << "\nNew Game loading..." << endl;
            system("cls");

            // Initialize the Game
            // This sets up the grid, places the exit/treasure, and spawns enemies
            game.InitGame(false);
        }
        else 
        {
            system("cls");

            // Initialize the Game
            // This sets up the grid, places the exit/treasure, and spawns enemies
            game.InitGame(true);
        }

        // Start the Main Loop
        // This runs the game until the player wins or dies
        game.MainLoop();
    } 
	// Handle any errors
    catch (const exception& ex) 
    {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }
    catch (...) 
    {
        cerr << "Unknown EWrror" << endl;
        return 2;
    }
    // End of program
    cout << "Thanks for playing!" << endl;
    return 0;
}