/**
 * @file mainwindow.cpp
 * @author Ryan Hecht
 * @date 2024-01-21
 * @brief Implementation of the MainWindow class. It manages the user interface,
 *        including the grid of tiles and interactions with the GameLogicHandler
 */

#include <iostream>
#include <QMessageBox>
#include <QApplication>
#include "mainwindow.h"
#include "constants.h"
#include "gamelogichandler.h"

/**
 * @brief Constructor for MainWindow.
 *
 * This constructor sets up the main window of the Minesweeper game, including the grid of tiles
 * and connections to handle game-over events.
 *
 * @param parent The parent widget of the MainWindow, typically the desktop.
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), gridLayout(new QGridLayout) {
    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(gridLayout);
    gridLayout->setSpacing(1);

    gameLogicHandler = new GameLogicHandler(centralWidget);
    connect(gameLogicHandler, &GameLogicHandler::gameOver, this, &MainWindow::onGameOver);
    connect(this, &MainWindow::restartGame, gameLogicHandler, &GameLogicHandler::restartGame);

    for (int i = 0; i < GRID_WIDTH; ++i) {
        for (int j = 0; j < GRID_HEIGHT; ++j) {
            Tile *tile = gameLogicHandler->getTile(i, j);
            gridLayout->addWidget(tile, j, i);
        }
    }
}

/**
 * @brief Destructor for MainWindow.
 *
 * Cleans up dynamically allocated resources owned by the MainWindow instance.
 */
MainWindow::~MainWindow() {
    delete gridLayout;
}

/**
 * @brief Handles the game-over event.
 *
 * Invoked when the GameLogicHandler emits the gameOver signal. This slot displays a message box
 * prompting the user to play again or quit the game.
 *
 * @param won Boolean flag indicating if the game was won (true) or lost (false).
 */
void MainWindow::onGameOver(bool won) {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Game Over");
    msgBox.setText(won ? "Congratulations! You won!" : "Boom! Game over.");
    msgBox.setInformativeText("Do you want to play again?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);

    int ret = msgBox.exec();

    switch (ret) {
        case QMessageBox::Yes:
            emit restartGame();
            break;
        case QMessageBox::No:
            QApplication::quit();
            break;
        default:
            // should never be reached
            qDebug() << "Invalid return value from QMessageBox::exec()";
            break;
    }
}
