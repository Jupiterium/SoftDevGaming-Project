#pragma once

#include "Player.h"
#include "Map.h"
#include "EnemyFactory.h"
#include <vector>

class GameManager
{
private:
	Player player;
	Map currentMap; 
	int currentLevel;
	bool isRunning;

	// We store enemies here to manage them
	std::vector<Enemy*> enemies;
	std::vector<Item*> itemList;

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

	template<typename T>
	void ClearPtrVector(vector<T*>& v);

	template<typename T>
	void DrawEntities(const vector<T*>& list, Map& m);

	bool AreEnemiesRemaining() const;

};