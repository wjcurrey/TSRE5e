/****************************************************************************
** Meta object code from reading C++ file 'NaviWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "NaviWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NaviWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NaviWindow_t {
    QByteArrayData data[27];
    char stringdata0[267];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NaviWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NaviWindow_t qt_meta_stringdata_NaviWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "NaviWindow"
QT_MOC_LITERAL(1, 11, 6), // "jumpTo"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 22), // "PreciseTileCoordinate*"
QT_MOC_LITERAL(4, 42, 7), // "sendMsg"
QT_MOC_LITERAL(5, 50, 4), // "name"
QT_MOC_LITERAL(6, 55, 3), // "val"
QT_MOC_LITERAL(7, 59, 12), // "windowClosed"
QT_MOC_LITERAL(8, 72, 16), // "jumpTileSelected"
QT_MOC_LITERAL(9, 89, 8), // "naviInfo"
QT_MOC_LITERAL(10, 98, 3), // "all"
QT_MOC_LITERAL(11, 102, 6), // "hidden"
QT_MOC_LITERAL(12, 109, 7), // "posInfo"
QT_MOC_LITERAL(13, 117, 6), // "coords"
QT_MOC_LITERAL(14, 124, 11), // "pointerInfo"
QT_MOC_LITERAL(15, 136, 6), // "float*"
QT_MOC_LITERAL(16, 143, 13), // "latLonChanged"
QT_MOC_LITERAL(17, 157, 9), // "xyChanged"
QT_MOC_LITERAL(18, 167, 7), // "mkrList"
QT_MOC_LITERAL(19, 175, 21), // "QMap<QString,Coords*>"
QT_MOC_LITERAL(20, 197, 4), // "list"
QT_MOC_LITERAL(21, 202, 16), // "mkrFilesSelected"
QT_MOC_LITERAL(22, 219, 4), // "item"
QT_MOC_LITERAL(23, 224, 15), // "mkrListSelected"
QT_MOC_LITERAL(24, 240, 9), // "recStatus"
QT_MOC_LITERAL(25, 250, 8), // "statName"
QT_MOC_LITERAL(26, 259, 7) // "statVal"

    },
    "NaviWindow\0jumpTo\0\0PreciseTileCoordinate*\0"
    "sendMsg\0name\0val\0windowClosed\0"
    "jumpTileSelected\0naviInfo\0all\0hidden\0"
    "posInfo\0coords\0pointerInfo\0float*\0"
    "latLonChanged\0xyChanged\0mkrList\0"
    "QMap<QString,Coords*>\0list\0mkrFilesSelected\0"
    "item\0mkrListSelected\0recStatus\0statName\0"
    "statVal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NaviWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       4,    1,  102,    2, 0x06 /* Public */,
       4,    2,  105,    2, 0x06 /* Public */,
       4,    2,  110,    2, 0x06 /* Public */,
       4,    2,  115,    2, 0x06 /* Public */,
       4,    2,  120,    2, 0x06 /* Public */,
       7,    0,  125,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,  126,    2, 0x0a /* Public */,
       9,    2,  127,    2, 0x0a /* Public */,
      12,    1,  132,    2, 0x0a /* Public */,
      14,    1,  135,    2, 0x0a /* Public */,
      16,    1,  138,    2, 0x0a /* Public */,
      17,    1,  141,    2, 0x0a /* Public */,
      18,    1,  144,    2, 0x0a /* Public */,
      21,    1,  147,    2, 0x0a /* Public */,
      23,    1,  150,    2, 0x0a /* Public */,
      24,    2,  153,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Float,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, 0x80000000 | 3,   13,
    QMetaType::Void, 0x80000000 | 15,   13,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   25,   26,

       0        // eod
};

void NaviWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NaviWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->jumpTo((*reinterpret_cast< PreciseTileCoordinate*(*)>(_a[1]))); break;
        case 1: _t->sendMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->sendMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->sendMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->sendMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->sendMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->windowClosed(); break;
        case 7: _t->jumpTileSelected(); break;
        case 8: _t->naviInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->posInfo((*reinterpret_cast< PreciseTileCoordinate*(*)>(_a[1]))); break;
        case 10: _t->pointerInfo((*reinterpret_cast< float*(*)>(_a[1]))); break;
        case 11: _t->latLonChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->xyChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->mkrList((*reinterpret_cast< QMap<QString,Coords*>(*)>(_a[1]))); break;
        case 14: _t->mkrFilesSelected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->mkrListSelected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->recStatus((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NaviWindow::*)(PreciseTileCoordinate * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NaviWindow::jumpTo)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NaviWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NaviWindow::sendMsg)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NaviWindow::*)(QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NaviWindow::sendMsg)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (NaviWindow::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NaviWindow::sendMsg)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (NaviWindow::*)(QString , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NaviWindow::sendMsg)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (NaviWindow::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NaviWindow::sendMsg)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (NaviWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NaviWindow::windowClosed)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NaviWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_NaviWindow.data,
    qt_meta_data_NaviWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NaviWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NaviWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NaviWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int NaviWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void NaviWindow::jumpTo(PreciseTileCoordinate * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NaviWindow::sendMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NaviWindow::sendMsg(QString _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NaviWindow::sendMsg(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void NaviWindow::sendMsg(QString _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void NaviWindow::sendMsg(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void NaviWindow::windowClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
