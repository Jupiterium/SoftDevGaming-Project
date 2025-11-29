#pragma once

#include <vector>
#include "Entity.h"
#include "Item.h"
using namespace std;

/*
* Purpose of this class:
* Player extends Entity with inventory management, score tracking, and
* player specific actions (move, defend, use items).
* Represents the user-controlled character in the game.
	- Combat: attacks enemies, can defend to block one incoming attack.
    - Inventory: holds items collected during gameplay.
    - Score: accumulates points for defeating enemies and completing objectives.
    - Movement: moves in four cardinal directions (WASD keys).
*/

class Player : public Entity
{
private:
	//Get a reference to the player's inventory
	vector<Item> inventory;

	// Player's score
	int score;

	// Whether the player is currently defending (blocks next attack)
	bool isDefending = false;

public:
	// Constructor passes data to Entity (name, char, health, x coordinate, y coordinate)
	Player(string n, char c, int health, int x, int y);

	// Overridden pure virtual methods
	void Attack(Entity* target) override;
	void DisplayStatus() const override;
	void takeDamage(int d) override;

	// Getters
	int getScore() const;
	vector<Item>& getInventory();

	//Setters (for loading data)
	void setAttack(int a) { attack = a; }
	void setScore(int s) { score = s; }
	void setPosition(int xPos, int yPos) { x = xPos; y = yPos; }
	void setInventory(const vector<Item>& items) { inventory = items; }

	// Player-specific methods
	void move(char direction);
	void defend();
	void addItemToInv(const Item& item);
	void useItem(int invSlot);
	void addScore(int amount);
};