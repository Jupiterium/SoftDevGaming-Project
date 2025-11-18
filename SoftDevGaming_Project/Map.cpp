#include "Map.h"
#include "Item.h"
#include <iostream>

// ANSI color codes
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define BROWN   "\033[33m"
#define GREY    "\033[90m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"

Map::Map(int _width, int _height) {
    this->width = _width;
    this->height = _height;
    vector<vector<Tile>> _temp(height, vector<Tile>(width));
    mapTile = _temp;

    GenerateHiddenGrid(); // fill the map initially
}

bool Map::isWalkable(int x, int y) {
    return (x >= 0 && x < width && y >= 0 && y < height);
}

void Map::ReplaceTile(char new_char, int x, int y) {
    if (isWalkable(x, y)) {
        mapTile[y][x] = Tile(new_char);
    }
}

// Fill map with hidden tiles (unexplored area)
void Map::GenerateHiddenGrid() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            mapTile[y][x] = Tile('.'); // unexplored tile
        }
    }
}

Tile& Map::getTile(int x, int y) {
    return mapTile[y][x];
}

ostream& operator<<(ostream& out, const Map& map) {
    // Top border
    out << '+';
    for (int x = 0; x < map.width; ++x)
        out << "-";
    out << "+\n";

    // Rows
    for (int y = 0; y < map.height; ++y) {
        out << '|';
        for (int x = 0; x < map.width; ++x) {
            char symbol = map.mapTile[y][x].getChar();

            switch (symbol) {
            case '.': out << GREY << symbol << RESET; break;   // hidden area (green)
            case 'P': out << CYAN << symbol << RESET; break;    // player
            case 'X': out << RED << symbol << RESET; break;    // Exit
            case 'T': out << BROWN << symbol << RESET; break;   // treasure
            case 'E': out << RED << symbol << RESET; break; // enemy (red)
            default:  out << BLUE << symbol << RESET; break;
            }
        }
        out << "|\n";
    }

    // Bottom border
    out << '+';
    for (int x = 0; x < map.width; ++x)
        out << "-";
    out << "+\n";

    return out;
}
