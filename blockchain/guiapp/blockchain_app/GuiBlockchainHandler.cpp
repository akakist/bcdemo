#include "GuiBlockchainHandler.h"
#include "tools_mt.h"

GuiBlockChainHandler::GuiBlockChainHandler(IInstance* ins): BlockchainHandler(ins)
{
}
void GuiBlockChainHandler::signal_connect_failed()
{
    emit connect_failed();
}
void GuiBlockChainHandler::signal_authorized()
{

}

void GuiBlockChainHandler::signal_connected()
{

    isConnected=true;
    emit connected();
}
void GuiBlockChainHandler::signal_disconnected()
{
    isConnected=false;
    emit disconnected();
}

/*bool GuiBlockChainHandler::on_JsonRSP(const jsonRefEvent::JsonRSP*e)
{
    if(e->errcode==0)
    {

    }
    emit onJsonRSP(e->errcode,e->action,e->json,e->binData);
    return true;
}*/
bool GuiBlockChainHandler::post_MakeInvoiceRSP(const invoiceEvent::MakeInvoiceRSP*e)
{
    emit onMakeInvoiceRSP(e);
    return true;
}
bool GuiBlockChainHandler::on_GetInvoiceRSP(const invoiceEvent::GetInvoiceRSP*e)
{
    emit onGetInvoiceRSP(e);
    return true;
}
bool GuiBlockChainHandler::on_PublishBlockRSP(const blockchainEvent::PublishBlockRSP *e)
{
    emit onPublishBlockRSP(e);
    return true;
}
void GuiBlockChainHandler::on_blockReceived(const std::string &payment)
{
    emit onPaymentReceived(payment);
}
bool GuiBlockChainHandler::on_GetAmountRSP(const blockchainEvent::GetAmountRSP*)
{
    return false;
}
