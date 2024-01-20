//
// Created by Ryan Hecht  on 2024-01-20.
//

#ifndef QT_MINESWEEPER_MAINWINDOW_H
#define QT_MINESWEEPER_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {

    class MainWindow;

} // Ui

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:

    void handleButton();

private:
    QPushButton *m_button;
};

#endif //QT_MINESWEEPER_MAINWINDOW_H
