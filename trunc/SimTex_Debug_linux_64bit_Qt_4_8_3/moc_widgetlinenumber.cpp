/****************************************************************************
** Meta object code from reading C++ file 'widgetlinenumber.h'
**
** Created: Sun Jul 7 10:37:53 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/widgetlinenumber.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widgetlinenumber.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WidgetLineNumber[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   18,   17,   17, 0x0a,
      53,   18,   17,   17, 0x0a,
      86,   76,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WidgetLineNumber[] = {
    "WidgetLineNumber\0\0,\0"
    "updateFirstVisibleBlock(int,int)\0"
    "setBlockRange(int,int)\0lineCount\0"
    "updateWidth(int)\0"
};

void WidgetLineNumber::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WidgetLineNumber *_t = static_cast<WidgetLineNumber *>(_o);
        switch (_id) {
        case 0: _t->updateFirstVisibleBlock((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->setBlockRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->updateWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WidgetLineNumber::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WidgetLineNumber::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WidgetLineNumber,
      qt_meta_data_WidgetLineNumber, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WidgetLineNumber::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WidgetLineNumber::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WidgetLineNumber::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WidgetLineNumber))
        return static_cast<void*>(const_cast< WidgetLineNumber*>(this));
    return QWidget::qt_metacast(_clname);
}

int WidgetLineNumber::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
