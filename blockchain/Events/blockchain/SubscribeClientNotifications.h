#ifndef _____H5GIRSubscribeClientNotifications1
#define _____H5GIRSubscribeClientNotifications1
#include "___blockchainEvent.h"
#include "SERVICE_id.h"
#include "route_t.h"
namespace blockchainEvent
{


    class SubscribeClientNotifications: public Event::Base
    {


    public:
        static Base* construct(const route_t &r)
        {
            Base* z=new SubscribeClientNotifications(r);
            return z;
        }
        SubscribeClientNotifications(const SHA1_id& _publicKey,
                                     const route_t&r)
            :Base(blockchainEventEnum::SubscribeClientNotifications,r),
             publicKey(_publicKey)
        {}
        SubscribeClientNotifications(const route_t&r)
            :Base(blockchainEventEnum::SubscribeClientNotifications,r) {}
        SHA1_id publicKey;

        void unpack(inBuffer& o)
        {
            o>>publicKey;
        }
        void pack(outBuffer&o) const
        {
            o<<publicKey;
        }
        void jdump(Json::Value &j) const
        {
            j["SHA1"]=publicKey.hex();
        }

    };

}
#endif
