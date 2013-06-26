/****************************************************************************
** Meta object code from reading C++ file 'builder.h'
**
** Created: Wed 26. Jun 17:25:45 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/builder.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'builder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Builder[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      32,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,    8,    8,    8, 0x0a,
      76,   56,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Builder[] = {
    "Builder\0\0statusChanged(QString)\0"
    "pdfChanged()\0pdflatex()\0exitCode,exitStatus\0"
    "onFinished(int,QProcess::ExitStatus)\0"
};

void Builder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Builder *_t = static_cast<Builder *>(_o);
        switch (_id) {
        case 0: _t->statusChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->pdfChanged(); break;
        case 2: _t->pdflatex(); break;
        case 3: _t->onFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Builder::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Builder::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Builder,
      qt_meta_data_Builder, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Builder::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Builder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Builder::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Builder))
        return static_cast<void*>(const_cast< Builder*>(this));
    return QObject::qt_metacast(_clname);
}

int Builder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Builder::statusChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Builder::pdfChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
