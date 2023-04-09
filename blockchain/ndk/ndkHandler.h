#ifndef ______________________NDKHANDLER_H
#define ______________________NDKHANDLER_H

#include "jsonHandler.h"
#include "blockchainHandler.h"
#include "../common/blockchainHandler.h"
#include "../Events/invoice/MakeInvoice.h"

class NDKHandler: public BlockchainHandler
{
public:
    NDKHandler(IInstance *ins);
    void signal_connected();
    void signal_disconnected();
    void signal_connect_failed();
    void signalUi(const std::string &opcode);
    void signal_authorized();
    bool post_MakeInvoiceRSP(const invoiceEvent::MakeInvoiceRSP*){return false;}




};

#endif // NDKHANDLER_H
