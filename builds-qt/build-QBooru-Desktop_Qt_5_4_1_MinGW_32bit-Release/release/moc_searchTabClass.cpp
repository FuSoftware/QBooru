/****************************************************************************
** Meta object code from reading C++ file 'searchTabClass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/viewer/Widget/searchTabClass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'searchTabClass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SearchTab_t {
    QByteArrayData data[9];
    char stringdata[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SearchTab_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SearchTab_t qt_meta_stringdata_SearchTab = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SearchTab"
QT_MOC_LITERAL(1, 10, 19), // "searchActionToggled"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 6), // "sender"
QT_MOC_LITERAL(4, 38, 9), // "setViewer"
QT_MOC_LITERAL(5, 48, 9), // "newSearch"
QT_MOC_LITERAL(6, 58, 19), // "startLoadingPicture"
QT_MOC_LITERAL(7, 78, 1), // "i"
QT_MOC_LITERAL(8, 80, 12) // "image_loaded"

    },
    "SearchTab\0searchActionToggled\0\0sender\0"
    "setViewer\0newSearch\0startLoadingPicture\0"
    "i\0image_loaded"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchTab[] = {

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
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       5,    0,   45,    2, 0x0a /* Public */,
       6,    1,   46,    2, 0x0a /* Public */,
       8,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,

       0        // eod
};

void SearchTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SearchTab *_t = static_cast<SearchTab *>(_o);
        switch (_id) {
        case 0: _t->searchActionToggled((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setViewer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->newSearch(); break;
        case 3: _t->startLoadingPicture((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->image_loaded(); break;
        default: ;
        }
    }
}

const QMetaObject SearchTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SearchTab.data,
      qt_meta_data_SearchTab,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SearchTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SearchTab::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SearchTab.stringdata))
        return static_cast<void*>(const_cast< SearchTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int SearchTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
