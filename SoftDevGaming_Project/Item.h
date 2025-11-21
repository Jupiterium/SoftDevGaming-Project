#pragma once

#include <string>
#include <vector>
using namespace std;

/*
* Purpose of this class:
* A simple data class to hold item information.
*/

class Item
{
private:
    
    string name;
    string type;
    char symbol;
    int boostAmount;
    int x, y;

public:
    // Constructor to create an item
    Item(string name = "Default", string type = "Default", char symbol = ' ', int boost = 0, int x = 0, int y = 0);

    // Getters   
    string getName() const;
    string getType() const;
    char getSymbol() const;
    int getBoostAmount() const;
    int getX() const;
    int getY() const;

    static vector<Item*> createItemList();
    //TODO: create a vector list of predefined keys in the scene for each level
    //Like a ItemFactory similar to EnemyFactory
    static vector<Item*> createKeyList();

    friend std::ostream& operator<< (std::ostream& out, const Item& item);
};

//Specific type of items
struct Block {
    int x, y;
    char symbol = 'B';
};

struct Switch {
    int x, y;
    char symbol = 'S';
    bool activated = false;
};

