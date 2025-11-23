#pragma once

#include <vector>
#include "Entity.h"
#include "Item.h"
using namespace std;

/*
* Purpose of this class:
* Represents the player. Implements the inherited Entity interface.
*/

class Player : public Entity
{
private:
	vector<Item> inventory;
	int score;
	bool isDefending = false;

public:
	Player(string n, char c, int health, int x, int y);

	// Overridden pure virtual methods
	void Attack(Entity* target) override;
	void DisplayStatus() const override;
	void takeDamage(int d) override;

	// Getter
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