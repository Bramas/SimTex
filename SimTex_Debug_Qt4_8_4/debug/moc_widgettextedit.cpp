/****************************************************************************
** Meta object code from reading C++ file 'widgettextedit.h'
**
** Created: Wed 26. Jun 23:12:52 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/widgettextedit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widgettextedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WidgetTextEdit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   16,   15,   15, 0x05,
      51,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      86,   15,   15,   15, 0x0a,
     100,   15,   15,   15, 0x0a,
     120,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WidgetTextEdit[] = {
    "WidgetTextEdit\0\0,\0updateFirstVisibleBlock(int,int)\0"
    "updatedWithSameFirstVisibleBlock()\0"
    "scrollTo(int)\0updateIndentation()\0"
    "onCursorPositionChange()\0"
};

void WidgetTextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WidgetTextEdit *_t = static_cast<WidgetTextEdit *>(_o);
        switch (_id) {
        case 0: _t->updateFirstVisibleBlock((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->updatedWithSameFirstVisibleBlock(); break;
        case 2: _t->scrollTo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateIndentation(); break;
        case 4: _t->onCursorPositionChange(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WidgetTextEdit::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WidgetTextEdit::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata_WidgetTextEdit,
      qt_meta_data_WidgetTextEdit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WidgetTextEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WidgetTextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WidgetTextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WidgetTextEdit))
        return static_cast<void*>(const_cast< WidgetTextEdit*>(this));
    return QTextEdit::qt_metacast(_clname);
}

int WidgetTextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void WidgetTextEdit::updateFirstVisibleBlock(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WidgetTextEdit::updatedWithSameFirstVisibleBlock()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
