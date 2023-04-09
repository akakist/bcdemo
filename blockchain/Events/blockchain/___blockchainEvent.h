#ifndef _______HTTTP___SERVICE____EVENT_______H12BCZZA
#define _______HTTTP___SERVICE____EVENT_______H12BCZZA

#include "event_mt.h"

#include "serviceEnum.h"
#include <string>
#include "EVENT_id.h"
#include "SERVICE_id.h"
#include "RSA_id.h"
#include "SHA1_id.h"
extern std::string root_public_key;

namespace ServiceEnum
{
    const SERVICE_id BlockchainTop("bc.BlockchainTop");
    const SERVICE_id BlockchainNode("bc.BlockchainNode");

}

namespace blockchainEventEnum
{

    const EVENT_id RegisterDownlinkREQ("bc.RegisterDownlinkREQ");
    const EVENT_id RegisterDownlinkRSP("bc.RegisterDownlinkRSP");
    const EVENT_id PublishBlockREQ("bc.PublishBlockREQ");
    const EVENT_id PublishBlockRSP("bc.PublishBlockRSP");

    const EVENT_id GetAmountREQ("bc.GetAmountREQ");
    const EVENT_id GetAmountRSP("bc.GetAmountRSP");

    const EVENT_id GetCreditLimitREQ("bc.GetCreditLimitREQ");
    const EVENT_id GetCreditLimitRSP("bc.GetCreditLimitRSP");


    const EVENT_id BlockchainChanged("bc.BlockchainChanged");
    const EVENT_id GetBlocksSinceIdRSP("bc.GetBlocksSinceIdRSP");
    const EVENT_id GetBlocksSinceIdREQ("bc.GetBlocksSinceIdREQ");
    const EVENT_id SubscribeClientNotifications("bc.SubscribeClientNotifications");
    const EVENT_id GetBlockForSingleIdForClientREQ("bc.GetBlockForSingleIdForClientREQ");
    const EVENT_id GetBlockForSingleIdForClientRSP("bc.GetBlockForSingleIdForClientRSP");


    const EVENT_id GetLastIdAndSha1REQ("bc.GetLastIdAndSha1REQ");
    const EVENT_id GetLastIdAndSha1RSP("bc.GetLastIdAndSha1RSP");

}




namespace blockchainData
{
    enum blockType
    {
        BLOCK_PAYMENT = 0,
        BLOCK_REGISTRATION = 1,
        BLOCK_SET_CREDIT_LIMIT=2,
    };

    struct KeyStore
    {
        struct Document
        {
            RSA_id encryptedPrivateKey;
            std::string md5_PrivateKey;
            RSA_id publicKey;
            time_t createDate;
            std::string name;
        };
        Document document;
        std::string hash_sha256;
        void initFromB64(const std::string& buffer);
        std::string dump();
        std::string getPrivateKey(const std::string& privKeyPassword);
        std::string getEmitentCode();
        std::string getPublicAccountCode();
//        int32_t getPublicKeyCRC32();
//        std::string getK
    };
    struct Invoice
    {
        SHA1_id emitentPublicKeySHA1;
        SHA1_id creditorPublicKeySHA1;
        double amount;
        std::string comments;
        int64_t date;
    };
    struct Payment
    {
        struct Document
        {
            SHA1_id creditorPublicKeySHA1;
            std::string invoiceId;
            double amount;
            SHA1_id emitentPublicKeySHA1;
            SHA1_id debetorPublicKeySHA1;
            int64_t date;
            Json::Value dump() const
            {
                Json::Value j;
                j["invoiceId"]=invoiceId;
                j["amount"]=std::to_string(amount);
                j["date"]=std::to_string(date);
                return j;
            }
        };
        Document document;
        std::string sign_sha256_rsaByUserPrivKey;
        void create(const SHA1_id &emitentPublicKeySHA1,
                    const SHA1_id &debetorPublicKeySHA1,
                    const SHA1_id &creditorPublicKeySHA1,
                    double amount,
                    const std::string& invoiceId,
                    const time_t& date,
                    const RSA_id& privKey_decoded);
        Json::Value dump() const
        {
            Json::Value j;
            j["sign_sha256_rsaByUserPrivKey"]="sign_sha256_rsaByUserPrivKey";
            j["document"]=document.dump();
            return j;
        }
    };
    struct Registration
    {
        struct Document
        {
            int64_t date;
            RSA_id pubkey;
        };
        Document document;



    };
    struct SetCreditLimit
    {
        struct Document
        {
            SHA1_id emitentPublicKeySHA1;
            SHA1_id debetorPublicKeySHA1;
            double credit_limit;
            int64_t date;
        };
        Document document;
        std::string sign_sha256_rsaByUserPrivKey;

        void create(const SHA1_id& emitentPublicKeySHA1,
                     const SHA1_id& debetorPublicKeySHA1,
                     double credit_limit,
                     const int64_t& date,
                     const RSA_id &privKey_decoded
                                             );

    };

}
outBuffer& operator<< (outBuffer& b,const blockchainData::KeyStore::Document& s);
inBuffer& operator>> (inBuffer& b,  blockchainData::KeyStore::Document& s);
outBuffer& operator<< (outBuffer& b,const blockchainData::KeyStore& s);
inBuffer& operator>> (inBuffer& b,  blockchainData::KeyStore& s);

outBuffer& operator<< (outBuffer& b,const blockchainData::Invoice& s);
inBuffer& operator>> (inBuffer& b,  blockchainData::Invoice& s);

outBuffer& operator<< (outBuffer& b,const blockchainData::Payment::Document& s);
inBuffer& operator>> (inBuffer& b,  blockchainData::Payment::Document& s);
outBuffer& operator<< (outBuffer& b,const blockchainData::Payment& s);
inBuffer& operator>> (inBuffer& b,  blockchainData::Payment& s);


outBuffer& operator<< (outBuffer& b,const blockchainData::Registration& s);
inBuffer& operator>> (inBuffer& b,  blockchainData::Registration& s);

outBuffer& operator<< (outBuffer& b,const blockchainData::Registration::Document& s);
inBuffer& operator>> (inBuffer& b,  blockchainData::Registration::Document& s);


outBuffer& operator<< (outBuffer& b,const blockchainData::SetCreditLimit& s);
inBuffer& operator>> (inBuffer& b,  blockchainData::SetCreditLimit& s);

outBuffer& operator<< (outBuffer& b,const blockchainData::SetCreditLimit::Document& s);
inBuffer& operator>> (inBuffer& b,  blockchainData::SetCreditLimit::Document& s);



#endif
