//
// Created by Ryan Hecht  on 2024-01-20.
//

#ifndef QT_MINESWEEPER_MAINWINDOW_H
#define QT_MINESWEEPER_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include "tile.h"
#include "gamelogichandler.h"

namespace Ui {

    class MainWindow;

} // Ui

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:

    void onLeftClicked(Tile *tile);

    void onRightClicked(Tile *tile);

private:
    QGridLayout *gridLayout;
    GameLogicHandler *gameLogicHandler;
//    Tile *tiles[30][16];
};

#endif //QT_MINESWEEPER_MAINWINDOW_H
