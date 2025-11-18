#include "Player.h"
#include <iostream>
using namespace std;

// This is the key: we pass the Entity's data up using the initializer list.
// We only set the Player's *own* variables (score) in the body.
Player::Player(string n, int x, int y) : Entity(n, 100, 10, x, y)
{
    // Player-specific variable
    score = 0;
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

// Getter
int Player::getScore() const { return score; }


// The Player-specific methods
// The main logic for these is called by the Managers
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

void Player::defend()
{
    cout << this->name << " is defending!" << endl;
}

void Player::addItemToInv(const Item& item)
{
    cout << item.getName() << " was added to your inventory!" << endl;
    inventory.push_back(item);
}

void Player::useItem(int invSlot)
{
    if (invSlot < 0 || invSlot >= inventory.size())
    {
        cout << "Invalid item slot." << endl;
        return;
    }

    Item& item = inventory[invSlot];

    cout << this->name << " uses the " << item.getName() << "!" << endl;

    // Check for an item type
    if (item.getType() == "potion")
    {
        this->setHealth(this->getHealth() + item.getBoostAmount());
        cout << "You feel healthier!" << endl;
    }

    // Erase the item from the inventory after using it
    inventory.erase(inventory.begin() + invSlot);
}

// Add score to our player
void Player::addScore(int amount) {
    score += amount;
}