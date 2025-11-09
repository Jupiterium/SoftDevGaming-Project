
#include <iostream>
#include "Map.h"

int main()
{
    int numRows = 25;
    int numCols = 70;

    Map map(numCols, numRows); //width x height
    Item i("Sword", "Weapon", 's', 30);

    map.ReplaceTile('P', 2, 3);
    map.ReplaceTile(i.getSymbol(), 25, 12);

    std::cout << map;
    return 0;
}