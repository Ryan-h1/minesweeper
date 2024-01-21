//
// Created by Ryan Hecht  on 2024-01-21.
//

#include "gamelogichandler.h"

GameLogicHandler::GameLogicHandler(QWidget *parent) {
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            tiles[x][y] = new Tile(parent);
        }
    }

    InitializeBombLocations();
    CalculateAdjacentMines();
}

GameLogicHandler::~GameLogicHandler() = default;

Tile *GameLogicHandler::getTile(int x, int y) {
    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        return tiles[x][y];
    } else {
        qDebug() << "Invalid tile location: (" << x << ", " << y << ")";
        return nullptr;
    }
}


void GameLogicHandler::InitializeBombLocations() {
    std::srand(std::time(0)); // Seeding the random number generator with the time
    int placedMines = 0;

    while (placedMines < NUMBER_OF_MINES) {
        int x = std::rand() % GRID_WIDTH;
        int y = std::rand() % GRID_HEIGHT;

        // Check if there's already a mine at this location
        if (!tiles[x][y]->isMine()) {
            tiles[x][y]->setMine(true);
            placedMines++;
        }
    }
}

void GameLogicHandler::CalculateAdjacentMines() {
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            // Skip this tile if it is a mine
            if (tiles[x][y]->isMine()) continue;

            int mineCount = 0;

            // Check all adjacent tiles
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int nx = x + i;
                    int ny = y + j;

                    // Check if the adjacent tile is within the grid bounds
                    if (nx >= 0 && nx < GRID_WIDTH && ny >= 0 && ny < GRID_HEIGHT) {
                        // Increment count if the adjacent tile is a mine
                        if (tiles[nx][ny]->isMine()) {
                            mineCount++;
                        }
                    }
                }
            }

            // Set the count of adjacent mines
            tiles[x][y]->setAdjacentMines(mineCount);
        }
    }
}
