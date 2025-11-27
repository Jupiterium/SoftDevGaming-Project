#include "Item.h"
#include <iostream>

Item::Item(std::string name, string type, char symbol, int boost, int x, int y) {
	this->name = name;
	this->type = type;
	this->symbol = symbol;
	this->boostAmount = boost;
	this->x = x;
	this->y = y;
}

string Item::getName() const {
	return this->name;
}

string Item::getType() const {
	return this->type;
}

char Item::getSymbol() const {
	return this->symbol;
}

int Item::getBoostAmount() const {
	return this->boostAmount;
}

int Item::getX() const {
	return this->x;
}

int Item::getY() const {
	return this->y;
}

//create items for different levels with different pos
vector<Item*> Item::createItemList(int level) {
	vector<Item*> itemList;

	if (level == 1) {
		itemList.push_back(new Item("Sword", "weapon", 's', 10, 5, 7));
		itemList.push_back(new Item("Meat", "potion", 'm', 50, 2, 8));	
	}
	else if (level == 2) {
		itemList.push_back(new Item("Dagger", "weapon", 'd', 5, 6, 7));
		itemList.push_back(new Item("Meat", "potion", 'm', 55, 1, 8));
		itemList.push_back(new Item("Bread", "potion", 'b',45, 3, 7));
		itemList.push_back(new Item("Rock", "weapon", 'r', 2, 13, 0));
	}
	else if (level >= 3) {
		itemList.push_back(new Item("Magic water", "potion", 'w', 100, 4, 7));
	}

	return itemList;
}

//create items for different levels with different pos
vector<Item*> Item::createKeyList(int level) {
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
	else if (level >= 3) {
		keys.push_back(new Item("Key", "unlock", 'K', 0, 10, 5));
		keys.push_back(new Item("Key", "unlock", 'K', 0, 9, 4));
		keys.push_back(new Item("Key", "unlock", 'K', 0, 7, 7));
	}

	return keys;
}

std::ostream& operator<<(std::ostream& out, const Item& item) {
	out << item.getName();
	return out;
}

