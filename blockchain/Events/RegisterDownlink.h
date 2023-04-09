#ifndef _____H5GIRRegisterDownlink12
#define _____H5GIRRegisterDownlink12
#include "___imEvent.h"
#include "SERVICE_id.h"
#include "route_t.h"
namespace imEvent
{


    class RegisterDownlinkREQ: public Event::Base
    {
        enum {channel=CHANNEL_100};


    public:
        static Base* construct(const route_t &r)
        {
            Base* z=new RegisterDownlinkREQ(r);
            return z;
        }
        RegisterDownlinkREQ(const route_t&r)
            :Base(imEventEnum::RegisterDownlinkREQ,r) {}
//    std::string publicKey;

        void unpack(inBuffer& )
        {
        }
        void pack(outBuffer&) const
        {
        }
        void jdump(Json::Value &) const
        {
        }

    };
    class RegisterDownlinkRSP: public Event::Base
    {
        enum {channel=CHANNEL_100};


    public:
        static Base* construct(const route_t &r)
        {
            Base* z=new RegisterDownlinkRSP(r);
            return z;
        }
        RegisterDownlinkRSP(const route_t&r)
            :Base(imEventEnum::RegisterDownlinkRSP,r) {}
//    std::string publicKey;

        void unpack(inBuffer& )
        {
        }
        void pack(outBuffer&) const
        {
        }
        void jdump(Json::Value &) const
        {
        }

    };

}
#endif
