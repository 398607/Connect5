/****************************************************************************
** Meta object code from reading C++ file 'game.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../game.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Set_s_t {
    QByteArrayData data[8];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Set_s_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Set_s_t qt_meta_stringdata_Set_s = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Set_s"
QT_MOC_LITERAL(1, 6, 7), // "giveAdd"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 3), // "str"
QT_MOC_LITERAL(4, 19, 7), // "confirm"
QT_MOC_LITERAL(5, 27, 10), // "keyPressed"
QT_MOC_LITERAL(6, 38, 1), // "i"
QT_MOC_LITERAL(7, 40, 4) // "key_"

    },
    "Set_s\0giveAdd\0\0str\0confirm\0keyPressed\0"
    "i\0key_"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Set_s[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   37,    2, 0x09 /* Protected */,
       5,    1,   38,    2, 0x09 /* Protected */,
       7,    0,   41,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,

       0        // eod
};

void Set_s::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Set_s *_t = static_cast<Set_s *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->giveAdd((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->confirm(); break;
        case 2: _t->keyPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->key_(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Set_s::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Set_s::giveAdd)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Set_s::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Set_s.data,
      qt_meta_data_Set_s,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Set_s::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Set_s::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Set_s.stringdata0))
        return static_cast<void*>(const_cast< Set_s*>(this));
    return QDialog::qt_metacast(_clname);
}

int Set_s::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Set_s::giveAdd(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_Game_t {
    QByteArrayData data[37];
    char stringdata0[342];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Game_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Game_t qt_meta_stringdata_Game = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Game"
QT_MOC_LITERAL(1, 5, 7), // "confirm"
QT_MOC_LITERAL(2, 13, 0), // ""
QT_MOC_LITERAL(3, 14, 4), // "host"
QT_MOC_LITERAL(4, 19, 10), // "timeCostTo"
QT_MOC_LITERAL(5, 30, 1), // "t"
QT_MOC_LITERAL(6, 32, 4), // "move"
QT_MOC_LITERAL(7, 37, 6), // "Player"
QT_MOC_LITERAL(8, 44, 1), // "p"
QT_MOC_LITERAL(9, 46, 1), // "x"
QT_MOC_LITERAL(10, 48, 1), // "y"
QT_MOC_LITERAL(11, 50, 7), // "endGame"
QT_MOC_LITERAL(12, 58, 4), // "undo"
QT_MOC_LITERAL(13, 63, 7), // "saveMap"
QT_MOC_LITERAL(14, 71, 7), // "loadMap"
QT_MOC_LITERAL(15, 79, 12), // "setWaitForMe"
QT_MOC_LITERAL(16, 92, 5), // "value"
QT_MOC_LITERAL(17, 98, 12), // "sendNoneMove"
QT_MOC_LITERAL(18, 111, 13), // "setMyTimeCost"
QT_MOC_LITERAL(19, 125, 6), // "oneSec"
QT_MOC_LITERAL(20, 132, 10), // "askForAddS"
QT_MOC_LITERAL(21, 143, 10), // "initServer"
QT_MOC_LITERAL(22, 154, 4), // "_add"
QT_MOC_LITERAL(23, 159, 12), // "startConnect"
QT_MOC_LITERAL(24, 172, 10), // "askForAddC"
QT_MOC_LITERAL(25, 183, 10), // "initClient"
QT_MOC_LITERAL(26, 194, 15), // "beginBtnClicked"
QT_MOC_LITERAL(27, 210, 11), // "beginBattle"
QT_MOC_LITERAL(28, 222, 15), // "reviveWaitForMe"
QT_MOC_LITERAL(29, 238, 9), // "getMsgStr"
QT_MOC_LITERAL(30, 248, 3), // "str"
QT_MOC_LITERAL(31, 252, 6), // "getMsg"
QT_MOC_LITERAL(32, 259, 11), // "sendMsgType"
QT_MOC_LITERAL(33, 271, 21), // "NetBattleMsg::MsgType"
QT_MOC_LITERAL(34, 293, 16), // "sendBeginRequest"
QT_MOC_LITERAL(35, 310, 15), // "sendQuitRequest"
QT_MOC_LITERAL(36, 326, 15) // "sendUndoRequest"

    },
    "Game\0confirm\0\0host\0timeCostTo\0t\0move\0"
    "Player\0p\0x\0y\0endGame\0undo\0saveMap\0"
    "loadMap\0setWaitForMe\0value\0sendNoneMove\0"
    "setMyTimeCost\0oneSec\0askForAddS\0"
    "initServer\0_add\0startConnect\0askForAddC\0"
    "initClient\0beginBtnClicked\0beginBattle\0"
    "reviveWaitForMe\0getMsgStr\0str\0getMsg\0"
    "sendMsgType\0NetBattleMsg::MsgType\0"
    "sendBeginRequest\0sendQuitRequest\0"
    "sendUndoRequest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Game[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  149,    2, 0x06 /* Public */,
       4,    1,  152,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    3,  155,    2, 0x09 /* Protected */,
      11,    1,  162,    2, 0x09 /* Protected */,
      12,    0,  165,    2, 0x09 /* Protected */,
      13,    0,  166,    2, 0x09 /* Protected */,
      14,    0,  167,    2, 0x09 /* Protected */,
      15,    1,  168,    2, 0x09 /* Protected */,
      17,    0,  171,    2, 0x09 /* Protected */,
      18,    1,  172,    2, 0x09 /* Protected */,
      19,    0,  175,    2, 0x09 /* Protected */,
      20,    0,  176,    2, 0x09 /* Protected */,
      21,    1,  177,    2, 0x09 /* Protected */,
      21,    0,  180,    2, 0x29 /* Protected | MethodCloned */,
      23,    0,  181,    2, 0x09 /* Protected */,
      24,    0,  182,    2, 0x09 /* Protected */,
      25,    1,  183,    2, 0x09 /* Protected */,
      25,    0,  186,    2, 0x29 /* Protected | MethodCloned */,
      26,    0,  187,    2, 0x09 /* Protected */,
      27,    0,  188,    2, 0x09 /* Protected */,
      28,    0,  189,    2, 0x09 /* Protected */,
      29,    1,  190,    2, 0x09 /* Protected */,
      31,    0,  193,    2, 0x09 /* Protected */,
      32,    1,  194,    2, 0x09 /* Protected */,
      34,    0,  197,    2, 0x09 /* Protected */,
      35,    0,  198,    2, 0x09 /* Protected */,
      36,    0,  199,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int, QMetaType::Int,    8,    9,   10,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 33,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Game *_t = static_cast<Game *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->confirm((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->timeCostTo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->move((*reinterpret_cast< const Player(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->endGame((*reinterpret_cast< const Player(*)>(_a[1]))); break;
        case 4: _t->undo(); break;
        case 5: _t->saveMap(); break;
        case 6: _t->loadMap(); break;
        case 7: _t->setWaitForMe((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->sendNoneMove(); break;
        case 9: _t->setMyTimeCost((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->oneSec(); break;
        case 11: _t->askForAddS(); break;
        case 12: _t->initServer((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->initServer(); break;
        case 14: _t->startConnect(); break;
        case 15: _t->askForAddC(); break;
        case 16: _t->initClient((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: _t->initClient(); break;
        case 18: _t->beginBtnClicked(); break;
        case 19: _t->beginBattle(); break;
        case 20: _t->reviveWaitForMe(); break;
        case 21: _t->getMsgStr((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: _t->getMsg(); break;
        case 23: _t->sendMsgType((*reinterpret_cast< const NetBattleMsg::MsgType(*)>(_a[1]))); break;
        case 24: _t->sendBeginRequest(); break;
        case 25: _t->sendQuitRequest(); break;
        case 26: _t->sendUndoRequest(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Game::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Game::confirm)) {
                *result = 0;
            }
        }
        {
            typedef void (Game::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Game::timeCostTo)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject Game::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Game.data,
      qt_meta_data_Game,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Game::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Game.stringdata0))
        return static_cast<void*>(const_cast< Game*>(this));
    return QDialog::qt_metacast(_clname);
}

int Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 27)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void Game::confirm(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Game::timeCostTo(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
