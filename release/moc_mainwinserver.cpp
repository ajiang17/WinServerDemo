/****************************************************************************
** Meta object code from reading C++ file 'mainwinserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwinserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwinserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWinServer_t {
    QByteArrayData data[13];
    char stringdata0[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWinServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWinServer_t qt_meta_stringdata_MainWinServer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MainWinServer"
QT_MOC_LITERAL(1, 14, 16), // "starSerialThread"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 12), // "UpdateSerial"
QT_MOC_LITERAL(4, 45, 13), // "AddThreadList"
QT_MOC_LITERAL(5, 59, 13), // "SubThreadList"
QT_MOC_LITERAL(6, 73, 15), // "timerScanSerial"
QT_MOC_LITERAL(7, 89, 20), // "sendtoPrinterMessage"
QT_MOC_LITERAL(8, 110, 11), // "readMessage"
QT_MOC_LITERAL(9, 122, 20), // "slotconnectedsuccess"
QT_MOC_LITERAL(10, 143, 12), // "displayError"
QT_MOC_LITERAL(11, 156, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(12, 185, 16) // "slotupdateserver"

    },
    "MainWinServer\0starSerialThread\0\0"
    "UpdateSerial\0AddThreadList\0SubThreadList\0"
    "timerScanSerial\0sendtoPrinterMessage\0"
    "readMessage\0slotconnectedsuccess\0"
    "displayError\0QAbstractSocket::SocketError\0"
    "slotupdateserver"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWinServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    2,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   60,    2, 0x08 /* Private */,
       7,    0,   61,    2, 0x08 /* Private */,
       8,    0,   62,    2, 0x08 /* Private */,
       9,    0,   63,    2, 0x08 /* Private */,
      10,    1,   64,    2, 0x08 /* Private */,
      12,    2,   67,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList, QMetaType::QStringList,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,

       0        // eod
};

void MainWinServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWinServer *_t = static_cast<MainWinServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->starSerialThread(); break;
        case 1: _t->UpdateSerial((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 2: _t->timerScanSerial(); break;
        case 3: _t->sendtoPrinterMessage(); break;
        case 4: _t->readMessage(); break;
        case 5: _t->slotconnectedsuccess(); break;
        case 6: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 7: _t->slotupdateserver((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MainWinServer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWinServer::starSerialThread)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWinServer::*_t)(QStringList , QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWinServer::UpdateSerial)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MainWinServer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWinServer.data,
      qt_meta_data_MainWinServer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWinServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWinServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWinServer.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWinServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MainWinServer::starSerialThread()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWinServer::UpdateSerial(QStringList _t1, QStringList _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
