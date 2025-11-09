#include "Item.h"
#include <iostream>

Item::Item(std::string name, string type, char symbol, int boost) {
	this->name = name;
	this->type = type;
	this->symbol = symbol;
	this->boostAmount = boost;
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

std::ostream& operator<<(std::ostream& out, const Item& item) {
	out << item.getName();
	return out;
}