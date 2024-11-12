#include "Map.h"
#include "Game.h"
#include <fstream>
#include <string>

Map::Map() {}
Map::~Map() {}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
    std::fstream mapFile;
    mapFile.open(path);

    if (!mapFile.is_open()) {
        std::cout << "Failed to open map file: " << path << std::endl;
        return;
    }

    char c;
    std::string number;
    int x = 0, y = 0;

    while (mapFile.get(c) && y < sizeY) {
        // Skip commas and newlines
        if (c == ',' || c == '\n') {
            continue;
        }

        // Convert the number and calculate source coordinates
        int tileNum = c - '0';  // Convert char to int

        // Only process valid digits
        if (tileNum >= 0 && tileNum <= 9) {
            int srcX = tileNum * 32;  // Each tile is 32 pixels wide
            int srcY = 0;             // All tiles are in the first row

            // Create tile for all numbers including 0
            Game::AddTile(srcX, srcY, x * 64, y * 64);

            // Move to next position
            x++;
            if (x >= sizeX) {
                x = 0;
                y++;
            }
        }
    }

    mapFile.close();
}