/**
 * @file mainwindow.h
 * @author Ryan Hecht
 * @date 2024-01-21
 * @brief Header file of the MainWindow responsible in the Minesweeper game.
 */

#ifndef QT_MINESWEEPER_MAINWINDOW_H
#define QT_MINESWEEPER_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include "tile.h"
#include "gamelogichandler.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    MainWindow(const MainWindow &) = delete;

    MainWindow &operator=(const MainWindow &) = delete;

    MainWindow(MainWindow &&) = delete;

    MainWindow &operator=(MainWindow &&) = delete;


signals:

    void restartGame();

private slots:

    void onGameOver(bool won);

private:
    QGridLayout *gridLayout;
    GameLogicHandler *gameLogicHandler;
};

#endif //QT_MINESWEEPER_MAINWINDOW_H
