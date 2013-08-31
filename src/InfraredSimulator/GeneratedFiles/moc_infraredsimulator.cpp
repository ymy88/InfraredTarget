/****************************************************************************
** Meta object code from reading C++ file 'infraredsimulator.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Stdafx.h"
#include "infraredsimulator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'infraredsimulator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InfraredSimulator[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,
      35,   18,   18,   18, 0x0a,
      42,   18,   18,   18, 0x0a,
      47,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_InfraredSimulator[] = {
    "InfraredSimulator\0\0showParameter()\0"
    "back()\0go()\0speed()\0"
};

void InfraredSimulator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InfraredSimulator *_t = static_cast<InfraredSimulator *>(_o);
        switch (_id) {
        case 0: _t->showParameter(); break;
        case 1: _t->back(); break;
        case 2: _t->go(); break;
        case 3: _t->speed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData InfraredSimulator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InfraredSimulator::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_InfraredSimulator,
      qt_meta_data_InfraredSimulator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InfraredSimulator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InfraredSimulator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InfraredSimulator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InfraredSimulator))
        return static_cast<void*>(const_cast< InfraredSimulator*>(this));
    if (!strcmp(_clname, "EventHandler"))
        return static_cast< EventHandler*>(const_cast< InfraredSimulator*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int InfraredSimulator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
