/****************************************************************************
** Meta object code from reading C++ file 'viewerTabClass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../sources/viewer/Widget/viewerTabClass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewerTabClass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ViewerTab_t {
    QByteArrayData data[11];
    char stringdata[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ViewerTab_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ViewerTab_t qt_meta_stringdata_ViewerTab = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ViewerTab"
QT_MOC_LITERAL(1, 10, 13), // "buttonClicked"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 14), // "on_tagSelected"
QT_MOC_LITERAL(4, 40, 3), // "tag"
QT_MOC_LITERAL(5, 44, 15), // "downloadPicture"
QT_MOC_LITERAL(6, 60, 14), // "viewFullscreen"
QT_MOC_LITERAL(7, 75, 19), // "showPreviousPicture"
QT_MOC_LITERAL(8, 95, 15), // "showNextPicture"
QT_MOC_LITERAL(9, 111, 19), // "startLoadingPicture"
QT_MOC_LITERAL(10, 131, 11) // "imageLoaded"

    },
    "ViewerTab\0buttonClicked\0\0on_tagSelected\0"
    "tag\0downloadPicture\0viewFullscreen\0"
    "showPreviousPicture\0showNextPicture\0"
    "startLoadingPicture\0imageLoaded"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ViewerTab[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    1,   55,    2, 0x0a /* Public */,
       5,    0,   58,    2, 0x0a /* Public */,
       6,    0,   59,    2, 0x0a /* Public */,
       7,    0,   60,    2, 0x0a /* Public */,
       8,    0,   61,    2, 0x0a /* Public */,
       9,    0,   62,    2, 0x0a /* Public */,
      10,    0,   63,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ViewerTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ViewerTab *_t = static_cast<ViewerTab *>(_o);
        switch (_id) {
        case 0: _t->buttonClicked(); break;
        case 1: _t->on_tagSelected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->downloadPicture(); break;
        case 3: _t->viewFullscreen(); break;
        case 4: _t->showPreviousPicture(); break;
        case 5: _t->showNextPicture(); break;
        case 6: _t->startLoadingPicture(); break;
        case 7: _t->imageLoaded(); break;
        default: ;
        }
    }
}

const QMetaObject ViewerTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ViewerTab.data,
      qt_meta_data_ViewerTab,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ViewerTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ViewerTab::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ViewerTab.stringdata))
        return static_cast<void*>(const_cast< ViewerTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int ViewerTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
