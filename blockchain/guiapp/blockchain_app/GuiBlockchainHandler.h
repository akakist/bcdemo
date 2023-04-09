#ifndef GUIDSHANDLER_H
#define GUIDSHANDLER_H
#include "blockchainHandler.h"
#include <QObject>
class GuiBlockChainHandler: public QObject, public BlockchainHandler
{
    Q_OBJECT
public:
    GuiBlockChainHandler(IInstance *ins);
    void signal_connected();
    void signal_connect_failed();
    void signal_disconnected();
    void signal_authorized();

    //bool on_JsonRSP(const jsonRefEvent::JsonRSP*);

//    bool on_MakeInvoiceRSP(const invoiceEvent::MakeInvoiceRSP*);
    bool post_MakeInvoiceRSP(const invoiceEvent::MakeInvoiceRSP*);

    bool on_GetInvoiceRSP(const invoiceEvent::GetInvoiceRSP*);
    bool on_PublishBlockRSP(const blockchainEvent::PublishBlockRSP *);
    void on_blockReceived(const std::string & payment);
    bool on_GetAmountRSP(const blockchainEvent::GetAmountRSP*);

signals:
    void connected();
    void connect_failed();
    void disconnected();
    void onJsonRSP(int errcode, std::string action, std::string json,std::string binData);

    void onMakeInvoiceRSP(const invoiceEvent::MakeInvoiceRSP*);
    void onGetInvoiceRSP(const invoiceEvent::GetInvoiceRSP*);
    void onPublishBlockRSP(const blockchainEvent::PublishBlockRSP*);

    void onPaymentReceived(std::string payment);


};

#endif // GUIDSHANDLER_H
