/**
 * @file tile.h
 * @author Ryan Hecht
 * @date 2024-01-21
 * @brief Defines the Tile class that represents a single tile in the Minesweeper game.
 *
 * Tile is a QPushButton that represents a single tile in the Minesweeper game.
 */
#ifndef QT_MINESWEEPER_TILE_H
#define QT_MINESWEEPER_TILE_H


#include <QPushButton>
#include <QMouseEvent>

class Tile : public QPushButton {
Q_OBJECT

public:
    explicit Tile(QWidget *parent);

    ~Tile() override;

    void reveal(bool gameOver);

    void reset();

    int getAdjacentMines() const;

    void setAdjacentMines(int adjacentMines);

    bool isMine() const;

    void setMine(bool mine);

    bool isRevealed() const;

    void setRevealed(bool revealed);

signals:

    void tileRevealed(bool steppedOnMine);

private:
    void mousePressEvent(QMouseEvent *event) override;

    void updateMarkState();

    void attachIcon(const QString &path);

    enum class MarkState {
        UNMARKED,
        FLAGGED,
        QUESTIONED
    };

    MarkState markState;
    int adjacentMines; // [0, 8]
    bool mine;
    bool revealed;
};


#endif //QT_MINESWEEPER_TILE_H
