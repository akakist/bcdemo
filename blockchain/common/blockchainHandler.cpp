#include "blockchainHandler.h"
#include <math.h>
#include <megatron_config.h>
#include "../main/configObj.h"
#include "../main/CUtils.h"
#include "tools_mt.h"
#include "__crc64.h"
#include "__crc16.h"
#include "__crc32.h"
#include "ISSL.h"
#include "st_rsa.h"
#include "SQLiteCpp/Database.h"
#include "_QUERY.h"
//#include "megatronClient.h"
#include "Events/DFS/Referrer/InitClient.h"
#include "Events/DFS/Referrer/ToplinkDeliver.h"

const char emitent[]="c4393323dc2cc32a4b9e30aea0b91878a78693d3";/// shuvalow

const char* config=R"ZXC(
Start=RPC,ReferrerClient
CapsIP=x.testquant.com:10101,x.testquant.com:10102,x.testquant.com:10103,x.testquant.com:10104,x.testquant.com:10105,
RPC.BindAddr_MAIN=NONE
RPC.BindAddr_RESERVE=NONE
RPC.ConnectionActivity=600.000000
RPC.IterateTimeoutSec=60.000000
ReferrerClient.T_001_common_connect_failed=20.000000
ReferrerClient.T_002_D3_caps_get_service_request_is_timed_out=15.000000
ReferrerClient.T_007_D6_resend_ping_caps_short=7.000000
ReferrerClient.T_008_D6_resend_ping_caps_long=20.000000
ReferrerClient.T_009_pong_timed_out_caps_long=40.000000
ReferrerClient.T_020_D31_wait_after_send_PT_CACHE_on_recvd_from_GetReferrers=2.000000
ReferrerClient.T_040_D2_cache_pong_timed_out_from_neighbours=2.000000
SocketIO.epoll_timeout_millisec=1000
SocketIO.listen_backlog=128
SocketIO.n_workers=2
)ZXC";


//void registerHTTPModule(const char*);
void registerSqliteModule(const char*);
//void registerTelnetService(const char*);
//void registerWebHandlerModule(const char*);
void registerErrorDispatcherService(const char*);

void registerObjectProxyModule(const char*);
void registerOscarModule(const char*);
void registerOscarSecureModule(const char*);
void registerRPCService(const char*);
void registerSocketModule(const char*);
void registerTimerService(const char*);
void registerReferrerClientService(const char* pn);
static void registerModules()
{
    MUTEX_INSPECTOR;
    logErr2("static void registerModules() %s",_DMI().c_str());
    char *pn=NULL;
    {
//        registerHTTPModule(pn);
//        registerTelnetService(pn);
//        registerWebHandlerModule(pn);
        registerObjectProxyModule(pn);
        registerOscarModule(pn);
        registerOscarSecureModule(pn);
        registerRPCService(pn);
        registerSocketModule(pn);
        registerTimerService(pn);
        registerReferrerClientService(pn);
    }
    void registerSSL(const char* pn);
    registerSSL(pn);
}

IInstance* BlockchainHandler::init(int argc, char ** argv, const std::string & filesDir)
{
    iUtils=new CUtils(argc, argv, "bcwallet");

    //IUtils *iu=Megatron::initMegatron(argc,argv,filesDir);
    
    
    
    
    iUtils->setFilesDir(filesDir);
    
    
    
    registerModules();
    
    

    IInstance *instance1=iUtils->createNewInstance("BlockchainHandler");
                                                   
//                                                   );
    ConfigObj *cnf1=new ConfigObj("BlockchainHandler",config);
    instance1->setConfig(cnf1);
    instance1->initServices();

//    auto instance=Megatron::createInstance(""
//                                           ""
//                                           "\nRPC.ConnectionActivity=600.000000"
//                                           "\nRPC.IterateTimeoutSec=60.000000"
//                                           "\nRPC.ListenerBuffered.MaxThreadsCount=10"
//                                           "\nStart=RPC,ReferrerClient"
//                                           "\nOscarSecure.ListenerBuffered.MaxThreadsCount=10"
//                                           "\nOscarSecure.RSA_keysize=256"
//                                           "\nOscarSecure.maxPacketSize=33554432"
//                                           "\nRPC.BindAddr_MAIN=INADDR_ANY:0"
//                                           "\nRPC.BindAddr_RESERVE=NONE"
//                                           "\nSocketIO.ListenerBuffered.MaxThreadsCount=10"
//                                           "\nSocketIO.listen_backlog=128"
//                                           "\nSocketIO.maxOutBufferSize=8388608"
//                                           "\nSocketIO.size=1024"
//                                           "\nSocketIO.timeout_millisec=10"
//                                           "\nWebHandler.bindAddr=NONE"
//                                           "\nTelnet.BindAddr=NONE"
//                                           "\nimsfTestService1.ListenerBuffered.MaxThreadsCount=10"
//                                           "\nReferrerClient.T_001_common_connect_failed=20.000000"
//                                           "\nReferrerClient.T_002_D3_caps_get_service_request_is_timed_out=15.000000"
//                                           "\nReferrerClient.T_007_D6_resend_ping_caps_short=7.000000"
//                                           "\nReferrerClient.T_008_D6_resend_ping_caps_long=20.000000"
//                                           "\nReferrerClient.T_009_pong_timed_out_caps_long=40.000000"
//                                           "\nReferrerClient.T_020_D31_wait_after_send_PT_CACHE_on_recvd_from_GetReferrers=2.000000"
//                                           "\nReferrerClient.T_040_D2_cache_pong_timed_out_from_neighbours=2.000000");

    iUtils->registerEvent(invoiceEvent::MakeInvoiceREQ::construct);
    iUtils->registerEvent(invoiceEvent::MakeInvoiceRSP::construct);
    iUtils->registerEvent(invoiceEvent::GetInvoiceREQ::construct);
    iUtils->registerEvent(invoiceEvent::GetInvoiceRSP::construct);

    iUtils->registerEvent(blockchainEvent::PublishBlockREQ::construct);
    iUtils->registerEvent(blockchainEvent::PublishBlockRSP::construct);

    {

        std::set<msockaddr_in> caps;
        msockaddr_in sa;
         caps=instance1->getConfig()->get_tcpaddr("CapsIP","x.testquant.com:10100","Root cloud address");
//        if(!sas.size())
//            throw CommonError("if(!sas.size())");
//        sa=*sas.begin();
////        sa.initFromUrl(SERCLIENT_ADDRESS);
        caps.insert(sa);
        for(auto& z:caps)
        {
            logErr2("caps %s",z.dump().c_str());
        }
        instance1->sendEvent(ServiceEnum::ReferrerClient,new dfsReferrerEvent::InitClient(caps));
    }

    return instance1;

}
BlockchainHandler::BlockchainHandler(IInstance* ins)
    :
    TimerHelper(ins),
#ifdef __MOBILE__
    ObjectHandlerThreaded("BlockchainHandler",ins),
#else
    ObjectHandlerPolled("BlockchainHandler",ins),

#endif
    isConnected(false),instance(ins)
{
    MUTEX_INSPECTOR;
    try {
        MUTEX_INSPECTOR;

        iUtils->registerEvent(
            (event_static_constructor) dfsReferrerEvent::UpdateConfigRSP::construct);
        iUtils->registerEvent(
            (event_static_constructor) dfsReferrerEvent::UpdateConfigREQ::construct);
        iUtils->registerEvent(
            (event_static_constructor) blockchainEvent::BlockchainChanged::construct);

        iUtils->registerEvent(
            (event_static_constructor) invoiceEvent::MakeInvoiceRSP::construct);
        iUtils->registerEvent(
            (event_static_constructor) blockchainEvent::PublishBlockRSP::construct);
        iUtils->registerEvent(
            (event_static_constructor) invoiceEvent::GetInvoiceRSP::construct);
        iUtils->registerEvent(
            (event_static_constructor) blockchainEvent::GetAmountRSP::construct);
        iUtils->registerEvent(
            (event_static_constructor) blockchainEvent::GetCreditLimitREQ::construct);
        iUtils->registerEvent(
            (event_static_constructor) blockchainEvent::GetCreditLimitRSP::construct);
        iUtils->registerEvent(
            (event_static_constructor) blockchainEvent::GetBlockForSingleIdForClientRSP::construct);

        iUtils->registerEvent(
            (event_static_constructor) ErrorEvent::ErrorRSP::construct);
        iUtils->registerEvent(
            (event_static_constructor) dfsReferrerEvent::ToplinkDeliverRSP::construct);

        sendEvent(ServiceEnum::ReferrerClient,new dfsReferrerEvent::SubscribeNotifications(this));

    } catch(std::exception &e)
    {
        logErr2("BlockchainHandler::BlockchainHandler: %s",e.what());
    }

    SQLite::Database d(sqlDbName(HANDLER_DB),SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    SQLite::Transaction tr(d);
    d.exec("CREATE TABLE  IF NOT EXISTS tbl_keystore ("
           "id  INTEGER PRIMARY KEY AUTOINCREMENT,"
           "data blob"
           ")");
    d.exec("CREATE TABLE  IF NOT EXISTS tbl_emitent ("
           "id  INTEGER PRIMARY KEY AUTOINCREMENT,"
           "data blob"
           ")"
          );

    tr.commit();
}




void BlockchainHandler::subscribeReferrerNotifications()
{
    SQLite::Database d(sqlDbName(HANDLER_DB),SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

    SQLite::Statement q(d,"select data from tbl_keystore");

    while(q.executeStep())
    {
        std::string buf=q.getColumn(0).getString();

        inBuffer iz(buf);
        blockchainData::KeyStore ks2;
        iz>>ks2;


        {
            sendEvent(referrer,ServiceEnum::BlockchainNode,
                      new blockchainEvent::SubscribeClientNotifications(ks2.document.publicKey.sha1(),this));
            pubKeys.insert(ks2.document.publicKey);
        }

    }

}
bool BlockchainHandler::on_NotifyReferrerUplinkIsConnected(const dfsReferrerEvent::NotifyReferrerUplinkIsConnected *e)
{
    XTRY;
    isConnected=true;
    referrer.insert(e->sa);
    signal_connected();

    subscribeReferrerNotifications();

    std::deque<std::pair<SERVICE_id,REF_getter<Event::Base> > > dq;
    std::deque<offline_cache_referrer_struct> dq2;
    {
        M_LOCK(mx);
        dq=mx.offline_cache_local;
        mx.offline_cache_local.clear();

        dq2=mx.offline_cache_referrer;
        mx.offline_cache_referrer.clear();
    }
    for(auto& z:dq)
    {
        logErr2("send from cache local %s",z.second->dump().toStyledString().c_str());
        sendEvent(z.first,z.second);
    }
    for(auto& z:dq2)
    {
        logErr2("send from cache referrer %s",z.ev->dump().toStyledString().c_str());
        sendEvent(referrer,z.sid,z.ev);
    }
    return true;
    XPASS;
}


bool BlockchainHandler::on_NotifyReferrerUplinkIsDisconnected(const dfsReferrerEvent::NotifyReferrerUplinkIsDisconnected *e)
{
    MUTEX_INSPECTOR;
    isConnected=false;
    signal_disconnected();
    referrer.erase(e->sa);
    return true;

}
bool BlockchainHandler::on_ToplinkDeliverRSP(const dfsReferrerEvent::ToplinkDeliverRSP* e_tl)
{
    MUTEX_INSPECTOR;
    XTRY;
    REF_getter<Event::Base> z=e_tl->getEvent();
    auto &ID=z->id;
    if(ErrorEventEnum::ErrorRSP==ID)
    {
        ErrorEvent::ErrorRSP*er=(ErrorEvent::ErrorRSP*)z.operator->();
        logErr2("Error %s",er->errText.c_str());
        std::string javaCookie=e_tl->route.getLastJavaCookie();
        Json::Value j;
        j["javaCookie"]=javaCookie;
        j["action"]="ErrorRSP";
        j["errcode"]=std::to_string(1);
        j["errstr"]=er->errText;
        push_msg(j,"");

        return true;
    }
    if(invoiceEventEnum::MakeInvoiceRSP==ID)
    {
        MUTEX_INSPECTOR;
        invoiceEvent::MakeInvoiceRSP *E=(invoiceEvent::MakeInvoiceRSP*)z.operator ->();


        invoices_cached[E->newid]=E->invoice;

        const blockchainData::Invoice &inv=E->invoice;
        //    in>>inv;
        Json::Value j;
        logErr2("MakeInvoiceRSP e_tl %s",e_tl->route.dump().c_str());
        j["javaCookie"]=e_tl->route.getLastJavaCookie();
        j["action"]="MakeInvoiceRSP";
        j["errcode"]=std::to_string(E->errcode);
        j["errstr"]=E->errstr;
        j["newid"]=std::to_string(E->newid);
        j["rnd"]=std::to_string(E->rnd);
        j["amount"]=std::to_string(inv.amount);
        j["comments"]=inv.comments;
//        invoices_cached[e->newid]=inv;
        push_msg(j,"");
        logErr2("j %s",j.toStyledString().c_str());
        post_MakeInvoiceRSP(E);
        return true;


    }
    if(invoiceEventEnum::GetInvoiceRSP==ID)
    {
        MUTEX_INSPECTOR;

        invoiceEvent::GetInvoiceRSP *E=(invoiceEvent::GetInvoiceRSP*)z.operator ->();
        if(E->errcode==0)
        {
            blockchainData::Invoice inv=E->invoice;

            invoices_cached[E->invoiceId]=inv;

        }
        blockchainData::Invoice inv=E->invoice;
        Json::Value j;
        j["javaCookie"]=e_tl->route.getLastJavaCookie();
        j["action"]="GetInvoiceRSP";
        j["errcode"]=std::to_string(E->errcode);
        j["errstr"]=E->errstr;
        j["invoiceId"]=std::to_string(E->invoiceId);
        j["amount"]=std::to_string(inv.amount);
        j["comments"]=inv.comments;
        logErr2("on_GetInvoiceRSP");
        logErr2("on_GetInvoiceRSP invoices_cached size=%d",invoices_cached.size());
        push_msg(j,"");

        return true;


    }
    if(blockchainEventEnum::PublishBlockRSP==ID)
    {
        MUTEX_INSPECTOR;
        logErr2("e_tl.route %s",e_tl->route.dump().c_str());
        on_PublishBlockRSP((blockchainEvent::PublishBlockRSP*)z.operator ->(),e_tl->route);
        return true;

    }

    XPASS;
    return false;
}

bool BlockchainHandler::OH_handleObjectEvent(const REF_getter<Event::Base>& e)
{
    MUTEX_INSPECTOR;
    try {

        logErr2("OH_handleObjectEvent %s",e->dump().toStyledString().c_str());
        auto& ID=e->id;
        if(dfsReferrerEventEnum::UpdateConfigRSP==ID)
        {
            MUTEX_INSPECTOR;
            const dfsReferrerEvent::UpdateConfigRSP*xe=(const dfsReferrerEvent::UpdateConfigRSP*)e.operator ->();
            config_bod=xe->bod;
            return true;
        }
        if( dfsReferrerEventEnum::ToplinkDeliverRSP==ID)
            return on_ToplinkDeliverRSP((const dfsReferrerEvent::ToplinkDeliverRSP*)e.operator ->());
        if( dfsReferrerEventEnum::NotifyReferrerUplinkIsConnected==ID)
            return on_NotifyReferrerUplinkIsConnected((const dfsReferrerEvent::NotifyReferrerUplinkIsConnected*)e.operator ->());
        if( dfsReferrerEventEnum::NotifyReferrerUplinkIsDisconnected==ID)
            return on_NotifyReferrerUplinkIsDisconnected((const dfsReferrerEvent::NotifyReferrerUplinkIsDisconnected*)e.operator ->());

        if(timerEventEnum::TickAlarm==ID)
            return on_TickAlarm((const timerEvent::TickAlarm*)e.operator ->());

        if(rpcEventEnum::IncomingOnConnector==ID)
        {
            MUTEX_INSPECTOR;
            const rpcEvent::IncomingOnConnector*ze=(const rpcEvent::IncomingOnConnector*)e.operator ->();
            auto& IDC=ze->e->id;
            if(dfsReferrerEventEnum::UpdateConfigRSP==IDC)
            {
                MUTEX_INSPECTOR;
                const dfsReferrerEvent::UpdateConfigRSP*xe=(const dfsReferrerEvent::UpdateConfigRSP*)ze->e.operator ->();
                config_bod=xe->bod;
                return true;
            }
            if(blockchainEventEnum::BlockchainChanged==IDC)
            {
                MUTEX_INSPECTOR;
                return on_BlockchainChanged((blockchainEvent::BlockchainChanged*)ze->e.operator ->());
            }
            if(blockchainEventEnum::GetBlockForSingleIdForClientRSP==IDC)
            {
                MUTEX_INSPECTOR;
                return on_GetBlockForSingleIdForClientRSP((blockchainEvent::GetBlockForSingleIdForClientRSP*)ze->e.operator ->());
            }
            if(blockchainEventEnum::GetAmountRSP==IDC)
            {
                MUTEX_INSPECTOR;
                return on_GetAmountRSP((blockchainEvent::GetAmountRSP*)ze->e.operator ->());
            }
            if(blockchainEventEnum::GetCreditLimitRSP==IDC)
            {
                MUTEX_INSPECTOR;
                return on_GetCreditLimitRSP((blockchainEvent::GetCreditLimitRSP*)ze->e.operator ->());
            }


        }

    }
    catch(std::exception &e)
    {
        logErr2("exception %s",e.what());
    }
    catch(...)
    {
        logErr2("exception ...");
    }
    return false;
}
bool BlockchainHandler::on_TickAlarm(const timerEvent::TickAlarm*)
{
    MUTEX_INSPECTOR;
    return false;
}

bool BlockchainHandler::on_BlockchainChanged(const blockchainEvent::BlockchainChanged* e)
{
    MUTEX_INSPECTOR;
    XTRY;
    sendEvent(referrer,ServiceEnum::BlockchainNode,
              new blockchainEvent::GetBlockForSingleIdForClientREQ(e->lastBlockId,this));
    XPASS;

    return true;
}

bool BlockchainHandler::on_GetBlockForSingleIdForClientRSP(const blockchainEvent::GetBlockForSingleIdForClientRSP* e)
{
    on_blockReceived(e->blockId, e->block);
    return true;
}
void BlockchainHandler::makePayment(long invoiceId, const std::string& password, const std::string& javaCookie)
{
    MUTEX_INSPECTOR;
    XTRY;

    ConfigDB_private c;

    std::string kss=c.get_string("keystore","");

    if(kss.size()==0)
        throw CommonError("Keystore is not set");


    inBuffer inks(kss);
    blockchainData::KeyStore ks;
    inks>>ks;


    if(!invoices_cached.count(invoiceId))
        throw CommonError("if(!invoices_cached.count(invoiceId))");


    auto z=invoices_cached[invoiceId];




    blockchainData::Payment payment;

    payment.create(getEmitentSha1(),
                   ks.document.publicKey.sha1(),
                   z.creditorPublicKeySHA1,
                   z.amount,
                   std::to_string(invoiceId),
                   time(NULL),
                   ks.getPrivateKey(password));


    outBuffer o;
    o<<blockchainData::BLOCK_PAYMENT<<payment;
    
    REF_getter<Event::Base> e=new blockchainEvent::PublishBlockREQ( o.asString()->asString());

    route_t r(javaCookie,this);
    REF_getter<Event::Base> et=new dfsReferrerEvent::ToplinkDeliverREQ(ServiceEnum::BlockchainTop,e,r);


    //sendEventCached(ServiceEnum::ReferrerClient)

    sendEventCached(ServiceEnum::ReferrerClient,et);

    XPASS;

}

void BlockchainHandler::makeInvoice(const std::string& amount, const std::string& comments, const std::string &javaCookie)
{
    MUTEX_INSPECTOR;
    XTRY;

    ConfigDB_private c;
    std::string keystore=c.get_string("keystore", "");
    if(keystore.size()==0)
        throw CommonError("keystore is not set");
    blockchainData::KeyStore ks;
    inBuffer in(keystore);
    in>>ks;
    blockchainData::Invoice invoice;
    invoice.amount=atof(amount.c_str());
    invoice.comments=comments;
    invoice.date=time(NULL);
    invoice.creditorPublicKeySHA1=ks.document.publicKey.sha1();


    invoice.emitentPublicKeySHA1=getEmitentSha1();

    REF_getter<Event::Base> e=new invoiceEvent::MakeInvoiceREQ(invoice);
    route_t r(javaCookie,this);
    REF_getter<Event::Base> et=new dfsReferrerEvent::ToplinkDeliverREQ(ServiceEnum::IMInvoicer,e,r);
    sendEventCached(ServiceEnum::ReferrerClient,et);

    XPASS;
}
//#endif
void BlockchainHandler::push_msg(const Json::Value &s,const std::string& binData)
{
    M_LOCK(mx);
    mx.java_msgs.push_back(std::make_pair(s.toStyledString(),binData));
}

void BlockchainHandler::push_err(const std::string & action, const std::string& s, const std::string &javaCookie)
{

    M_LOCK(mx);
    Json::Value j;
    j["data"]=s;
    j["action"]=action;
    j["errcode"]="1";
    j["javacookie"]=javaCookie;
#ifdef __MOBILE__
    mx.java_msgs.push_back(std::make_pair(j.toStyledString(),""));
#else
    //logErr2("msg: %s",s.c_str());
#endif

}
bool BlockchainHandler::on_PublishBlockRSP(const blockchainEvent::PublishBlockRSP*e,const route_t& tl_route)
{
    MUTEX_INSPECTOR;
    logErr2("bool BlockchainHandler::on_PublishBlockRSP(const blockchainEvent::PublishBlockRSP*e)");
    Json::Value j;
//    invoicesCurrentToPay.clear();
    std::string javaCookie=tl_route.getLastJavaCookie();
    j["javaCookie"]=javaCookie;
//    e->b
    j["action"]="PublishBlockRSP";
    j["errcode"]=std::to_string(e->errcode);
    j["errstr"]=e->errstr;

    push_msg(j,"");

    return true;
}
bool BlockchainHandler::on_GetAmountRSP(const blockchainEvent::GetAmountRSP*e)
{
    MUTEX_INSPECTOR;
    Json::Value j;
    std::string javaCookie=e->route.getLastJavaCookie();

    j["javaCookie"]=javaCookie;
    j["action"]="GetAmountRSP";
    j["errcode"]=std::to_string(e->errcode);
    j["errstr"]=e->errstr;
    j["amount"]=e->amount;

    push_msg(j,"");
    return true;
}
bool BlockchainHandler::on_GetCreditLimitRSP(const blockchainEvent::GetCreditLimitRSP *e)
{
    MUTEX_INSPECTOR;
    Json::Value j;
    std::string javaCookie=e->route.getLastJavaCookie();

    j["javaCookie"]=javaCookie;
    j["action"]="GetAmountRSP";
    j["errcode"]=std::to_string(e->errcode);
    j["errstr"]=e->errstr;
    j["amount"]=e->creditLimit;

    push_msg(j,"");
    return true;
}
std::set<int64_t> blockReceivedSignalled;

void BlockchainHandler::on_blockReceived(int64_t blockId,const std::string & block)
{
    I_ssl *ssl=(I_ssl*)iUtils->queryIface(Ifaces::SSL);
    if(blockReceivedSignalled.count(blockId))
    {
        logErr2("if(blockReceivedSignalled.count(blockId))");
        return;
    }
    blockReceivedSignalled.insert(blockId);
    Json::Value j;
    j["javaCookie"]="BROADCAST";

    j["errcode"]="0";
    j["errstr"]="";

    inBuffer inFull(block);
    std::string bod=inFull.get_PSTR();
    std::string sha1Enc=inFull.get_PSTR();
    st_rsa rsa;
    rsa.initFromPublicKey(iUtils->hex2bin(root_public_key));
    std::string sha1=rsa.publicDecrypt(sha1Enc);
    if(sha1!=ssl->sha1(bod))
    {
        throw CommonError("if(sha1!=ssl->sha1(bod))");
    }
    inBuffer in_Intermediate(bod);
    int64_t blockId_=in_Intermediate.get_PN();
    std::string clientBlock=in_Intermediate.get_PSTR();

    if(blockId!=blockId_)
        throw CommonError("@@@@@!!!!!!!!!!! if(blockId!=blockId_)");

    std::map<SHA1_id /*pubkey*/,std::string /*name*/> pubKeys;
    {
        SQLite::Database d(sqlDbName(HANDLER_DB),SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

        SQLite::Statement q(d,"select data from tbl_keystore");

        while(q.executeStep())
        {
            std::string buf=q.getColumn(0).getString();

            inBuffer iz(buf);
            blockchainData::KeyStore ks2;
            iz>>ks2;
            pubKeys[ks2.document.publicKey.sha1()]=ks2.document.name;
        }
    }

    inBuffer inClient(clientBlock);
    int blockType=inClient.get_PN();
    if(blockType==blockchainData::BLOCK_PAYMENT)
    {
        j["action"]="paymentReceived";
        blockchainData::Payment ps;
        inClient>>ps;
        std::map<SHA1_id,real> totalAmounts;
        if(pubKeys.count(ps.document.debetorPublicKeySHA1))
        {

            if(!totalAmounts.count(ps.document.debetorPublicKeySHA1))
                totalAmounts[ps.document.debetorPublicKeySHA1]=0;
            totalAmounts[ps.document.debetorPublicKeySHA1]-=ps.document.amount;
        }
        if(pubKeys.count(ps.document.creditorPublicKeySHA1))
        {
            if(!totalAmounts.count(ps.document.creditorPublicKeySHA1))
                totalAmounts[ps.document.creditorPublicKeySHA1]=0;
            totalAmounts[ps.document.creditorPublicKeySHA1]+=ps.document.amount;
        }

        Json::Value jout;
        for(auto& z:totalAmounts)
        {
            std::string name=pubKeys[z.first];
            real amount=z.second;
            Json::Value j;
            j["name"]=name;
            j["amount"]=std::to_string(amount);
            jout.append(j);
        }
        j["result"]=jout;

    }
    else if(blockType==blockchainData::BLOCK_REGISTRATION)
    {
        j["action"]="registrationtReceived";
        blockchainData::Registration ps;
        inClient>>ps;
        if(pubKeys.count(ps.document.pubkey.sha1()))
        {
            std::string name=pubKeys[ps.document.pubkey.sha1()];
            j["name"]=name;
            j["status"]="account published in blockchain";
        }
        j["result"]=j;

        logErr2("check in registration %s",ps.document.pubkey.sha1().hex().c_str());
        if(registrations.count(ps.document.pubkey.sha1()))
        {
            logErr2("if(registrations.count(ps.document.pubkey.sha1()))");
            auto keystore=registrations[ps.document.pubkey.sha1()];
            outBuffer o1;
            o1<<keystore;

            SQLite::Database d(sqlDbName(HANDLER_DB),SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Transaction tr(d);

            tr.getDatabase().exec(((QUERY)"insert into tbl_keystore(data) values (x'?')"
                                   <<iUtils->bin2hex(o1.asString()->asString())).prepare());
            tr.commit();


            ConfigDB_private c;
            c.set("keystore",o1.asString()->asString());
            {
                sendEvent(referrer,ServiceEnum::BlockchainNode,
                          new blockchainEvent::SubscribeClientNotifications(keystore.document.publicKey.sha1(),this));


            }
        }
        else throw CommonError("reg not found");



    }
    else throw CommonError("invalid block type");

////////////////


    logErr2("push_msg j@@@: %s",j.toStyledString().c_str());
    push_msg(j,"");
    return;
}

std::pair<std::string,std::string> BlockchainHandler::getMessage()
{
    M_LOCK(mx);
    if(mx.java_msgs.size())
    {
        auto msg=*mx.java_msgs.begin();
        mx.java_msgs.pop_front();
        return msg;
    }
    return std::make_pair("","");
}




void BlockchainHandler::getAmountREQ(const SHA1_id& pubk,
                                     const std::string &javaCookie)
{
    MUTEX_INSPECTOR;
    ConfigDB_private c;

    route_t r(javaCookie,this);
    sendEventCachedToReferrer(ServiceEnum::BlockchainNode,
                              new blockchainEvent::GetAmountREQ(pubk,
                                      getEmitentSha1(),
                                      r));

}
void BlockchainHandler::getCreditLimitREQ(const SHA1_id& pubk,
                                     const std::string &javaCookie)
{
    MUTEX_INSPECTOR;
    ConfigDB_private c;

    route_t r(javaCookie,this);
    sendEventCachedToReferrer(ServiceEnum::BlockchainNode,
                              new blockchainEvent::GetCreditLimitREQ(pubk,
                                      getEmitentSha1(),
                                      r));

}

void BlockchainHandler::getAmountREQ_forDefaultKeystore(const std::string &javaCookie)
{
    MUTEX_INSPECTOR;
    ConfigDB_private c;
    std::string em=c.get_string("keystore", "");
    if(em.size()==0)
    {
        logErr2("default keystore is not set");
        return;
    }
    inBuffer in(em);
    blockchainData::KeyStore ks;
    in>>ks;


    logErr2("getAmountREQ_forDefaultKeystore %s",javaCookie.c_str());
    route_t r(javaCookie,this);
    sendEventCachedToReferrer(ServiceEnum::BlockchainNode,
                              new blockchainEvent::GetAmountREQ(ks.document.publicKey.sha1(),
                                      getEmitentSha1(),
                                      r));

}
void BlockchainHandler::getCreditLimitREQ_forDefaultKeystore(const std::string &javaCookie)
{
    MUTEX_INSPECTOR;
    ConfigDB_private c;
    std::string em=c.get_string("keystore", "");
    if(em.size()==0)
    {
        logErr2("default keystore is not set");
        return;
    }
    inBuffer in(em);
    blockchainData::KeyStore ks;
    in>>ks;


    logErr2("getAmountREQ_forDefaultKeystore %s",javaCookie.c_str());
    route_t r(javaCookie,this);
    sendEventCachedToReferrer(ServiceEnum::BlockchainNode,
                              new blockchainEvent::GetAmountREQ(ks.document.publicKey.sha1(),
                                      getEmitentSha1(),
                                      r));

}



void BlockchainHandler::addKeyStoreB64(SQLite::Transaction& tr, const std::string& ksB64)
{
    MUTEX_INSPECTOR;
    XTRY;
    std::string buf=iUtils->Base64Decode(ksB64);
    inBuffer in(buf);
    blockchainData::KeyStore ks;
    in>>ks;

    SQLite::Statement q(tr.getDatabase(),"select data from tbl_keystore");

    while(q.executeStep())
    {
        std::string buf=q.getColumn(0).getString();

        inBuffer iz(buf);
        blockchainData::KeyStore ks2;
        iz>>ks2;
        if(ks.document.publicKey==ks2.document.publicKey)
        {
            throw CommonError("Keystore already installed");
        }
//        outName=ks2.document.name;

    }
    tr.getDatabase().exec(((QUERY)"insert into tbl_keystore (data) values(x'?')"<<iUtils->bin2hex(buf)).prepare());
//    tr.commit();
    XPASS;


}


std::vector<accountRec> BlockchainHandler::getAccounts(SQLite::Database& d)
{
    MUTEX_INSPECTOR;
    XTRY;
    std::vector<accountRec> ret;
    SQLite::Statement q(d,"select id,buffer from tbl_keystore order by id");
    while(q.executeStep())
    {
        int64_t id=q.getColumn(0).getInt64();
        std::string buf=q.getColumn(1).getString();
        inBuffer in(buf);
        blockchainData::KeyStore ks;
        in>>ks;
        accountRec r;
        r.id=id;
        r.store=ks;
        ret.push_back(r);

    }

    return ret;
    XPASS;
}

Json::Value BlockchainHandler::getAccountInfo(SQLite::Database &d, int accountId)
{
    MUTEX_INSPECTOR;
    XTRY;
    Json::Value j;
    logErr2("getAccountById %d ",accountId);
    blockchainData::KeyStore keystore=getAccountById(d,accountId);
//    logErr2("KeyStore %s",keystore.dump().c_str());

    j["createDate"]=std::to_string((int64_t)keystore.document.createDate);
//    j["encryptedPrivateKey_hex"]=keystore.document.encryptedPrivateKey.sha1().hex();
    j["name"]=keystore.document.name;
    j["publicKey_sha1"]=keystore.document.publicKey.sha1().hex();
    {
        outBuffer o;
        o<<keystore.document.name<<keystore.document.publicKey;
        j["publicKey_share"]=iUtils->Base64Encode(o.asString()->asString());
    }
    {
        outBuffer o;
        o<<keystore;
        j["keyStore_share"]=iUtils->Base64Encode(o.asString()->asString());
    }


    return j;
    XPASS;

}
void BlockchainHandler::createAccount(
                                      const std::string& accountName,
                                      const std::string& keyStorePassword
                                      , const std::string& javaCookie)
{
    MUTEX_INSPECTOR;
    XTRY;
    I_ssl *ssl=(I_ssl*)iUtils->queryIface(Ifaces::SSL);

    st_rsa rsa;
    rsa.generate_key(1024);
    st_AES aes;
    aes.init(keyStorePassword);

    blockchainData::KeyStore keystore;
    keystore.document.encryptedPrivateKey=aes.encrypt(toRef(rsa.getPrivateKey()))->asString();
    keystore.document.md5_PrivateKey=ssl->md5(rsa.getPrivateKey());
    keystore.document.publicKey=rsa.getPublicKey();
    keystore.document.createDate=time(NULL);
    keystore.document.name=accountName;

    outBuffer o;
    o<<keystore.document;
    keystore.hash_sha256=ssl->sha256(o.asString()->asString());

#ifdef QT_CORE_LIB
    std::string fn_dump=accountName+".bks";
    std::string fn_priv=accountName+".priv";
    std::string fn_pub=accountName+".pub";
    std::string fn_emt=accountName+".emt";
    FILE *f=fopen(fn_dump.c_str(),"wb");
    fprintf(f,"%s",keystore.dump().c_str());
    fclose(f);

    std::string privK=/*"private_key@"+iUtils->Base64Encode(*/rsa.getPrivateKey()/*)*/;
    f=fopen(fn_priv.c_str(),"wb");
    fwrite(privK.data(),1,privK.size(),f);
    fclose(f);

    std::string pubK=/*"public_key@"+iUtils->Base64Encode(*/rsa.getPublicKey()/*)*/;
    f=fopen(fn_pub.c_str(),"wb");
    fwrite(pubK.data(),1,pubK.size(),f);
    fclose(f);

    std::string emPub=iUtils->bin2hex(ssl->sha1(rsa.getPublicKey()));
    f=fopen(fn_emt.c_str(),"wb");
    fwrite(emPub.data(),1,emPub.size(),f);
    fclose(f);

#endif

    pubKeys.insert(keystore.document.publicKey);

    registrations[keystore.document.publicKey.sha1()]=keystore;

    logErr2("placed to registrations %s",keystore.document.publicKey.sha1().hex().c_str());

    {
        logErr2("create Account javaCookie %s",javaCookie.c_str());
        blockchainData::Registration reg;
        reg.document.pubkey=rsa.getPublicKey();
        reg.document.date=time(nullptr);
        outBuffer o;
        o<<blockchainData::BLOCK_REGISTRATION<<reg;
        REF_getter<Event::Base> e=new blockchainEvent::PublishBlockREQ(o.asString()->asString());

        route_t r(javaCookie,this);

        REF_getter<Event::Base> et=new dfsReferrerEvent::ToplinkDeliverREQ(ServiceEnum::BlockchainTop,e,r);
        sendEvent(ServiceEnum::ReferrerClient,et);
    }
    {
        RSA_id pubk;
        pubk.set(rsa.getPublicKey());
        sendEvent(referrer,ServiceEnum::BlockchainNode,
              new blockchainEvent::SubscribeClientNotifications(pubk.sha1(),this));
    }



    return;
    XPASS;
}

void BlockchainHandler::createSetCreditLimit(
                                      const SHA1_id & debetorSHa1,
                                        double credit_limit,
                                         const std::string& keyStorePassword,
                                       const std::string& javaCookie)
{
    MUTEX_INSPECTOR;
    XTRY;
    I_ssl *ssl=(I_ssl*)iUtils->queryIface(Ifaces::SSL);



    ConfigDB_private c;
    std::string keystore_s=c.get_string("keystore", "");
    if(keystore_s.size()==0)
        throw CommonError("keystore is not set");
    blockchainData::KeyStore keystore;
    inBuffer in(keystore_s);
    in>>keystore;



    blockchainData::SetCreditLimit cl;

   cl.create(getEmitentSha1(),
                   debetorSHa1,
             credit_limit,
             time(nullptr),
             keystore.getPrivateKey(keyStorePassword)
            );


    outBuffer o;
    o<<blockchainData::BLOCK_SET_CREDIT_LIMIT<<cl;

    REF_getter<Event::Base> e=new blockchainEvent::PublishBlockREQ( o.asString()->asString());

    route_t r(javaCookie,this);
    REF_getter<Event::Base> et=new dfsReferrerEvent::ToplinkDeliverREQ(ServiceEnum::BlockchainTop,e,r);

    return;
    XPASS;
}

blockchainData::KeyStore BlockchainHandler::getAccountById(SQLite::Database& d,int id)
{
    MUTEX_INSPECTOR;
    XTRY;
    std::string k=d.execAndGet(((QUERY)"select data from tbl_keystore where id=?"<<id).prepare());
    inBuffer in(k);

    blockchainData::KeyStore ks;
    in>>ks;

    return ks;
    XPASS;
}
std::vector<int> BlockchainHandler::getAccountIds(SQLite::Database& d)
{
    MUTEX_INSPECTOR;
    XTRY;
    SQLite::Statement q(d,"select id from tbl_keystore order by id");
    std::vector<int> ret;
    while(q.executeStep())
    {
        int id=q.getColumn(0).getInt();
        ret.push_back(id);
    }

    return ret;
    XPASS;
}

SHA1_id BlockchainHandler::getEmitentSha1()
{

    SHA1_id ret;
    ret.set(iUtils->hex2bin(emitent));
    return ret;


}
void BlockchainHandler::getInvoiceREQ(long invId, long rnd, const std::string& javacookie)
{
    REF_getter<Event::Base> e=new invoiceEvent::GetInvoiceREQ(invId,rnd);
    route_t r(javacookie,this);

    REF_getter<Event::Base> et=new dfsReferrerEvent::ToplinkDeliverREQ(ServiceEnum::IMInvoicer,e,r);
    sendEventCached(ServiceEnum::ReferrerClient,et);

}
std::string BlockchainHandler::getDefaultKeystoreNameOrThrow()
{
    ConfigDB_private c;
    std::string em=c.get_string("keystore", "");
    if(em.size()==0)
        throw CommonError("Keystore not set");;
    inBuffer in(em);
    blockchainData::KeyStore ks;
    in>>ks;
    return ks.document.name;

}
std::string BlockchainHandler::getDefaultKeystoreName()
{
    ConfigDB_private c;
    std::string em=c.get_string("keystore", "");
    if(em.size()==0)
        return "???";
    inBuffer in(em);
    blockchainData::KeyStore ks;
    in>>ks;
    std::string nm=ks.document.name;
    if(nm.size()==0)
        return "???";
    return nm;

}
void BlockchainHandler::setDefaultKeystore(long aid)
{
    SQLite::Database d(sqlDbName(HANDLER_DB),SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);


    blockchainData::KeyStore ks;
    ks=getAccountById(d, aid);
    outBuffer o;
    o<<ks;
    ConfigDB_private c;
    c.set("keystore", o.asString()->asString());

}
void BlockchainHandler::sendEventCachedToReferrer(const SERVICE_id &sid, const REF_getter<Event::Base>&e)
{
    if(!isConnected)
    {
        logErr2("cached %s",e->dump().toStyledString().c_str());
        M_LOCK(mx);
        offline_cache_referrer_struct s;
        s.sid=sid;
        s.ev=e;
        mx.offline_cache_referrer.push_back(s);
        return;
    }
    sendEvent(referrer,sid,e);
}
void BlockchainHandler::sendEventCached(const SERVICE_id &sid, const REF_getter<Event::Base>&e)
{
    logErr2("cached %s",e->dump().toStyledString().c_str());
    if(!isConnected)
    {
        M_LOCK(mx);
        mx.offline_cache_local.push_back(std::make_pair(sid,e));
        return;
    }
    sendEvent(sid,e);
}
int64_t BlockchainHandler::getLastBlockReceived()
{
    ConfigDB_private c;
    int64_t lb=c.get_uint64_t("lastAmountChangeReceivedOnBlockId", 0);
    return lb;

}
void BlockchainHandler::setLastBlockReceived(int64_t lastBlock)
{
    ConfigDB_private c;
    c.set("lastAmountChangeReceivedOnBlockId",std::to_string(lastBlock));
}


