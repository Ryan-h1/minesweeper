/**
 * @file main.cpp
 * @author Ryan Hecht
 * @date 2024-01-21
 * @brief Entry point of the Minesweeper game.
 */

#include <QApplication>
#include "mainwindow.h"

/**
 * @function main
 * @brief Entry point of the Minesweeper game.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return The exit code of the application.
 */
int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    QCoreApplication::setApplicationName("Minesweeper");
    QCoreApplication::setApplicationVersion("1.0.0");

    MainWindow mainWindow;
    mainWindow.showNormal();

    return QApplication::exec();
}
