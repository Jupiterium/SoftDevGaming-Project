#include "GameManager.h"
#include "CombatController.h"
#include "GameData.h"
#include <iostream>
#include <conio.h> // For _getch()
using namespace std;

// Constructor: Initializes Player at (1,1) and Map at (15, 10)
GameManager::GameManager() : player("Hero", 1, 1), currentMap(15, 10), currentLevel(1), isRunning(true) {}

// Destructor to clean up memory
GameManager::~GameManager() 
{
    for (auto e : enemies) delete e;
    enemies.clear();
}

void GameManager::InitGame()
{
    // Initialize Map visual features for Level 1
    currentMap.GenerateHiddenGrid(); // Reset to dots

    // Place an Exit
    currentMap.ReplaceTile('X', 13, 8);

    // Place a Treasure
    currentMap.ReplaceTile('T', 8, 5);

    // Draw Features using helper
    DrawEntityPos('X', 13, 8); // Exit
    DrawEntityPos('T', 8, 5);  // Treasure

    // Create Enemies
    // Clear old enemies if restarting
    for (auto e : enemies) delete e;
    enemies.clear();

    enemies = EnemyFactory::CreateEnemiesForLevel(currentLevel);

    // Draw Enemies
    for (auto e : enemies) {
        DrawEntityPos('E', e->getX(), e->getY());
    }

    // Draw Player
    DrawEntityPos('P', player.getX(), player.getY());

    cout << "Welcome to the Forest Survival Adventure!" << endl;
    cout << "Press any key to start..." << endl;
    _getch();
}

void GameManager::MainLoop()
{
    while (isRunning && player.isAlive())
    {
        UpdateGameState();
        HandleInput();
    }

    if (!player.isAlive())
    {
        cout << "\nGAME OVER. You died." << endl;
    }
}

void GameManager::UpdateGameState()
{
    system("cls"); // Clear console

    // 1. Print the Map
    // The map already contains the P, E, X, T chars because we updated them in HandleInput/Init
    cout << currentMap;

    // 2. Draw HUD
    player.DisplayStatus();
    cout << "Pos: (" << player.getX() << "," << player.getY() << ")" << endl;

    // 3. Check Enemy Logic (Collision & Combat)
    for (int i = 0; i < enemies.size(); ++i)
    {
        // Check for collision
        if (player.getX() == enemies[i]->getX() && player.getY() == enemies[i]->getY())
        {
            // Start Combat
            bool won = CombatController::StartBattle(player, *enemies[i]);

            if (won)
            {
                // Reward Score
                player.addScore(50); 

                // Combat won: Remove enemy visual from map
                currentMap.ReplaceTile('.', enemies[i]->getX(), enemies[i]->getY());

                // Re-draw player (in case map was redrawn or cleared)
                currentMap.ReplaceTile('P', player.getX(), player.getY());

                // Remove from vector
                delete enemies[i];
                enemies.erase(enemies.begin() + i);
                // Decrement i so we don't skip the next enemy
                i--;
            }
            else
            {
                isRunning = false; // Player died
            }
        }
    }

    // 4. Check Win Condition (Reaching 'X')
    // We check the tile *under* the player. 
    // Note: Since we replaced the tile with 'P', we might need to check logic differently.
    // A simple way is checking coordinates against known Exit coordinates.
    if (player.getX() == 13 && player.getY() == 8)
    {
        NextLevel();
    }
}

void GameManager::HandleInput()
{
    if (_kbhit())
    {
        char key = _getch();
        int oldX = player.getX();
        int oldY = player.getY();
        int nextX = oldX;
        int nextY = oldY;

        switch (key)
        {
        case 'w': nextY--; break;
        case 's': nextY++; break;
        case 'a': nextX--; break;
        case 'd': nextX++; break;
        case 'q': isRunning = false; return;
        case 'k': GameData::GetInstance()->SaveGame(player); return;
        }

        if (currentMap.isWalkable(nextX, nextY))
        {
            // 1. Check for Treasure BEFORE moving
            // (Assuming your Tile class has getSymbol() or similar)
            char nextTileChar = currentMap.getTile(nextX, nextY).getChar();

            if (nextTileChar == 'T')
            {
                player.addScore(100); // +100 points for treasure
                cout << "Treasure collected! Score +100" << endl;
            }

            // Visual Update Logic (Clear old)
            ClearEntityPos(oldX, oldY);

            // Update Player Data
            player.move(key);

            // raw Player at new position
            DrawEntityPos('P', player.getX(), player.getY());
        }
    }
}

// Replaces the visual character at (x,y) with a floor tile '.'
void GameManager::ClearEntityPos(int x, int y)
{
    // '.' is our default floor character
    currentMap.ReplaceTile('.', x, y);
}

// Draws a specific character (P, E, X, etc.) at (x,y)
void GameManager::DrawEntityPos(char symbol, int x, int y)
{
    currentMap.ReplaceTile(symbol, x, y);
}

void GameManager::NextLevel()
{
    currentLevel++;
    cout << "Level Complete! Moving to Level " << currentLevel << "..." << endl;
    _getch();

    // Reset the player's position to the start of the map
    player.setPosition(1, 1);

    // Re-initialize the map and enemies
    // InitGame() will redraw the 'P' at the new (1,1) coordinates
    InitGame();
}