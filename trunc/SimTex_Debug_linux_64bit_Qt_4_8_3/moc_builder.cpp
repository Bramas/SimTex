/****************************************************************************
** Meta object code from reading C++ file 'builder.h'
**
** Created: Sun Jul 7 10:37:57 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/builder.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'builder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Builder[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      32,    8,    8,    8, 0x05,
      53,    8,    8,    8, 0x05,
      66,    8,    8,    8, 0x05,
      74,    8,    8,    8, 0x05,
      84,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      94,    8,    8,    8, 0x0a,
     125,  105,    8,    8, 0x0a,
     162,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Builder[] = {
    "Builder\0\0statusChanged(QString)\0"
    "outputReady(QString)\0pdfChanged()\0"
    "error()\0success()\0started()\0pdflatex()\0"
    "exitCode,exitStatus\0"
    "onFinished(int,QProcess::ExitStatus)\0"
    "onStandartOutputReady()\0"
};

void Builder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Builder *_t = static_cast<Builder *>(_o);
        switch (_id) {
        case 0: _t->statusChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->outputReady((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->pdfChanged(); break;
        case 3: _t->error(); break;
        case 4: _t->success(); break;
        case 5: _t->started(); break;
        case 6: _t->pdflatex(); break;
        case 7: _t->onFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 8: _t->onStandartOutputReady(); break;
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
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
void Builder::outputReady(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Builder::pdfChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Builder::error()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Builder::success()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Builder::started()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
