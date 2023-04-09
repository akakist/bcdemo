#ifndef _________H_GetBlockForSingleIdForClientREQ1
#define _________H_GetBlockForSingleIdForClientREQ1
#include "___blockchainEvent.h"
namespace blockchainEvent
{
    class GetBlockForSingleIdForClientREQ: public Event::Base
    {


    public:
        static Base* construct(const route_t &r)
        {
            return new GetBlockForSingleIdForClientREQ(r);
        }
        GetBlockForSingleIdForClientREQ(int64_t _blockId,
                                        const route_t&r)
            :Base(blockchainEventEnum::GetBlockForSingleIdForClientREQ,r),
             blockId(_blockId)
        {}
        GetBlockForSingleIdForClientREQ(const route_t&r)
            :Base(blockchainEventEnum::GetBlockForSingleIdForClientREQ,r) {}

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

    class GetBlockForSingleIdForClientRSP: public Event::Base
    {



    public:
        static Base* construct(const route_t &r)
        {
            return new GetBlockForSingleIdForClientRSP(r);
        }
        GetBlockForSingleIdForClientRSP(int64_t _blockId,const std::string& _block,
                                        const route_t&r)
            :Base(blockchainEventEnum::GetBlockForSingleIdForClientRSP,r),
             blockId(_blockId),
             block(_block)
        {}
        GetBlockForSingleIdForClientRSP(const route_t&r)
            :Base(blockchainEventEnum::GetBlockForSingleIdForClientRSP,r) {}
        int64_t blockId;
        std::string block;
        void unpack(inBuffer& o)
        {
            o>>blockId>>block;
        }
        void pack(outBuffer&o) const
        {
            o<<blockId<<block;
        }
        void jdump(Json::Value &) const
        {
        }

    };

}
#endif
