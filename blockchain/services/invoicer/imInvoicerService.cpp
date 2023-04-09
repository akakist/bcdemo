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
#include "imInvoicerService.h"
#include "events_imInvoicerService.hpp"


bool IMInvoicer::Service::on_startService(const systemEvent::startService*)
{
    MUTEX_INSPECTOR;
    auto d=getDB();
    st_TRANSACTION tr(d);


    d->execSimple((QUERY)"CREATE TABLE  IF NOT EXISTS " TBL_INVOICE " ("
                  "id  BIGINT AUTO_INCREMENT,"
                  "rnd INTEGER,"
                  "data blob,"
                  "PRIMARY KEY(id)"
                  ")"

                 );

    tr.commit();

    return true;
}


bool IMInvoicer::Service::handleEvent(const REF_getter<Event::Base>& e)
{
    XTRY;
    try {
        MUTEX_INSPECTOR;
        auto& ID=e->id;
        if(timerEventEnum::TickTimer==ID)
        {
//            const timerEvent::TickTimer*ev=static_cast<const timerEvent::TickTimer*>(e.operator ->());
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

    } catch(std::exception &e)
    {
        logErr2("IMInvoicer std::exception  %s",e.what());
    }
    XPASS;
    return false;
}


bool IMInvoicer::Service::on_CommandEntered(const telnetEvent::CommandEntered*)
{

    return true;
}

IMInvoicer::Service::~Service()
{
}


IMInvoicer::Service::Service(const SERVICE_id& id, const std::string& nm,IInstance* ins):
    UnknownBase(nm),
    ListenerBuffered1Thread(this,nm,ins->getConfig(),id,ins),
    Broadcaster(ins),
    DBH_feature(ins)
{
}

bool IMInvoicer::Service::on_RequestIncoming(const webHandlerEvent::RequestIncoming* )
{
    return true;
}
void registerIMInvoicerService(const char* pn)
{
    MUTEX_INSPECTOR;

    XTRY;
    if(pn)
    {
        iUtils->registerPlugingInfo(COREVERSION,pn,IUtils::PLUGIN_TYPE_SERVICE,ServiceEnum::IMInvoicer,"IMInvoicer",getEvents_imInvoicerService());
    }
    else
    {
        iUtils->registerService(COREVERSION,ServiceEnum::IMInvoicer,IMInvoicer::Service::construct,"IMInvoicer");
        regEvents_imInvoicerService();
    }
    XPASS;
}








bool IMInvoicer::Service::on_ToplinkDeliverREQ(const dfsReferrerEvent::ToplinkDeliverREQ* e_toplink)
{

    MUTEX_INSPECTOR;
    REF_getter<Event::Base> z=e_toplink->getEvent();
    if(!z.valid())
        return false;
    if(invoiceEventEnum::MakeInvoiceREQ==z->id)
    {
        const invoiceEvent::MakeInvoiceREQ * E=(const invoiceEvent::MakeInvoiceREQ *)z.operator ->();
        return on_MakeInvoiceREQ(E,e_toplink->route);

    }
    if(invoiceEventEnum::GetInvoiceREQ==z->id)
    {
        const invoiceEvent::GetInvoiceREQ * E=(const invoiceEvent::GetInvoiceREQ *)z.operator ->();
        return on_GetInvoiceREQ(E,e_toplink->route);

    }
    logErr2("unhandler ev %s",z->dump().toStyledString().c_str());
    return false;
}
bool IMInvoicer::Service::on_GetInvoiceREQ(const invoiceEvent::GetInvoiceREQ* e, const route_t& toplinkRoute)
{
    logErr2("@@@ %s %s %s",__PRETTY_FUNCTION__,std::to_string(e->invId).c_str(),std::to_string(e->rnd).c_str());
    try {


        auto d=getDB();
        std::vector<std::string> v=d->select_1_column((QUERY)"select data from ? where id=? and rnd=?"
                                   <<TBL_INVOICE
                                   <<e->invId
                                   <<e->rnd);

        for(auto& z: v)
        {
            inBuffer in(z);
            blockchainData::Invoice inv;
            in>>inv;
            REF_getter<invoiceEvent::GetInvoiceRSP> z2=new invoiceEvent::GetInvoiceRSP(0,"",e->invId,inv);
            passEvent(new dfsReferrerEvent::ToplinkDeliverRSP(
                          z2.operator ->(),poppedFrontRoute(toplinkRoute)));
            return true;

        }
        blockchainData::Invoice inv;
        passEvent(new dfsReferrerEvent::ToplinkDeliverRSP(
                      new invoiceEvent::GetInvoiceRSP(1,"Invoice not found",e->invId,inv),
                      poppedFrontRoute(toplinkRoute)));


    }
    catch(std::exception& err)
    {
        blockchainData::Invoice inv;
        passEvent(new dfsReferrerEvent::ToplinkDeliverRSP(
                      new invoiceEvent::GetInvoiceRSP(1,err.what(),e->invId,inv),
                      poppedFrontRoute(toplinkRoute)));

    }
    return true;

}
bool IMInvoicer::Service::on_MakeInvoiceREQ(const invoiceEvent::MakeInvoiceREQ* E, const route_t& toplinkRoute)
{
    try {
        I_ssl *ssl=(I_ssl*)iUtils->queryIface(Ifaces::SSL);
        int rnd=std::abs(ssl->rand_int()%10000);
        outBuffer o;
        o<<E->invoice;

        auto d=getDB();
        st_TRANSACTION tr(d);

        d->execSimple((QUERY)"insert into ? (rnd,data) values (?,x'?')"
                      <<TBL_INVOICE
                      <<rnd
                      <<iUtils->bin2hex(o.asString()->asString()));
        auto newId=d->select_1_int_orThrow((QUERY)"select last_insert_id()");
        if(newId==0)
            throw CommonError("if(newId.size()==0)");

        tr.commit();

        passEvent(new dfsReferrerEvent::ToplinkDeliverRSP(
                      new invoiceEvent::MakeInvoiceRSP(0,"",newId,rnd,E->invoice),
                      poppedFrontRoute(toplinkRoute)));
    }
    catch(std::exception& e)
    {
        passEvent(new dfsReferrerEvent::ToplinkDeliverRSP(
                      new invoiceEvent::MakeInvoiceRSP(1,e.what(),0,0,E->invoice),
                      poppedFrontRoute(toplinkRoute)));

    }
    return true;
}
