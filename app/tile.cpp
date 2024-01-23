/**
 * @file tile.cpp
 * @author Ryan Hecht
 * @date 2024-01-21
 * @brief Implementation of the Tile class, which represents a single tile in the Minesweeper game.
 */

#include <QDir>
#include "tile.h"

/**
 * @function Tile
 * @brief Constructs a Tile object.
 *
 * Sets the tile's size and attaches the default tile icon.
 *
 * @param parent The QWidget parent of this tile, usually the game board.
 */
Tile::Tile(QWidget *parent) : QPushButton(parent) {
    setFixedSize(30, 40);
    attachIcon(":/assets/tile.png");
    markState = MarkState::UNMARKED;
    adjacentMines = 0;
    mine = false;
    revealed = false;
}

/**
 * @function ~Tile
 * @brief Destructor for the Tile object.
 *
 * Since Tile objects do not own any dynamically allocated resources, this destructor is empty.
 */
Tile::~Tile() = default;

/**
 * @function reveal
 * @brief Reveals the tile's state.
 *
 * If the tile is a mine, the tile is disabled and the mine icon is attached. If the tile is not a mine, the tile is
 * disabled and the appropriate icon is attached based on the number of adjacent mines. When the game is over, some
 * additional logic is performed to ensure that the correct bomb icons (unexploded) are attached and that this method
 * does not emit anymore events.
 *
 * @param isGameOver Indicates if the game is over.
 */
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

/**
 * @function reset
 * @brief Resets the tile's state.
 *
 * Resets the tile's state to the default state, as if the tile was just created.
 */
void Tile::reset() {
    markState = MarkState::UNMARKED;
    adjacentMines = 0;
    mine = false;
    revealed = false;
    setDisabled(false);
    attachIcon(":/assets/tile.png");
}

/**
 * @function getAdjacentMines
 * @brief Returns the number of adjacent mines.
 *
 * @return The number of adjacent mines.
 */
int Tile::getAdjacentMines() const {
    return adjacentMines;
}

/**
 * @function setAdjacentMines
 * @brief Sets the number of adjacent mines.
 *
 * @param adjacentMines The number of adjacent mines.
 */
void Tile::setAdjacentMines(int adjacentMines) {
    Tile::adjacentMines = adjacentMines;
}

/**
 * @function isMine
 * @brief Returns true if the tile is a mine.
 *
 * @return True if the tile is a mine, false otherwise.
 */
bool Tile::isMine() const {
    return mine;
}

/**
 * @function setMine
 * @brief Sets the mine flag.
 *
 * @param mine Boolean flag indicating if the tile is a mine.
 */
void Tile::setMine(bool mine) {
    Tile::mine = mine;
}

/**
 * @function isRevealed
 * @brief Returns true if the tile is revealed.
 *
 * @return True if the tile is revealed, false otherwise.
 */
bool Tile::isRevealed() const {
    return revealed;
}

/**
 * @function setRevealed
 * @brief Sets the revealed flag.
 *
 * @param revealed Boolean flag indicating if the tile is revealed.
 */
void Tile::setRevealed(bool revealed) {
    Tile::revealed = revealed;
}

/**
 * @function mousePressEvent
 * @brief Handles the mouse press event.
 *
 * If the right mouse button is pressed, the tile's mark state is updated. If the left mouse button is pressed, the
 * tile is revealed.
 *
 * @param event The QMouseEvent object containing details about the mouse event.
 */
void Tile::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        updateMarkState();
    } else {
        reveal(false);
    }
}

/**
 * @function updateMarkState
 * @brief Updates the tile's mark state.
 *
 * Updates the tile's mark state and attaches the appropriate icon.
 */
void Tile::updateMarkState() {
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

/**
 * @function attachIcon
 * @brief Attaches an icon to the tile.
 *
 * @param path The file path to the icon image.
 */
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





