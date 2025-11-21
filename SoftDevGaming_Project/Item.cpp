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
vector<Item*> Item::createItemList() {
	vector<Item*> itemList;
	itemList.push_back(new Item("Sword", "weapon", 's', 30, 5, 7));
	itemList.push_back(new Item("Meat", "potion", 'm', 20, 2, 8));

	return itemList;
}

//create items for different levels with different pos
vector<Item*> Item::createKeyList() {
	vector<Item*> keys;
	keys.push_back(new Item("Key", "unlock", 'K', 0, 8, 5));
	keys.push_back(new Item("Key", "unlock", 'K', 0, 2, 4));
	return keys;
}

std::ostream& operator<<(std::ostream& out, const Item& item) {
	out << item.getName();
	return out;
}

