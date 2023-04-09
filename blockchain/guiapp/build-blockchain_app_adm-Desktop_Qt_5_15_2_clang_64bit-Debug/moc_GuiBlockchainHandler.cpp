/****************************************************************************
** Meta object code from reading C++ file 'GuiBlockchainHandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../blockchain_app/GuiBlockchainHandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GuiBlockchainHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GuiBlockChainHandler_t {
    QByteArrayData data[19];
    char stringdata0[298];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GuiBlockChainHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GuiBlockChainHandler_t qt_meta_stringdata_GuiBlockChainHandler = {
    {
QT_MOC_LITERAL(0, 0, 20), // "GuiBlockChainHandler"
QT_MOC_LITERAL(1, 21, 9), // "connected"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 14), // "connect_failed"
QT_MOC_LITERAL(4, 47, 12), // "disconnected"
QT_MOC_LITERAL(5, 60, 9), // "onJsonRSP"
QT_MOC_LITERAL(6, 70, 7), // "errcode"
QT_MOC_LITERAL(7, 78, 11), // "std::string"
QT_MOC_LITERAL(8, 90, 6), // "action"
QT_MOC_LITERAL(9, 97, 4), // "json"
QT_MOC_LITERAL(10, 102, 7), // "binData"
QT_MOC_LITERAL(11, 110, 16), // "onMakeInvoiceRSP"
QT_MOC_LITERAL(12, 127, 35), // "const invoiceEvent::MakeInvoi..."
QT_MOC_LITERAL(13, 163, 15), // "onGetInvoiceRSP"
QT_MOC_LITERAL(14, 179, 34), // "const invoiceEvent::GetInvoic..."
QT_MOC_LITERAL(15, 214, 17), // "onPublishBlockRSP"
QT_MOC_LITERAL(16, 232, 39), // "const blockchainEvent::Publis..."
QT_MOC_LITERAL(17, 272, 17), // "onPaymentReceived"
QT_MOC_LITERAL(18, 290, 7) // "payment"

    },
    "GuiBlockChainHandler\0connected\0\0"
    "connect_failed\0disconnected\0onJsonRSP\0"
    "errcode\0std::string\0action\0json\0binData\0"
    "onMakeInvoiceRSP\0const invoiceEvent::MakeInvoiceRSP*\0"
    "onGetInvoiceRSP\0const invoiceEvent::GetInvoiceRSP*\0"
    "onPublishBlockRSP\0"
    "const blockchainEvent::PublishBlockRSP*\0"
    "onPaymentReceived\0payment"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GuiBlockChainHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    4,   57,    2, 0x06 /* Public */,
      11,    1,   66,    2, 0x06 /* Public */,
      13,    1,   69,    2, 0x06 /* Public */,
      15,    1,   72,    2, 0x06 /* Public */,
      17,    1,   75,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7, 0x80000000 | 7, 0x80000000 | 7,    6,    8,    9,   10,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, 0x80000000 | 7,   18,

       0        // eod
};

void GuiBlockChainHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GuiBlockChainHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->connect_failed(); break;
        case 2: _t->disconnected(); break;
        case 3: _t->onJsonRSP((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3])),(*reinterpret_cast< std::string(*)>(_a[4]))); break;
        case 4: _t->onMakeInvoiceRSP((*reinterpret_cast< const invoiceEvent::MakeInvoiceRSP*(*)>(_a[1]))); break;
        case 5: _t->onGetInvoiceRSP((*reinterpret_cast< const invoiceEvent::GetInvoiceRSP*(*)>(_a[1]))); break;
        case 6: _t->onPublishBlockRSP((*reinterpret_cast< const blockchainEvent::PublishBlockRSP*(*)>(_a[1]))); break;
        case 7: _t->onPaymentReceived((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GuiBlockChainHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiBlockChainHandler::connected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GuiBlockChainHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiBlockChainHandler::connect_failed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GuiBlockChainHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiBlockChainHandler::disconnected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GuiBlockChainHandler::*)(int , std::string , std::string , std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiBlockChainHandler::onJsonRSP)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GuiBlockChainHandler::*)(const invoiceEvent::MakeInvoiceRSP * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiBlockChainHandler::onMakeInvoiceRSP)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GuiBlockChainHandler::*)(const invoiceEvent::GetInvoiceRSP * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiBlockChainHandler::onGetInvoiceRSP)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GuiBlockChainHandler::*)(const blockchainEvent::PublishBlockRSP * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiBlockChainHandler::onPublishBlockRSP)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GuiBlockChainHandler::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiBlockChainHandler::onPaymentReceived)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GuiBlockChainHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GuiBlockChainHandler.data,
    qt_meta_data_GuiBlockChainHandler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GuiBlockChainHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GuiBlockChainHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GuiBlockChainHandler.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "BlockchainHandler"))
        return static_cast< BlockchainHandler*>(this);
    return QObject::qt_metacast(_clname);
}

int GuiBlockChainHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void GuiBlockChainHandler::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GuiBlockChainHandler::connect_failed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void GuiBlockChainHandler::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GuiBlockChainHandler::onJsonRSP(int _t1, std::string _t2, std::string _t3, std::string _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GuiBlockChainHandler::onMakeInvoiceRSP(const invoiceEvent::MakeInvoiceRSP * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GuiBlockChainHandler::onGetInvoiceRSP(const invoiceEvent::GetInvoiceRSP * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GuiBlockChainHandler::onPublishBlockRSP(const blockchainEvent::PublishBlockRSP * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void GuiBlockChainHandler::onPaymentReceived(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
