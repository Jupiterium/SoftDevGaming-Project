#pragma once

#include <string>
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

public:
    // Constructor to create an item
    Item(string name = "Default", string type = "Default", char symbol = ' ', int boost = 0);

    // Getters   
    string getName() const;
    string getType() const;
    char getSymbol() const;
    int getBoostAmount() const;

    friend std::ostream& operator<< (std::ostream& out, const Item& item);
};
