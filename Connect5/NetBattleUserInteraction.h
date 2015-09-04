#ifndef NBUI_H
#define NBUI_H

#include <QObject>
#include <QDebug>

#include "UserInteraction.h"
#include "MouseObserver.h"
#include "Map.h"

class NetBattleUserInteraction : public UserInteraction {
    Q_OBJECT
public:
    NetBattleUserInteraction(QWidget* parent, int _size, const QRect& rect) {
        currentPlayer = Player::Black;
        mouseObs = new MouseObserver(parent, _size, rect);
        mouseObs->show();
        connect(mouseObs, &MouseObserver::click, this, &NetBattleUserInteraction::claimMove);
    }
    ~NetBattleUserInteraction() {
        delete mouseObs;
    }
public slots:
    void claimMove(int x, int y) {
        // qDebug() << "!";
        emit move(currentPlayer, x, y, false);
    }
private:
    MouseObserver* mouseObs;
};

#endif