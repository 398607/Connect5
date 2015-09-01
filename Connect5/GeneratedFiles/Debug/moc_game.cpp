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
    QByteArrayData data[5];
    char stringdata0[27];
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
QT_MOC_LITERAL(4, 19, 7) // "confirm"

    },
    "Set_s\0giveAdd\0\0str\0confirm"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Set_s[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   27,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
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
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
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
    QByteArrayData data[15];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Game_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Game_t qt_meta_stringdata_Game = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Game"
QT_MOC_LITERAL(1, 5, 4), // "move"
QT_MOC_LITERAL(2, 10, 0), // ""
QT_MOC_LITERAL(3, 11, 6), // "Player"
QT_MOC_LITERAL(4, 18, 1), // "p"
QT_MOC_LITERAL(5, 20, 1), // "x"
QT_MOC_LITERAL(6, 22, 1), // "y"
QT_MOC_LITERAL(7, 24, 7), // "endGame"
QT_MOC_LITERAL(8, 32, 10), // "askForAddS"
QT_MOC_LITERAL(9, 43, 10), // "askForAddC"
QT_MOC_LITERAL(10, 54, 10), // "initServer"
QT_MOC_LITERAL(11, 65, 3), // "add"
QT_MOC_LITERAL(12, 69, 10), // "initClient"
QT_MOC_LITERAL(13, 80, 12), // "startConnect"
QT_MOC_LITERAL(14, 93, 6) // "getMsg"

    },
    "Game\0move\0\0Player\0p\0x\0y\0endGame\0"
    "askForAddS\0askForAddC\0initServer\0add\0"
    "initClient\0startConnect\0getMsg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Game[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   64,    2, 0x09 /* Protected */,
       7,    1,   71,    2, 0x09 /* Protected */,
       8,    0,   74,    2, 0x09 /* Protected */,
       9,    0,   75,    2, 0x09 /* Protected */,
      10,    1,   76,    2, 0x09 /* Protected */,
      10,    0,   79,    2, 0x29 /* Protected | MethodCloned */,
      12,    1,   80,    2, 0x09 /* Protected */,
      12,    0,   83,    2, 0x29 /* Protected | MethodCloned */,
      13,    0,   84,    2, 0x09 /* Protected */,
      14,    0,   85,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
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
        case 0: _t->move((*reinterpret_cast< const Player(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->endGame((*reinterpret_cast< const Player(*)>(_a[1]))); break;
        case 2: _t->askForAddS(); break;
        case 3: _t->askForAddC(); break;
        case 4: _t->initServer((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->initServer(); break;
        case 6: _t->initClient((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->initClient(); break;
        case 8: _t->startConnect(); break;
        case 9: _t->getMsg(); break;
        default: ;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
