/****************************************************************************
** Meta object code from reading C++ file 'Map.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Map.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Map.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CellMatrix_t {
    QByteArrayData data[10];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CellMatrix_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CellMatrix_t qt_meta_stringdata_CellMatrix = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CellMatrix"
QT_MOC_LITERAL(1, 11, 7), // "endGame"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 6), // "Player"
QT_MOC_LITERAL(4, 27, 1), // "p"
QT_MOC_LITERAL(5, 29, 4), // "undo"
QT_MOC_LITERAL(6, 34, 4), // "save"
QT_MOC_LITERAL(7, 39, 4), // "load"
QT_MOC_LITERAL(8, 44, 8), // "QWidget*"
QT_MOC_LITERAL(9, 53, 6) // "parent"

    },
    "CellMatrix\0endGame\0\0Player\0p\0undo\0"
    "save\0load\0QWidget*\0parent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CellMatrix[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,
       7,    1,   44,    2, 0x0a /* Public */,
       7,    0,   47,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, 0x80000000 | 8,    9,
    QMetaType::Bool,

       0        // eod
};

void CellMatrix::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CellMatrix *_t = static_cast<CellMatrix *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->endGame((*reinterpret_cast< const Player(*)>(_a[1]))); break;
        case 1: _t->undo(); break;
        case 2: _t->save(); break;
        case 3: { bool _r = _t->load((*reinterpret_cast< QWidget*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->load();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CellMatrix::*_t)(const Player & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CellMatrix::endGame)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject CellMatrix::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CellMatrix.data,
      qt_meta_data_CellMatrix,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CellMatrix::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CellMatrix::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CellMatrix.stringdata0))
        return static_cast<void*>(const_cast< CellMatrix*>(this));
    return QObject::qt_metacast(_clname);
}

int CellMatrix::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CellMatrix::endGame(const Player & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
