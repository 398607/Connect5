#ifndef GAME_H
#define GAME_H

#include <QtWidgets/QDialog>
#include <QLCDNumber>
#include <QFrame>
#include <QPaintEvent>
#include <QSize>
#include <QMessageBox>
#include <QSound>
#include <QIcon>
#include <QHostInfo>
#include <QTextEdit>
#include <QLabel>
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
    void timeCostTo(int t);

protected slots:
    // basic
    void move(const Player& p, int x, int y) {
        // qDebug() << x << " " << y;

        if (gameMode == GameMode::NETBATTLE) {
            if (loading) {
                qDebug() << "loading";
                map->move(p, Pos(x, y));
                return;
            }
            if (before)
                return;
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
            arr->append(NetBattleMsg(p, x, y, myTimeCost).toQString().c_str());

            useSocket->write(arr->data());
            useSocket->flush();
            delete arr;
        }
    }
    void endGame(const Player& p) {
        QString winnerName = "black";
        if (p == Player::White)
            winnerName = "white";

        if (gameMode == GameMode::LOCALMULTI) {
            QMessageBox* m = new QMessageBox(QMessageBox::Icon::Warning, "Game Over!", "Player " + winnerName + " has won this game.");
            m->show();
        }
        else if (gameMode == GameMode::NETBATTLE) {
            setWaitForMe(false);

            QDialog* m = new QDialog();
            m->setWindowTitle("Game End!");
            m->setFixedSize(800, 600);

            QLabel * label = new QLabel(m);
            QString str("");
            str += "Player " + winnerName + " has won this game!\n\n";
            str += "Your time cost: " + QString::number(myTimeCost) + "\n\n";
            str += "Opponent`s time cost: " + QString::number(oppoTimeCost) + "\n\n";
            label->setText(str);

            QString music;
            if (p == myPlayer)
                music = QString(":/Connect5/Resources/win.wav");
            else 
                music = QString(":/Connect5/Resources/lose.wav");

            QSound* p = new QSound(music, m);
            p->play();

            connect(m, &QDialog::rejected, p, &QSound::stop);

            m->show();

        }
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
        else if (gameMode == GameMode::NETBATTLE) {
            sendMsgType(NetBattleMsg::MsgType::SL_REQUEST);
        }

    }

    // network

    void setWaitForMe(bool value) {
        waitForMe = value;
        if (gameMode == GameMode::NETBATTLE) {
            if (value) {
                countDown->start();
            }
            else {
                countDown->stop();
            }
        }
    }
    void sendNoneMove() {
        QByteArray* arr = new QByteArray();
        arr->clear();
        arr->append(NetBattleMsg(Player::None, 0, 0, myTimeCost).toQString().c_str());

        useSocket->write(arr->data());
        delete arr;
        setWaitForMe(false);
    }
    void setMyTimeCost(int t) {
        myTimeCost = t;
        emit timeCostTo(t);
    }
    void oneSec() {
        if (map->checkWin())
            setWaitForMe(false);
        setMyTimeCost(myTimeCost + 1);
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
        // listenSocket->close();
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
            before = false;
        }

        if (beginRequestNum == 2) {
            QMessageBox* box = new QMessageBox(QMessageBox::Icon::Information, "Battle Begin!", "Host uses black, and move first.");
            box->show();
            before = false;
            beginBattle();
        }
    }
    void beginBattle() {
        // qDebug() << "begin!";

        // wait for both to confirm
        before = false;

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
            oppoTimeCost = msg.time;
            if (!loading)
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
                setMyTimeCost(0);
                before = true;
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
            setMyTimeCost(0);
            before = true;
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
        else if (msg.type == NetBattleMsg::MsgType::SL_REQUEST) {
            QMessageBox::StandardButton choose = QMessageBox::question(NULL, 
                                                 "Load Request", "Opponent intends to load a map. Allow?", 
                                                 QMessageBox::Yes | QMessageBox::No, 
                                                 QMessageBox::No);
            if (choose == QMessageBox::Yes) {
                sendMsgType(NetBattleMsg::MsgType::SL_PERMISSION);
                map->clear();
                loading = true;
            }
            else {
                sendMsgType(NetBattleMsg::MsgType::SL_DECLINE);
            }
        }
        else if (msg.type == NetBattleMsg::MsgType::SL_PERMISSION) {
            // load

            map->load();
            repaint();
            setWaitForMe(false);
            // send the map

            for (int i = 0; i < map->len(); i++)
                for (int j = 0; j < map->len(); j++)
                    if (map->cellAt(Pos(i, j)) != Cell::Empty && !(Pos(i, j) == map->last())) {
                        QByteArray* arr = new QByteArray();
                        arr->clear();
                        arr->append(NetBattleMsg(Player(map->cellAt(Pos(i, j))), i, j, myTimeCost).toQString().c_str());

                        useSocket->write(arr->data());
                        useSocket->flush();
                        delete arr;
                    }

            QByteArray* arr = new QByteArray();
            arr->clear();
            arr->append(NetBattleMsg(Player(map->cellAt(map->last())), map->last().x(), map->last().y(), myTimeCost).toQString().c_str());

            useSocket->write(arr->data());
            useSocket->flush();
            delete arr;

            // set color
            myPlayer = CellMatrix::nextPlayer(Player(map->cellAt(map->last())));
            userInteraction->setPlayer(myPlayer);

            setWaitForMe(true);
            sendMsgType(NetBattleMsg::MsgType::SL_END);
        }
        else if (msg.type == NetBattleMsg::MsgType::SL_DECLINE) {
        }
        else if (msg.type == NetBattleMsg::MsgType::SL_END) {

            loading = false;
            myPlayer = Player(map->cellAt(map->last()));
            userInteraction->setPlayer(myPlayer);
            setWaitForMe(false);
            repaint();
            loading = false;
        }
    }
    void getMsg() {
        
        QString str;
        str = useSocket->readAll();

        std::string s = str.toStdString();
        // getMsgStr(str);

        while (s.length() > 0) {
            unsigned p = s.substr(1, 1000).find_first_of("MS");
            if (p != std::string::npos) {
                std::string cur = s.substr(0, p + 1);
                // qDebug() << cur.c_str();
                getMsgStr(QString(cur.c_str()));
                s = s.substr(p + 1, 10000);
            }
            else {
                // qDebug() << s.c_str();
                getMsgStr(QString(s.c_str()));
                s = "";
            }
        }

    }
    void sendMsgType(const NetBattleMsg::MsgType& y) {
        if (useSocket == nullptr || !(useSocket->state() == QAbstractSocket::ConnectedState))
            return;
        QByteArray* arr = new QByteArray();
        arr->clear();
        arr->append(NetBattleMsg(y).toQString().c_str());
        useSocket->write(arr->data());
        useSocket->flush();
        delete arr;
    }
    void sendBeginRequest() {
        sendMsgType(NetBattleMsg::MsgType::BEGIN_GAME);
    }
    void sendQuitRequest() {
        if (useSocket == nullptr || !(useSocket->state() == QAbstractSocket::ConnectedState))
            return;
        sendMsgType(NetBattleMsg::MsgType::LOAD_REQUEST);
    }
    void sendUndoRequest() {
        if (useSocket == nullptr || !(useSocket->state() == QAbstractSocket::ConnectedState))
            return;
        if (!waitForMe)
            return;
        sendMsgType(NetBattleMsg::MsgType::UNDO_REQUEST);
    }

protected:
    void closeEvent(QCloseEvent* e) {
        if (gameMode == GameMode::LOCALMULTI)
            e->accept();
        else if (gameMode == GameMode::NETBATTLE) {
            if (useSocket == nullptr || !(useSocket->state() == QAbstractSocket::ConnectedState))
                e->accept();
            else {
                sendQuitRequest();
                e->ignore();
            }
        }
    }
    void paintEvent(QPaintEvent* e) {
        paintEngine->paint(this, *map, mapRect);
    }
    void initLM() {
        userInteraction = new LocalMultiUserInteraction(this, 1000 / map->len(), mapRect);
        myPlayer = Player::Black;
            
        setWaitForMe(true);

        currDisplay->setText("Black`s turn");

       
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
        begin_btn->setGeometry(1080, 150, 200, 50);
        begin_btn->setText("Battle!");
        begin_btn->setEnabled(false);
        connect(begin_btn, &QPushButton::clicked, this, &Game::beginBtnClicked);

        QPushButton* btn_quit = new QPushButton(this);
        btn_quit->setGeometry(1300, 370, 200, 50);
        btn_quit->setText("Quit Game");
        connect(btn_quit, &QPushButton::clicked, this, &Game::sendQuitRequest);

        addDisplay = new QTextEdit(this);
        addDisplay->setGeometry(1600, 40, 400, 50);
        addDisplay->setReadOnly(true);

        countDown = new Countdown(20);
        connect(countDown, &Countdown::timeOut, this, &Game::sendNoneMove);
        connect(countDown, &Countdown::oneSecSignal, this, &Game::oneSec);

        QLabel* numL = new QLabel(this);
        numL->setGeometry(1600, 210, 400, 50);
        numL->setText("Current Move Countdown:");

        QLCDNumber* num = new QLCDNumber(2, this);
        num->setGeometry(1600, 260, 400, 50);
        connect(countDown, SIGNAL(timeChanged(int)), num, SLOT(display(int)));

        QLabel* numL2 = new QLabel(this);
        numL2->setGeometry(1600, 320, 400, 50);
        numL2->setText("Total Time Cost:");
        
        QLCDNumber* num2 = new QLCDNumber(4, this);
        num2->setGeometry(1600, 370, 400, 50);
        connect(this, SIGNAL(timeCostTo(int)), num2, SLOT(display(int)));

        useSocket = nullptr;

        loading = false;

        setWaitForMe(false);
        waitForMe = false;
        before = true;

        setMyTimeCost(0);

    }
    void init() { // done first

        QLabel* labelL = new QLabel(this);
        labelL->setGeometry(1600, 100, 400, 50);
        labelL->setText("Game Status:");
        
        currDisplay = new QTextEdit(this);
        currDisplay->setGeometry(1600, 150, 400, 50);
        currDisplay->setReadOnly(true);
        currDisplay->setText("Game Isn`t On");

        QPushButton* save = new QPushButton(this);
        save->setGeometry(1080, 260, 200, 50);
        save->setText("Save game");
        connect(save, &QPushButton::clicked, this, &Game::saveMap);

        QPushButton* load = new QPushButton(this);
        load->setGeometry(1300, 260, 200, 50);
        load->setText("Load game");
        connect(load, &QPushButton::clicked, this, &Game::loadMap);

        QPushButton* undo = new QPushButton(this);
        undo->setGeometry(1080, 370, 200, 50);
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
    int myTimeCost;
    int oppoTimeCost;

    bool waitForMe;
    bool loading;
    int beginRequestNum;

    bool before;
};

#endif // GAME_H
