#pragma once

#include <iostream>
#include "Player.h"
#include "Enemy.h"

/*
* Purpose of this Class:
* Singleton handler for game save/load operations.
* GameData manages serialization and deserialization of game state to/from disk.
* It is a Singleton to ensure only one save state exists at a time.
*/

class GameData 
{
private:
	static GameData* instance; //Singleton instance
    GameData();

    // Deleted copy/assignment
    GameData(const GameData&) = delete;
    void operator=(const GameData&) = delete;

public:
    // Singleton accessor
    static GameData* GetInstance(); 

    // File I/O methods
    //Save the current game state to disk.
    void SaveGame(Player& player, int currentLevel, const vector<Item*>& worldItems, const vector<Item*>& worldKeys, const vector<Enemy*>& enemies);
    
    //Load a saved game state from disk.
    //If the file is missing, returns false silently (no error message).
    bool LoadGame(Player& player, int& currentLevel, vector<Item*>& worldItems, vector<Item*>& worldKeys, vector<Enemy*>& enemies);
};