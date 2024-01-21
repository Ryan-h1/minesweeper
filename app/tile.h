//
// Created by Ryan Hecht  on 2024-01-21.
//

#ifndef QT_MINESWEEPER_TILE_H
#define QT_MINESWEEPER_TILE_H


#include <QPushButton>
#include <QMouseEvent>

class Tile : public QPushButton {
Q_OBJECT

public:
    explicit Tile(QWidget *parent = nullptr);

    ~Tile() override;

signals:

    void leftClicked(Tile *tile);

    void rightClicked(Tile *tile);

private:
    void mousePressEvent(QMouseEvent *event) override;

    enum class MarkState {
        UNMARKED,
        FLAGGED,
        QUESTIONED
    };

    int adjacentMines;
    bool isMine;
    bool isRevealed;
};


#endif //QT_MINESWEEPER_TILE_H
