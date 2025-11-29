#pragma once

#include <string>
#include <vector>
using namespace std;

/*
* Purpose of this class:
* An item that can be picked up and used by the player.
* Items can be weapons (increase attack), potions (restore health),
* or keys (unlock progression). Items have a type, name, symbol, buffed value, and position on the map.
*/

class Item
{
	// Private members to encapsulate item properties
private:
	// Item attributes
    string name;
    string type;
    char symbol;
    int boostAmount; //Value applied when used (damage or healing)
	int x, y; // Position on the map

public:
    // Construct an Item with optional default values
    Item(string name = "Default", string type = "Default", char symbol = ' ', int boost = 0, int x = 0, int y = 0);

	// Getters for item properties
    string getName() const;
    string getType() const;
    char getSymbol() const;
    int getBoostAmount() const;
    int getX() const;
    int getY() const;

	// Return the item description for each type
    string getItemDescription() const;

    //Create a list of items appropriate for a given level
    static vector<Item*> createItemList(int level);

    //Create a list of keys (unlock items) for a given level
    static vector<Item*> createKeyList(int level);

	// Overloaded output operator for easy printing of item details
    friend ostream& operator<< (ostream& out, const Item& item);
};