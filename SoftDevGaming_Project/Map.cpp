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

Map::Map(int _width, int _height) {
    this->width = _width;
    this->height = _height;
    vector<vector<Tile>> _temp(height, vector<Tile>(width));
    mapTile = _temp;

    GenerateBushLayout();
    GenerateTrees(6);
    GenerateWater(5);
}

bool Map::isWalkable(int x, int y) {
    if (x < this->width && x > 0) {
        if (y > 0 && y < this->height) {
            return true;
        }
    }
    std::cout << "Invalid location!\n";
    return false;
}


void Map::ReplaceTile(char new_char, int x, int y) {
    if (isWalkable(x, y)) {
        this->mapTile[y][x] = Tile(new_char);
    }
}


// Create natural rectangular areas bordered by bushes
void Map::GenerateBushLayout() {
    
    struct Rect { int x1, y1, x2, y2; };
    vector<Rect> bushRects = {
        {10, 2, 30, 10},   // rectangle 1
        {20, 15, 35, 20}, // rectangle 2
        {50, 5, 65, 15}  // rectangle 3
    };

    for (auto& r : bushRects) {
        for (int y = r.y1; y <= r.y2; ++y) {
            for (int x = r.x1; x <= r.x2; ++x) {
                mapTile[y][x] = Tile('#'); // fill entire rectangle
            }
        }
    }
}

// Create filled clusters of trees
void Map::GenerateTrees(int count) {
    for (int i = 0; i < count; ++i) {
        // Random top-left position for tree cluster
        int x1 = rand() % (width - 6) + 1;   // leave some margin
        int y1 = rand() % (height - 6) + 1;

        // Random size for tree cluster
        int clusterWidth = rand() % 4 + 2;  // width 2-5
        int clusterHeight = rand() % 3 + 2; // height 2-4

        int x2 = min(x1 + clusterWidth, width - 2);
        int y2 = min(y1 + clusterHeight, height - 2);

        for (int y = y1; y <= y2; ++y) {
            for (int x = x1; x <= x2; ++x) {
                if (mapTile[y][x].getChar() == ' ')
                    mapTile[y][x] = Tile('@'); // filled tree cluster
            }
        }
    }
}


// Create filled rectangular water lakes
void Map::GenerateWater(int count) {
    for (int i = 0; i < count; ++i) {
        // Random top-left position
        int x1 = rand() % (width - 10) + 1;   // leave some margin
        int y1 = rand() % (height - 6) + 1;

        // Random size for lake
        int lakeWidth = rand() % 6 + 3;  // width 3-8
        int lakeHeight = rand() % 4 + 2; // height 2-5

        int x2 = min(x1 + lakeWidth, width - 2);
        int y2 = min(y1 + lakeHeight, height - 2);

        for (int y = y1; y <= y2; ++y) {
            for (int x = x1; x <= x2; ++x) {
                if (isWalkable(x, y))
                    mapTile[y][x] = Tile('~'); // filled water
            }
        }
    }
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
        for (int x = 0; x < map.width; ++x)
        {
            char symbol = map.mapTile[y][x].getChar();

            switch (symbol) {
            case '#': out << GREEN << symbol << RESET; break;  // bushes
            case '@': out << BROWN << symbol << RESET; break;  // trees
            case '~': out << BLUE << symbol << RESET; break;   // water
            case 'P': out << CYAN << symbol << RESET; break;   // player (if added)
            default:  out << GREY << symbol; break;
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
