#ifndef LMUI_H
#define LMUI_H

#include <QObject>
#include <QDebug>

#include "UserInteraction.h"
#include "MouseObserver.h"
#include "Map.h"

class LocalMultiUserInteraction : public UserInteraction {
    Q_OBJECT
public:
    LocalMultiUserInteraction(QWidget* parent, int _size, const QRect& rect) {
        currentPlayer = Player::Black;
        mouseObs = new MouseObserver(parent, _size, rect);
        mouseObs->show();
        connect(mouseObs, &MouseObserver::click, this, &LocalMultiUserInteraction::claimMove);
    }
    ~LocalMultiUserInteraction() {
        delete mouseObs;
    }
public slots:
    void claimMove(int x, int y) {
        // qDebug() << "!";
        emit move(currentPlayer, x, y);
        currentPlayer = CellMatrix::nextPlayer(currentPlayer);
    }
private:
    Player currentPlayer;
    MouseObserver* mouseObs;
};

#endif