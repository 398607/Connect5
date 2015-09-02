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
        BEGIN_GAME,

        LOAD_REQUEST,
        LOAD_PERMISSION,
        LOAD_DECLINE,

        UNDO_REQUEST, 
        UNDO_PERMISSION,
        UNDO_DECLINE
    };
    // get a MOVE msg
    NetBattleMsg(const Player& p, int x, int y) {
        type = MsgType::MOVE;
        player = p;
        pos = Pos(x, y);
    }
    // a msg only contains a type name
    NetBattleMsg(const MsgType& t) {
        type = t;
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
        // ugly
        else if (str[0] == 'L') {
            if (str[1] == 'R')
                type = MsgType::LOAD_REQUEST;
            else if (str[1] == 'P')
                type = MsgType::LOAD_PERMISSION;
            else if (str[1] == 'D')
                type = MsgType::LOAD_DECLINE;
        }
        else if (str[0] == 'U') {
            if (str[1] == 'R')
                type = MsgType::UNDO_REQUEST;
            else if (str[1] == 'P')
                type = MsgType::UNDO_PERMISSION;
            else if (str[1] == 'D')
                type = MsgType::UNDO_DECLINE;
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
        else if (type == MsgType::LOAD_REQUEST) {
            str += "LR";
        }
        else if (type == MsgType::LOAD_PERMISSION) {
            str += "LP";
        }
        else if (type == MsgType::LOAD_DECLINE) {
            str+= "LD";
        }
        else if (type == MsgType::UNDO_REQUEST) {
            str += "UR";
        }
        else if (type == MsgType::UNDO_PERMISSION) {
            str += "UP";
        }
        else if (type == MsgType::UNDO_DECLINE) {
            str+= "UD";
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