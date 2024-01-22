//
// Created by Ryan Hecht  on 2024-01-21.
//

#include <QDir>
#include "tile.h"

Tile::Tile(QWidget *parent) : QPushButton(parent) {
    setFixedSize(30, 40);
    attachIcon(":/assets/tile.png");
    markState = MarkState::UNMARKED;
    adjacentMines = 0;
    mine = false;
    revealed = false;
}

Tile::~Tile() = default;

void Tile::reveal(bool isGameOver) {
    bool steppedOnMine = false;

    if (isMine()) {
        if (isGameOver) {
            attachIcon(":/assets/bomb.png");
        } else {
            attachIcon(":/assets/bomb_explode.png");
            steppedOnMine = true;
        }
    } else {
        switch (adjacentMines) {
            case 0:
                attachIcon(":/assets/zero_tile.png");
                break;
            case 1:
                attachIcon(":/assets/one_tile.png");
                break;
            case 2:
                attachIcon(":/assets/two_tile.png");
                break;
            case 3:
                attachIcon(":/assets/three_tile.png");
                break;
            case 4:
                attachIcon(":/assets/four_tile.png");
                break;
            case 5:
                attachIcon(":/assets/five_tile.png");
                break;
            case 6:
                attachIcon(":/assets/six_tile.png");
                break;
            case 7:
                attachIcon(":/assets/seven_tile.png");
                break;
            case 8:
                attachIcon(":/assets/eight_tile.png");
                break;
            default:
                attachIcon(":/assets/tile.png");
                qDebug() << "Invalid adjacent mines value: " << adjacentMines;
                break;
        }
    }
    setDisabled(true);
    setRevealed(true);

    if (isGameOver) {
        return;
    }

    if (steppedOnMine) {
        emit tileRevealed(true);
    } else {
        emit tileRevealed(false);
    }

}

void Tile::reset() {
    markState = MarkState::UNMARKED;
    adjacentMines = 0;
    mine = false;
    revealed = false;
    setDisabled(false);
    attachIcon(":/assets/tile.png");
}

int Tile::getAdjacentMines() const {
    return adjacentMines;
}

void Tile::setAdjacentMines(int adjacentMines) {
    Tile::adjacentMines = adjacentMines;
}

bool Tile::isMine() const {
    return mine;
}

void Tile::setMine(bool mine) {
    Tile::mine = mine;
}

bool Tile::isRevealed() const {
    return revealed;
}

void Tile::setRevealed(bool revealed) {
    Tile::revealed = revealed;
}

void Tile::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        onRightClicked();
    } else {
        reveal(false);
    }
}

void Tile::onRightClicked() {
    // Update the state and change the icon
    if (markState == MarkState::UNMARKED) {
        markState = MarkState::FLAGGED;
        attachIcon(":/assets/mine_flag.png");
    } else if (markState == MarkState::FLAGGED) {
        markState = MarkState::QUESTIONED;
        attachIcon(":/assets/question_mark.png");
    } else if (markState == MarkState::QUESTIONED) {
        markState = MarkState::UNMARKED;
        attachIcon(":/assets/tile.png");
    }
}

void Tile::attachIcon(const QString &path) {
    QPixmap pixmap(path);
    if (!pixmap.isNull()) {
        setIcon(QIcon(pixmap));
        setIconSize(rect().size());
    } else {
        qDebug() << "Failed to load image: " << path;
        qDebug() << "Current directory: " << QDir::currentPath();
    }
}





