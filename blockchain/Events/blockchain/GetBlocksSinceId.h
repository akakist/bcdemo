#ifndef _________H_GetBlocksSinceIdREQ1
#define _________H_GetBlocksSinceIdREQ1
#include "___blockchainEvent.h"
namespace blockchainEvent
{
    class GetBlocksSinceIdREQ: public Event::Base
    {
        


    public:
        static Base* construct(const route_t &r)
        {
            return new GetBlocksSinceIdREQ(r);
        }
        GetBlocksSinceIdREQ(int64_t _blockId,
                            const route_t&r)
            :Base(blockchainEventEnum::GetBlocksSinceIdREQ,r),blockId(_blockId)
        {}
        GetBlocksSinceIdREQ(const route_t&r)
            :Base(blockchainEventEnum::GetBlocksSinceIdREQ,r) {}
        int64_t blockId;
        void unpack(inBuffer& o)
        {
            o>>blockId;
        }
        void pack(outBuffer&o) const
        {
            o<<blockId;
        }
        void jdump(Json::Value &v) const
        {
            v["blockId"]=(int)blockId;
        }

    };

    class GetBlocksSinceIdRSP: public Event::Base
    {
        


    public:
        static Base* construct(const route_t &r)
        {
            return new GetBlocksSinceIdRSP(r);
        }
        GetBlocksSinceIdRSP(const std::vector<std::string>& _blocks, int64_t _lastBlockIHave,
                            const route_t&r)
            :Base(blockchainEventEnum::GetBlocksSinceIdRSP,r),blocks(_blocks),lastBlockIHave(_lastBlockIHave)
        {}
        GetBlocksSinceIdRSP(const route_t&r)
            :Base(blockchainEventEnum::GetBlocksSinceIdRSP,r) {}
        std::vector<std::string> blocks;
        int64_t lastBlockIHave;
        void unpack(inBuffer& o)
        {
            o>>blocks>>lastBlockIHave;
        }
        void pack(outBuffer&o) const
        {
            o<<blocks<<lastBlockIHave;
        }
        void jdump(Json::Value &j) const
        {
            j["lastBlockIHave"]=(int)lastBlockIHave;
            j["blocks size"]=(int)blocks.size();

        }

    };

}
#endif
