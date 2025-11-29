#include "Item.h"
#include <iostream>
using namespace std;

// Implementation of Item class and factory methods

// Construct an Item with specified properties
Item::Item(string name, string type, char symbol, int boost, int x, int y) 
{
	// Initialize item properties
	this->name = name;
	this->type = type;
	this->symbol = symbol;
	this->boostAmount = boost;
	this->x = x;
	this->y = y;
}

// Accessor methods implementation for item properties
string Item::getName() const { return this->name; }
string Item::getType() const { return this->type; }
char Item::getSymbol() const { return this->symbol; }
int Item::getBoostAmount() const { return this->boostAmount; }
int Item::getX() const { return this->x; }
int Item::getY() const { return this->y; }

// Return the item description for each type
string Item::GetItemDescription() const
{
	// Convert type to lowercase for case-insensitive comparison
	string lowerType = type;

	for (auto &c : lowerType) c = tolower(c);

	// For healing items
	if (lowerType.find("potion") != string::npos || lowerType.find("meat") != string::npos) // Npos to check if a substring exists within a string
	{
		return string("Restore ") + to_string(boostAmount) + " HP";
	}
	// For attack items
	else if (lowerType.find("weapon") != string::npos || lowerType.find("sword") != string::npos || lowerType.find("dagger") != string::npos || lowerType.find("rock") != string::npos)
	{
		return string("Increase ATK by ") + to_string(boostAmount);
	}
	// For keys/unlock items
	else if (lowerType.find("key") != string::npos || lowerType.find("unlock") != string::npos)
	{
		return string("Unlocks doors/areas");
	}

	// Fallback generic description
	return string("Effect: ") + to_string(boostAmount);
}

// Factory method (creates level-specific world items)
vector<Item*> Item::createItemList(int level) 
{
	vector<Item*> itemList;

	if (level == 1) 
	{
		itemList.push_back(new Item("Sword", "weapon", 's', 10, 5, 7));
		itemList.push_back(new Item("Meat", "potion", 'm', 50, 2, 8));	
	}
	else if (level == 2) 
	{
		itemList.push_back(new Item("Dagger", "weapon", 'd', 5, 6, 7));
		itemList.push_back(new Item("Meat", "potion", 'm', 55, 1, 8));
		itemList.push_back(new Item("Bread", "potion", 'b',45, 3, 7));
		itemList.push_back(new Item("Rock", "weapon", 'r', 2, 13, 0));
	}
	else if (level >= 3) { itemList.push_back(new Item("Magic water", "potion", 'w', 100, 4, 7)); }

	return itemList;
}

// Factory method (create level-specific keys)
vector<Item*> Item::createKeyList(int level) 
{
	vector<Item*> keys;
	
	if (level == 1)
	{
		keys.push_back(new Item("Key", "unlock", 'K', 0, 8, 5));
	}
	else if (level == 2)
	{
		keys.push_back(new Item("Key", "unlock", 'K', 0, 2, 5));
		keys.push_back(new Item("Key", "unlock", 'K', 0, 1, 4));
	}
	else if (level >= 3) 
	{
		keys.push_back(new Item("Key", "unlock", 'K', 0, 10, 5));
		keys.push_back(new Item("Key", "unlock", 'K', 0, 9, 4));
		keys.push_back(new Item("Key", "unlock", 'K', 0, 7, 7));
	}

	return keys;
}

// Print item by name to output stream
ostream& operator<<(ostream& out, const Item& item) 
{
	out << item.getName();
	return out;
}