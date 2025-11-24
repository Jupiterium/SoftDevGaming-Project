#pragma once

#include "Player.h"
#include "Map.h"
#include "EnemyFactory.h"
#include "GameData.h"
#include <vector>
#include <windows.h>

class GameManager
{
private:
	Player player;
	Map currentMap;
	int currentLevel;
	bool isRunning;
	int loadedLevel = 1;

	ULONGLONG hudMessageStartTime = 0;
	bool hudMessageActive = false;
	string hudMessage = "";

	// We store enemies here to manage them
	std::vector<Enemy*> enemies;
	std::vector<Item*> itemList;
	vector<Item*> keyList;

	// Helper methods
	void HandleInput();
	void UpdateGameState();

	// Helper to clean up map visuals before moving entities
	void ClearEntityPos(int x, int y);
	void DrawEntityPos(char symbol, int x, int y);

public:
	GameManager();
	~GameManager(); // Destructor to clean up enemies

	// Initialize the game (grid, places, enemies)
	void InitGame();

	// Main Loop of the game (input -> update -> draw)
	void MainLoop();

	// Move to next level
	void NextLevel();

	void SetCursorPosition(int x, int y);
	void HideCursor();

	bool AreEnemiesRemaining() const;
	bool AreAllKeysCollected() const;

	void DrawMap();
	void ClearHUD();
	void DrawHUD();
	//void SetTimer();
	void CallTimer(int time);

	// Templates are to be defined in the header
	template<typename T>
	void ClearPtrVector(vector<T*>& v)
	{
		for (auto p : v) delete p;
		v.clear();
	}

	template<typename T>
	void DrawEntities(const vector<T*>& list, Map& m)
	{
		for (auto e : list)
			m.ReplaceTile(e->getSymbol(), e->getX(), e->getY());
	}
};