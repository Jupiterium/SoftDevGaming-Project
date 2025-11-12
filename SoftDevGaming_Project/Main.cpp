
#include <iostream>
#include "Map.h"

int main()
{
    std::cout << "Game: The Maze Runner\n\n";
    int numRows = 10;
    int numCols = 20;

    Map map(numCols, numRows); //width x height
    Item i("Sword", "Weapon", 's', 30);

    map.ReplaceTile('P', 0, 0);
    map.ReplaceTile('X', 19, 9);

    std::cout << map;
    return 0;
}