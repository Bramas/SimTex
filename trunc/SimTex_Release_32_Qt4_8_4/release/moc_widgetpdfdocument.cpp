/****************************************************************************
** Meta object code from reading C++ file 'widgetpdfdocument.h'
**
** Created: Mon 1. Jul 19:20:45 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/widgetpdfdocument.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widgetpdfdocument.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WidgetPdfDocument[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      38,   19,   18,   18, 0x0a,
      94,   71,   18,   18, 0x0a,
     127,   18,   18,   18, 0x0a,
     136,   18,   18,   18, 0x0a,
     160,  146,   18,   18, 0x0a,
     186,  179,   18,   18, 0x2a,
     198,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WidgetPdfDocument[] = {
    "WidgetPdfDocument\0\0firstVisibleBlock,\0"
    "jumpToPdfFromSourceView(int,int)\0"
    "sourceFile,source_line\0"
    "jumpToPdfFromSource(QString,int)\0"
    "zoomIn()\0zoomOut()\0factor,target\0"
    "zoom(qreal,QPoint)\0factor\0zoom(qreal)\0"
    "updatePdf()\0"
};

void WidgetPdfDocument::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WidgetPdfDocument *_t = static_cast<WidgetPdfDocument *>(_o);
        switch (_id) {
        case 0: _t->jumpToPdfFromSourceView((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->jumpToPdfFromSource((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->zoomIn(); break;
        case 3: _t->zoomOut(); break;
        case 4: _t->zoom((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 5: _t->zoom((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 6: _t->updatePdf(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WidgetPdfDocument::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WidgetPdfDocument::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WidgetPdfDocument,
      qt_meta_data_WidgetPdfDocument, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WidgetPdfDocument::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WidgetPdfDocument::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WidgetPdfDocument::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WidgetPdfDocument))
        return static_cast<void*>(const_cast< WidgetPdfDocument*>(this));
    return QWidget::qt_metacast(_clname);
}

int WidgetPdfDocument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
