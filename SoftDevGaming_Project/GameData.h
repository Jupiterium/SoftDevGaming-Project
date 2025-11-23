#pragma once

#include <iostream>
#include "Player.h"

/*
* Purpose of this Class:
* Handles saving/loading game data using the Singleton Pattern.
*/

class GameData 
{
private:
    static GameData* instance;
    GameData();

    // Deleted copy/assignment
    GameData(const GameData&) = delete;
    void operator=(const GameData&) = delete;

public:
    // Singleton accessor
    static GameData* GetInstance(); 

    // File I/O methods
    void SaveGame(Player& player, int currentLevel);
    void LoadGame(Player& player, int& currentLevel);
};
