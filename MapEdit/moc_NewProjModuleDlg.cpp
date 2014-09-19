/****************************************************************************
** Meta object code from reading C++ file 'NewProjModuleDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "NewProjModuleDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NewProjModuleDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewProjModuleDlg[] = {

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
      39,   17,   17,   17, 0x0a,
      52,   17,   17,   17, 0x0a,
      67,   17,   17,   17, 0x0a,
      80,   17,   17,   17, 0x0a,
      93,   17,   17,   17, 0x0a,
     112,  108,   17,   17, 0x0a,
     130,  108,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NewProjModuleDlg[] = {
    "NewProjModuleDlg\0\0accept()\0addObject()\0"
    "editObject()\0removeObject()\0saveObject()\0"
    "chooseFile()\0imageOnclick()\0val\0"
    "SizeXChanged(int)\0SizeYChanged(int)\0"
};

void NewProjModuleDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NewProjModuleDlg *_t = static_cast<NewProjModuleDlg *>(_o);
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->addObject(); break;
        case 2: _t->editObject(); break;
        case 3: _t->removeObject(); break;
        case 4: _t->saveObject(); break;
        case 5: _t->chooseFile(); break;
        case 6: _t->imageOnclick(); break;
        case 7: _t->SizeXChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->SizeYChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NewProjModuleDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NewProjModuleDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewProjModuleDlg,
      qt_meta_data_NewProjModuleDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewProjModuleDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewProjModuleDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewProjModuleDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewProjModuleDlg))
        return static_cast<void*>(const_cast< NewProjModuleDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewProjModuleDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
