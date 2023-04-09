/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../blockchain_app/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[489];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "onTimer"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 9), // "connected"
QT_MOC_LITERAL(4, 30, 12), // "disconnected"
QT_MOC_LITERAL(5, 43, 14), // "connect_failed"
QT_MOC_LITERAL(6, 58, 16), // "onMakeInvoiceRSP"
QT_MOC_LITERAL(7, 75, 35), // "const invoiceEvent::MakeInvoi..."
QT_MOC_LITERAL(8, 111, 15), // "onGetInvoiceRSP"
QT_MOC_LITERAL(9, 127, 34), // "const invoiceEvent::GetInvoic..."
QT_MOC_LITERAL(10, 162, 17), // "onPublishBlockRSP"
QT_MOC_LITERAL(11, 180, 39), // "const blockchainEvent::Publis..."
QT_MOC_LITERAL(12, 220, 17), // "onPaymentReceived"
QT_MOC_LITERAL(13, 238, 11), // "std::string"
QT_MOC_LITERAL(14, 250, 5), // "block"
QT_MOC_LITERAL(15, 256, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(16, 284, 5), // "index"
QT_MOC_LITERAL(17, 290, 41), // "on_comboBox_keystores_current..."
QT_MOC_LITERAL(18, 332, 35), // "on_pushButton_createAccount_c..."
QT_MOC_LITERAL(19, 368, 36), // "on_pushButton_invoice_create_..."
QT_MOC_LITERAL(20, 405, 31), // "on_pushButtonGetInvoice_clicked"
QT_MOC_LITERAL(21, 437, 24), // "on_pushButtonPay_clicked"
QT_MOC_LITERAL(22, 462, 26) // "on_pushButton_scan_clicked"

    },
    "MainWindow\0onTimer\0\0connected\0"
    "disconnected\0connect_failed\0"
    "onMakeInvoiceRSP\0const invoiceEvent::MakeInvoiceRSP*\0"
    "onGetInvoiceRSP\0const invoiceEvent::GetInvoiceRSP*\0"
    "onPublishBlockRSP\0"
    "const blockchainEvent::PublishBlockRSP*\0"
    "onPaymentReceived\0std::string\0block\0"
    "on_tabWidget_currentChanged\0index\0"
    "on_comboBox_keystores_currentIndexChanged\0"
    "on_pushButton_createAccount_clicked\0"
    "on_pushButton_invoice_create_clicked\0"
    "on_pushButtonGetInvoice_clicked\0"
    "on_pushButtonPay_clicked\0"
    "on_pushButton_scan_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    1,   93,    2, 0x08 /* Private */,
       8,    1,   96,    2, 0x08 /* Private */,
      10,    1,   99,    2, 0x08 /* Private */,
      12,    1,  102,    2, 0x08 /* Private */,
      15,    1,  105,    2, 0x08 /* Private */,
      17,    1,  108,    2, 0x08 /* Private */,
      18,    0,  111,    2, 0x08 /* Private */,
      19,    0,  112,    2, 0x08 /* Private */,
      20,    0,  113,    2, 0x08 /* Private */,
      21,    0,  114,    2, 0x08 /* Private */,
      22,    0,  115,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTimer(); break;
        case 1: _t->connected(); break;
        case 2: _t->disconnected(); break;
        case 3: _t->connect_failed(); break;
        case 4: _t->onMakeInvoiceRSP((*reinterpret_cast< const invoiceEvent::MakeInvoiceRSP*(*)>(_a[1]))); break;
        case 5: _t->onGetInvoiceRSP((*reinterpret_cast< const invoiceEvent::GetInvoiceRSP*(*)>(_a[1]))); break;
        case 6: _t->onPublishBlockRSP((*reinterpret_cast< const blockchainEvent::PublishBlockRSP*(*)>(_a[1]))); break;
        case 7: _t->onPaymentReceived((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 8: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_comboBox_keystores_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_pushButton_createAccount_clicked(); break;
        case 11: _t->on_pushButton_invoice_create_clicked(); break;
        case 12: _t->on_pushButtonGetInvoice_clicked(); break;
        case 13: _t->on_pushButtonPay_clicked(); break;
        case 14: _t->on_pushButton_scan_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
