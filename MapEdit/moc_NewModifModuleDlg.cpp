/****************************************************************************
** Meta object code from reading C++ file 'NewModifModuleDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "NewModifModuleDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NewModifModuleDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewModifModuleDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,
      28,   18,   18,   18, 0x0a,
      40,   18,   18,   18, 0x0a,
      53,   18,   18,   18, 0x0a,
      68,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NewModifModuleDlg[] = {
    "NewModifModuleDlg\0\0accept()\0addObject()\0"
    "editObject()\0removeObject()\0saveObject()\0"
};

void NewModifModuleDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NewModifModuleDlg *_t = static_cast<NewModifModuleDlg *>(_o);
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->addObject(); break;
        case 2: _t->editObject(); break;
        case 3: _t->removeObject(); break;
        case 4: _t->saveObject(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData NewModifModuleDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NewModifModuleDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewModifModuleDlg,
      qt_meta_data_NewModifModuleDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewModifModuleDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewModifModuleDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewModifModuleDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewModifModuleDlg))
        return static_cast<void*>(const_cast< NewModifModuleDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewModifModuleDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
