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

public:
	Player(string n, int x, int y);

	// Overridden pure virtual methods
	void Attack(Entity* target) override;
	void DisplayStatus() const override;

	// Getter
	int getScore() const;

	// Player-specific methods
	void move(char direction);
	void defend();
	void addItemToInv(const Item& item);
	void useItem(int invSlot);
};