/****************************************************************************
** Meta object code from reading C++ file 'NewTileModuleDlg.h'
**
** Created: Fri Aug 22 19:41:21 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Forms/NewTileModuleDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NewTileModuleDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewTileModuleDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
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

       0        // eod
};

static const char qt_meta_stringdata_NewTileModuleDlg[] = {
    "NewTileModuleDlg\0\0accept()\0addTile()\0"
    "editTile()\0removeTile()\0saveTile()\0"
    "chooseFile()\0"
};

void NewTileModuleDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NewTileModuleDlg *_t = static_cast<NewTileModuleDlg *>(_o);
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->addTile(); break;
        case 2: _t->editTile(); break;
        case 3: _t->removeTile(); break;
        case 4: _t->saveTile(); break;
        case 5: _t->chooseFile(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData NewTileModuleDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NewTileModuleDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewTileModuleDlg,
      qt_meta_data_NewTileModuleDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewTileModuleDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewTileModuleDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewTileModuleDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewTileModuleDlg))
        return static_cast<void*>(const_cast< NewTileModuleDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewTileModuleDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
