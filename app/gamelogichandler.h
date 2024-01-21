//
// Created by Ryan Hecht  on 2024-01-21.
//

#ifndef QT_MINESWEEPER_GAMELOGICHANDLER_H
#define QT_MINESWEEPER_GAMELOGICHANDLER_H


#include "constants.h"
#include "tile.h"

class GameLogicHandler {

public:
    explicit GameLogicHandler(QWidget *parent);

    ~GameLogicHandler();

    Tile *getTile(int x, int y);

private:
    void InitializeBombLocations();

    void CalculateAdjacentMines();

    Tile *tiles[GRID_WIDTH][GRID_HEIGHT];
};


#endif //QT_MINESWEEPER_GAMELOGICHANDLER_H
