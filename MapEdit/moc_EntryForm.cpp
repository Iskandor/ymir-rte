/****************************************************************************
** Meta object code from reading C++ file 'EntryForm.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Forms/EntryForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EntryForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EntryForm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      20,   10,   10,   10, 0x0a,
      30,   10,   10,   10, 0x0a,
      40,   10,   10,   10, 0x0a,
      52,   10,   10,   10, 0x0a,
      59,   10,   10,   10, 0x0a,
      76,   10,   10,   10, 0x0a,
      93,   10,   10,   10, 0x0a,
     112,   10,   10,   10, 0x0a,
     135,   10,   10,   10, 0x0a,
     156,   10,   10,   10, 0x0a,
     173,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EntryForm[] = {
    "EntryForm\0\0newMap()\0openMap()\0saveMap()\0"
    "saveMapAs()\0exit()\0openUnitModule()\0"
    "openTileModule()\0openObjectModule()\0"
    "openProjectileModule()\0openModifierModule()\0"
    "moveCameraX(int)\0moveCameraY(int)\0"
};

void EntryForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EntryForm *_t = static_cast<EntryForm *>(_o);
        switch (_id) {
        case 0: _t->newMap(); break;
        case 1: _t->openMap(); break;
        case 2: _t->saveMap(); break;
        case 3: _t->saveMapAs(); break;
        case 4: _t->exit(); break;
        case 5: _t->openUnitModule(); break;
        case 6: _t->openTileModule(); break;
        case 7: _t->openObjectModule(); break;
        case 8: _t->openProjectileModule(); break;
        case 9: _t->openModifierModule(); break;
        case 10: _t->moveCameraX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->moveCameraY((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData EntryForm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject EntryForm::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_EntryForm,
      qt_meta_data_EntryForm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EntryForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EntryForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EntryForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EntryForm))
        return static_cast<void*>(const_cast< EntryForm*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int EntryForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
