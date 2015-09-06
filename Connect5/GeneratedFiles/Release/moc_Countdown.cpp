/****************************************************************************
** Meta object code from reading C++ file 'Countdown.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Countdown.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Countdown.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Countdown_t {
    QByteArrayData data[11];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Countdown_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Countdown_t qt_meta_stringdata_Countdown = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Countdown"
QT_MOC_LITERAL(1, 10, 11), // "timeChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 4), // "time"
QT_MOC_LITERAL(4, 28, 7), // "timeOut"
QT_MOC_LITERAL(5, 36, 12), // "oneSecSignal"
QT_MOC_LITERAL(6, 49, 6), // "oneSec"
QT_MOC_LITERAL(7, 56, 5), // "pause"
QT_MOC_LITERAL(8, 62, 4), // "stop"
QT_MOC_LITERAL(9, 67, 6), // "resume"
QT_MOC_LITERAL(10, 74, 5) // "start"

    },
    "Countdown\0timeChanged\0\0time\0timeOut\0"
    "oneSecSignal\0oneSec\0pause\0stop\0resume\0"
    "start"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Countdown[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,
       5,    0,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   59,    2, 0x0a /* Public */,
       7,    0,   60,    2, 0x0a /* Public */,
       8,    0,   61,    2, 0x0a /* Public */,
       9,    0,   62,    2, 0x0a /* Public */,
      10,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Countdown::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Countdown *_t = static_cast<Countdown *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->timeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->timeOut(); break;
        case 2: _t->oneSecSignal(); break;
        case 3: _t->oneSec(); break;
        case 4: _t->pause(); break;
        case 5: _t->stop(); break;
        case 6: _t->resume(); break;
        case 7: _t->start(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Countdown::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Countdown::timeChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (Countdown::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Countdown::timeOut)) {
                *result = 1;
            }
        }
        {
            typedef void (Countdown::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Countdown::oneSecSignal)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject Countdown::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Countdown.data,
      qt_meta_data_Countdown,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Countdown::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Countdown::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Countdown.stringdata0))
        return static_cast<void*>(const_cast< Countdown*>(this));
    return QObject::qt_metacast(_clname);
}

int Countdown::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Countdown::timeChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Countdown::timeOut()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Countdown::oneSecSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
