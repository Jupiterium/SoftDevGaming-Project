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

void GameManager::InitGame(bool loadFromSave)
{
    system("cls");
    HideCursor();

    bool loaded = false;
    int loadedLevel = 0;

    if (loadFromSave)
    {
        // Only try to load if we were told to
        loaded = GameData::GetInstance()->LoadGame(player, loadedLevel, itemList, keyList, enemies);
    }

    if (loadFromSave && loaded)
    {
        // Loaded from file successfully
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

    if (AreAllKeysCollected())
    {
        DrawEntityPos('X', 13, 8);
    }

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
                isRunning = false; // Player died
            }
        }
    }

    // Check for Items
    for (int i = 0; i < itemList.size(); ++i)
    {
        if (player.getX() == itemList[i]->getX() && player.getY() == itemList[i]->getY())
        {
            player.addItemToInv(*itemList[i]);
            delete itemList[i];
            itemList.erase(itemList.begin() + i);

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
            ClearHUD();
            GameData::GetInstance()->SaveGame(player, currentLevel, itemList, keyList, enemies);
            hudMessage = "Game Saved";
            hudMessageStartTime = GetTickCount64();
            hudMessageActive = true;
            return;
        }
        }

        if (currentMap.isWalkable(nextX, nextY))
        {
            bool canMove = true;

            // Check Keys
            for (int i = 0; i < keyList.size(); ++i)
            {
                if (nextX == keyList[i]->getX() && nextY == keyList[i]->getY()) {
                    if (!AreEnemiesRemaining()) {
                        player.addScore(50);
                        player.addItemToInv(Item("Key", "Unlock", 'K', 0, 0, 0));

                        currentMap.ReplaceTile('.', nextX, nextY);
                        delete keyList[i];
                        keyList.erase(keyList.begin() + i);

                        hudMessage = "Key Collected!";
                        hudMessageStartTime = GetTickCount64();
                        hudMessageActive = true;

                        if (AreAllKeysCollected()) {
							//Treasure appears
                            DrawEntityPos('X', 13, 8);
                        }
                    }
                    else {
                        hudMessage = "Locked! Defeat enemies first.";
                        canMove = false;
                        hudMessageStartTime = GetTickCount64();
                        hudMessageActive = true;
                    }
                }
            }

            if (canMove)
            {
                ClearEntityPos(oldX, oldY);
                player.setPosition(nextX, nextY);
                DrawEntityPos('P', player.getX(), player.getY());
            }
        }
    }
}

void GameManager::ClearEntityPos(int x, int y)
{
    currentMap.ReplaceTile('.', x, y);
}

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
    return keyList.empty();
}

void GameManager::DrawMap() {
    SetCursorPosition(0, 0);
    cout << currentMap;
}

void GameManager::ClearHUD() {
    int hudStartY = currentMap.getHeight() + 2;
    int hudWidth = 100;
    for (int i = 0; i < 10; i++) {
        SetCursorPosition(0, hudStartY + i);
        cout << string(hudWidth, ' ');
    }
}

void GameManager::DrawHUD() {
    int hudStartY = currentMap.getHeight() + 2;
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
        if (now - hudMessageStartTime >= time) {
            ClearHUD();
            hudMessageActive = false;
            hudMessage.clear();
        }
    }
}