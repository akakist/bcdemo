#include "lft_jni.h"
#include <unistd.h>
#include <megatron_config.h>
#include <Events/DFS/Referrer/InitClient.h>
#include "megatronClient.h"
#include "ndkHandler.h"
//megatron *mega=NULL;
NDKHandler* ndkHandler=NULL;
std::string reverseProxyCode;
#ifdef DEBUG
#define WITH_SIGNALS
#endif

#ifdef WITH_SIGNALS
static bool ex=false;

void onterm(int signum)
{
    static std::string ss;
    char s[200];
    snprintf(s,sizeof(s),"Terminating on SIGNAL %d\n",signum);
    if(ss!=s)
    {
        printf("%s",s);
        ss=s;
    }

    if(signum==SIGINT) exit(1);
    try
    {
        if (!ex)
        {
#ifndef WIN32
            if(signum==SIGHUP)
            {
                iUtils->getIThreadNameController()->print_term(signum);
                return;
            }
            if(signum==SIGABRT)
            {
                iUtils->getIThreadNameController()->print_term(signum);
            }
#endif
            ex=true;
            iUtils->getIThreadNameController()->print_term(signum);
            DBG(printf("Terminating on SIGNAL %d\n",signum));
        }

    }
    catch (std::exception &e)
    {
        printf("onterm exception: %s\n",e.what());
        sleep(10);
    }
    catch (...)
    {
        printf("--Error: unknow error in on_term()\n");
        sleep(10);
    }
}
void setupSignals()
{

#ifndef _WIN32
    signal(SIGPIPE,SIG_IGN);
#endif
    signal(SIGABRT,onterm);
    signal(SIGTERM,onterm);
    signal(SIGINT,onterm);
    signal(SIGSEGV,onterm);
    signal(SIGFPE,onterm);
    signal(SIGILL,onterm);
#ifndef _WIN32
    signal(SIGQUIT,onterm);
    signal(SIGBUS,onterm);
    signal(SIGHUP,onterm);
#endif
    signal(10,onterm);

}
#endif
#ifdef __ANDROID__
extern "C"
jint JNI_OnLoad (JavaVM * vm, void * reserved)
{

    JNIEnv *env;
    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
    {
        logErr2("Failed to get the environment using GetEnv()");
        return -1;
    }

    return JNI_VERSION_1_4;
}
#endif
//void registerlftServiceLocal(const char* pn);

//std::string __remote_host;
std::string __files_dir;

//void registerJsonNoRefClientService(const char* pn);
//void registerJsonRefClientService(const char* pn);
//void registerJsonLocalRefClientService(const char* pn);
//void registerDFSReferrerService(const char* pn);

void check_megatron()
{
//    if(__remote_host.size()==0)
//    {
//        logErr2("if(__remote_host.size()==0)");
//        throw CommonError("if(__remote_host.size()==0)");
//    }
    if(__files_dir.size()==0)
    {
        logErr2("if(__files_dir.size()==0)");
        throw CommonError("if(__files_dir.size()==0)");
    }


    if(ndkHandler)
    {
        return;
    }
#ifdef WITH_SIGNALS
    setupSignals();
#endif

//    mega=new megatron;
//
//
//    mega->run(0,NULL);
//    auto iu=Megatron::initMegatron(0,NULL,__files_dir);
//    auto instance=Megatron::createInstance(
//            "\nRPC.ConnectionActivity=600.000000"
//            "\nRPC.IterateTimeoutSec=60.000000"
//            "\nRPC.ListenerBuffered.MaxThreadsCount=10"
//            "\nStart=RPC,ReferrerClient"
//            "\nOscarSecure.ListenerBuffered.MaxThreadsCount=10"
//            "\nOscarSecure.RSA_keysize=256"
//            "\nOscarSecure.maxPacketSize=33554432"
//            "\nRPC.BindAddr_MAIN=INADDR_ANY:0"
//            "\nRPC.BindAddr_RESERVE=NONE"
//            "\nSocketIO.ListenerBuffered.MaxThreadsCount=10"
//            "\nSocketIO.listen_backlog=128"
//            "\nSocketIO.maxOutBufferSize=8388608"
//            "\nSocketIO.size=1024"
//            "\nSocketIO.timeout_millisec=10"
//            "\nWebHandler.bindAddr=NONE"
//            "\nTelnet.BindAddr=NONE"
//            "\nimsfTestService1.ListenerBuffered.MaxThreadsCount=10"
//            "\nReferrerClient.T_001_common_connect_failed=20.000000"
//            "\nReferrerClient.T_002_D3_caps_get_service_request_is_timed_out=15.000000"
//            "\nReferrerClient.T_007_D6_resend_ping_caps_short=7.000000"
//            "\nReferrerClient.T_008_D6_resend_ping_caps_long=20.000000"
//            "\nReferrerClient.T_009_pong_timed_out_caps_long=40.000000"
//            "\nReferrerClient.T_020_D31_wait_after_send_PT_CACHE_on_recvd_from_GetReferrers=2.000000"
//            "\nReferrerClient.T_040_D2_cache_pong_timed_out_from_neighbours=2.000000"
//            );
//    iUtils->setFilesDir(__files_dir);

    //RPC::InterfaceClient::regEvents();

    //jsonRef::InterfaceClient::regEvents();
    auto instance=NDKHandler::init(0,NULL,__files_dir);
    ndkHandler=new NDKHandler(instance);

//    std::set<msockaddr_in> caps;
//    caps.insert(msockaddr_in(CAPS_ADDRESS));
//    msockaddr_in sa;
//    sa.initFromUrl(CAPS_ADDRESS);
//    caps.insert(sa);
//    for(auto& z:caps)
//    {
//        logErr2("caps %s",z.dump().c_str());
//    }
//    ndkHandler->sendEvent(ServiceEnum::ReferrerClient,new dfsReferrerEvent::InitClient(caps,ndkHandler));



//    registerJsonNoRefClientService(NULL);
//    registerJsonRefClientService(NULL);
//    registerJsonLocalRefClientService(NULL);
}

