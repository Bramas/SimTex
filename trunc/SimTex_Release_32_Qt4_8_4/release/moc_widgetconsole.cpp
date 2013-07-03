/****************************************************************************
** Meta object code from reading C++ file 'widgetconsole.h'
**
** Created: Wed 3. Jul 17:35:05 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/widgetconsole.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widgetconsole.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WidgetConsole[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   14,   14,   14, 0x0a,
      41,   14,   14,   14, 0x0a,
      53,   14,   14,   14, 0x0a,
      63,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WidgetConsole[] = {
    "WidgetConsole\0\0requestLine(int)\0"
    "expand()\0collapsed()\0onError()\0"
    "onSuccess()\0"
};

void WidgetConsole::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WidgetConsole *_t = static_cast<WidgetConsole *>(_o);
        switch (_id) {
        case 0: _t->requestLine((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->expand(); break;
        case 2: _t->collapsed(); break;
        case 3: _t->onError(); break;
        case 4: _t->onSuccess(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WidgetConsole::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WidgetConsole::staticMetaObject = {
    { &QPlainTextEdit::staticMetaObject, qt_meta_stringdata_WidgetConsole,
      qt_meta_data_WidgetConsole, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WidgetConsole::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WidgetConsole::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WidgetConsole::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WidgetConsole))
        return static_cast<void*>(const_cast< WidgetConsole*>(this));
    return QPlainTextEdit::qt_metacast(_clname);
}

int WidgetConsole::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
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
void WidgetConsole::requestLine(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
