#include "ndkHandler.h"
#include "tools_mt.h"
#include "st_FILE.h"

NDKHandler::NDKHandler(IInstance *ins): BlockchainHandler(ins)
{
}

void NDKHandler::signal_connected()
{
    signalUi("connected");
}
void NDKHandler::signal_disconnected()
{
    signalUi("disconnected");
}
void NDKHandler::signal_connect_failed()
{
    signalUi("connect_failed");
}
void NDKHandler::signal_authorized()
{
    signalUi("authorized");
}


void NDKHandler::signalUi(const std::string &opcode)
{
    //logErr2("signalUi: %s",opcode.c_str());
    MUTEX_INSPECTOR;
    Json::Value v;
    v["action"]=opcode;
    v["javaCookie"]="BROADCAST";
    push_msg(v,"");
}


