#ifndef _______________displayzzPLAYBCNODE___H1INV
#define _______________displayzzPLAYBCNODE___H1INV
#include "broadcaster.h"



#include "logging.h"
#include "listenerBuffered1Thread.h"
#include "DBH.h"
#include "USER_id.h"
#include "IProgress.h"
#include "tools_mt.h"
#include <map>


#include "Real.h"

#include "Events/invoice/GetInvoice.h"
#include "Events/invoice/MakeInvoice.h"
#include "Events/DFS/Referrer/ToplinkDeliver.h"
#include "Events/System/Net/rpc/IncomingOnAcceptor.h"
#include "Events/System/Run/startService.h"
#include "Events/System/timer/TickTimer.h"
#include "Events/Tools/telnet/CommandEntered.h"
#include "Events/Tools/webHandler/RequestIncoming.h"
#include "Events/System/Error/Error.h"

#include "version_mega.h"
#define INVOICE_DBNAME "invoice"
#define TBL_INVOICE "tbl_invoice2"
namespace IMInvoicer
{

    class Service:
        public UnknownBase,
        public ListenerBuffered1Thread,
        public Broadcaster,
        public DBH_feature
    {
        bool on_startService(const systemEvent::startService*);
        bool handleEvent(const REF_getter<Event::Base>& e);



        Service(const SERVICE_id&, const std::string&  nm, IInstance *ins);
        ~Service();


        bool on_CommandEntered(const telnetEvent::CommandEntered*);

    public:
        void deinit()
        {
            ListenerBuffered1Thread::deinit();
        }

        static UnknownBase* construct(const SERVICE_id& id, const std::string&  nm,IInstance* obj)
        {
            return new Service(id,nm,obj);
        }
        bool on_RequestIncoming(const webHandlerEvent::RequestIncoming* e);



        bool on_ToplinkDeliverREQ(const dfsReferrerEvent::ToplinkDeliverREQ* e_toplink);
        bool on_MakeInvoiceREQ(const invoiceEvent::MakeInvoiceREQ* E, const route_t& toplinkRoute);
        bool on_GetInvoiceREQ(const invoiceEvent::GetInvoiceREQ* e, const route_t& toplinkRoute);


    };

}
#endif

