/**
 * @file gamelogichandler.h
 * @author Ryan Hecht
 * @date 2024-01-21
 * @brief Defines the GameLogicHandler class that manages the state and logic of the Minesweeper game.
 *
 * GameLogicHandler is a responsible for initializing the game grid with tiles, setting up mines,
 * calculating adjacent mines for each tile, and determining the game's end conditions. It provides
 * the functionality to restart the game and to handle tile reveal actions, emitting signals when
 * the game is over due to a win or a loss.
 */

#ifndef QT_MINESWEEPER_GAMELOGICHANDLER_H
#define QT_MINESWEEPER_GAMELOGICHANDLER_H

#include <QObject>
#include "constants.h"
#include "tile.h"

class GameLogicHandler : public QObject {
Q_OBJECT

public:

    explicit GameLogicHandler(QWidget *parent);

    ~GameLogicHandler() override;

    GameLogicHandler(const GameLogicHandler &) = delete;

    GameLogicHandler &operator=(const GameLogicHandler &) = delete;

    GameLogicHandler(GameLogicHandler &&) = delete;

    GameLogicHandler &operator=(GameLogicHandler &&) = delete;

    Tile *getTile(int x, int y);

signals:

    void gameOver(bool won);

public slots:

    void restartGame();

private:

    void initializeGame();

    void initializeBombLocations();

    void calculateAdjacentMines();

    void deleteAllTiles();

    Tile *tiles[GRID_WIDTH][GRID_HEIGHT];
    int revealedNonBombTiles;
    int totalNonBombTiles;

private slots:

    void onTileRevealed(bool steppedOnMine);

};

#endif //QT_MINESWEEPER_GAMELOGICHANDLER_H

