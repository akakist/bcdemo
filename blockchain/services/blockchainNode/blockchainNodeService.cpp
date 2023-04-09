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
#include "blockchainNodeService.h"
#include "__crc64.h"
#include "Events/System/Error/Error.h"
#include "Events/DFS/Referrer/ToplinkDeliver.h"

#include "events_blockchainNodeService.hpp"



bool BlockchainNode::Service::on_startService(const systemEvent::startService*)
{
    MUTEX_INSPECTOR;

    auto db=getDB();

    st_TRANSACTION tr(db);

    initDB(&tr);

    readBlockchain(&tr);

    sendEvent(ServiceEnum::DFSReferrer, new dfsReferrerEvent::SubscribeNotifications(ListenerBase::serviceId));

    tr.commit();
    return true;
}


bool BlockchainNode::Service::handleEvent(const REF_getter<Event::Base>& e)
{

    XTRY;
    try {
        MUTEX_INSPECTOR;
        auto& ID=e->id;
        if(blockchainEventEnum::PublishBlockREQ==ID)
        {
            return on_PublishBlockREQ((blockchainEvent::PublishBlockREQ*)e.operator ->());
        }
        if(dfsReferrerEventEnum::ToplinkDeliverREQ==ID)
            return on_ToplinkDeliverREQ((dfsReferrerEvent::ToplinkDeliverREQ*)e.operator ->());

        if(dfsReferrerEventEnum::NotifyReferrerUplinkIsConnected==ID)
        {
            MUTEX_INSPECTOR;
            auto d=getDB();
            return on_NotifyReferrerUplinkIsConnected(d.operator ->(),(dfsReferrerEvent::NotifyReferrerUplinkIsConnected*)e.operator ->());
        }
        if(dfsReferrerEventEnum::NotifyReferrerUplinkIsDisconnected==ID)
            return on_NotifyReferrerUplinkIsDisconnected((dfsReferrerEvent::NotifyReferrerUplinkIsDisconnected*)e.operator ->());


        if(dfsReferrerEventEnum::NotifyReferrerDownlinkDisconnected==ID)
            return on_NotifyReferrerDownlinkDisconnected((dfsReferrerEvent::NotifyReferrerDownlinkDisconnected*)e.operator ->());
        if(dfsReferrerEventEnum::NotifyReferrerUplinkIsDisconnected==ID)
            return on_NotifyReferrerUplinkIsDisconnected((dfsReferrerEvent::NotifyReferrerUplinkIsDisconnected*)e.operator ->());


        if(timerEventEnum::TickTimer==ID)
        {
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
            MUTEX_INSPECTOR;
            if(!readyToServe && !isRoot)
            {
                logErr2("if(!readyToServe)");
                return false;
            }
            const rpcEvent::IncomingOnAcceptor*ev=static_cast<const rpcEvent::IncomingOnAcceptor*>(e.operator ->());
            auto &IDA=ev->e->id;
            if(dfsReferrerEventEnum::ToplinkDeliverREQ==IDA)
                return on_ToplinkDeliverREQ((dfsReferrerEvent::ToplinkDeliverREQ*)ev->e.operator ->());
            if(blockchainEventEnum::PublishBlockREQ==IDA)
            {
                return on_PublishBlockREQ((blockchainEvent::PublishBlockREQ*)ev->e.operator ->());
            }
            if(blockchainEventEnum::GetBlocksSinceIdREQ==IDA)
            {
                MUTEX_INSPECTOR;
                auto dbh=getDB();
                st_TRANSACTION tr(dbh);
                bool r=on_GetBlocksSinceIdREQ(dbh.operator ->(),(blockchainEvent::GetBlocksSinceIdREQ*)ev->e.operator ->());
                tr.commit();
                return r;
            }
            if(blockchainEventEnum::SubscribeClientNotifications==IDA)
            {
                MUTEX_INSPECTOR;
                blockchainEvent::SubscribeClientNotifications *ze=(blockchainEvent::SubscribeClientNotifications *) ev->e.operator ->();
                clientConsumersOnPublicKeyAkaUID[ze->publicKey].insert(ze->route);
                return true;
            }
            if(blockchainEventEnum::GetAmountREQ==IDA)
            {
                MUTEX_INSPECTOR;
                bool r=on_GetAmountREQ((blockchainEvent::GetAmountREQ*)ev->e.operator ->());
                return r;
            }

            if(blockchainEventEnum::GetBlockForSingleIdForClientREQ==IDA)
            {
                MUTEX_INSPECTOR;
                auto dbh=getDB();
                st_TRANSACTION tr(dbh);

                bool r=on_GetBlockForSingleIdForClientREQ(dbh.operator ->(),(blockchainEvent::GetBlockForSingleIdForClientREQ*)ev->e.operator ->());
                tr.commit();
                return r;
            }

            if(imEventEnum::RegisterDownlinkREQ==IDA)
            {
                MUTEX_INSPECTOR;
                downlinks.insert(std::make_pair(ev->esi->m_id,ev->e->route));
                passEvent(new imEvent::RegisterDownlinkRSP(poppedFrontRoute(ev->e->route)));
                logErr2("downlinks insert %s",ev->e->route.dump().c_str());
                return true;
            }

            return false;
        }
        if(rpcEventEnum::IncomingOnConnector==ID)
        {
            const rpcEvent::IncomingOnConnector*ev=static_cast<const rpcEvent::IncomingOnConnector*>(e.operator ->());
            auto &IDC=ev->e->id;
            if(dfsReferrerEventEnum::ToplinkDeliverREQ==IDC)
                return on_ToplinkDeliverREQ((dfsReferrerEvent::ToplinkDeliverREQ*)ev->e.operator ->());
            if(blockchainEventEnum::PublishBlockREQ==IDC)
            {
                return on_PublishBlockREQ((blockchainEvent::PublishBlockREQ*)ev->e.operator ->());
            }
            if(blockchainEventEnum::GetBlocksSinceIdRSP==IDC)
            {
                MUTEX_INSPECTOR;
                auto dbh=getDB();
                st_TRANSACTION tr(dbh);

                bool r=on_GetBlocksSinceIdRSP(&tr,(blockchainEvent::GetBlocksSinceIdRSP*)ev->e.operator ->());
                tr.commit();
                return r;
            }
            if(blockchainEventEnum::BlockchainChanged==IDC)
            {
                MUTEX_INSPECTOR;
                auto dbh=getDB();
                st_TRANSACTION tr(dbh);
                bool r=on_BlockchainChanged(dbh.operator ->());
                tr.commit();
                return r;
            }
            if(imEventEnum::RegisterDownlinkRSP==IDC)
            {
                logErr2("RegisterDownlinkRSP uplink %s",ev->esi->remote_name->addr.dump().c_str());
                uplink.insert(ev->esi->remote_name->addr);
                return true;
            }

        }

    } catch(std::exception &e)
    {
        logErr2(" BlockchainNode std::exception  %s",e.what());
    }
    XPASS;
    return false;
}


bool BlockchainNode::Service::on_CommandEntered(const telnetEvent::CommandEntered*)
{

    return true;
}

BlockchainNode::Service::~Service()
{
}


BlockchainNode::Service::Service(const SERVICE_id& id, const std::string& nm,IInstance* ins):
    UnknownBase(nm),
    ListenerBuffered1Thread(this,nm,ins->getConfig(),id,ins),
    Broadcaster(ins),DBH_feature(ins),
    instance(ins),
    uplinkIsNotified(false), isRoot(false),readyToServe(false)

{
        isRoot=ins->getConfig()->get_bool("isRoot",false,"is root");
        if(isRoot)
        {
            std::string root_rsa_private_key_bod=ins->getConfig()->get_string("root_rsa_private_key","","root RSA private key");
            if(root_rsa_private_key_bod.empty())
                throw CommonError("if(root_rsa_private_key_bod.empty())");
            root_rsa_private_key=iUtils->hex2bin(root_rsa_private_key_bod);

        }

}

bool BlockchainNode::Service::on_RequestIncoming(const webHandlerEvent::RequestIncoming* )
{
    return true;
}
void registerBlockchainNodeService(const char* pn)
{
    MUTEX_INSPECTOR;
    /// регистрация в фабрике сервиса и событий

    XTRY;
    if(pn)
    {
        iUtils->registerPlugingInfo(COREVERSION,pn,IUtils::PLUGIN_TYPE_SERVICE,ServiceEnum::BlockchainNode,"BlockchainNode",getEvents_blockchainNodeService());
    }
    else
    {
        iUtils->registerService(COREVERSION,ServiceEnum::BlockchainNode,BlockchainNode::Service::construct,"BlockchainNode");
        regEvents_blockchainNodeService();
    }
    XPASS;
}




bool BlockchainNode::Service::on_NotifyReferrerDownlinkDisconnected(const dfsReferrerEvent::NotifyReferrerDownlinkDisconnected*e)
{
    MUTEX_INSPECTOR;
    downlinks.erase(e->socketId);
    return true;
}

bool BlockchainNode::Service::on_NotifyReferrerUplinkIsConnected(DBH *dbh, const dfsReferrerEvent::NotifyReferrerUplinkIsConnected*e)
{
    MUTEX_INSPECTOR;
    uplink.insert(e->sa);

    int64_t maxId=getMaxIdFromTblBlock(dbh);
    {
        MUTEX_INSPECTOR;
        if(uplink.size()==0)
            throw CommonError("uplink size 0");
        instance->sendEvent(e->sa,ServiceEnum::BlockchainNode,
                            new blockchainEvent::GetBlocksSinceIdREQ(maxId,ListenerBase::serviceId));
    }

    return true;
}
bool BlockchainNode::Service::on_NotifyReferrerUplinkIsDisconnected(const dfsReferrerEvent::NotifyReferrerUplinkIsDisconnected*e)
{
    MUTEX_INSPECTOR;

    uplink.erase(e->sa);
    uplinkIsNotified=false;
    return true;
}


void BlockchainNode::Service::addBlocks(st_TRANSACTION* tr, const std::vector<std::string> &fullBlock)
{
    XTRY;
    MUTEX_INSPECTOR;

    logErr2("add block");

    std::set<SHA1_id> interestedAccounts;


    int64_t lastBlock=0;
    for(auto &b: fullBlock)
    {
        int64_t blockId=blockchainStats.processBlock(b,&interestedAccounts,nullptr);

        tr->dbh->exec((QUERY)"delete from ? where id=?"
                      <<TBL_BLOCK
                      <<blockId
                      );
        tr->dbh->exec((QUERY)"insert into  ? (id,body) values(?,x'?') "
                      <<TBL_BLOCK
                      <<blockId
                      <<iUtils->bin2hex(b));
        lastBlock=blockId;
    }

    notifyDownlinks(lastBlock,interestedAccounts);




    XPASS;
}




int64_t BlockchainNode::Service::getMaxIdFromTblBlock(DBH* dbh)
{
    MUTEX_INSPECTOR;
    return blockchainStats.lastBlockId;
}

bool BlockchainNode::Service::on_BlockchainChanged(DBH *dbh)
{
    MUTEX_INSPECTOR;
    logErr2("on_BlockchainChanged");
    int64_t maxId = getMaxIdFromTblBlock(dbh);
    if(uplink.size()==0)
        throw CommonError("if(uplink.size()==0)");
    instance->sendEvent(*uplink.begin(),ServiceEnum::BlockchainNode,
                        new blockchainEvent::GetBlocksSinceIdREQ(maxId,ListenerBase::serviceId));
    return true;
}
bool BlockchainNode::Service::on_GetBlocksSinceIdREQ(DBH *dbh, const blockchainEvent::GetBlocksSinceIdREQ*e)
{
    MUTEX_INSPECTOR;
    std::vector<std::string> mres;

    QUERY qz=(QUERY)"select id from ? where id>? "
             "order by id limit ?"
             <<TBL_BLOCK
             <<e->blockId
             <<PACK_LIMIT;

    REF_getter<QueryResult>r=dbh->exec(qz);
    try {
        for(size_t i=0; i<r->values.size(); i++)
        {
            MUTEX_INSPECTOR;
            if(r->values[i].size()!=1)
                throw CommonError("if(r->values[i].size()!=1)");
            int64_t id=atoll(r->values[i][0].c_str());
            if(id<=blockchainStats.lastBlockId)
            {
                    mres.push_back(prepareBlockForTransition(dbh,id));
            }

        }

    } catch (std::exception& e) {

            logErr2("exception %s",e.what());
    }

    int64_t lastId = getMaxIdFromTblBlock(dbh);
    instance->passEvent(new blockchainEvent::GetBlocksSinceIdRSP(mres,lastId,poppedFrontRoute(e->route)));
    return true;
}


bool BlockchainNode::Service::on_GetBlocksSinceIdRSP(st_TRANSACTION *tr, const blockchainEvent::GetBlocksSinceIdRSP*e)
{

    MUTEX_INSPECTOR;

    addBlocks(tr,e->blocks);

    int64_t maxId = getMaxIdFromTblBlock(tr->dbh.operator ->());

    if(maxId < e->lastBlockIHave)
    {
        MUTEX_INSPECTOR;
        if(uplink.size()==0)
            throw CommonError("uplink size 0");
        instance->sendEvent(*uplink.begin(),ServiceEnum::BlockchainNode,
                            new blockchainEvent::GetBlocksSinceIdREQ(maxId,ListenerBase::serviceId));
    }
    else
    {
        MUTEX_INSPECTOR;
        instance->sendEvent(*uplink.begin(),ServiceEnum::BlockchainNode,
                            new imEvent::RegisterDownlinkREQ(ListenerBase::serviceId));
        readyToServe=true;

    }
    return true;
}


bool BlockchainNode::Service::on_GetBlockForSingleIdForClientREQ(DBH *dbh, const blockchainEvent::GetBlockForSingleIdForClientREQ*e)
{
    MUTEX_INSPECTOR;
    std::map<int64_t, blockchainData::Payment> mres;
    REF_getter<QueryResult>r=dbh->exec((QUERY)"select id from ? where id=?"
                                       <<TBL_BLOCK
                                       <<e->blockId);
    for(auto& rr:r->values)
    {
        MUTEX_INSPECTOR;

        if(rr.size()==1)
        {
            MUTEX_INSPECTOR;
            passEvent(new blockchainEvent::GetBlockForSingleIdForClientRSP(atoll(rr[0].c_str()),
                      prepareBlockForTransition(dbh,atoll(rr[0].c_str())),poppedFrontRoute(e->route)));

        }
        else
            throw CommonError("!if(rr.size()==1)");

    }

    return true;
}
bool BlockchainNode::Service::on_GetAmountREQ(const blockchainEvent::GetAmountREQ*e)
{
    MUTEX_INSPECTOR;

    double amount=0;

    if(blockchainStats.accounts.count(e->pubKeySHA1))
        amount=blockchainStats.accounts[e->pubKeySHA1].amounts[e->emitentKeySHA1].v;

    passEvent(new blockchainEvent::GetAmountRSP(0,"",e->pubKeySHA1,e->emitentKeySHA1,std::to_string(amount),
              poppedFrontRoute(e->route)));

    return true;
}

std::string BlockchainNode::Service::prepareBlockForTransition(DBH *dbh, int64_t blockId)
{
    MUTEX_INSPECTOR;
    {
        REF_getter<QueryResult> r=dbh->exec((QUERY)"select "
                                            "body"
                                            " from ? where id=?"
                                            <<TBL_BLOCK
                                            <<blockId
                                           );
        if(r->values.size()!=1)
            throw CommonError("invalid response %s %d",__FILE__,__LINE__);
        if(r->values[0].size()!=1)
            throw CommonError("invalid response %s %d",__FILE__,__LINE__);

        return r->values[0][0];
    }
    throw CommonError("wrong block type");
}
bool BlockchainNode::Service::on_PublishBlockREQ(const blockchainEvent::PublishBlockREQ* e)
{
    MUTEX_INSPECTOR;
        XTRY;

        auto d=getDB();
        st_TRANSACTION tr(d);

    if(!isRoot)
        throw CommonError("if(!isRoot) @#123");

        int64_t lastId=blockchainStats.lastBlockId;

        I_ssl *ssl=(I_ssl*)iUtils->queryIface(Ifaces::SSL);

        st_rsa rsa;
        rsa.initFromPrivateKey(root_rsa_private_key);
        outBuffer o_client_block_plus_id;
        o_client_block_plus_id<<lastId+1<<e->block;

        std::string sha1=ssl->sha1(o_client_block_plus_id.asString()->asString());
        std::string sha1Enc=rsa.privateEncrypt(sha1);
        outBuffer o1;
        o1<<o_client_block_plus_id.asString()->asString()<<sha1Enc;

        std::vector<std::string> v;
        v.push_back(o1.asString()->asString());
        addBlocks(&tr,v);
        tr.commit();

        XPASS;

    return true;

}

bool BlockchainNode::Service::on_ToplinkDeliverREQ(dfsReferrerEvent::ToplinkDeliverREQ*e)
{
    MUTEX_INSPECTOR;
    auto z=e->getEvent();
    if(z->id==blockchainEventEnum::PublishBlockREQ)
    {
        MUTEX_INSPECTOR;
        try {
            MUTEX_INSPECTOR;
            XTRY;
            blockchainEvent::PublishBlockREQ *ze=(blockchainEvent::PublishBlockREQ *)z.operator ->();

            on_PublishBlockREQ(ze);

            REF_getter<Event::Base> re=new dfsReferrerEvent::ToplinkDeliverRSP(
                        new blockchainEvent::PublishBlockRSP(0,"OK",ze->block,ze->route),poppedFrontRoute(e->route));
            passEvent(re);

            XPASS;

        }
        catch(std::exception& err)
        {
            REF_getter<ErrorEvent::ErrorRSP> err_ev=new ErrorEvent::ErrorRSP(1,err.what());
            REF_getter<dfsReferrerEvent::ToplinkDeliverRSP> rsp=new dfsReferrerEvent::ToplinkDeliverRSP(err_ev.operator ->(),poppedFrontRoute(e->route));
            passEvent(rsp.operator ->());
            logErr2("@@ %s %s",__PRETTY_FUNCTION__,err.what());

        }

    }
    return true;
}

void BlockchainNode::Service::readBlockchain(st_TRANSACTION* tr)
{

    int64_t maxId=0;

    REF_getter<QueryResult> r0=tr->dbh->exec((QUERY)"select max(id) from ?"<<TBL_BLOCK);
    if(r0->values.size()==1)
    {
        if(r0->values[0].size())
            maxId=atoll(r0->values[0][0].c_str());
    }
    logErr2("maxId %s",std::to_string(maxId).c_str());
    int N=1000;
    for(int64_t i=0;i<maxId;i+=N)
    {
        REF_getter<QueryResult> r=tr->dbh->exec((QUERY)"select id,body from ? where id>=? order by id  limit ?"
                                                <<TBL_BLOCK
                                                <<i
                                                <<N);
        for(int j=0;j<r->values.size();j++)
        {
            if(r->values[j].size()!=2)
                throw CommonError("if(r->values[j].size()!=2)");
            int64_t blockIdFromDB=atoll(r->values[j][0].c_str());
            std::string block=r->values[j][1];
            try {
                int64_t bid=blockchainStats.processBlock(block,nullptr,&blockIdFromDB);

            } catch (std::exception& e) {
                logErr2("block failed aborting next blocks %s",e.what());
                break;
            }
        }

    }
}
void BlockchainStats::updateAmounts(blockchainData::Payment& ps)
{
    MUTEX_INSPECTOR;
    logErr2("updateAmounts: ");
    logErr2("debetorPublicKeySHA1: %s",ps.document.debetorPublicKeySHA1.hex().c_str());
    logErr2("creditorPublicKeySHA1: %s",ps.document.creditorPublicKeySHA1.hex().c_str());
    logErr2("emitentPublicKeySHA1: %s",ps.document.emitentPublicKeySHA1.hex().c_str());
    updateAmount(ps.document.debetorPublicKeySHA1, ps.document.emitentPublicKeySHA1,-ps.document.amount);
    updateAmount(ps.document.creditorPublicKeySHA1,ps.document.emitentPublicKeySHA1, ps.document.amount);

}

void BlockchainStats::updateAmount(const SHA1_id& creditor_pubkeySHA1,
        const SHA1_id& emitent_pubkeySHA1, double amount)
{
    MUTEX_INSPECTOR;



    if(!accounts.count(creditor_pubkeySHA1))
        throw  CommonError("if(!accounts.count(creditor_pubkeySHA1))");

    Rational oldAmount=accounts[creditor_pubkeySHA1].amounts[emitent_pubkeySHA1];
    if(oldAmount.v+amount<0 && creditor_pubkeySHA1!=emitent_pubkeySHA1)
    {
        throw CommonError("amount below zero possible for emitent only" );
    }
    accounts[creditor_pubkeySHA1].amounts[emitent_pubkeySHA1].v+=amount;



}

int64_t BlockchainStats::processBlock(const std::string& fullBlock,std::set<SHA1_id>* interestedAccounts, int64_t* blockIdFromDB)
{

        XTRY;
        MUTEX_INSPECTOR;

        logErr2("add block");
        I_ssl *ssl=(I_ssl*)iUtils->queryIface(Ifaces::SSL);

        inBuffer inFull(fullBlock);
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
        int64_t blockId=in_Intermediate.get_PN();
        logErr2("blockId %s",std::to_string(blockId).c_str());
        std::string clientBlock=in_Intermediate.get_PSTR();

        if(blockIdFromDB)
        {
            if(blockId!=*blockIdFromDB)
            {
                throw CommonError("if(blockId!=*blockIdFromDB)");
            }
        }

        if(blockId-lastBlockId!=1)
        {
            throw CommonError("prev block does not exists blockId %lld lastId %lld",blockId,lastBlockId);
        }


        inBuffer inClient(clientBlock);
        int blockType=inClient.get_PN();


        if(blockType==blockchainData::BLOCK_PAYMENT)
        {
            MUTEX_INSPECTOR;
            logErr2("BLOCK_PAYMENT_SET");
            blockchainData::Payment ps;

            inClient>>ps;

            if(!verifySign(ps))
                throw CommonError("invalid debetor sign "+_DMI());

            {
                MUTEX_INSPECTOR;
                if(paidInvoices.count(ps.document.invoiceId))
                    throw CommonError("invoice already paid");
                paidInvoices.insert(ps.document.invoiceId);
                updateAmounts(ps);
                if(interestedAccounts)
                {
                    interestedAccounts->insert(ps.document.debetorPublicKeySHA1);
                    interestedAccounts->insert(ps.document.creditorPublicKeySHA1);
                }
//                notifyDownlinks(ps,blockId);
            }
        }
        else if(blockType==blockchainData::BLOCK_REGISTRATION)
        {
            MUTEX_INSPECTOR;
            logErr2("BLOCK_REGISTRATION");
            blockchainData::Registration reg;
            inClient>>reg;
            if(accounts.count(reg.document.pubkey.sha1()) )
                throw CommonError("same account already exists");

            accounts[reg.document.pubkey.sha1()].rsaPublicKey=reg.document.pubkey;
            accounts[reg.document.pubkey.sha1()].createdate=reg.document.date;

            logErr2("registered account %s",reg.document.pubkey.sha1().hex().c_str());
            if(interestedAccounts)
            {
                interestedAccounts->insert(reg.document.pubkey.sha1());
            }


        }
        else if(blockType==blockchainData::BLOCK_SET_CREDIT_LIMIT)
        {
            blockchainData::SetCreditLimit cl;
            inClient>>cl;
            if(!verifySign(cl))
                throw CommonError("invalid emitent sign "+_DMI());
            accounts[cl.document.debetorPublicKeySHA1].credit_limits[cl.document.emitentPublicKeySHA1]=cl.document.credit_limit;
            if(interestedAccounts)
            {
                interestedAccounts->insert(cl.document.emitentPublicKeySHA1);
                interestedAccounts->insert(cl.document.debetorPublicKeySHA1);
            }
        }
        else throw CommonError("unhandled block type");

        lastBlockId=blockId;

        return blockId;

        XPASS;

        return 0;
}
bool BlockchainStats::verifySign(blockchainData::Payment &payment)
{
    MUTEX_INSPECTOR;
    try {
        I_ssl *ssl=(I_ssl*)iUtils->queryIface(Ifaces::SSL);

        outBuffer od;
        od<<payment.document;
        std::string sha256=ssl->sha256(od.asString()->asString());


        if(!accounts.count(payment.document.debetorPublicKeySHA1))
        {
            throw CommonError("payment.document.debetorPublicKeySHA1 does not exist");
        }
        auto key=accounts[payment.document.debetorPublicKeySHA1].rsaPublicKey;
        st_rsa rsa;
        rsa.initFromPublicKey(key.get());
        std::string sha256_from_rsa=rsa.publicDecrypt(payment.sign_sha256_rsaByUserPrivKey);


        if(sha256!=sha256_from_rsa)
        {
            return false;

        }
    }
    catch(std::exception& e)
    {
        logErr2("verifySign catched %s",e.what());
        throw;
    }
    catch(...)
    {
        logErr2("verifySign catched");
        throw;
    }
    return true;

}
bool BlockchainStats::verifySign(blockchainData::SetCreditLimit &cl)
{
    MUTEX_INSPECTOR;
    try {
        I_ssl *ssl=(I_ssl*)iUtils->queryIface(Ifaces::SSL);

        outBuffer od;
        od<<cl.document;
        std::string sha256=ssl->sha256(od.asString()->asString());


        if(!accounts.count(cl.document.emitentPublicKeySHA1))
        {
            throw CommonError("payment.document.debetorPublicKeySHA1 does not exist");
        }
        auto key=accounts[cl.document.emitentPublicKeySHA1].rsaPublicKey;
        st_rsa rsa;
        rsa.initFromPublicKey(key.get());
        std::string sha256_from_rsa=rsa.publicDecrypt(cl.sign_sha256_rsaByUserPrivKey);


        if(sha256!=sha256_from_rsa)
        {
            return false;

        }
    }
    catch(std::exception& e)
    {
        logErr2("verifySign catched %s",e.what());
        throw;
    }
    catch(...)
    {
        logErr2("verifySign catched");
        throw;
    }
    return true;

}

void BlockchainNode::Service::notifyDownlinks(int64_t blockId_final,const std::set<SHA1_id>&interestedAccount)
{
    MUTEX_INSPECTOR;
    std::set<route_t> blockchainChangedNotif;
    for(auto& l:clientConsumersOnPublicKeyAkaUID)
    {
        MUTEX_INSPECTOR;
        if(interestedAccount.count(l.first))
        {
            for(auto& s: l.second)
            {
                MUTEX_INSPECTOR;
                logErr2("pass BlockchainChanged to client to %s",s.dump().c_str());
                blockchainChangedNotif.insert(s);
            }
        }
    }
    for(auto& l:downlinks)
    {
        MUTEX_INSPECTOR;
        blockchainChangedNotif.insert(l.second);
    }
    for(auto &z: blockchainChangedNotif)
    {
        MUTEX_INSPECTOR;
        REF_getter<Event::Base> e = new blockchainEvent::BlockchainChanged(blockId_final,poppedFrontRoute(z));
        passEvent(e);
    }

}
