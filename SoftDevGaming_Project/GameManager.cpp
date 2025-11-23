#include "GameManager.h"
#include "CombatController.h"
#include "GameData.h"
#include "Item.h"
#include "Constants.h"
#include <iostream>
#include <conio.h> // For _getch()
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
GameManager::GameManager() : player("Labubu", 'P', 100,  0, 0), currentMap(MAP_WIDTH, MAP_HEIGHT), currentLevel(1), isRunning(true) {}

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

    GameData::GetInstance()->LoadGame(player, loadedLevel);
    currentLevel = loadedLevel;

    // Initialize Map visual features for Level 1
    currentMap.GenerateHiddenGrid(); // Reset to dots

    //Add Items
    //Sword
    ClearPtrVector(itemList);
    ClearPtrVector(keyList);


    itemList = Item::createItemList(currentLevel);
    keyList = Item::createKeyList(currentLevel);     // Keys

    // Draw
    DrawEntities(itemList, currentMap);
    DrawEntities(keyList, currentMap);


    // Draw Features using helper
    //DrawEntityPos('K', 8, 5);  // Key Item
    

    // Create Enemies
    // Clear old enemies if restarting
    ClearPtrVector(enemies);
    enemies = EnemyFactory::CreateEnemiesForLevel(currentLevel);

    // Draw Enemies
    DrawEntities(enemies, currentMap);

    // Draw Player
    DrawEntityPos(player.getSymbol(), player.getX(), player.getY());

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
    // 1. Draw map
    DrawMap();

    //2. Draw HUD

    /*Every time game updated, 
    this will call the timer to clear any unnecessary messages with timer*/
    CallTimer(1500);
    DrawHUD();

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
            hudMessageStartTime = GetTickCount64(); // record time now
            hudMessageActive = true;
            break;
        }
    }

    // 5. Check Win Condition (Reaching 'X')
    // We check the tile *under* the player. 
    // Note: Since we replaced the tile with 'P', we might need to check logic differently.
    // A simple way is checking coordinates against known Treasure coordinates.
    // Only allow player to win if treasure is visible/unlocked
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
            case 'k':
            {
                ClearHUD();              
                GameData::GetInstance()->SaveGame(player, currentLevel); 
                hudMessage = "Game Saved";
                hudMessageStartTime = GetTickCount64(); // record time now
                hudMessageActive = true;
                return;
            }
        }

        if (currentMap.isWalkable(nextX, nextY))
        {
            bool canMove = true;

            ////using different logic to check all the keys in the scene
            for (int i = 0; i < keyList.size(); ++i)
            {
                if (nextX == keyList[i]->getX() && nextY == keyList[i]->getY()) {
                    if (!AreEnemiesRemaining()) {

                        player.addScore(50); // +100 points for key item
                        player.addItemToInv(Item("Key", "Unlock", 'K', 0, player.getX(), player.getY()));
                        cout << "Key collected! Score +50." << endl;

                        // Remove the key item visually
                        currentMap.ReplaceTile('.', nextX, nextY);
                        
                        delete keyList[i];
                        keyList.erase(keyList.begin() + i);
                        // Check if this was the last key to reveal treasure
                        if (AreAllKeysCollected()) {
                            DrawEntityPos('X', 13, 8); // now exit is visible
                            cout << "Treasure appeared!" << endl;
                        }
                    }
                    else {
                        cout << "The key is locked! Defeat all enemies first." << endl;
                        canMove = false; // Prevent player from moving onto the locked treasure
                        hudMessageStartTime = GetTickCount64(); // record time now
                        hudMessageActive = true;
                    }
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
    system("cls");
    currentLevel++;
    loadedLevel = currentLevel;
    cout << "Treasure unlocked! Score +100." << endl;
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

bool GameManager::AreAllKeysCollected() const {
    return keyList.empty();    // If no keys remain, they were all collected
}


// Draws map at top-left (0,0)
void GameManager::DrawMap() {
    SetCursorPosition(0, 0);
    cout << currentMap;
}

void GameManager::ClearHUD() {
    int hudStartY = currentMap.getHeight() + 2; // row where HUD begins
    int hudWidth = 100; // width wide enough for all HUD lines
    for (int i = 0; i < 10; i++) { // assuming 10 lines of HUD
        SetCursorPosition(0, hudStartY + i);
        cout << string(hudWidth, ' '); // overwrite with spaces
    }
}

void GameManager::DrawHUD() {
    int hudStartY = currentMap.getHeight()+ 2;
    SetCursorPosition(0, hudStartY);
    cout << CYAN << hudMessage << RESET << endl;
    cout << "\nHP: " << player.getHealth() << "  Score: " << player.getScore() << endl;
    cout << "Pos: (" << player.getX() << "," << player.getY() << ")" << endl;
    cout << "Enemies remaining: " << enemies.size() << endl;
    cout << "Keys remaining: " << keyList.size() << endl;
    
}

void GameManager::CallTimer(int time) {
    if (hudMessageActive) {
        ULONGLONG now = GetTickCount64();
        if (now - hudMessageStartTime >= time) { // 2000ms = 2 second
            ClearHUD();
            hudMessageActive = false;
            hudMessage.clear();
        }
    }
}
