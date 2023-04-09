#ifndef _____H5MakeInvoiceREQz
#define _____H5MakeInvoiceREQz
#include "___invoiceEvent.h"
#include "SERVICE_id.h"
#include "route_t.h"
#include "JAVACOOKIE_id.h"
#include "../blockchain/___blockchainEvent.h"
namespace invoiceEvent
{


    class MakeInvoiceREQ: public Event::Base
    {


    public:
        static Base* construct(const route_t &r)
        {
            Base* z=new MakeInvoiceREQ(r);
            return z;
        }
        MakeInvoiceREQ(const blockchainData::Invoice& inv)
            :Base(invoiceEventEnum::MakeInvoiceREQ),invoice(inv)
        {}
        MakeInvoiceREQ(const route_t&r)
            :Base(invoiceEventEnum::MakeInvoiceREQ,r) {}
        blockchainData::Invoice invoice;

        void unpack(inBuffer& o)
        {
            o>>invoice;
        }
        void pack(outBuffer&o) const
        {
            o<<invoice;
        }
        void jdump(Json::Value &) const
        {
        }

    };
    class MakeInvoiceRSP: public Event::Base
    {


    public:
        static Base* construct(const route_t &r)
        {
            return new MakeInvoiceRSP(r);
        }
        MakeInvoiceRSP(int _errCode, const std::string& _errstr,
                       const int64_t &_newid,const int64_t& _rnd,
                       const blockchainData::Invoice& inv)
            :Base(invoiceEventEnum::MakeInvoiceRSP),
             errcode(_errCode),
             errstr(_errstr),
             newid(_newid),
             rnd(_rnd),
             invoice(inv)
        {}
        MakeInvoiceRSP(const route_t&r)
            :Base(invoiceEventEnum::MakeInvoiceRSP,r) {}
        int errcode;
        std::string errstr;
        int64_t newid;
        int64_t rnd;
        blockchainData::Invoice invoice;
        void unpack(inBuffer& o)
        {
            o>>errcode>>errstr>>newid>>rnd>>invoice;
        }
        void pack(outBuffer&o) const
        {
            o<<errcode<<errstr<<newid<<rnd<<invoice;
        }
        void jdump(Json::Value &v) const
        {
            v["errcode"]=errcode;
            v["errstr"]=errstr;
            //v["newid"]=newid;
        }

    };

}
#endif
