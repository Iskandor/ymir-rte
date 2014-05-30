/****************************************************************************
** Meta object code from reading C++ file 'NewUnitModuleDlg.h'
**
** Created: Sat May 10 22:55:56 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Forms/NewUnitModuleDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NewUnitModuleDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewUnitModuleDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      27,   17,   17,   17, 0x0a,
      37,   17,   17,   17, 0x0a,
      48,   17,   17,   17, 0x0a,
      61,   17,   17,   17, 0x0a,
      72,   17,   17,   17, 0x0a,
      85,   17,   17,   17, 0x0a,
     104,  100,   17,   17, 0x0a,
     122,  100,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NewUnitModuleDlg[] = {
    "NewUnitModuleDlg\0\0accept()\0addUnit()\0"
    "editUnit()\0removeUnit()\0saveUnit()\0"
    "chooseFile()\0imageOnclick()\0val\0"
    "SizeXChanged(int)\0SizeYChanged(int)\0"
};

void NewUnitModuleDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NewUnitModuleDlg *_t = static_cast<NewUnitModuleDlg *>(_o);
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->addUnit(); break;
        case 2: _t->editUnit(); break;
        case 3: _t->removeUnit(); break;
        case 4: _t->saveUnit(); break;
        case 5: _t->chooseFile(); break;
        case 6: _t->imageOnclick(); break;
        case 7: _t->SizeXChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->SizeYChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NewUnitModuleDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NewUnitModuleDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewUnitModuleDlg,
      qt_meta_data_NewUnitModuleDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewUnitModuleDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewUnitModuleDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewUnitModuleDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewUnitModuleDlg))
        return static_cast<void*>(const_cast< NewUnitModuleDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewUnitModuleDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
