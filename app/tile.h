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
    explicit Tile(QWidget *parent);

    ~Tile() override;

signals:

    void leftClicked(Tile *tile);

    void rightClicked(Tile *tile);

private:
    void mousePressEvent(QMouseEvent *event) override;

    void onLeftClicked();

    void onRightClicked();

    void blowUp();

    void reveal();

    void attachIcon(const QString &path);

    enum class MarkState {
        UNMARKED,
        FLAGGED,
        QUESTIONED
    };

    MarkState markState;
public:
    int getAdjacentMines() const;

    void setAdjacentMines(int adjacentMines);

    bool isMine() const;

    void setMine(bool mine);

    bool isRevealed() const;

    void setRevealed(bool revealed);

private:
    int adjacentMines; // [0, 8]
    bool mine;
    bool revealed;
};


#endif //QT_MINESWEEPER_TILE_H
