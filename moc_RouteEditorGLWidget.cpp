/****************************************************************************
** Meta object code from reading C++ file 'RouteEditorGLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "RouteEditorGLWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RouteEditorGLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RouteEditorGLWidget_t {
    QByteArrayData data[96];
    char stringdata0[1267];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RouteEditorGLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RouteEditorGLWidget_t qt_meta_stringdata_RouteEditorGLWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "RouteEditorGLWidget"
QT_MOC_LITERAL(1, 20, 10), // "showWindow"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 11), // "routeLoaded"
QT_MOC_LITERAL(4, 44, 6), // "Route*"
QT_MOC_LITERAL(5, 51, 1), // "a"
QT_MOC_LITERAL(6, 53, 12), // "itemSelected"
QT_MOC_LITERAL(7, 66, 13), // "Ref::RefItem*"
QT_MOC_LITERAL(8, 80, 7), // "pointer"
QT_MOC_LITERAL(9, 88, 8), // "naviInfo"
QT_MOC_LITERAL(10, 97, 3), // "all"
QT_MOC_LITERAL(11, 101, 6), // "hidden"
QT_MOC_LITERAL(12, 108, 7), // "posInfo"
QT_MOC_LITERAL(13, 116, 22), // "PreciseTileCoordinate*"
QT_MOC_LITERAL(14, 139, 3), // "pos"
QT_MOC_LITERAL(15, 143, 11), // "pointerInfo"
QT_MOC_LITERAL(16, 155, 6), // "float*"
QT_MOC_LITERAL(17, 162, 10), // "setToolbox"
QT_MOC_LITERAL(18, 173, 4), // "name"
QT_MOC_LITERAL(19, 178, 17), // "setBrushTextureId"
QT_MOC_LITERAL(20, 196, 3), // "val"
QT_MOC_LITERAL(21, 200, 14), // "showProperties"
QT_MOC_LITERAL(22, 215, 8), // "GameObj*"
QT_MOC_LITERAL(23, 224, 3), // "obj"
QT_MOC_LITERAL(24, 228, 16), // "updateProperties"
QT_MOC_LITERAL(25, 245, 8), // "flexData"
QT_MOC_LITERAL(26, 254, 1), // "x"
QT_MOC_LITERAL(27, 256, 1), // "z"
QT_MOC_LITERAL(28, 258, 1), // "p"
QT_MOC_LITERAL(29, 260, 7), // "mkrList"
QT_MOC_LITERAL(30, 268, 21), // "QMap<QString,Coords*>"
QT_MOC_LITERAL(31, 290, 4), // "list"
QT_MOC_LITERAL(32, 295, 15), // "refreshObjLists"
QT_MOC_LITERAL(33, 311, 7), // "sendMsg"
QT_MOC_LITERAL(34, 319, 9), // "updStatus"
QT_MOC_LITERAL(35, 329, 8), // "statName"
QT_MOC_LITERAL(36, 338, 9), // "statValue"
QT_MOC_LITERAL(37, 348, 7), // "cleanup"
QT_MOC_LITERAL(38, 356, 10), // "enableTool"
QT_MOC_LITERAL(39, 367, 13), // "setPaintBrush"
QT_MOC_LITERAL(40, 381, 6), // "Brush*"
QT_MOC_LITERAL(41, 388, 5), // "brush"
QT_MOC_LITERAL(42, 394, 6), // "jumpTo"
QT_MOC_LITERAL(43, 401, 4), // "posT"
QT_MOC_LITERAL(44, 406, 1), // "X"
QT_MOC_LITERAL(45, 408, 1), // "Z"
QT_MOC_LITERAL(46, 410, 1), // "y"
QT_MOC_LITERAL(47, 412, 3), // "msg"
QT_MOC_LITERAL(48, 416, 4), // "text"
QT_MOC_LITERAL(49, 421, 8), // "editCopy"
QT_MOC_LITERAL(50, 430, 9), // "editPaste"
QT_MOC_LITERAL(51, 440, 10), // "editSelect"
QT_MOC_LITERAL(52, 451, 11), // "editFind1x1"
QT_MOC_LITERAL(53, 463, 11), // "editFind3x3"
QT_MOC_LITERAL(54, 475, 8), // "editFind"
QT_MOC_LITERAL(55, 484, 6), // "radius"
QT_MOC_LITERAL(56, 491, 8), // "editUndo"
QT_MOC_LITERAL(57, 500, 12), // "showTrkEditr"
QT_MOC_LITERAL(58, 513, 10), // "rebuildTDB"
QT_MOC_LITERAL(59, 524, 15), // "showContextMenu"
QT_MOC_LITERAL(60, 540, 5), // "point"
QT_MOC_LITERAL(61, 546, 14), // "createNewTiles"
QT_MOC_LITERAL(62, 561, 25), // "QMap<int,QPair<int,int>*>"
QT_MOC_LITERAL(63, 587, 16), // "createNewLoTiles"
QT_MOC_LITERAL(64, 604, 14), // "objectSelected"
QT_MOC_LITERAL(65, 619, 17), // "QVector<GameObj*>"
QT_MOC_LITERAL(66, 637, 23), // "selectToolresetMoveStep"
QT_MOC_LITERAL(67, 661, 18), // "selectToolresetRot"
QT_MOC_LITERAL(68, 680, 16), // "selectToolSelect"
QT_MOC_LITERAL(69, 697, 16), // "selectToolRotate"
QT_MOC_LITERAL(70, 714, 19), // "selectToolTranslate"
QT_MOC_LITERAL(71, 734, 15), // "selectToolScale"
QT_MOC_LITERAL(72, 750, 20), // "toolBrushDirectionUp"
QT_MOC_LITERAL(73, 771, 22), // "toolBrushDirectionDown"
QT_MOC_LITERAL(74, 794, 29), // "putTerrainTexToolSelectRandom"
QT_MOC_LITERAL(75, 824, 30), // "putTerrainTexToolSelectPresent"
QT_MOC_LITERAL(76, 855, 24), // "putTerrainTexToolSelect0"
QT_MOC_LITERAL(77, 880, 25), // "putTerrainTexToolSelect90"
QT_MOC_LITERAL(78, 906, 26), // "putTerrainTexToolSelect180"
QT_MOC_LITERAL(79, 933, 26), // "putTerrainTexToolSelect270"
QT_MOC_LITERAL(80, 960, 21), // "placeToolStickTerrain"
QT_MOC_LITERAL(81, 982, 17), // "placeToolStickAll"
QT_MOC_LITERAL(82, 1000, 13), // "reloadRefFile"
QT_MOC_LITERAL(83, 1014, 15), // "setCameraObject"
QT_MOC_LITERAL(84, 1030, 11), // "setMoveStep"
QT_MOC_LITERAL(85, 1042, 12), // "paintToolObj"
QT_MOC_LITERAL(86, 1055, 20), // "paintToolObjSelected"
QT_MOC_LITERAL(87, 1076, 12), // "paintToolTDB"
QT_MOC_LITERAL(88, 1089, 18), // "paintToolTDBVector"
QT_MOC_LITERAL(89, 1108, 15), // "setTerrainToObj"
QT_MOC_LITERAL(90, 1124, 30), // "adjustObjPositionToTerrainMenu"
QT_MOC_LITERAL(91, 1155, 30), // "adjustObjRotationToTerrainMenu"
QT_MOC_LITERAL(92, 1186, 19), // "pickObjForPlacement"
QT_MOC_LITERAL(93, 1206, 22), // "pickObjRotForPlacement"
QT_MOC_LITERAL(94, 1229, 26), // "pickObjRotElevForPlacement"
QT_MOC_LITERAL(95, 1256, 10) // "initRoute2"

    },
    "RouteEditorGLWidget\0showWindow\0\0"
    "routeLoaded\0Route*\0a\0itemSelected\0"
    "Ref::RefItem*\0pointer\0naviInfo\0all\0"
    "hidden\0posInfo\0PreciseTileCoordinate*\0"
    "pos\0pointerInfo\0float*\0setToolbox\0"
    "name\0setBrushTextureId\0val\0showProperties\0"
    "GameObj*\0obj\0updateProperties\0flexData\0"
    "x\0z\0p\0mkrList\0QMap<QString,Coords*>\0"
    "list\0refreshObjLists\0sendMsg\0updStatus\0"
    "statName\0statValue\0cleanup\0enableTool\0"
    "setPaintBrush\0Brush*\0brush\0jumpTo\0"
    "posT\0X\0Z\0y\0msg\0text\0editCopy\0editPaste\0"
    "editSelect\0editFind1x1\0editFind3x3\0"
    "editFind\0radius\0editUndo\0showTrkEditr\0"
    "rebuildTDB\0showContextMenu\0point\0"
    "createNewTiles\0QMap<int,QPair<int,int>*>\0"
    "createNewLoTiles\0objectSelected\0"
    "QVector<GameObj*>\0selectToolresetMoveStep\0"
    "selectToolresetRot\0selectToolSelect\0"
    "selectToolRotate\0selectToolTranslate\0"
    "selectToolScale\0toolBrushDirectionUp\0"
    "toolBrushDirectionDown\0"
    "putTerrainTexToolSelectRandom\0"
    "putTerrainTexToolSelectPresent\0"
    "putTerrainTexToolSelect0\0"
    "putTerrainTexToolSelect90\0"
    "putTerrainTexToolSelect180\0"
    "putTerrainTexToolSelect270\0"
    "placeToolStickTerrain\0placeToolStickAll\0"
    "reloadRefFile\0setCameraObject\0setMoveStep\0"
    "paintToolObj\0paintToolObjSelected\0"
    "paintToolTDB\0paintToolTDBVector\0"
    "setTerrainToObj\0adjustObjPositionToTerrainMenu\0"
    "adjustObjRotationToTerrainMenu\0"
    "pickObjForPlacement\0pickObjRotForPlacement\0"
    "pickObjRotElevForPlacement\0initRoute2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RouteEditorGLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      75,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      19,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  389,    2, 0x06 /* Public */,
       3,    1,  390,    2, 0x06 /* Public */,
       6,    1,  393,    2, 0x06 /* Public */,
       9,    2,  396,    2, 0x06 /* Public */,
      12,    1,  401,    2, 0x06 /* Public */,
      15,    1,  404,    2, 0x06 /* Public */,
      17,    1,  407,    2, 0x06 /* Public */,
      19,    1,  410,    2, 0x06 /* Public */,
      21,    1,  413,    2, 0x06 /* Public */,
      24,    1,  416,    2, 0x06 /* Public */,
      25,    3,  419,    2, 0x06 /* Public */,
      29,    1,  426,    2, 0x06 /* Public */,
      32,    0,  429,    2, 0x06 /* Public */,
      33,    1,  430,    2, 0x06 /* Public */,
      33,    2,  433,    2, 0x06 /* Public */,
      33,    2,  438,    2, 0x06 /* Public */,
      33,    2,  443,    2, 0x06 /* Public */,
      33,    2,  448,    2, 0x06 /* Public */,
      34,    2,  453,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      37,    0,  458,    2, 0x0a /* Public */,
      38,    1,  459,    2, 0x0a /* Public */,
      39,    1,  462,    2, 0x0a /* Public */,
      42,    1,  465,    2, 0x0a /* Public */,
      42,    2,  468,    2, 0x0a /* Public */,
      42,    5,  473,    2, 0x0a /* Public */,
      47,    1,  484,    2, 0x0a /* Public */,
      47,    2,  487,    2, 0x0a /* Public */,
      47,    2,  492,    2, 0x0a /* Public */,
      47,    2,  497,    2, 0x0a /* Public */,
      47,    2,  502,    2, 0x0a /* Public */,
      49,    0,  507,    2, 0x0a /* Public */,
      50,    0,  508,    2, 0x0a /* Public */,
      51,    0,  509,    2, 0x0a /* Public */,
      52,    0,  510,    2, 0x0a /* Public */,
      53,    0,  511,    2, 0x0a /* Public */,
      54,    1,  512,    2, 0x0a /* Public */,
      54,    0,  515,    2, 0x2a /* Public | MethodCloned */,
      56,    0,  516,    2, 0x0a /* Public */,
      57,    0,  517,    2, 0x0a /* Public */,
      58,    0,  518,    2, 0x0a /* Public */,
      59,    1,  519,    2, 0x0a /* Public */,
      61,    1,  522,    2, 0x0a /* Public */,
      63,    1,  525,    2, 0x0a /* Public */,
      64,    1,  528,    2, 0x0a /* Public */,
      64,    1,  531,    2, 0x0a /* Public */,
      66,    0,  534,    2, 0x0a /* Public */,
      67,    0,  535,    2, 0x0a /* Public */,
      68,    0,  536,    2, 0x0a /* Public */,
      69,    0,  537,    2, 0x0a /* Public */,
      70,    0,  538,    2, 0x0a /* Public */,
      71,    0,  539,    2, 0x0a /* Public */,
      72,    0,  540,    2, 0x0a /* Public */,
      73,    0,  541,    2, 0x0a /* Public */,
      74,    0,  542,    2, 0x0a /* Public */,
      75,    0,  543,    2, 0x0a /* Public */,
      76,    0,  544,    2, 0x0a /* Public */,
      77,    0,  545,    2, 0x0a /* Public */,
      78,    0,  546,    2, 0x0a /* Public */,
      79,    0,  547,    2, 0x0a /* Public */,
      80,    0,  548,    2, 0x0a /* Public */,
      81,    0,  549,    2, 0x0a /* Public */,
      82,    0,  550,    2, 0x0a /* Public */,
      83,    1,  551,    2, 0x0a /* Public */,
      84,    1,  554,    2, 0x0a /* Public */,
      85,    0,  557,    2, 0x0a /* Public */,
      86,    0,  558,    2, 0x0a /* Public */,
      87,    0,  559,    2, 0x0a /* Public */,
      88,    0,  560,    2, 0x0a /* Public */,
      89,    0,  561,    2, 0x0a /* Public */,
      90,    0,  562,    2, 0x0a /* Public */,
      91,    0,  563,    2, 0x0a /* Public */,
      92,    0,  564,    2, 0x0a /* Public */,
      93,    0,  565,    2, 0x0a /* Public */,
      94,    0,  566,    2, 0x0a /* Public */,
      95,    0,  567,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,   14,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 16,   26,   27,   28,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   18,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   18,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::Float,   18,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   18,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   35,   36,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, 0x80000000 | 40,   41,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 16,   43,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float, QMetaType::Float, QMetaType::Float,   44,   45,   26,   46,   27,
    QMetaType::Void, QMetaType::QString,   48,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   18,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   18,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::Float,   18,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   18,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   55,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   60,
    QMetaType::Void, 0x80000000 | 62,   31,
    QMetaType::Void, 0x80000000 | 62,   31,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 65,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, QMetaType::Float,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RouteEditorGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RouteEditorGLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showWindow(); break;
        case 1: _t->routeLoaded((*reinterpret_cast< Route*(*)>(_a[1]))); break;
        case 2: _t->itemSelected((*reinterpret_cast< Ref::RefItem*(*)>(_a[1]))); break;
        case 3: _t->naviInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->posInfo((*reinterpret_cast< PreciseTileCoordinate*(*)>(_a[1]))); break;
        case 5: _t->pointerInfo((*reinterpret_cast< float*(*)>(_a[1]))); break;
        case 6: _t->setToolbox((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->setBrushTextureId((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->showProperties((*reinterpret_cast< GameObj*(*)>(_a[1]))); break;
        case 9: _t->updateProperties((*reinterpret_cast< GameObj*(*)>(_a[1]))); break;
        case 10: _t->flexData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float*(*)>(_a[3]))); break;
        case 11: _t->mkrList((*reinterpret_cast< QMap<QString,Coords*>(*)>(_a[1]))); break;
        case 12: _t->refreshObjLists(); break;
        case 13: _t->sendMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->sendMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 15: _t->sendMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 16: _t->sendMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 17: _t->sendMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 18: _t->updStatus((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 19: _t->cleanup(); break;
        case 20: _t->enableTool((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->setPaintBrush((*reinterpret_cast< Brush*(*)>(_a[1]))); break;
        case 22: _t->jumpTo((*reinterpret_cast< PreciseTileCoordinate*(*)>(_a[1]))); break;
        case 23: _t->jumpTo((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< float*(*)>(_a[2]))); break;
        case 24: _t->jumpTo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5]))); break;
        case 25: _t->msg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 26: _t->msg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 27: _t->msg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 28: _t->msg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 29: _t->msg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 30: _t->editCopy(); break;
        case 31: _t->editPaste(); break;
        case 32: _t->editSelect(); break;
        case 33: _t->editFind1x1(); break;
        case 34: _t->editFind3x3(); break;
        case 35: _t->editFind((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->editFind(); break;
        case 37: _t->editUndo(); break;
        case 38: _t->showTrkEditr(); break;
        case 39: _t->rebuildTDB(); break;
        case 40: _t->showContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 41: _t->createNewTiles((*reinterpret_cast< QMap<int,QPair<int,int>*>(*)>(_a[1]))); break;
        case 42: _t->createNewLoTiles((*reinterpret_cast< QMap<int,QPair<int,int>*>(*)>(_a[1]))); break;
        case 43: _t->objectSelected((*reinterpret_cast< GameObj*(*)>(_a[1]))); break;
        case 44: _t->objectSelected((*reinterpret_cast< QVector<GameObj*>(*)>(_a[1]))); break;
        case 45: _t->selectToolresetMoveStep(); break;
        case 46: _t->selectToolresetRot(); break;
        case 47: _t->selectToolSelect(); break;
        case 48: _t->selectToolRotate(); break;
        case 49: _t->selectToolTranslate(); break;
        case 50: _t->selectToolScale(); break;
        case 51: _t->toolBrushDirectionUp(); break;
        case 52: _t->toolBrushDirectionDown(); break;
        case 53: _t->putTerrainTexToolSelectRandom(); break;
        case 54: _t->putTerrainTexToolSelectPresent(); break;
        case 55: _t->putTerrainTexToolSelect0(); break;
        case 56: _t->putTerrainTexToolSelect90(); break;
        case 57: _t->putTerrainTexToolSelect180(); break;
        case 58: _t->putTerrainTexToolSelect270(); break;
        case 59: _t->placeToolStickTerrain(); break;
        case 60: _t->placeToolStickAll(); break;
        case 61: _t->reloadRefFile(); break;
        case 62: _t->setCameraObject((*reinterpret_cast< GameObj*(*)>(_a[1]))); break;
        case 63: _t->setMoveStep((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 64: _t->paintToolObj(); break;
        case 65: _t->paintToolObjSelected(); break;
        case 66: _t->paintToolTDB(); break;
        case 67: _t->paintToolTDBVector(); break;
        case 68: _t->setTerrainToObj(); break;
        case 69: _t->adjustObjPositionToTerrainMenu(); break;
        case 70: _t->adjustObjRotationToTerrainMenu(); break;
        case 71: _t->pickObjForPlacement(); break;
        case 72: _t->pickObjRotForPlacement(); break;
        case 73: _t->pickObjRotElevForPlacement(); break;
        case 74: _t->initRoute2(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RouteEditorGLWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::showWindow)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(Route * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::routeLoaded)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(Ref::RefItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::itemSelected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::naviInfo)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(PreciseTileCoordinate * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::posInfo)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(float * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::pointerInfo)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::setToolbox)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::setBrushTextureId)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(GameObj * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::showProperties)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(GameObj * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::updateProperties)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(int , int , float * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::flexData)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(QMap<QString,Coords*> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::mkrList)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::refreshObjLists)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::sendMsg)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::sendMsg)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::sendMsg)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(QString , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::sendMsg)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::sendMsg)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (RouteEditorGLWidget::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RouteEditorGLWidget::updStatus)) {
                *result = 18;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RouteEditorGLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_RouteEditorGLWidget.data,
    qt_meta_data_RouteEditorGLWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RouteEditorGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RouteEditorGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RouteEditorGLWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int RouteEditorGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 75)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 75;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 75)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 75;
    }
    return _id;
}

// SIGNAL 0
void RouteEditorGLWidget::showWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void RouteEditorGLWidget::routeLoaded(Route * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RouteEditorGLWidget::itemSelected(Ref::RefItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RouteEditorGLWidget::naviInfo(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void RouteEditorGLWidget::posInfo(PreciseTileCoordinate * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void RouteEditorGLWidget::pointerInfo(float * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void RouteEditorGLWidget::setToolbox(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void RouteEditorGLWidget::setBrushTextureId(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void RouteEditorGLWidget::showProperties(GameObj * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void RouteEditorGLWidget::updateProperties(GameObj * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void RouteEditorGLWidget::flexData(int _t1, int _t2, float * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void RouteEditorGLWidget::mkrList(QMap<QString,Coords*> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void RouteEditorGLWidget::refreshObjLists()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void RouteEditorGLWidget::sendMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void RouteEditorGLWidget::sendMsg(QString _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void RouteEditorGLWidget::sendMsg(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void RouteEditorGLWidget::sendMsg(QString _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void RouteEditorGLWidget::sendMsg(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void RouteEditorGLWidget::updStatus(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
