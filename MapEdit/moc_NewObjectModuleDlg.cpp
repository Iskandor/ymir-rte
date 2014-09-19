/****************************************************************************
** Meta object code from reading C++ file 'NewObjectModuleDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Forms/NewObjectModuleDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NewObjectModuleDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewObjectModuleDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      29,   19,   19,   19, 0x0a,
      41,   19,   19,   19, 0x0a,
      54,   19,   19,   19, 0x0a,
      69,   19,   19,   19, 0x0a,
      82,   19,   19,   19, 0x0a,
      95,   19,   19,   19, 0x0a,
     114,  110,   19,   19, 0x0a,
     131,  110,   19,   19, 0x0a,
     149,  110,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NewObjectModuleDlg[] = {
    "NewObjectModuleDlg\0\0accept()\0addObject()\0"
    "editObject()\0removeObject()\0saveObject()\0"
    "chooseFile()\0imageOnclick()\0val\0"
    "ChangeClass(int)\0SizeXChanged(int)\0"
    "SizeYChanged(int)\0"
};

void NewObjectModuleDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NewObjectModuleDlg *_t = static_cast<NewObjectModuleDlg *>(_o);
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->addObject(); break;
        case 2: _t->editObject(); break;
        case 3: _t->removeObject(); break;
        case 4: _t->saveObject(); break;
        case 5: _t->chooseFile(); break;
        case 6: _t->imageOnclick(); break;
        case 7: _t->ChangeClass((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->SizeXChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->SizeYChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NewObjectModuleDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NewObjectModuleDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewObjectModuleDlg,
      qt_meta_data_NewObjectModuleDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewObjectModuleDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewObjectModuleDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewObjectModuleDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewObjectModuleDlg))
        return static_cast<void*>(const_cast< NewObjectModuleDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewObjectModuleDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
