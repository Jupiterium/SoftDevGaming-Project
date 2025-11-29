#include "GameManager.h"
#include "CombatController.h"
#include "GameData.h"
#include "Item.h"
#include "Constants.h"
#include <iostream>
#include <conio.h> // For _getch()
using namespace std;

/* Templates are defined in the header */

// Constructor initializes Player at (1,1) and Map at (15, 10)
GameManager::GameManager() : player("Labubu", 'P', 100, 0, 0), currentMap(MAP_WIDTH, MAP_HEIGHT), currentLevel(1), isRunning(true) {}

// Destructor to clean up memory
GameManager::~GameManager()
{
    ClearPtrVector(enemies);
    ClearPtrVector(itemList);
    ClearPtrVector(keyList);
}

// Initialize the game (grid, places, enemies).
void GameManager::InitGame(bool loadFromSave)
{
    //Clear the console
    system("cls");

	// Hide cursor for cleaner rendering
    HideCursor();

    bool loaded = false;
    int loadedLevel = 0;

	// Attempt to load from save file if requested
    if (loadFromSave)
    {
		//Load game data from file
        loaded = GameData::GetInstance()->LoadGame(player, loadedLevel, itemList, keyList, enemies);
    }

    //If required to load and is loaded successfully 
    if (loadFromSave && loaded)
    {
		// Set current level to loaded level
        currentLevel = loadedLevel;
        
    }
    else
    {
        // Either:
        // - loadFromSave is false (we are starting a fresh level)
        // - or loading failed (no save file)

        // If not loading from save, decide what level we are on
        // When starting a brand new game, you can set currentLevel = 1 before calling this
        // or do it here if level is unknown.
		//Error handling for when loaded level is invalid
        if (!loadFromSave && currentLevel <= 0)
        {
            currentLevel = 1;
        }

        ClearPtrVector(itemList);
        ClearPtrVector(keyList);
        ClearPtrVector(enemies);

        itemList = Item::createItemList(currentLevel);
        keyList = Item::createKeyList(currentLevel);
        enemies = EnemyFactory::CreateEnemiesForLevel(currentLevel);
      
    }

    // Initialize Map visual features
    currentMap.GenerateHiddenGrid();

    // Draw the items
    DrawEntities(itemList, currentMap);
    DrawEntities(keyList, currentMap);

    // Draw Enemies 
    DrawEntities(enemies, currentMap);

    // Draw Player
    DrawEntityPos(player.getSymbol(), player.getX(), player.getY());

	// If all keys are already collected (loaded game), draw treasure
    if (AreAllKeysCollected())
    {
        DrawEntityPos('X', 13, 8);
    }

    system("cls");
}

// Run the main game loop until the player dies or quits.
void GameManager::MainLoop()
{
    system("cls");
	//Check the game is running and player is alive
    while (isRunning && player.isAlive())
    {
		// Update game state (collisions, combat, items, win conditions)
        UpdateGameState();

		//Check for player input
        HandleInput();
    }

    if (!player.isAlive())
    {
        cout << "\nYou Died, Game Over!" << endl;
    }
}

void GameManager::UpdateGameState()
{
    // Draw map
    DrawMap();

    // Call timer to clear messages
    CallTimer(1500);
    DrawHUD();

    // Check Enemy Logic (Collision & Combat)
    for (int i = 0; i < enemies.size(); ++i)
    {
        // Check for collision
        if (player.getX() == enemies[i]->getX() && player.getY() == enemies[i]->getY())
        {
            // Start Combat
            bool won = CombatController::StartBattle(player, *enemies[i]);

            if (won)
            {
                player.addScore(50);

                // Remove enemy visual from map
                currentMap.ReplaceTile('.', enemies[i]->getX(), enemies[i]->getY());

                // Re-draw player
                currentMap.ReplaceTile('P', player.getX(), player.getY());

                // Remove from vector
                delete enemies[i];
                enemies.erase(enemies.begin() + i);
                i--;
            }
            else
            {
                isRunning = false; // Player died, game stopped
            }
        }
    }

    // Check for Items
    for (int i = 0; i < itemList.size(); ++i)
    {
		//If player is on the same position as an item
        if (player.getX() == itemList[i]->getX() && player.getY() == itemList[i]->getY())
        {
			// Collect item
            player.addItemToInv(*itemList[i]);

			//Remove item from map
            delete itemList[i];
            itemList.erase(itemList.begin() + i);

            //Set timer for HUD message ("Item collected")
            hudMessageStartTime = GetTickCount64();
            hudMessageActive = true;
            break;
        }
    }

    // Check Win Condition
    if (AreAllKeysCollected()) {
        if (player.getX() == 13 && player.getY() == 8)
        {
            player.addScore(100);
            NextLevel();
        }
    }
}

void GameManager::HandleInput()
{
	// Poll keyboard input without blocking
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
        case 'k':
        {
			// Save Game
            ClearHUD();
            GameData::GetInstance()->SaveGame(player, currentLevel, itemList, keyList, enemies);
			//Show message in timed HUD
            hudMessage = "Game Saved";
            hudMessageStartTime = GetTickCount64();
            hudMessageActive = true;
            return;
        }
        }

		// Validate movement
        if (currentMap.isWalkable(nextX, nextY))
        {
            bool canMove = true;

            // Check Keys
            for (int i = 0; i < keyList.size(); ++i)
            {
                if (nextX == keyList[i]->getX() && nextY == keyList[i]->getY()) {
					//If all enemies are defeated, keys are unlocked
                    if (!AreEnemiesRemaining()) {
                        player.addScore(50);
                        player.addItemToInv(Item("Key", "Unlock", 'K', 0, 0, 0));

                        currentMap.ReplaceTile('.', nextX, nextY);
                        delete keyList[i];
                        keyList.erase(keyList.begin() + i);

						//Show timed message in HUD
                        hudMessage = "Key Collected!";
                        hudMessageStartTime = GetTickCount64();
                        hudMessageActive = true;

						//If all keys are collected, draw treasure
                        if (AreAllKeysCollected()) {
							//Treasure appears
                            DrawEntityPos('X', 13, 8);
                        }
                    }
                    else {
						//If enemies remain, cannot collect key
                        hudMessage = "Locked! Defeat enemies first.";
                        canMove = false;
                        hudMessageStartTime = GetTickCount64();
                        hudMessageActive = true;
                    }
                }
            }

			//Move player if allowed
            if (canMove)
            {
                //Set player previous position to .
                ClearEntityPos(oldX, oldY);

                //Update player new position on the map
                player.setPosition(nextX, nextY);
                DrawEntityPos('P', player.getX(), player.getY());
            }
        }
    }
}

// Reset previous tile where entity was located to . as they move to new place
void GameManager::ClearEntityPos(int x, int y)
{
    currentMap.ReplaceTile('.', x, y);
}

// Draw entity symbol at new position
void GameManager::DrawEntityPos(char symbol, int x, int y)
{
    currentMap.ReplaceTile(symbol, x, y);
}

void GameManager::NextLevel()
{
    system("cls");
    currentLevel++;
    loadedLevel = currentLevel;
    cout << "Treasure collected. Score +100" << endl;

    cout << "Level Complete! Moving to Level " << currentLevel << "..." << endl;
    _getch();

    player.setPosition(1, 1);
    InitGame(false);
}

// Set console cursor position
//To rerender/reprint map with new updates without glitching 
void GameManager::SetCursorPosition(int x, int y) 
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, pos);
}

// Hide console cursor for cleaner rendering
void GameManager::HideCursor() 
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

// Check if any enemies are still alive
bool GameManager::AreEnemiesRemaining() const 
{
    for (auto e : enemies) { if (e->isAlive()) return true; }
    return false;
}

// Check if all keys have been collected
bool GameManager::AreAllKeysCollected() const { return keyList.empty(); }

//Set cursor to top-left and draw the current map
void GameManager::DrawMap() 
{
    SetCursorPosition(0, 0);
    cout << currentMap;
}

// Clear the HUD area below the map once message duration expires
void GameManager::ClearHUD() 
{
    int hudStartY = currentMap.getHeight() + 2;
    int hudWidth = 100;
    for (int i = 0; i < 15; i++) 
    {
        SetCursorPosition(0, hudStartY + i);
        cout << string(hudWidth, ' ');
    }
}

// Draw the HUD below the map with player stats and messages
void GameManager::DrawHUD() 
{
    int hudStartY = currentMap.getHeight() + 2;
    SetCursorPosition(0, hudStartY);
    cout << "Level " << currentLevel << endl;
    cout << CYAN << "[Press K to save, Q to quit] " << RESET << endl;
    cout << GREEN << hudMessage << RESET << endl;
    cout << "\nHP: " << player.getHealth() << "  Score: " << player.getScore() << endl;
    cout << "Pos: (" << player.getX() << "," << player.getY() << ")" << endl;
    cout << "Enemies remaining: " << enemies.size() << endl;
    cout << "Keys remaining: " << keyList.size() << endl;

}

//Timer to clear HUD message after specified time
void GameManager::CallTimer(int time) 
{
    if (hudMessageActive) {
        ULONGLONG now = GetTickCount64();
        if (now - hudMessageStartTime >= time) 
        {
            ClearHUD();
            hudMessageActive = false;
            hudMessage.clear();
        }
    }
}