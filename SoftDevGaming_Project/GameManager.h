#pragma once

#include "Player.h"
#include "Map.h"
#include "EnemyFactory.h"
#include "GameData.h"
#include <vector>
#include <windows.h>

/*
* Central game loop and high-level state manager.
* GameManager coordinates the player, map, enemies, items, and the main
* game loop (input -> update -> draw). It manages level progression,
* collision detection, HUD display, and save/load functionality.
* Responsibilities:
* - Initialize and manage game state (player, map, enemies, items)
* - Execute the main loop: draw -> handle input -> update state
* - Handle collisions (enemies, items, keys)
* - Manage level progression and asset generation
* - Provide save/load integration
* - Manage console cursor and HUD display
* The GameManager owns all dynamic game objects (player, enemies, items)
* and is responsible for their cleanup in the destructor.
*/

class GameManager
{
//Private members to encapsulate game state, use public methods to control game flow
private:
	Player player;
	Map currentMap;
	int currentLevel;
	bool isRunning; // Is the game running
	int loadedLevel = 1; // Level loaded from save (if any)

	ULONGLONG hudMessageStartTime = 0; // Time when the HUD message was set
	bool hudMessageActive = false; //If HUD message is active
	string hudMessage = "";

	// We store things here to manage them
	std::vector<Enemy*> enemies; 
	std::vector<Item*> itemList;
	vector<Item*> keyList;

	// Helper methods
	//Poll keyboard input and move player, handle commands.
	void HandleInput();

	// Update game state: collisions, combat, items, win conditions
	void UpdateGameState();

	// Move to next level
	void NextLevel();

	//Set console cursor position and visibility
	void SetCursorPosition(int x, int y);
	//Hide console cursor for cleaner rendering
	void HideCursor();

	bool AreEnemiesRemaining() const;
	bool AreAllKeysCollected() const;

	//Render current maps
	void DrawMap();

	// HUD methods
	void ClearHUD();
	void DrawHUD();

	//Clear a timed HUD message after duration
	void CallTimer(int time);

	// Helper to clean up map visuals before moving entities
	void ClearEntityPos(int x, int y); // Memory deallocation
	void DrawEntityPos(char symbol, int x, int y); // Memory allocation

	// Templates are to be defined in the header
	//Delete pointers in a vector and clear the vector (Memory deallocation)
	template<typename T>
	void ClearPtrVector(vector<T*>& v)
	{
		for (auto p : v) delete p;
		v.clear();
	}

	//Draw all entities from a list onto the map (Memory allocation)
	template<typename T>
	void DrawEntities(const vector<T*>& list, Map& m)
	{
		for (auto e : list) m.ReplaceTile(e->getSymbol(), e->getX(), e->getY());
	}


public:
	GameManager(); //Construct with default map and player
	~GameManager(); // Destructor to clean up enemies

	// Initialize the game (grid, places, enemies)
	/// @param loadFromSave 
	/// If true, attempt to load from "savegame.txt"                  
	/// If false, start a fresh level
	void InitGame(bool loadFromSave = false);

	// Run the main game loop until the player dies or quits
	// Loop iteration:
	// 1. Draw map and HUD
	// 2. Handle player input
	// 3. Update game state (collisions, combat, win conditions)
	// Exits when isRunning becomes false or player is dead.
	void MainLoop();

};