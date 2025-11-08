#pragma once

#include "Player.h"
#include "Map.h"

/*
* Purpose of this Class:
* The class that controls the main game loop, levels, and transitions.
*/

class GameManager 
{
private:
    Player player;
    Map currentMap;
    int currentLevel;
    bool isRunning;

    // Helper methods
    void HandleInput();
    void UpdateGameState();

public:
    GameManager();
    void InitGame();
    void MainLoop();
    void NextLevel();
};
