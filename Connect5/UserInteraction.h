#ifndef UIMOTHE_H
#define UIMOTHE_H

#include <QObject>
#include "Map.h"

class UserInteraction : public QObject {
    Q_OBJECT

public:
    void setPlayer(const Player& p) {
        currentPlayer = p;
    }
    void setNextPlayer() {
        currentPlayer = CellMatrix::nextPlayer(currentPlayer);
    }
    void setAccessible(bool value) {
        accessible = value;
    }
signals:
    void move(const Player& player, int x, int y);

public:
    Player currentPlayer;
    bool accessible;
};

#endif