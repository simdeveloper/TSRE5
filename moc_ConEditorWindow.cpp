/****************************************************************************
** Meta object code from reading C++ file 'ConEditorWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ConEditorWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConEditorWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ConEditorWindow_t {
    QByteArrayData data[19];
    char stringdata[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConEditorWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConEditorWindow_t qt_meta_stringdata_ConEditorWindow = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ConEditorWindow"
QT_MOC_LITERAL(1, 16, 7), // "showEng"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 4), // "path"
QT_MOC_LITERAL(4, 30, 4), // "name"
QT_MOC_LITERAL(5, 35, 7), // "showCon"
QT_MOC_LITERAL(6, 43, 2), // "id"
QT_MOC_LITERAL(7, 46, 15), // "engListSelected"
QT_MOC_LITERAL(8, 62, 15), // "conListSelected"
QT_MOC_LITERAL(9, 78, 21), // "conSliderValueChanged"
QT_MOC_LITERAL(10, 100, 3), // "val"
QT_MOC_LITERAL(11, 104, 11), // "viewConList"
QT_MOC_LITERAL(12, 116, 4), // "show"
QT_MOC_LITERAL(13, 121, 12), // "viewEngList1"
QT_MOC_LITERAL(14, 134, 12), // "viewEngList2"
QT_MOC_LITERAL(15, 147, 12), // "viewConUnits"
QT_MOC_LITERAL(16, 160, 11), // "viewEngView"
QT_MOC_LITERAL(17, 172, 11), // "viewConView"
QT_MOC_LITERAL(18, 184, 5) // "about"

    },
    "ConEditorWindow\0showEng\0\0path\0name\0"
    "showCon\0id\0engListSelected\0conListSelected\0"
    "conSliderValueChanged\0val\0viewConList\0"
    "show\0viewEngList1\0viewEngList2\0"
    "viewConUnits\0viewEngView\0viewConView\0"
    "about"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConEditorWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x06 /* Public */,
       5,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   82,    2, 0x0a /* Public */,
       8,    1,   85,    2, 0x0a /* Public */,
       9,    1,   88,    2, 0x0a /* Public */,
      11,    1,   91,    2, 0x0a /* Public */,
      13,    1,   94,    2, 0x0a /* Public */,
      14,    1,   97,    2, 0x0a /* Public */,
      15,    1,  100,    2, 0x0a /* Public */,
      16,    1,  103,    2, 0x0a /* Public */,
      17,    1,  106,    2, 0x0a /* Public */,
      18,    0,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,

       0        // eod
};

void ConEditorWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConEditorWindow *_t = static_cast<ConEditorWindow *>(_o);
        switch (_id) {
        case 0: _t->showEng((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->showCon((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->engListSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->conListSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->conSliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->viewConList((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->viewEngList1((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->viewEngList2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->viewConUnits((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->viewEngView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->viewConView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->about(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ConEditorWindow::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConEditorWindow::showEng)) {
                *result = 0;
            }
        }
        {
            typedef void (ConEditorWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConEditorWindow::showCon)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject ConEditorWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ConEditorWindow.data,
      qt_meta_data_ConEditorWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ConEditorWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConEditorWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ConEditorWindow.stringdata))
        return static_cast<void*>(const_cast< ConEditorWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ConEditorWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ConEditorWindow::showEng(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConEditorWindow::showCon(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE