//
// Created by Ryan Hecht  on 2024-01-21.
//

#include <QDir>
#include "tile.h"

Tile::Tile(QWidget *parent) : QPushButton(parent) {
    this->setFixedSize(30, 40);

    QPixmap pixmap(":/assets/bomb.png");
    if (!pixmap.isNull()) {
        setIcon(QIcon(pixmap));
        setIconSize(this->rect().size());
    } else {
        qDebug() << "Failed to load image at 'assets/bomb.png'.";
        qDebug() << "Current directory:" << QDir::currentPath();
        qDebug() << "Full path attempted:" << QDir::current().absoluteFilePath("assets/bomb.png");
    }

    adjacentMines = 0;
    isMine = false;
    isRevealed = false;
}

Tile::~Tile() = default;

void Tile::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Handle left click
        emit leftClicked(this);
    } else if (event->button() == Qt::RightButton) {
        // Handle right click
        emit rightClicked(this);
    } else {
        // Call the base class implementation for other types of clicks
        QPushButton::mousePressEvent(event);
    }
}

