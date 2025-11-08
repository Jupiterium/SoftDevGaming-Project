#pragma once

/*
* Purpose of this class:
* A simple data class to hold item information.
*/

class Item
{
private:
    string name;
    string type;
    int boostAmount;

public:
    // Constructor to create an item
    Item(string n, string type, int b);

    // Getters
    string getName() const;
    string getType() const;
    int getBoostAmount() const;
};
