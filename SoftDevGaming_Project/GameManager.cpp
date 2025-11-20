#include "GameManager.h"
#include "CombatController.h"
#include "GameData.h"
#include "Item.h"
#include "Constants.h"
#include <iostream>
#include <conio.h> // For _getch()
#include <windows.h>
using namespace std;

template<typename T>
void GameManager::ClearPtrVector(vector<T*>& v) {
    for (auto p : v) delete p;
    v.clear();
}

template<typename T>
void GameManager::DrawEntities(const vector<T*>& list, Map& m) {
    for (auto e : list)
        m.ReplaceTile(e->getSymbol(), e->getX(), e->getY());
}


// Constructor initializes Player at (1,1) and Map at (15, 10)
GameManager::GameManager() : player("Labubu", 'P', 100,  1, 1), currentMap(MAP_WIDTH, MAP_HEIGHT), currentLevel(1), isRunning(true) {}

// Destructor to clean up memory
GameManager::~GameManager() 
{
    ClearPtrVector(enemies);

    ClearPtrVector(itemList);
}

void GameManager::InitGame()
{
    system("cls");
    HideCursor();
    // Initialize Map visual features for Level 1
    currentMap.GenerateHiddenGrid(); // Reset to dots

    //Add Items
    //Sword
    ClearPtrVector(itemList);

    itemList = Item::createItemList();

    // Draw Enemies
    DrawEntities(itemList, currentMap);


    // Draw Features using helper
    DrawEntityPos('X', 13, 8); // Exit
    DrawEntityPos('T', 8, 5);  // Treasure
    

    // Create Enemies
    // Clear old enemies if restarting
    ClearPtrVector(enemies);
    enemies = EnemyFactory::CreateEnemiesForLevel(currentLevel);

    // Draw Enemies
    DrawEntities(enemies, currentMap);

    // Draw Player
    DrawEntityPos(player.getSymbol(), player.getX(), player.getY());

    cout << "Welcome to the Forest Survival Adventure!" << endl;
    cout << "Press any key to start..." << endl;
    _getch();
    system("cls");

}

void GameManager::MainLoop()
{
    system("cls");
    while (isRunning && player.isAlive())
    {
        UpdateGameState();
        HandleInput();
    }

    if (!player.isAlive())
    {
        cout << "\nYou Died, Game Over!" << endl;
    }
}

void GameManager::UpdateGameState()
{
   /* system("cls");*/ // Clear console
    SetCursorPosition(0, 0);

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
    
    //4. Check for Items
    //TODO: Add items to inventory so that can be used for attack purpose
    for (int i = 0; i < itemList.size(); ++i)
    {
        // Check for collision
        if (player.getX() == itemList[i]->getX() && player.getY() == itemList[i]->getY())
        {
            player.addItemToInv(*itemList[i]);
            delete itemList[i];
            itemList.erase(itemList.begin() + i);

            break;
        }
    }

    // 5. Check Win Condition (Reaching 'X')
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
    // Checks if a key is currently being pressed
    if (_kbhit()) // _kbhit() (Keyboard Hit) peeks to see if a key is waiting
    {
        // Grabs the keyboard hit key immediately
        char key = _getch(); // _getch (Get Character)

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
            char nextTileChar = currentMap.getTile(nextX, nextY).getChar();

            bool canMove = true;

            if (nextTileChar == 'T') {
                if (!AreEnemiesRemaining()) {
                    player.addScore(100); // +100 points for treasure
                    cout << "Treasure collected! Score +100" << endl;

                    // Remove the treasure visually
                    currentMap.ReplaceTile('.', nextX, nextY);
                }
                else {
                    cout << "The treasure is locked! Defeat all enemies first." << endl;
                    canMove = false; // Prevent player from moving onto the locked treasure
                }
            }

            if (canMove)
            {
                // Visual Update Logic (Clear old)
                ClearEntityPos(oldX, oldY);

                // Update Player Data
                player.setPosition(nextX, nextY);

                // Place the Player at new position
                DrawEntityPos('P', player.getX(), player.getY());
            }
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
    _getch(); // Grab the pressed character 

    // Reset the player's position to the start of the map
    player.setPosition(1, 1);

    // Re-initialize the map and enemies
    // InitGame() will redraw the 'P' at the new (1,1) coordinates
    InitGame();
}


void GameManager::SetCursorPosition(int x, int y) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, pos);
}

void GameManager::HideCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

bool GameManager::AreEnemiesRemaining() const {
    for (auto e : enemies) {
        if (e->isAlive()) return true;
    }
    return false;
}