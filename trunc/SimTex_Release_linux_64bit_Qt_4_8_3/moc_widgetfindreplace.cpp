/****************************************************************************
** Meta object code from reading C++ file 'widgetfindreplace.h'
**
** Created: Sun Jul 7 17:24:43 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/widgetfindreplace.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widgetfindreplace.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WidgetFindReplace[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      42,   24,   19,   18, 0x0a,
      62,   57,   19,   18, 0x2a,
      72,   18,   19,   18, 0x2a,
      79,   18,   18,   18, 0x0a,
      89,   18,   19,   18, 0x0a,
     106,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WidgetFindReplace[] = {
    "WidgetFindReplace\0\0bool\0from,canStartOver\0"
    "find(int,bool)\0from\0find(int)\0find()\0"
    "replace()\0replaceAndFind()\0replaceAll()\0"
};

void WidgetFindReplace::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WidgetFindReplace *_t = static_cast<WidgetFindReplace *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->find((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = _t->find((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->find();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->replace(); break;
        case 4: { bool _r = _t->replaceAndFind();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: _t->replaceAll(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WidgetFindReplace::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WidgetFindReplace::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WidgetFindReplace,
      qt_meta_data_WidgetFindReplace, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WidgetFindReplace::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WidgetFindReplace::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WidgetFindReplace::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WidgetFindReplace))
        return static_cast<void*>(const_cast< WidgetFindReplace*>(this));
    return QWidget::qt_metacast(_clname);
}

int WidgetFindReplace::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE