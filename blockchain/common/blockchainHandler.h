#ifndef ____DS_HANDLER__________h
#define ____DS_HANDLER__________h
#include "configDB.h"



#include "Events/DFS/Referrer/NotifyReferrer.h"
#include "Events/DFS/Referrer/SubscribeNotifications.h"
#include "Events/DFS/Referrer/ToplinkDeliver.h"
#include "Events/DFS/Referrer/UpdateConfig.h"
#include "Events/System/Net/rpc/IncomingOnAcceptor.h"
#include "Events/System/Net/rpc/IncomingOnConnector.h"
#include "Events/System/timer/TickAlarm.h"
#include "../Events/blockchain/BlockchainChanged.h"
#include "../Events/blockchain/GetBlockForSingleIdForClient.h"
#include "../Events/blockchain/PublishBlock.h"
#include "../Events/blockchain/SubscribeClientNotifications.h"
#include "../Events/invoice/GetInvoice.h"
#include "../Events/invoice/MakeInvoice.h"
#include "objectHandler.h"
#include "../Events/blockchain/GetAmount.h"
#include "../Events/blockchain/GetCreditLimit.h"
#include "../Events/System/Error/Error.h"
#include "timerHelper.h"
#include "SQLiteCpp/Transaction.h"

#define HANDLER_DB "h_db"
struct accountRec
{
    int64_t id;
    blockchainData::KeyStore store;
};

class BlockchainHandler:
    public TimerHelper,
    public
#ifdef __MOBILE__
    ObjectHandlerThreaded
#else
    ObjectHandlerPolled
#endif


{
public:
    BlockchainHandler(IInstance *ins);
    IInstance *instance;

    bool OH_handleObjectEvent(const REF_getter<Event::Base>& e);

    virtual void signal_connected()=0;
    virtual void signal_disconnected()=0;


    bool on_NotifyReferrerUplinkIsConnected(const dfsReferrerEvent::NotifyReferrerUplinkIsConnected *);
    bool on_NotifyReferrerUplinkIsDisconnected(const dfsReferrerEvent::NotifyReferrerUplinkIsDisconnected *);
    bool on_ToplinkDeliverRSP(const dfsReferrerEvent::ToplinkDeliverRSP* e);
    bool on_TickAlarm(const timerEvent::TickAlarm*e);
    bool on_BlockchainChanged(const blockchainEvent::BlockchainChanged*e);
    bool on_GetBlockForSingleIdForClientRSP(const blockchainEvent::GetBlockForSingleIdForClientRSP*);

    virtual bool post_MakeInvoiceRSP(const invoiceEvent::MakeInvoiceRSP*)=0;
    bool on_PublishBlockRSP(const blockchainEvent::PublishBlockRSP*, const route_t &tl_route);
    bool on_GetAmountRSP(const blockchainEvent::GetAmountRSP*);
    bool on_GetCreditLimitRSP(const blockchainEvent::GetCreditLimitRSP*);

    void on_blockReceived(int64_t blockId, const std::string & block);



    /// ACCOUNTS

    void makeInvoice(const std::string& amount, const std::string& comments, const std::string& javaCookie);
    void makePayment(long invoiceId, const std::string& password, const std::string& javaCookie);
    void getAmountREQ(const SHA1_id &pubk, const std::string& javaCookie);
    void getCreditLimitREQ(const SHA1_id& pubk,const std::string &javaCookie);

    std::pair<std::string,std::string> getMessage();
    std::string getDefaultKeystoreNameOrThrow();
    std::string getDefaultKeystoreName();
    int64_t getLastBlockReceived();
    void setLastBlockReceived(int64_t lastBlock);

    void subscribeReferrerNotifications();

    struct offline_cache_referrer_struct
    {
        offline_cache_referrer_struct():ev(NULL){}
        SERVICE_id sid;
        REF_getter<Event::Base> ev;
    };
    struct __mx: public Mutexable
    {
        std::deque<std::pair<std::string,std::string> > java_msgs;
        __mx() {}
        std::deque<std::pair<SERVICE_id,REF_getter<Event::Base> > >  offline_cache_local;
        std::deque<offline_cache_referrer_struct> offline_cache_referrer;

    };
    __mx mx;
    void push_msg(const Json::Value&, const std::string &binData);
    void push_err(const std::string& action,const std::string& err, const std::string &javaCookie);

    std::set<msockaddr_in> referrer;
    bool isConnected;
    std::string config_bod;
    std::set<RSA_id> pubKeys;

    std::map<int64_t,blockchainData::Invoice> invoices_cached;
    std::deque<Json::Value> create_block_data;

    std::map<SHA1_id,blockchainData::KeyStore > registrations;

    void addKeyStoreB64(SQLite::Transaction& tr, const std::string& ksB64);
    std::vector<accountRec> getAccounts(SQLite::Database& d);
    void setDefaultKeystore(long id);

    Json::Value getAccountInfo(SQLite::Database&d,int accountId);
    blockchainData::KeyStore getAccountById(SQLite::Database& d,int id);
    std::vector<int> getAccountIds(SQLite::Database& d);
    void createAccount(const std::string& accountName, const std::string& keyStorePassword, const std::string &javaCookie);
    void createSetCreditLimit( const SHA1_id & debetorSHa1,
                                            double credit_limit,
                                            const std::string& keyStorePassword,
                                           const std::string& javaCookie);

    void getInvoiceREQ(long invId, long rnd, const std::string& javacookie);
    void getAmountREQ_forDefaultKeystore(const std::string &javaCookie);
    void getCreditLimitREQ_forDefaultKeystore(const std::string &javaCookie);


    SHA1_id getEmitentSha1();

    static IInstance *init(int argc, char **argv, const std::string &filesDir);

    void sendEventCachedToReferrer(const SERVICE_id& sid, const REF_getter<Event::Base>&e);
    void sendEventCached(const SERVICE_id& sid, const REF_getter<Event::Base>&e);










};
#endif
