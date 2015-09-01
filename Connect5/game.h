#ifndef GAME_H
#define GAME_H

#include <QtWidgets/QDialog>
#include <QPaintEvent>
#include <QSize>
#include <QMessageBox>
#include <QIcon>
#include <QRect>
#include <QDebug>

#include "Map.h"
#include "MapPaintEngine.h"
#include "UserInteraction.h"
#include "LocalMultiUserInteraction.h"
#include "MouseObserver.h"

class Game : public QDialog
{
    Q_OBJECT

public:
    Game() {
        windowSize = QSize(1920, 1080);
        mapRect = QRect(QPoint(40, 40), QSize(1000, 1000));

        this->setFixedSize(windowSize);

        map = new CellMatrix(15);
        connect(map, &CellMatrix::endGame, this, &Game::endGame);

        paintEngine = new MapPaintEngine();

        userInteraction = new LocalMultiUserInteraction(this, 1000 / map->len(), mapRect);
        connect(userInteraction, &UserInteraction::move, this, &Game::move);
        /*
        mouseObserver = new MouseObserver(this, 1000 / map->len(), mapRect);
        mouseObserver->show();
        connect(mouseObserver, &MouseObserver::click, this, &Game::click);
        */
        // map->move(Player::White, Pos(0, 0));
        // map->move(Player::Black, Pos(0, 1));
    }
    ~Game() {
        delete map;
        delete paintEngine;
    }
protected slots:
    void click(int x, int y) {
        qDebug() << x << " " << y;
    }
    void move(const Player& p, int x, int y) {
        qDebug() << x << " " << y;
        map->move(p, Pos(x, y));
        repaint();
    }
    void endGame(const Player& p) {
        QString winnerName = "black";
        if (p == Player::White)
            winnerName = "white";
        QMessageBox* m = new QMessageBox(QMessageBox::Icon::Warning, "Game Over!", "Player " + winnerName + " has won this game.");
        m->show();
    }
protected:
    void paintEvent(QPaintEvent* e) {
        paintEngine->paint(this, *map, mapRect);
    }
private:
    QSize windowSize;
    QRect mapRect;

    CellMatrix* map;
    MapPaintEngine* paintEngine;
    MouseObserver* mouseObserver;

    UserInteraction* userInteraction;
};

#endif // GAME_H
