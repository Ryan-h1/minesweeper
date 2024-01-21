#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    MainWindow mainWindow;
    mainWindow.showNormal();

    return QApplication::exec();
}
