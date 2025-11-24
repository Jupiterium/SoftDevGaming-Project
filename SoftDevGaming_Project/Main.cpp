#include "GameManager.h"
#include "Constants.h"
#include <iostream>
#include <conio.h> // For _getch()

int main()
{
    // Game Manager instance creation
    // This calls the constructor, which sets up the Player and Map sizing
    GameManager game;
    std::cout << "Welcome to the Forest Survival Adventure!" << endl;
    std::cout << "Find the treasure X in the forest." << endl;

    std::cout << "\nLegends: " << endl;
    std::cout << CYAN << "P = Player" << RESET << endl;
    std::cout << RED << "X = Treasure" << RESET << endl;
    std::cout << GREEN << "K = Key" << RESET << endl;
    std::cout << BROWN << "E = Enemy" << RESET << endl;
    std::cout << BLUE << "Others = Collectables" << RESET << endl;

    std::cout << "\nPress K to save game. " << endl;
    std::cout << "-------------------------" << endl;

    std::cout << "\nPress any key to start..." << endl;
    _getch();
    system("cls");

    // Initialize the Game
    // This sets up the grid, places the exit/treasure, and spawns enemies
    game.InitGame(true);

    // Start the Main Loop
    // This runs the game (Input -> Update -> Draw) until the player wins or dies
    game.MainLoop();

    // End of program
    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}