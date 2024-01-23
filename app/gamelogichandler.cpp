/**
 * @file gamelogichandler.cpp
 * @author Ryan Hecht
 * @date 2024-01-21
 * @brief Implementation of the GameLogicHandler class, which manages the game's state, including
 *        initializing the game board, handling game restarts, and revealing tiles.
 */

#include "gamelogichandler.h"

/**
 * @function GameLogicHandler
 * @brief Constructor for GameLogicHandler.
 *
 * Initializes the game grid and connects the tile revealed signal to the appropriate slot.
 * Calls initializeGame() to set up the board.
 *
 * @param parent The parent widget, which is passed to each tile.
 */
GameLogicHandler::GameLogicHandler(QWidget *parent) {
    // Perform onetime initialization of tiles
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            tiles[x][y] = new Tile(parent);
            connect(tiles[x][y], &Tile::tileRevealed, this, &GameLogicHandler::onTileRevealed);
        }
    }

    initializeGame();
}

/**
 * @function ~GameLogicHandler
 * @brief Destructor for GameLogicHandler.
 *
 * Cleans up resources when the GameLogicHandler instance is destroyed.
 */
GameLogicHandler::~GameLogicHandler() {
    // Delete all tiles
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            delete tiles[x][y];
        }
    }
};

/**
 * @function getTile
 * @brief Gets the tile at the specified location.
 *
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @return The tile at the specified location.
 */
Tile *GameLogicHandler::getTile(int x, int y) {
    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        return tiles[x][y];
    } else {
        qDebug() << "Invalid tile location: (" << x << ", " << y << ")";
        return nullptr;
    }
}

/**
 * @function restartGame
 * @brief Restarts the game.
 *
 * Resets all tiles and reinitializes the game board.
 */
void GameLogicHandler::restartGame() {
    // Reset all tiles
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            tiles[x][y]->reset();
        }
    }

    initializeGame();
}

/**
 * @function initializeGame
 * @brief Initializes the game state.
 *
 * Sets the initial state of the game, including the number of non-bomb tiles and resetting the revealed tiles counter.
 * Also calls methods to place mines and calculate adjacent mines.
 */
void GameLogicHandler::initializeGame() {
    totalNonBombTiles = GRID_WIDTH * GRID_HEIGHT - NUMBER_OF_MINES;
    revealedNonBombTiles = 0;

    initializeBombLocations();
    calculateAdjacentMines();
}

/**
 * @function initializeBombLocations
 * @brief Initializes bomb locations randomly on the grid.
 *
 * This function randomly places mines on the game grid until the number of mines specified by
 * NUMBER_OF_MINES is reached. It ensures that each tile can only have one mine.
 */
void GameLogicHandler::initializeBombLocations() {
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

/**
 * @function calculateAdjacentMines
 * @brief Calculates the number of adjacent mines for each tile.
 *
 * Iterates over each tile on the grid and counts the number of adjacent mines. This count is then
 * set on the tile for game logic and display purposes.
 */
void GameLogicHandler::calculateAdjacentMines() {
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

/**
 * @function onTileRevealed
 * @brief Slot to handle when a tile is revealed.
 *
 * When a tile is revealed, this function checks if the tile is a mine. If so, it reveals all tiles
 * and emits a gameOver signal with a loss. If not, it increments the count of revealed non-bomb tiles
 * and checks if the player has won.
 *
 * @param steppedOnMine Indicates whether the revealed tile was a mine.
 */
void GameLogicHandler::onTileRevealed(bool steppedOnMine) {
    if (steppedOnMine) {
        // Player stepped on a mine, reveal all tiles and end game as loss
        for (int x = 0; x < GRID_WIDTH; x++) {
            for (int y = 0; y < GRID_HEIGHT; y++) {
                if (!tiles[x][y]->isRevealed()) {
                    tiles[x][y]->reveal(true);
                }
            }
        }

        emit gameOver(false); // Emit loss
    } else {
        revealedNonBombTiles++; // Increment the count of safe revealed tiles

        // Check if the player has won by revealing all non-bomb tiles
        if (revealedNonBombTiles == totalNonBombTiles) {
            emit gameOver(true); // Emit win
        }
    }
}
