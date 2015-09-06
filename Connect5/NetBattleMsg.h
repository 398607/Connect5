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
        BEGIN_LOADED_GAME,
        LOADING_END,

        LOAD_REQUEST,
        LOAD_PERMISSION,
        LOAD_DECLINE,

        UNDO_REQUEST, 
        UNDO_PERMISSION,
        UNDO_DECLINE,

        SL_REQUEST,
        SL_PERMISSION,
        SL_DECLINE,
        SL_END
    };
    // get a MOVE msg
    NetBattleMsg(const Player& p, int x, int y, int t) {
        type = MsgType::MOVE;
        player = p;
        pos = Pos(x, y);
        time = t;
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
            if (str[1] == 'N')
                player = Player::None;

            int x, y;
            x = atoi(str.substr(2, 2).c_str());
            y = atoi(str.substr(4, 2).c_str());
            // qDebug() << x << " " << y;
            time = atoi(str.substr(6, 100).c_str());
            
            pos = Pos(x, y);
        }
        else if (str[0] == 'B') {
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
        else if (str[0] == 'S') {
            if (str[1] == 'R')
                type = MsgType::SL_REQUEST;
            else if (str[1] == 'P')
                type = MsgType::SL_PERMISSION;
            else if (str[1] == 'D')
                type = MsgType::SL_DECLINE;
            else if (str[1] == 'E')
                type = MsgType::SL_END;
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
            else if (player == Player::None)
                str += 'N';

            // ugly
            if (pos.x() < 10)
                str += '0';
            str += QString::number(pos.x()).toStdString();

            if (pos.y() < 10)
                str += '0';
            str += QString::number(pos.y()).toStdString();

            str += QString::number(time).toStdString();
        }
        else if (type == MsgType::BEGIN_GAME) {
            str += 'B';
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
        else if (type == MsgType::SL_REQUEST) {
            str += "SR";
        }
        else if (type == MsgType::SL_PERMISSION) {
            str += "SP";
        }
        else if (type == MsgType::SL_DECLINE) {
            str+= "SD";
        }
        else if (type == MsgType::SL_END) {
            str += "SE";
        }
        // qDebug() << QString(str.c_str());

        return str;
    }
public:
    // move
    MsgType type;
    Player player;
    Pos pos;
    int time;
};

#endif