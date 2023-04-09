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
#include "__crc64.h"

#include <sys/stat.h>
#include "Real.h"
#define USE_DB 1

#include "Events/RegisterDownlink.h"
#include "../../Events/blockchain/BlockchainChanged.h"
#include "../../Events/blockchain/GetAmount.h"
#include "../../Events/blockchain/GetBlockForSingleIdForClient.h"
#include "../../Events/blockchain/GetBlocksSinceId.h"
#include "../../Events/blockchain/PublishBlock.h"
#include "../../Events/blockchain/SubscribeClientNotifications.h"
#include "Events/DFS/Referrer/NotifyReferrer.h"
#include "Events/DFS/Referrer/SubscribeNotifications.h"
#include "Events/DFS/Referrer/ToplinkDeliver.h"
#include "Events/System/Net/rpc/IncomingOnAcceptor.h"
#include "Events/System/Net/rpc/IncomingOnConnector.h"
#include "Events/System/Run/startService.h"
#include "Events/System/timer/TickTimer.h"
#include "Events/Tools/telnet/CommandEntered.h"
#include "Events/Tools/webHandler/RequestIncoming.h"

#include "st_FILE.h"

#include "version_mega.h"
#define BCNODE_DBNAME "bcnode"
#define db_postfix "0"
#define TBL_BLOCK ("tbl_block" db_postfix)

#define PACK_LIMIT 1000

struct downlinkClientItem: public Refcountable
{
    downlinkClientItem():erased(false) {}
    uint64_t crc;
    SOCKET_id socketId;
    SHA1_id publicKey;
    route_t backRoute;
    bool erased;
};

struct BlockchainAccountStat
{
    RSA_id rsaPublicKey;
    int64_t createdate;
    std::map<SHA1_id,Rational> amounts;
    std::map<SHA1_id,Rational> credit_limits;
    BlockchainAccountStat(){}
};
struct BlockchainStats
{
    int64_t lastBlockId;
    std::map<SHA1_id, BlockchainAccountStat> accounts;
    std::set<std::string> paidInvoices;
    BlockchainStats():lastBlockId(0){}

    int64_t processBlock(const std::string& fullBlock, std::set<SHA1_id> *interestedAccounts, int64_t *blockIdFromDB);
    bool verifySign(blockchainData::Payment &payment);
    bool verifySign(blockchainData::SetCreditLimit &cl);

    void updateAmounts(blockchainData::Payment& ps);
    void updateAmount(const SHA1_id& creditor_pubkeySHA1, const SHA1_id& emitent_pubkeySHA1, double amount);



};
namespace BlockchainNode
{

    class Service:
        public UnknownBase,
        public ListenerBuffered1Thread,
        public Broadcaster
        #ifdef USE_DB
            ,
        public DBH_feature
        #endif
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


        IInstance *instance;
        std::map<SHA1_id,std::set<route_t> > clientConsumersOnPublicKeyAkaUID;
        BlockchainStats blockchainStats;


        void readBlockchain(st_TRANSACTION* tr);


        bool on_NotifyReferrerDownlinkDisconnected(const dfsReferrerEvent::NotifyReferrerDownlinkDisconnected*e);
        bool on_NotifyReferrerUplinkIsDisconnected(const dfsReferrerEvent::NotifyReferrerUplinkIsDisconnected*e);


        bool on_NotifyReferrerUplinkIsConnected(DBH *dbh, const dfsReferrerEvent::NotifyReferrerUplinkIsConnected*e);

        bool on_BlockchainChanged(DBH *dbh);
        bool on_GetBlocksSinceIdREQ(DBH *dbh, const blockchainEvent::GetBlocksSinceIdREQ*e);
        bool on_GetBlocksSinceIdRSP(st_TRANSACTION *tr, const blockchainEvent::GetBlocksSinceIdRSP*e);

        bool on_PublishBlockREQ(const blockchainEvent::PublishBlockREQ* e);

        bool on_ToplinkDeliverREQ(dfsReferrerEvent::ToplinkDeliverREQ*);
        bool on_GetBlockForSingleIdForClientREQ(DBH *dbh, const blockchainEvent::GetBlockForSingleIdForClientREQ*e);
        bool on_GetAmountREQ(const blockchainEvent::GetAmountREQ*e);



        void addBlocks(st_TRANSACTION* tr, const std::vector<std::string> &block);

        void initDB(st_TRANSACTION *tr);

        void updateAmount(st_TRANSACTION *tr, const SHA1_id& creditor_pubkeySHA1, const SHA1_id& emitent_pubkeySHA1, double amount);
        int64_t getMaxIdFromTblBlock(DBH *dbh);

        std::string prepareBlockForTransition(DBH *dbh, int64_t blockId);


        std::set<msockaddr_in> uplink;
        std::map<SOCKET_id,route_t> downlinks;

        bool uplinkIsNotified;



        void notifyDownlinks(int64_t blockId_final,const std::set<SHA1_id>&interestedAccount);


        bool isRoot;
        std::string root_rsa_private_key;

        bool readyToServe;
    };



}
#endif

