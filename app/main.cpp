#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    QCoreApplication::setApplicationName("Minesweeper");
    QCoreApplication::setApplicationVersion("1.0.0");

    MainWindow mainWindow;
    mainWindow.showNormal();

    return QApplication::exec();
}
