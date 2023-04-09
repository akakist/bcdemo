#ifndef _____H5GIRGetAmountREQz
#define _____H5GIRGetAmountREQz
#include "___blockchainEvent.h"
#include "SERVICE_id.h"
#include "route_t.h"
#include "SHA1_id.h"
namespace blockchainEvent
{


    class GetAmountREQ: public Event::Base
    {
        


    public:
        static Base* construct(const route_t &r)
        {
            Base* z=new GetAmountREQ(r);
            return z;
        }
        GetAmountREQ(const SHA1_id& _pubkeySHA1,const SHA1_id& _emkeySHA1, const route_t&r)
            :Base(blockchainEventEnum::GetAmountREQ,r),
             pubKeySHA1(_pubkeySHA1),
             emitentKeySHA1(_emkeySHA1)
        {}
        GetAmountREQ(const route_t&r)
            :Base(blockchainEventEnum::GetAmountREQ,r) {}
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
    class GetAmountRSP: public Event::Base
    {
        


    public:
        static Base* construct(const route_t &r)
        {
            Base* z=new GetAmountRSP(r);
            return z;
        }
        GetAmountRSP(int _errcode, const std::string& _errstr,
                     const SHA1_id &_pubkey,
                     const SHA1_id &_emkey,
                     const std::string& _amount, const route_t& r)
            :Base(blockchainEventEnum::GetAmountRSP,r),
             errcode(_errcode),errstr(_errstr),
             pubKey(_pubkey),
             emitentKey(_emkey),
             amount(_amount)
        {}
        GetAmountRSP(const route_t&r)
            :Base(blockchainEventEnum::GetAmountRSP,r) {}

        int errcode;
        std::string errstr;
        SHA1_id pubKey;
        SHA1_id emitentKey;
        std::string amount;

        void unpack(inBuffer& o)
        {
            o>>errcode>>errstr>>pubKey>>emitentKey>>amount;
        }
        void pack(outBuffer&o) const
        {
            o<<errcode<<errstr<<pubKey<<emitentKey<<amount;
        }
        void jdump(Json::Value &j) const
        {
            j["errcode"]=errcode;
            j["errstr"]=errstr;
            j["pubKey"]=pubKey.hex();
            j["emitentKey"]=emitentKey.hex();
            j["amount"]=amount;

        }

    };

}
#endif
