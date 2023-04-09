#include "corelib/mutexInspector.h"
#include "ISSL.h"
#include <time.h>
#include <time.h>

#include "tools_mt.h"
#include "st_FILE.h"

#include <map>
#include "js_utils.h"
#include "st_rsa.h"
#include "configDB.h"
#include "blockchainTopService.h"
#include "events_blockchainTopService.hpp"


bool BlockchainTop::Service::on_startService(const systemEvent::startService*)
{
    MUTEX_INSPECTOR;

    return true;
}


bool BlockchainTop::Service::handleEvent(const REF_getter<Event::Base>& e)
{
    XTRY;
    try {
        MUTEX_INSPECTOR;
        auto& ID=e->id;
        if(timerEventEnum::TickTimer==ID)
        {
            const timerEvent::TickTimer*ev=static_cast<const timerEvent::TickTimer*>(e.operator ->());
            return true;
        }
        if(webHandlerEventEnum::RequestIncoming==ID)
            return on_RequestIncoming((const webHandlerEvent::RequestIncoming*)e.operator->());
        if(telnetEventEnum::CommandEntered==ID)
            return on_CommandEntered((const telnetEvent::CommandEntered*)e.operator->());
        if(systemEventEnum::startService==ID)
            return on_startService((const systemEvent::startService*)e.operator->());
        if(rpcEventEnum::IncomingOnAcceptor==ID)
        {
            const rpcEvent::IncomingOnAcceptor*ev=static_cast<const rpcEvent::IncomingOnAcceptor*>(e.operator ->());
            auto &IDA=ev->e->id;
            if(dfsReferrerEventEnum::ToplinkDeliverREQ==IDA)
                return on_ToplinkDeliverREQ((const dfsReferrerEvent::ToplinkDeliverREQ*)ev->e.operator->());
            return false;
        }
        if(dfsReferrerEventEnum::ToplinkDeliverREQ==ID)
            return on_ToplinkDeliverREQ((const dfsReferrerEvent::ToplinkDeliverREQ*)e.operator->());
        if(dfsReferrerEventEnum::ToplinkDeliverRSP==ID)
        {
            passEvent(e);
            return true;
        }

    } catch(std::exception &e)
    {
        logErr2("BlockchainTop std::exception  %s",e.what());
    }
    XPASS;
    return false;
}


bool BlockchainTop::Service::on_CommandEntered(const telnetEvent::CommandEntered*)
{
    return true;
}

BlockchainTop::Service::~Service()
{
}


BlockchainTop::Service::Service(const SERVICE_id& id, const std::string& nm,IInstance* ins):
    UnknownBase(nm),
    ListenerBuffered1Thread(this,nm,ins->getConfig(),id,ins),
    Broadcaster(ins)
{

}

bool BlockchainTop::Service::on_RequestIncoming(const webHandlerEvent::RequestIncoming* )
{
    return true;
}
void registerBlockchainTopService(const char* pn)
{
    MUTEX_INSPECTOR;

    XTRY;
    if(pn)
    {
        iUtils->registerPlugingInfo(COREVERSION,pn,IUtils::PLUGIN_TYPE_SERVICE,ServiceEnum::BlockchainTop,"BlockchainTop",getEvents_blockchainTopService());
    }
    else
    {
        iUtils->registerService(COREVERSION,ServiceEnum::BlockchainTop,BlockchainTop::Service::construct,"BlockchainTop");
        regEvents_blockchainTopService();
    }
    XPASS;
}









bool BlockchainTop::Service::on_ToplinkDeliverREQ(const dfsReferrerEvent::ToplinkDeliverREQ* e_toplink)
{
    MUTEX_INSPECTOR;
    REF_getter<Event::Base> z=e_toplink->getEvent();
    if(!z.valid())
        return false;
    z->route=e_toplink->route;
    sendEvent(ServiceEnum::BlockchainNode,e_toplink);
    return true;
    logErr2("unhandler ev %s",z->dump().toStyledString().c_str());
    return false;
}
