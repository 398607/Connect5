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
        
        init();

        // userInteraction(differ with gameMode)
        if (gameMode == GameMode::LOCALMULTI) {
            initLM();
        }
        else if (gameMode == GameMode::NETBATTLE) {
            initNB();
        }

        // now userInteraction shall be init-ed
        connect(userInteraction, &UserInteraction::move, this, &Game::move);
    }
    ~Game() { }

signals:
    void confirm(bool host);

protected slots:
    // basic
    void move(const Player& p, int x, int y) {
        // qDebug() << x << " " << y;

        if (gameMode == GameMode::NETBATTLE) {
            if (!waitForMe && p == myPlayer)
                return;
        }

        if (map->move(p, Pos(x, y))) { // successful


            QString pal = "White";
            if (map->cellAt(map->last()) == Cell::White)
                pal = "Black";

            currDisplay->setText(pal + "`s turn");

            if (gameMode == GameMode::LOCALMULTI) {
                userInteraction->setNextPlayer();
                myPlayer = CellMatrix::nextPlayer(myPlayer);
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

    // file
    void saveMap() {
        map->save();
    }
    void loadMap() {
        map->load(this);
    }

    // network

    // host
    void askForAddS() {
        Set_s* set = new Set_s();
        connect(set, &Set_s::giveAdd, this, &Game::initServer);
        set->show();
    }
    void initServer(const QString& _add = "127.0.0.1") {
        add = _add;
        listenSocket = new QTcpServer();
        listenSocket->listen(QHostAddress(add), 8010);
        connect(listenSocket, &QTcpServer::newConnection, this, &Game::startConnect);

        addDisplay->setText(add + " waiting");

        isHost = true;
        userInteraction->setPlayer(myPlayer = Player::Black);
    }
    void startConnect() {
        // qDebug() << "start connect!";
        useSocket = listenSocket->nextPendingConnection();
        connect(useSocket, &QTcpSocket::readyRead, this, &Game::getMsg);
        addDisplay->setText(add + " connected");

        // send begin to client and wait both to confirm

        QMessageBox* box = new QMessageBox(QMessageBox::Icon::Information,
                                           "Connected!",
                                           "Game will immediately begin when both clicked 'Battle!' button.");
        box->show();

        beginRequestNum = 0;

        begin_btn->setEnabled(true);

        sendBeginRequest();
    }
    void sendBeginRequest() {
        QByteArray* arr = new QByteArray();
        arr->clear();
        arr->append(NetBattleMsg(NetBattleMsg::MsgType::BEGIN_GAME).toQString().c_str());
        useSocket->write(arr->data());
        delete arr;
    }

    // client
    void askForAddC() {
        Set_s* set = new Set_s();
        connect(set, &Set_s::giveAdd, this, &Game::initClient);
        set->show();
    }
    void initClient(const QString& _add = "127.0.0.1") {
        add = _add;
        useSocket = new QTcpSocket();
        useSocket->connectToHost(QHostAddress(add), 8010);
        connect(useSocket, &QTcpSocket::readyRead, this, &Game::getMsg);

        addDisplay->setText(add + " connected");

        isHost = false;
        userInteraction->setPlayer(myPlayer = Player::White);
    }
    
    // both
    void beginBtnClicked() {
        begin_btn->setEnabled(false);
        beginRequestNum++;

        if (!isHost) {
            sendBeginRequest();
        }

        if (beginRequestNum == 2) {
            QMessageBox* box = new QMessageBox(QMessageBox::Icon::Information, "Battle Begin!", "Host uses black, and move first.");
            box->show();
            beginBattle();
        }
    }
    void beginBattle() {
        qDebug() << "begin!";

        // wait for both to confirm

        if (isHost) {
            waitForMe = true;
            currDisplay->setText("White`s turn");
        }
        else {
            waitForMe = false;
            currDisplay->setText("Black`s turn");
        }
    }
    void getMsg() {
        
        QString str;
        str = useSocket->readAll();
        NetBattleMsg msg(str.toStdString());

        qDebug() << str;

        if (msg.type == NetBattleMsg::MsgType::MOVE) {
            if (waitForMe)
                return; // for safety?
            move(msg.player, msg.pos.x(), msg.pos.y());
            waitForMe = true;
        }
        else if (msg.type == NetBattleMsg::MsgType::BEGIN_GAME && isHost == false) { // client recieved begin request
            begin_btn->setEnabled(true);
        }
        else if (msg.type == NetBattleMsg::MsgType::BEGIN_GAME && isHost == true) { // client recieved begin request
            beginRequestNum++;
            if (beginRequestNum == 2) {
                QMessageBox* box = new QMessageBox(QMessageBox::Icon::Information, "Battle Begin!", "Host uses black, and move first.");
                box->show();
                beginBattle();
            }
        }
    }

protected:
    void paintEvent(QPaintEvent* e) {
        paintEngine->paint(this, *map, mapRect);
    }
    void initLM() {
        userInteraction = new LocalMultiUserInteraction(this, 1000 / map->len(), mapRect);
        myPlayer = Player::Black;
            
        waitForMe = true;

        currDisplay->setText("Black`s turn");
    }
    void initNB() {
        userInteraction = new NetBattleUserInteraction(this, 1000 / map->len(), mapRect);
        QPushButton* btn_inits = new QPushButton(this);
        btn_inits->setGeometry(1080, 40, 200, 50);
        btn_inits->setText("build Host");
        connect(btn_inits, &QPushButton::clicked, this, &Game::askForAddS);


        QPushButton* btn_initc = new QPushButton(this);
        btn_initc->setGeometry(1300, 40, 200, 50);
        btn_initc->setText("connect Host");
        connect(btn_initc, &QPushButton::clicked, this, &Game::askForAddC);

        begin_btn = new QPushButton(this);
        begin_btn->setGeometry(1080, 100, 200, 50);
        begin_btn->setText("Battle!");
        begin_btn->setEnabled(false);
        connect(begin_btn, &QPushButton::clicked, this, &Game::beginBtnClicked);

        addDisplay = new QTextEdit(this);
        addDisplay->setGeometry(1600, 40, 400, 50);
        addDisplay->setReadOnly(true);

        waitForMe = false;
    }
    void init() { // done first
        currDisplay = new QTextEdit(this);
        currDisplay->setGeometry(1080, 990, 400, 50);
        currDisplay->setReadOnly(true);
        currDisplay->setText("Game Isn`t On");

        QPushButton* save = new QPushButton(this);
        save->setGeometry(1500, 990, 200, 50);
        save->setText("Save game");
        connect(save, &QPushButton::clicked, this, &Game::saveMap);

        QPushButton* load = new QPushButton(this);
        load->setGeometry(1720, 990, 200, 50);
        load->setText("Load game");
        connect(load, &QPushButton::clicked, this, &Game::loadMap);

    }

private:
    QSize windowSize;
    QRect mapRect;

    // module
    CellMatrix* map;
    MapPaintEngine* paintEngine;
    UserInteraction* userInteraction;

    // commmon-ui
    QTextEdit* currDisplay;

    // game mode 
    GameMode gameMode;

    // network
    QTcpServer* listenSocket;
    QTcpSocket* useSocket;

    QTextEdit* addDisplay;
    QPushButton* begin_btn;

    QString add;
    bool isHost;
    Player myPlayer;
    bool waitForMe;
    int beginRequestNum;
};

#endif // GAME_H
