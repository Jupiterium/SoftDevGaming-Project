#include "GameManager.h"
#include <iostream>

int main()
{
    // Game Manager instance creation
    // This calls the constructor, which sets up the Player and Map sizing
    GameManager game;

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