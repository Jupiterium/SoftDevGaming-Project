#pragma once

#include <string>
#include <vector>
using namespace std;

/*
* Purpose of this class:
* An item that can be picked up and used by the player.
* Items can be weapons (increase attack), potions (restore health),
* or keys (unlock progression). Items have a type, name, symbol, boost value,
* and position on the map.
*/

class Item
{
private:
    
    string name;
    string type;
    char symbol;
    int boostAmount; //Value applied when used (damage or healing)
	int x, y; // Position on the map

public:
    // Construct an Item with optional default values.
    Item(string name = "Default", string type = "Default", char symbol = ' ', int boost = 0, int x = 0, int y = 0);

    // Getters   
    string getName() const;
    string getType() const;
    char getSymbol() const;
    int getBoostAmount() const;
    int getX() const;
    int getY() const;

    //Create a list of items appropriate for a given level.
    static vector<Item*> createItemList(int level);

    //Create a list of keys (unlock items) for a given level.
    static vector<Item*> createKeyList(int level);

    friend std::ostream& operator<< (std::ostream& out, const Item& item);
};

