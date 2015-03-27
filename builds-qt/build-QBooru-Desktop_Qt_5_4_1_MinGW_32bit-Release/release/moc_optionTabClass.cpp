/****************************************************************************
** Meta object code from reading C++ file 'optionTabClass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../sources/viewer/Widget/optionTabClass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'optionTabClass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OptionTab_t {
    QByteArrayData data[9];
    char stringdata[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OptionTab_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OptionTab_t qt_meta_stringdata_OptionTab = {
    {
QT_MOC_LITERAL(0, 0, 9), // "OptionTab"
QT_MOC_LITERAL(1, 10, 16), // "refreshCacheSize"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "deleteCache"
QT_MOC_LITERAL(4, 40, 15), // "refreshTagLists"
QT_MOC_LITERAL(5, 56, 10), // "runUpdater"
QT_MOC_LITERAL(6, 67, 19), // "resetBoorusSettings"
QT_MOC_LITERAL(7, 87, 22), // "resetBooruDownloadPath"
QT_MOC_LITERAL(8, 110, 11) // "saveOptions"

    },
    "OptionTab\0refreshCacheSize\0\0deleteCache\0"
    "refreshTagLists\0runUpdater\0"
    "resetBoorusSettings\0resetBooruDownloadPath\0"
    "saveOptions"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OptionTab[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OptionTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OptionTab *_t = static_cast<OptionTab *>(_o);
        switch (_id) {
        case 0: _t->refreshCacheSize(); break;
        case 1: _t->deleteCache(); break;
        case 2: _t->refreshTagLists(); break;
        case 3: _t->runUpdater(); break;
        case 4: _t->resetBoorusSettings(); break;
        case 5: _t->resetBooruDownloadPath(); break;
        case 6: _t->saveOptions(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject OptionTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_OptionTab.data,
      qt_meta_data_OptionTab,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OptionTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OptionTab::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OptionTab.stringdata))
        return static_cast<void*>(const_cast< OptionTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int OptionTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
