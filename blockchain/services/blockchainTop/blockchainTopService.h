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
#include "Events/System/Run/startService.h"
#include "Events/Tools/telnet/CommandEntered.h"
#include "Events/Tools/webHandler/RequestIncoming.h"
#include "Events/DFS/Referrer/ToplinkDeliver.h"
#include "../../Events/blockchain/PublishBlock.h"
#include "Events/System/Net/rpc/IncomingOnAcceptor.h"
#include "Events/System/timer/TickTimer.h"


#include "version_mega.h"
#define TOP_DBNAME "top_db"
namespace BlockchainTop
{

    class Service:
        public UnknownBase,
        public ListenerBuffered1Thread,
        public Broadcaster
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

    };

}
#endif

