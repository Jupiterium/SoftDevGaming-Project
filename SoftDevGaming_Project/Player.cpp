#include "Player.h"
#include <iostream>
using namespace std;

// Implementation of Player class: combat, inventory, movement

// This is the key: we pass the Entity's data up using the initializer list.
// Construct player with name, starting position and default health/attack.
Player::Player(string n, char c, int health, int x, int y) : Entity(n, 'P', 100, 10, x, y)
{
	score = 0; // Player-specific variable
}

// Overridden methods (the methods which require implementation)
void Player::Attack(Entity* target)
{
	cout << "\n" << this->name << " attacks " << target->getName() << "!" << endl;
	target->takeDamage(this->attack);
}

void Player::DisplayStatus() const
{
	cout << "> Player: " << this->name << " | HP: " << this->health << " | ATK: " << this->attack << " | Score: " << this->score << endl;
}

// Apply damage, with blocking if currently defending.
void Player::takeDamage(int d) 
{
    if (isDefending)
    {
        cout << name << " blocked the attack!" << endl;
        isDefending = false;  // Defend only lasts for one attack
        return;
    }

    Entity::takeDamage(d);
}

// Getter
int Player::getScore() const { return score; }
vector<Item>& Player::getInventory() { return inventory; }

// The Player-specific methods
// Move Player in the specified direction
void Player::move(char direction)
{
	// Update Player's position based on the direction from the input 
	switch (direction)
	{
	case 'w': this->y--; break;
	case 'a': this->x--; break;
	case 's': this->y++; break;
	case 'd': this->x++; break;
	}
}

// Activate defending state
void Player::defend()
{
	cout << this->name << " is defending!" << endl;
    isDefending = true;
}

// Add item to player's inventory
void Player::addItemToInv(const Item& item)
{
	cout << item.getName() << " was added to your inventory!" << endl;
	inventory.push_back(item);
}

// Use an item from the inventory slot index
void Player::useItem(int invSlot)
{
	// Error handling for empty inventory or invalid slot
    if (inventory.empty())
    {
        cout << "No items available." << endl;
        return;
    }

    if (invSlot < 0 || invSlot >= inventory.size())
    {
        cout << "Invalid item slot." << endl;
        return;
    }

    // If item exists in the inventory, player can use it
    Item& item = inventory[invSlot];
    cout << this->name << " uses the " << item.getName() << "!" << endl;

	// Apply item effects based on type
	// Potion restores health, weapon boosts attack
    if (item.getType() == "potion")
    {
        this->setHealth(this->getHealth() + item.getBoostAmount());
        cout << "You feel healthier!" << endl;
    }
    else if (item.getType() == "weapon")
    {
        this->setAttack(this->getAttack() + item.getBoostAmount());
        cout << "Attack increased by " << item.getBoostAmount() << endl;
    }

    // Remove used item from inventory
    inventory.erase(inventory.begin() + invSlot);
}


// Add score to our player
void Player::addScore(int amount) { score += amount; }