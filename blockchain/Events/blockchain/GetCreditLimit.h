#ifndef _____H5GIRGetCreditLimitREQz
#define _____H5GIRGetCreditLimitREQz
#include "___blockchainEvent.h"
#include "SERVICE_id.h"
#include "route_t.h"
#include "SHA1_id.h"
namespace blockchainEvent
{


    class GetCreditLimitREQ: public Event::Base
    {
        


    public:
        static Base* construct(const route_t &r)
        {
            Base* z=new GetCreditLimitREQ(r);
            return z;
        }
        GetCreditLimitREQ(const SHA1_id& _pubkeySHA1,const SHA1_id& _emkeySHA1, const route_t&r)
            :Base(blockchainEventEnum::GetCreditLimitREQ,r),
             pubKeySHA1(_pubkeySHA1),
             emitentKeySHA1(_emkeySHA1)
        {}
        GetCreditLimitREQ(const route_t&r)
            :Base(blockchainEventEnum::GetCreditLimitREQ,r) {}
        SHA1_id pubKeySHA1;
        SHA1_id emitentKeySHA1;
        void unpack(inBuffer& o)
        {
            o>>pubKeySHA1>>emitentKeySHA1;
        }
        void pack(outBuffer&o) const
        {
            o<<pubKeySHA1<<emitentKeySHA1;
        }
        void jdump(Json::Value &) const
        {
        }

    };
    class GetCreditLimitRSP: public Event::Base
    {
        


    public:
        static Base* construct(const route_t &r)
        {
            Base* z=new GetCreditLimitRSP(r);
            return z;
        }
        GetCreditLimitRSP(int _errcode, const std::string& _errstr,
                     const SHA1_id &_pubkey,
                     const SHA1_id &_emkey,
                     const std::string& _creditLimit, const route_t& r)
            :Base(blockchainEventEnum::GetCreditLimitRSP,r),
             errcode(_errcode),errstr(_errstr),
             pubKey(_pubkey),
             emitentKey(_emkey),
             creditLimit(_creditLimit)
        {}
        GetCreditLimitRSP(const route_t&r)
            :Base(blockchainEventEnum::GetCreditLimitRSP,r) {}

        int errcode;
        std::string errstr;
        SHA1_id pubKey;
        SHA1_id emitentKey;
        std::string creditLimit;

        void unpack(inBuffer& o)
        {
            o>>errcode>>errstr>>pubKey>>emitentKey>>creditLimit;
        }
        void pack(outBuffer&o) const
        {
            o<<errcode<<errstr<<pubKey<<emitentKey<<creditLimit;
        }
        void jdump(Json::Value &j) const
        {
            j["errcode"]=errcode;
            j["errstr"]=errstr;
            j["pubKey"]=pubKey.hex();
            j["emitentKey"]=emitentKey.hex();
            j["CreditLimit"]=creditLimit;

        }

    };

}
#endif
