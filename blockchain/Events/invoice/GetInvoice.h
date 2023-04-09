#ifndef _____H5GIRGetInvoiceREQz
#define _____H5GIRGetInvoiceREQz
#include "___invoiceEvent.h"
#include "SERVICE_id.h"
#include "route_t.h"
#include "JAVACOOKIE_id.h"
#include "../blockchain/___blockchainEvent.h"
namespace invoiceEvent
{


    class GetInvoiceREQ: public Event::Base
    {
        


    public:
        static Base* construct(const route_t &r)
        {
            Base* z=new GetInvoiceREQ(r);
            return z;
        }
        GetInvoiceREQ(const int64_t& _invId, int64_t _rnd)
            :Base(invoiceEventEnum::GetInvoiceREQ),invId(_invId),rnd(_rnd)
        {}
        GetInvoiceREQ(const route_t&r)
            :Base(invoiceEventEnum::GetInvoiceREQ,r) {}
        int64_t invId;
        int64_t rnd;
        void unpack(inBuffer& o)
        {
            o>>invId>>rnd;
        }
        void pack(outBuffer&o) const
        {
            o<<invId<<rnd;
        }
        void jdump(Json::Value &) const
        {
        }

    };
    class GetInvoiceRSP: public Event::Base
    {
        


    public:
        static Base* construct(const route_t &r)
        {
            Base* z=new GetInvoiceRSP(r);
            return z;
        }
        GetInvoiceRSP(int _errcode, const std::string& _errstr,
                      int64_t _invoiceId,
                      const blockchainData::Invoice& inv)
            :Base(invoiceEventEnum::GetInvoiceRSP),
             errcode(_errcode),errstr(_errstr),
             invoiceId(_invoiceId),invoice(inv)
        {}
        GetInvoiceRSP(const route_t&r)
            :Base(invoiceEventEnum::GetInvoiceRSP,r) {}
        int errcode;
        std::string errstr;
        int64_t invoiceId;

        blockchainData::Invoice invoice;

        void unpack(inBuffer& o)
        {
            o>>errcode>>errstr>>invoiceId>>invoice;
        }
        void pack(outBuffer&o) const
        {
            o<<errcode<<errstr<<invoiceId<<invoice;
        }
        void jdump(Json::Value &) const
        {
        }

    };

}
#endif
