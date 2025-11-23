#include "Map.h"
#include "Item.h"
#include <iostream>

Map::Map(int _width, int _height) {
    this->width = _width;
    this->height = _height;
    vector<vector<Tile>> _temp(height, vector<Tile>(width));
    mapTile = _temp;

    GenerateHiddenGrid(); // fill the map initially
}

//Getters
int Map::getWidth() { return this->width; }
int Map::getHeight() { return this->height; }

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
            case '.': out << GREY << symbol << RESET; break; // hidden area (green)
            case 'P': out << CYAN << symbol << RESET; break; // player
            case 'X': out << RED << symbol << RESET; break; // Treasure
            case 'K': out << GREEN << symbol << RESET; break; // Key
            case 'E': out << BROWN << symbol << RESET; break; // enemy (red)
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
