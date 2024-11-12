#include "Map.h"
#include "Game.h"
#include <fstream>
#include <string>
#include "ECS/Components.h"

extern Manager manager;

Map::Map(const char* mfp, int ms, int ts) : mapFilePath(mfp), mapScale(ms), tileSize(ts) {
    scaledSize = ms * ts;
}

Map::~Map() { }

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
    std::fstream mapFile;
    mapFile.open(path);
    if (!mapFile.is_open()) {
        std::cout << "Failed to open map file: " << path << std::endl;
        return;
    }

    // Load Layer 0 (Tiles)
    int x = 0, y = 0;
    std::string number;
    char c;
    std::string line;
    bool isLayer0 = false;

    // Find layer 0
    while (std::getline(mapFile, line)) {
        if (line == "layer 0") {
            isLayer0 = true;
            break;
        }
    }

    if (!isLayer0) {
        std::cout << "Layer 0 not found in map file" << std::endl;
        mapFile.close();
        return;
    }

    // Process layer 0 tiles
    while (mapFile.get(c) && y < sizeY) {
        // Stop if we hit the next layer
        if (c == 'l' && mapFile.peek() == 'a') {
            break;
        }

        // Skip commas and newlines
        if (c == ',' || c == '\n') {
            continue;
        }

        // If it's a digit, process it
        if (isdigit(c)) {
            number = c;
            // Look ahead for second digit
            c = mapFile.peek();
            if (isdigit(c)) {
                mapFile.get(c);
                number += c;
            }
            int tileNumber = std::stoi(number);
            int srcY = (tileNumber / 10) * tileSize;  // First digit
            int srcX = (tileNumber % 10) * tileSize;  // Second digit
            AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
            x++;
            if (x >= sizeX) {
                x = 0;
                y++;
            }
        }
    }

    // Reset file position to beginning for layer 1
    mapFile.clear();
    mapFile.seekg(0);

    // Find layer 1
    bool isLayer1 = false;
    while (std::getline(mapFile, line)) {
        if (line == "layer 1") {
            isLayer1 = true;
            break;
        }
    }

    if (!isLayer1) {
        std::cout << "Layer 1 not found in map file" << std::endl;
        mapFile.close();
        return;
    }

    // Reset position counters for layer 1
    x = 0;
    y = 0;

    // Process layer 1 for colliders
    while (mapFile.get(c) && y < sizeY) {
        // Stop if we hit the next layer
        if (c == 'l' && mapFile.peek() == 'a') {
            break;
        }

        // Skip commas, newlines, and minus signs
        if (c == ',' || c == '\n' || c == '-') {
            continue;
        }

        // If it's a digit, process it
        if (isdigit(c)) {
            number = c;
            // Look ahead for second digit
            c = mapFile.peek();
            if (isdigit(c)) {
                mapFile.get(c);
                number += c;
            }

            // Add collider only if the tile value is 24
            if (number == "24") {
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tcol.addGroup(Game::groupColliders);
            }
            x++;
            if (x >= sizeX) {
                x = 0;
                y++;
            }
        }
    }

    mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilePath);
    tile.addGroup(Game::groupMap);
}