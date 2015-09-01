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
signals:
    void move(const Player& player, int x, int y);

public:
    Player currentPlayer;
};

#endif