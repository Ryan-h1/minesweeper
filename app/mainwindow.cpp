//
// Created by Ryan Hecht  on 2024-01-20.
//

#include "mainwindow.h"
#include "constants.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), gridLayout(new QGridLayout) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(gridLayout);
    gridLayout->setSpacing(1);

    for (int i = 0; i < GRID_WIDTH; ++i) {
        for (int j = 0; j < GRID_HEIGHT; ++j) {
            tiles[i][j] = new Tile(centralWidget);
            gridLayout->addWidget(tiles[i][j], j, i);
            connect(tiles[i][j], &Tile::leftClicked, this, &MainWindow::onLeftClicked);
            connect(tiles[i][j], &Tile::rightClicked, this, &MainWindow::onRightClicked);
        }
    }

//    // Connect button signal to appropriate slot
//    connect(testButton, &QPushButton::released, this, &MainWindow::handleButton);
}

MainWindow::~MainWindow() {
    // Ensure proper deletion of tiles
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 16; ++j) {
            delete tiles[i][j];
        }
    }
    delete gridLayout;
}

void MainWindow::onLeftClicked(Tile *tile) {
    // Handle left click for the tile
    std::cout << "Tile left clicked" << std::endl;
}

void MainWindow::onRightClicked(Tile *tile) {
    // Handle right click for the tile
    std::cout << "Tile right clicked" << std::endl;
}

