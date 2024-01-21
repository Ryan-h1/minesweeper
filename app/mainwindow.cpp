//
// Created by Ryan Hecht  on 2024-01-20.
//

#include "mainwindow.h"
#include "constants.h"
#include "gamelogichandler.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), gridLayout(new QGridLayout) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(gridLayout);
    gridLayout->setSpacing(1);

    gameLogicHandler = new GameLogicHandler(centralWidget);

    for (int i = 0; i < GRID_WIDTH; ++i) {
        for (int j = 0; j < GRID_HEIGHT; ++j) {
            Tile *tile = gameLogicHandler->getTile(i, j);
            gridLayout->addWidget(tile, j, i);
            connect(tile, &Tile::leftClicked, this, &MainWindow::onLeftClicked);
            connect(tile, &Tile::rightClicked, this, &MainWindow::onRightClicked);
        }
    }
}

MainWindow::~MainWindow() {
    delete gridLayout;
    delete gameLogicHandler;
}

void MainWindow::onLeftClicked(Tile *tile) {
    // Handle left click for the tile
    std::cout << "Tile left clicked" << std::endl;
}

void MainWindow::onRightClicked(Tile *tile) {
    // Handle right click for the tile
    std::cout << "Tile right clicked" << std::endl;
}

