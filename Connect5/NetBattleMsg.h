#ifndef NBMSG_H
#define NBMSG_H

#include <string>

#include <QString>
#include <QDebug>

#include "Map.h"

class NetBattleMsg {
public:
    enum class MsgType {
        NONE = 0,
        MOVE,
        BEGIN_GAME
    };
    // get a MOVE msg
    NetBattleMsg(const Player& p, int x, int y) {
        type = MsgType::MOVE;
        player = p;
        pos = Pos(x, y);
    }
    NetBattleMsg(const MsgType& t) {
        if (t == MsgType::BEGIN_GAME) {
            type = t;
        }
    }
    NetBattleMsg(const std::string& str) {
        if (str[0] == 'M') { // MOVE
            type = MsgType::MOVE;

            player = Player::Black;
            if (str[1] == 'W')
                player = Player::White;

            int x, y;
            x = atoi(str.substr(2, 2).c_str());
            y = atoi(str.substr(4, 2).c_str());
            qDebug() << x << " " << y;
            
            pos = Pos(x, y);
        }
        else if (str[0] == 'S') {
            type = MsgType::BEGIN_GAME;
        }
    }
    std::string toQString() {
        std::string str = "";
        if (type == MsgType::MOVE) {

            str += 'M';
            if (player == Player::Black)
                str += 'B';
            else if (player == Player::White)
                str += 'W';

            // ugly
            if (pos.x() < 10)
                str += '0';
            str += QString::number(pos.x()).toStdString();

            if (pos.y() < 10)
                str += '0';
            str += QString::number(pos.y()).toStdString();
        }
        else if (type == MsgType::BEGIN_GAME) {
            str += 'S';
        }
        // qDebug() << QString(str.c_str());
        return str;
    }
public:
    // move
    MsgType type;
    Player player;
    Pos pos;
};

#endif