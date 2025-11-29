#include "Map.h"
#include "Item.h"
#include <iostream>

//Constructor to initialize map dimensions and fill with hidden tiles '.'
Map::Map(int _width, int _height) 
{
    this->width = _width;
    this->height = _height;

	// Initialize 2D vector with empty tiles
    vector<vector<Tile>> _temp(height, vector<Tile>(width));
    mapTile = _temp;

    GenerateHiddenGrid(); // Fill the map initially
}

//Getters
int Map::getWidth() { return this->width; }
int Map::getHeight() { return this->height; }

// Check if coordinates are within map bounds
bool Map::isWalkable(int x, int y) { return (x >= 0 && x < width && y >= 0 && y < height); }

// Replace tile at (x,y) with new character if walkable
void Map::ReplaceTile(char new_char, int x, int y) 
{
    if (isWalkable(x, y)) 
    {
        mapTile[y][x] = Tile(new_char);
    }
}

// Fill map with default forest tiles '.'
void Map::GenerateHiddenGrid() 
{
    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            mapTile[y][x] = Tile('.');
        }
    }
}

// Getter for specific tile
Tile& Map::getTile(int x, int y) { return mapTile[y][x]; }

// Overloaded output operator to print the map with color coding
ostream& operator<<(ostream& out, const Map& map) 
{
    // Top border
    out << '+';
    for (int x = 0; x < map.width; ++x) out << "-";
    out << "+\n";

    // Rows
	// If tiles are different characters, print with different colors
    for (int y = 0; y < map.height; ++y) {
        out << '|';
        for (int x = 0; x < map.width; ++x) {
            char symbol = map.mapTile[y][x].getChar();

            switch (symbol) {
            case '.': out << GREY << symbol << RESET; break;  // Forest floor
            case 'P': out << CYAN << symbol << RESET; break;  // Player
            case 'X': out << BROWN << symbol << RESET; break; // Treasure
            case 'K': out << GREEN << symbol << RESET; break; // Key
            case 'E': out << RED << symbol << RESET; break;   // Enemy
			default:  out << BLUE << symbol << RESET; break;  // Other items
            }
        }
        out << "|\n";
    }

    // Bottom border
    out << '+';
    for (int x = 0; x < map.width; ++x) out << "-";
    out << "+\n";

    return out;
}