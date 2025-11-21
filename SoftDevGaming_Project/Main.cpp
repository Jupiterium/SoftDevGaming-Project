#include "GameManager.h"
#include <iostream>
#include <conio.h> // For _getch()

int main()
{
    // Game Manager instance creation
    // This calls the constructor, which sets up the Player and Map sizing
    GameManager game;
    std::cout << "Welcome to the Forest Survival Adventure!" << endl;
    std::cout << "Find the treasure X in the forest." << endl;
    std::cout << "Press any key to start..." << endl;
    _getch();
    system("cls");

    // Initialize the Game
    // This sets up the grid, places the exit/treasure, and spawns enemies
    game.InitGame();

    // Start the Main Loop
    // This runs the game (Input -> Update -> Draw) until the player wins or dies
    game.MainLoop();

    // End of program
    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}