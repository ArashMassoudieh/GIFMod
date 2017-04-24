/****************************************************************************
** Meta object code from reading C++ file 'UnitTextBox2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GUI/UnitTextBox2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UnitTextBox2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UnitTextBox2_t {
    QByteArrayData data[9];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UnitTextBox2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UnitTextBox2_t qt_meta_stringdata_UnitTextBox2 = {
    {
QT_MOC_LITERAL(0, 0, 12), // "UnitTextBox2"
QT_MOC_LITERAL(1, 13, 15), // "editingFinished"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 11), // "closeEditor"
QT_MOC_LITERAL(4, 42, 8), // "QWidget*"
QT_MOC_LITERAL(5, 51, 6), // "editor"
QT_MOC_LITERAL(6, 58, 34), // "QAbstractItemDelegate::EndEdi..."
QT_MOC_LITERAL(7, 93, 4), // "hint"
QT_MOC_LITERAL(8, 98, 13) // "finishEditing"

    },
    "UnitTextBox2\0editingFinished\0\0closeEditor\0"
    "QWidget*\0editor\0QAbstractItemDelegate::EndEditHint\0"
    "hint\0finishEditing"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UnitTextBox2[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    2,   35,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x26 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 6,    5,    7,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void UnitTextBox2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UnitTextBox2 *_t = static_cast<UnitTextBox2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->editingFinished(); break;
        case 1: _t->closeEditor((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QAbstractItemDelegate::EndEditHint(*)>(_a[2]))); break;
        case 2: _t->closeEditor((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->finishEditing(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 2:
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
            typedef void (UnitTextBox2::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UnitTextBox2::editingFinished)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (UnitTextBox2::*_t)(QWidget * , QAbstractItemDelegate::EndEditHint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UnitTextBox2::closeEditor)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject UnitTextBox2::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UnitTextBox2.data,
      qt_meta_data_UnitTextBox2,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UnitTextBox2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UnitTextBox2::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UnitTextBox2.stringdata0))
        return static_cast<void*>(const_cast< UnitTextBox2*>(this));
    return QWidget::qt_metacast(_clname);
}

int UnitTextBox2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void UnitTextBox2::editingFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void UnitTextBox2::closeEditor(QWidget * _t1, QAbstractItemDelegate::EndEditHint _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
