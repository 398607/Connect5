#ifndef GAME_H
#define GAME_H

#include <QtWidgets/QDialog>
#include <QPaintEvent>
#include <QSize>
#include <QMessageBox>
#include <QIcon>
#include <QHostInfo>
#include <QTextEdit>
#include <QRect>
#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalMapper>

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
#include "Countdown.h"

class Set_s: public QDialog {

    Q_OBJECT

public:
    Set_s(bool _host = true) {

        host = _host;

        this->setFixedSize(800, 400);
        QPushButton* ok = new QPushButton(this);
        ok->setGeometry(120, 350, 200, 50);
        ok->setText("confirm");
        connect(ok, &QPushButton::clicked, this, &Set_s::confirm);

        QPushButton* cancel = new QPushButton(this);
        cancel->setGeometry(500, 350, 200, 50);
        cancel->setText("cancel");
        connect(cancel, &QPushButton::clicked, this, &Set_s::close);

        QString localHostName = QHostInfo::localHostName();
        QHostInfo info = QHostInfo::fromName(localHostName);
        bool flag = false;
        foreach(QHostAddress address, info.addresses()) {
            if(address.protocol() == QAbstractSocket::IPv4Protocol) {
                ip = address.toString();
                flag = true;
                break;
            }
        }
        if (!flag)
            ip = "127.0.0.1";

        text = new QLineEdit(this);
        text->setGeometry(50, 10, 700, 50);
        if (host) {
            text->setReadOnly(true);
            text->setText(ip);
        }

        if (!host) {

            // keyboard
            QSignalMapper* m = new QSignalMapper(this);
        
            for (int i = 0; i <= 9; i++) {
                QPushButton *b = new QPushButton(QString::number(i), this);
                if (i <= 4)
                    b->setGeometry((i + 1) * 120, 80, 100, 80);
                else 
                    b->setGeometry((i - 4) * 120, 170, 100, 80);
                b->setText(QString::number(i));
                b->show();
                connect(b, SIGNAL(clicked()), 
                        m, SLOT(map()));
                m->setMapping(b, i);

            }
            connect(m, SIGNAL(mapped(int)), this, SLOT(keyPressed(int)));

            // .
            QPushButton* b = new QPushButton(this);
            b->setGeometry(120, 260, 100, 80);
            b->setText(".");
            b->show();
            connect(b, &QPushButton::clicked, this, &Set_s::key_);
        }

    }

protected slots:
    void confirm() {
        if (host)
            emit(giveAdd(ip));
        else
            emit giveAdd(text->text());
        this->close();
    }
    void keyPressed(int i) {
        text->insert(QString::number(i));
    }
    void key_() {
        text->insert(".");
    }

signals:
    void giveAdd(const QString& str);

private:
    QLineEdit* text;
    bool host;
    QString ip;
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
                setWaitForMe(false);
            }
            else if (gameMode == GameMode::NETBATTLE && p != myPlayer) {
                setWaitForMe(true);
            }
        }
        else { // fail
            return;
        }

        repaint();

        if (gameMode == GameMode::NETBATTLE && p == myPlayer) { // me
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
    void undo() {
        if (gameMode == GameMode::LOCALMULTI) {
            map->undo();
            repaint();
        }
        else if (gameMode == GameMode::NETBATTLE) {
            sendUndoRequest();
        }
    }

    // file
    void saveMap() {
        map->save();
    }
    void loadMap() {
        if (gameMode == GameMode::LOCALMULTI) {
            map->clear();
            map->load(this);

            // find the correct "next" players
            userInteraction->setPlayer(CellMatrix::nextPlayer(Player(map->cellAt(map->last()))));

            QString pal = "White";
            if (map->cellAt(map->last()) == Cell::White)
                pal = "Black";
            currDisplay->setText(pal + "`s turn");
        }
    }

    // network

    void setWaitForMe(bool value) {
        waitForMe = value;
        if (value) {
            countDown->start();
        }
        else {
            countDown->pause();
        }
    }

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

    // client
    void askForAddC() {
        Set_s* set = new Set_s(false);
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
            setWaitForMe(true);
            currDisplay->setText("White`s turn");
        }
        else {
            setWaitForMe(false);
            currDisplay->setText("Black`s turn");
        }
    }
    void reviveWaitForMe() {
        userInteraction->setPlayer(CellMatrix::nextPlayer(Player(map->cellAt(map->last()))));
        if (myPlayer == userInteraction->currentPlayer)
            setWaitForMe(true);
    }
    void getMsgStr(const QString& str) {
        qDebug() << str;
        NetBattleMsg msg(str.toStdString());

        if (msg.type == NetBattleMsg::MsgType::MOVE) {
            if (waitForMe)
                return; // for safety?
            move(msg.player, msg.pos.x(), msg.pos.y());

            setWaitForMe(true);

        }
        else if (msg.type == NetBattleMsg::MsgType::BEGIN_GAME && isHost == false) { // client recieved begin request
            QMessageBox* box = new QMessageBox(QMessageBox::Icon::Information,
                                           "Connected!",
                                           "Game will immediately begin when both clicked 'Battle!' button.");
            box->show();
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
        else if (msg.type == NetBattleMsg::MsgType::LOAD_REQUEST) {
            QMessageBox::StandardButton choose = QMessageBox::question(NULL, 
                                                 "Quit Game Request", "Opponent intends to quit this game. Allow?", 
                                                 QMessageBox::Yes | QMessageBox::No, 
                                                 QMessageBox::No);
            if (choose == QMessageBox::Yes) {
                addDisplay->setText("");
                setWaitForMe(false);
                sendMsgType(NetBattleMsg::MsgType::LOAD_PERMISSION);
                useSocket->close();
                map->clear();
                repaint();
                if (isHost)
                    listenSocket->close();
            }
            else {
                sendMsgType(NetBattleMsg::MsgType::LOAD_DECLINE);
            }
        }
        else if (msg.type == NetBattleMsg::MsgType::LOAD_PERMISSION) {
            useSocket->close();
            if (isHost)
                listenSocket->close();
            addDisplay->setText("");
            map->clear();
            repaint();
            setWaitForMe(false);
            // quit
        }
        else if (msg.type == NetBattleMsg::MsgType::LOAD_DECLINE) {
            // nothing
        }
        else if (msg.type == NetBattleMsg::MsgType::UNDO_REQUEST) {
            QMessageBox::StandardButton choose = QMessageBox::question(NULL, 
                                                 "Undo Request", "Opponent intends to undo. Allow?", 
                                                 QMessageBox::Yes | QMessageBox::No, 
                                                 QMessageBox::No);
            if (choose == QMessageBox::Yes) {
                
                sendMsgType(NetBattleMsg::MsgType::UNDO_PERMISSION);
                map->undo();
                repaint();
            }
            else {
                sendMsgType(NetBattleMsg::MsgType::UNDO_DECLINE);
            }
        }
        else if (msg.type == NetBattleMsg::MsgType::UNDO_PERMISSION) {
            map->undo();
            repaint();
            // undo
        }
        else if (msg.type == NetBattleMsg::MsgType::UNDO_DECLINE) {
            // nothing
        }
    }
    void getMsg() {
        
        QString str;
        str = useSocket->readAll();
        getMsgStr(str);

    }
    void sendMsgType(const NetBattleMsg::MsgType& y) {
        QByteArray* arr = new QByteArray();
        arr->clear();
        arr->append(NetBattleMsg(y).toQString().c_str());
        useSocket->write(arr->data());
        delete arr;
    }
    void sendBeginRequest() {
        sendMsgType(NetBattleMsg::MsgType::BEGIN_GAME);
    }
    void sendQuitRequest() {
        sendMsgType(NetBattleMsg::MsgType::LOAD_REQUEST);
    }
    void sendUndoRequest() {
        sendMsgType(NetBattleMsg::MsgType::UNDO_REQUEST);
    }

protected:
    void paintEvent(QPaintEvent* e) {
        paintEngine->paint(this, *map, mapRect);
    }
    void initLM() {
        userInteraction = new LocalMultiUserInteraction(this, 1000 / map->len(), mapRect);
        myPlayer = Player::Black;
            
        setWaitForMe(true);

        currDisplay->setText("Black`s turn");

        QPushButton* load = new QPushButton(this);
        load->setGeometry(1300, 160, 200, 50);
        load->setText("Load game");
        connect(load, &QPushButton::clicked, this, &Game::loadMap);
    }
    void initNB() {
        userInteraction = new NetBattleUserInteraction(this, 1000 / map->len(), mapRect);
        QPushButton* btn_inits = new QPushButton(this);
        btn_inits->setGeometry(1080, 40, 200, 50);
        btn_inits->setText("Build Host");
        connect(btn_inits, &QPushButton::clicked, this, &Game::askForAddS);


        QPushButton* btn_initc = new QPushButton(this);
        btn_initc->setGeometry(1300, 40, 200, 50);
        btn_initc->setText("Connect Host");
        connect(btn_initc, &QPushButton::clicked, this, &Game::askForAddC);

        begin_btn = new QPushButton(this);
        begin_btn->setGeometry(1080, 100, 200, 50);
        begin_btn->setText("Battle!");
        begin_btn->setEnabled(false);
        connect(begin_btn, &QPushButton::clicked, this, &Game::beginBtnClicked);

        QPushButton* btn_quit = new QPushButton(this);
        btn_quit->setGeometry(1300, 220, 200, 50);
        btn_quit->setText("Quit Game");
        connect(btn_quit, &QPushButton::clicked, this, &Game::sendQuitRequest);

        addDisplay = new QTextEdit(this);
        addDisplay->setGeometry(1600, 40, 400, 50);
        addDisplay->setReadOnly(true);

        setWaitForMe(false);
        countDown = new Countdown(20);
    }
    void init() { // done first
        currDisplay = new QTextEdit(this);
        currDisplay->setGeometry(1600, 100, 400, 50);
        currDisplay->setReadOnly(true);
        currDisplay->setText("Game Isn`t On");

        QPushButton* save = new QPushButton(this);
        save->setGeometry(1080, 160, 200, 50);
        save->setText("Save game");
        connect(save, &QPushButton::clicked, this, &Game::saveMap);

        QPushButton* undo = new QPushButton(this);
        undo->setGeometry(1080, 220, 200, 50);
        undo->setText("Undo");
        connect(undo, &QPushButton::clicked, this, &Game::undo);

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
    Countdown* countDown;

    QString add;

    bool isHost;
    Player myPlayer;

    bool waitForMe;
    int beginRequestNum;
};

#endif // GAME_H
