/****************************************************************************
** Meta object code from reading C++ file 'widgettextedit.h'
**
** Created: Sun Jul 7 10:37:54 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/widgettextedit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widgettextedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WidgetTextEdit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   16,   15,   15, 0x05,
      51,   15,   15,   15, 0x05,
      86,   16,   15,   15, 0x05,
     109,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     131,   15,   15,   15, 0x0a,
     145,   15,   15,   15, 0x0a,
     165,   15,   15,   15, 0x0a,
     190,   15,   15,   15, 0x0a,
     205,   15,   15,   15, 0x0a,
     216,   15,   15,   15, 0x0a,
     233,  227,   15,   15, 0x0a,
     259,  254,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WidgetTextEdit[] = {
    "WidgetTextEdit\0\0,\0updateFirstVisibleBlock(int,int)\0"
    "updatedWithSameFirstVisibleBlock()\0"
    "setBlockRange(int,int)\0lineCountChanged(int)\0"
    "scrollTo(int)\0updateIndentation()\0"
    "onCursorPositionChange()\0matchCommand()\0"
    "matchAll()\0setFocus()\0event\0"
    "setFocus(QKeyEvent*)\0line\0goToLine(int)\0"
};

void WidgetTextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WidgetTextEdit *_t = static_cast<WidgetTextEdit *>(_o);
        switch (_id) {
        case 0: _t->updateFirstVisibleBlock((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->updatedWithSameFirstVisibleBlock(); break;
        case 2: _t->setBlockRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->lineCountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->scrollTo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateIndentation(); break;
        case 6: _t->onCursorPositionChange(); break;
        case 7: _t->matchCommand(); break;
        case 8: _t->matchAll(); break;
        case 9: _t->setFocus(); break;
        case 10: _t->setFocus((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 11: _t->goToLine((*reinterpret_cast< int(*)>(_a[1]))); break;
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
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

// SIGNAL 2
void WidgetTextEdit::setBlockRange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WidgetTextEdit::lineCountChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
