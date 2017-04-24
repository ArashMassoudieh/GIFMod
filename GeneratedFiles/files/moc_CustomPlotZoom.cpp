/****************************************************************************
** Meta object code from reading C++ file 'CustomPlotZoom.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GUI/CustomPlotZoom.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CustomPlotZoom.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CustomPlotZoom_t {
    QByteArrayData data[14];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomPlotZoom_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomPlotZoom_t qt_meta_stringdata_CustomPlotZoom = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CustomPlotZoom"
QT_MOC_LITERAL(1, 15, 15), // "mousePressEvent"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 45, 5), // "event"
QT_MOC_LITERAL(5, 51, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(6, 66, 10), // "wheelEvent"
QT_MOC_LITERAL(7, 77, 12), // "QWheelEvent*"
QT_MOC_LITERAL(8, 90, 17), // "mouseReleaseEvent"
QT_MOC_LITERAL(9, 108, 15), // "axisDoubleClick"
QT_MOC_LITERAL(10, 124, 8), // "QCPAxis*"
QT_MOC_LITERAL(11, 133, 4), // "axis"
QT_MOC_LITERAL(12, 138, 23), // "QCPAxis::SelectablePart"
QT_MOC_LITERAL(13, 162, 4) // "part"

    },
    "CustomPlotZoom\0mousePressEvent\0\0"
    "QMouseEvent*\0event\0mouseMoveEvent\0"
    "wheelEvent\0QWheelEvent*\0mouseReleaseEvent\0"
    "axisDoubleClick\0QCPAxis*\0axis\0"
    "QCPAxis::SelectablePart\0part"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomPlotZoom[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       5,    1,   42,    2, 0x08 /* Private */,
       6,    1,   45,    2, 0x08 /* Private */,
       8,    1,   48,    2, 0x08 /* Private */,
       9,    3,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 7,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 12, 0x80000000 | 3,   11,   13,    4,

       0        // eod
};

void CustomPlotZoom::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CustomPlotZoom *_t = static_cast<CustomPlotZoom *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->wheelEvent((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 3: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->axisDoubleClick((*reinterpret_cast< QCPAxis*(*)>(_a[1])),(*reinterpret_cast< QCPAxis::SelectablePart(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis::SelectablePart >(); break;
            }
            break;
        }
    }
}

const QMetaObject CustomPlotZoom::staticMetaObject = {
    { &QCustomPlot::staticMetaObject, qt_meta_stringdata_CustomPlotZoom.data,
      qt_meta_data_CustomPlotZoom,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CustomPlotZoom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomPlotZoom::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CustomPlotZoom.stringdata0))
        return static_cast<void*>(const_cast< CustomPlotZoom*>(this));
    return QCustomPlot::qt_metacast(_clname);
}

int CustomPlotZoom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCustomPlot::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
