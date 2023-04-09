#ifndef _____H5PAY1zBlockchainChanged1
#define _____H5PAY1zBlockchainChanged1
#include "___blockchainEvent.h"
#include "SERVICE_id.h"
#include "route_t.h"
namespace blockchainEvent
{


    class BlockchainChanged: public Event::Base
    {


    public:
        static Base* construct(const route_t &r)
        {
            Base* z=new BlockchainChanged(r);
            return z;
        }
        BlockchainChanged(int64_t _lastPaymentId,const route_t&r)
            :Base(blockchainEventEnum::BlockchainChanged,r), lastBlockId(_lastPaymentId) {}
        BlockchainChanged(const route_t&r)
            :Base(blockchainEventEnum::BlockchainChanged,r) {}

        int64_t lastBlockId;
        void unpack(inBuffer& b)
        {
            b>>lastBlockId;
        }
        void pack(outBuffer& b) const
        {
            b<<lastBlockId;
        }
        void jdump(Json::Value &j) const
        {
            j["lastPaymentId"]=(int)lastBlockId;
        }

    };

}
#endif
