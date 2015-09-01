#ifndef UIMOTHER_H
#define UIMOTHER_H

#include <QObject>
#include "Map.h"

class UserInteraction : public QObject {
    Q_OBJECT

signals:
    void move(const Player& player, int x, int y);
};

#endif