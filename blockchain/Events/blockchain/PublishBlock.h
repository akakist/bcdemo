#ifndef _________BCJSON_REF_EVENT_____H5PAYz
#define _________BCJSON_REF_EVENT_____H5PAYz
#include "___blockchainEvent.h"
#include "SERVICE_id.h"
#include "route_t.h"
namespace blockchainEvent
{


    class PublishBlockREQ: public Event::Base
    {


    public:
        static Base* construct(const route_t &r)
        {
            Base* z=new PublishBlockREQ(r);
            return z;
        }
        PublishBlockREQ(const std::string& _block)
            :Base(blockchainEventEnum::PublishBlockREQ),block(_block)
        {}
        PublishBlockREQ(const route_t&r)
            :Base(blockchainEventEnum::PublishBlockREQ,r) {}
        std::string block;

        void unpack(inBuffer& o)
        {
            o>>block;
        }
        void pack(outBuffer&o) const
        {
            o<<block;
        }
        void jdump(Json::Value &v) const
        {
            v["block size"]=(int)block.size();

        }

    };
    class PublishBlockRSP: public Event::Base
    {


    public:
        static Event::Base* construct(const route_t &r)
        {
            return  new PublishBlockRSP(r);
        }
        PublishBlockRSP(int _errCode, const std::string& _errstr,
                        const std::string& _block, const route_t &r
                       )
            :Base(blockchainEventEnum::PublishBlockRSP,r),errcode(_errCode),errstr(_errstr),
             block(_block)
        {}
        PublishBlockRSP(const route_t&r)
            :Base(blockchainEventEnum::PublishBlockRSP,r) {}
        int errcode;
        std::string errstr;
        std::string block;
        void unpack(inBuffer& o)
        {
            o>>errcode>>errstr>>block;
        }
        void pack(outBuffer&o) const
        {
            o<<errcode<<errstr<<block;
        }
        void jdump(Json::Value &v) const
        {
            v["errcode"]=errcode;
            v["errstr"]=errstr;
            v["block size"]=(int)block.size();
        }

    };

}
#endif
