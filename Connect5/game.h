#ifndef GAMEE_H
#define GAMEE_H

#include <QtWidgets/QDialog>
#include <QPaintEvent>
#include <QSize>
#include <QMessageBox>
#include <QIcon>
#include <QTextEdit>
#include <QRect>
#include <QDebug>
#include <QPushButton>

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

#include "Map.h"
#include "MapPaintEngine.h"
#include "UserInteraction.h"
#include "LocalMultiUserInteraction.h"
#include "NetBattleUserInteraction.h"
#include "MouseObserver.h"
#include "NetBattleMsg.h"

class Set_s: public QDialog {
    Q_OBJECT
public:
    Set_s() {
        this->setFixedSize(400, 300);
        QPushButton* ok = new QPushButton(this);
        ok->setGeometry(100, 240, 200, 50);
        ok->setText("confirm");
        connect(ok, &QPushButton::clicked, this, &Set_s::confirm);

        text = new QTextEdit(this);
        text->setGeometry(50, 10, 300, 50);
    }
protected slots:
    void confirm() {
        emit giveAdd(text->toPlainText());
        this->close();
    }
signals:
    void giveAdd(const QString& str);
private:
    QTextEdit* text;
};

class Game : public QDialog
{
    Q_OBJECT

public:
    enum class GameMode {
        LOCALMULTI = 0,
        NETBATTLE
    };

    Game(const GameMode& _gameMode = GameMode::LOCALMULTI) {
        gameMode = _gameMode;
        windowSize = QSize(1920, 1080);
        mapRect = QRect(QPoint(40, 40), QSize(1000, 1000));

        this->setFixedSize(windowSize);

        map = new CellMatrix(15);
        // end-game checkment
        connect(map, &CellMatrix::endGame, this, &Game::endGame);

        // paint engine 
        paintEngine = new MapPaintEngine();

        // userInteraction(differ with gameMode)
        if (gameMode == GameMode::LOCALMULTI) {
            userInteraction = new LocalMultiUserInteraction(this, 1000 / map->len(), mapRect);
            myPlayer = Player::Black;
        }
        else if (gameMode == GameMode::NETBATTLE) {
            userInteraction = new NetBattleUserInteraction(this, 1000 / map->len(), mapRect);
            QPushButton* btn_inits = new QPushButton(this);
            btn_inits->setGeometry(1080, 40, 200, 50);
            btn_inits->setText("build Host");
            connect(btn_inits, &QPushButton::clicked, this, &Game::askForAddS);


            QPushButton* btn_initc = new QPushButton(this);
            btn_initc->setGeometry(1300, 40, 200, 50);
            btn_initc->setText("connect Host");
            connect(btn_initc, &QPushButton::clicked, this, &Game::askForAddC);

            waitForMe = false;
        }

        connect(userInteraction, &UserInteraction::move, this, &Game::move);
    }
    ~Game() {
        delete map;
        delete paintEngine;
        delete userInteraction;
    }
protected slots:
    void move(const Player& p, int x, int y) {
        // qDebug() << x << " " << y;

        if (gameMode == GameMode::NETBATTLE) {
            if (!waitForMe && p == myPlayer)
                return;
        }

        if (map->move(p, Pos(x, y))) { // successful
            if (gameMode == GameMode::LOCALMULTI) {
                userInteraction->setNextPlayer();
            }
            else if (gameMode == GameMode::NETBATTLE && p == myPlayer) {
                waitForMe = false;
            }
            else if (gameMode == GameMode::NETBATTLE && p != myPlayer) {
                waitForMe = true;
            }
        }
        else { // fail
            return;
        }

        repaint();

        if (gameMode == GameMode::NETBATTLE && p == myPlayer) {
            QByteArray* arr = new QByteArray();
            arr->clear();
            arr->append(NetBattleMsg(p, x, y).toQString().c_str());

            useSocket->write(arr->data());
            delete arr;
        }
    }
    void endGame(const Player& p) {
        QString winnerName = "black";
        if (p == Player::White)
            winnerName = "white";
        QMessageBox* m = new QMessageBox(QMessageBox::Icon::Warning, "Game Over!", "Player " + winnerName + " has won this game.");
        m->show();
    }
    // network
    void askForAddS() {
        Set_s* set = new Set_s();
        connect(set, &Set_s::giveAdd, this, &Game::initServer);
        set->show();
    }
    void askForAddC() {
        Set_s* set = new Set_s();
        connect(set, &Set_s::giveAdd, this, &Game::initClient);
        set->show();
    }
    void initServer(const QString& add = "127.0.0.1") {
        listenSocket = new QTcpServer();
        listenSocket->listen(QHostAddress(add), 8010);
        connect(listenSocket, &QTcpServer::newConnection, this, &Game::startConnect);
        isHost = true;
        userInteraction->setPlayer(myPlayer = Player::Black);
    }
    void initClient(const QString& add = "127.0.0.1") {
        useSocket = new QTcpSocket();
        useSocket->connectToHost(QHostAddress(add), 8010);
        connect(useSocket, &QTcpSocket::readyRead, this, &Game::getMsg);
        isHost = false;
        userInteraction->setPlayer(myPlayer = Player::White);
    }
    void startConnect() {
        qDebug() << "start connect!";
        useSocket = listenSocket->nextPendingConnection();
        connect(useSocket, &QTcpSocket::readyRead, this, &Game::getMsg);
        if (isHost) {
            waitForMe = true;
        }
        else {
            waitForMe = false;
        }
    }
    void getMsg() {
        if (waitForMe)
            return; // for safety?

        QString str;
        str = useSocket->readAll();
        NetBattleMsg msg(str.toStdString());

        if (msg.type == NetBattleMsg::MsgType::MOVE) {
            move(msg.player, msg.pos.x(), msg.pos.y());
            waitForMe = true;
        }
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

    UserInteraction* userInteraction;

    GameMode gameMode;

    // network settings
    
    // network
    QTcpServer* listenSocket;
    QTcpSocket* useSocket;
    bool isHost;
    Player myPlayer;
    bool waitForMe;
};

#endif // GAME_H
