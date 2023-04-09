#ifndef _______________TL_JNI_____H
#define _______________TL_JNI_____H
#include "jsonHandler.h"
#include "lft_jni.h"
#include "ndkHandler.h"
#ifdef __ANDROID__
#include <jni.h>

//extern megatron *mega;
extern NDKHandler* ndkHandler;

inline jint throwNdkException( JNIEnv *env, const char *message )
{

    jclass exClass;
    const char *className = "com/xdiscount/bcwallet/utils/NdkException" ;
    exClass = env->FindClass(className );
    if ( exClass == NULL ) {
        logErr2("exClass==NULL");
    }

    return env->ThrowNew(exClass, message );
}
//extern std::string __remote_host;
extern std::string __files_dir;
#define JBEGIN try{check_megatron();
#define JEND     }catch(std::exception& e)\
    {\
        throwNdkException(env,e.what());\
        logErr2("CommonError %s %s",e.what(),_DMI().c_str());\
    }\
    catch(...)\
    {\
        throwNdkException(env,"...");\
        logErr2("exception ... %s",_DMI().c_str());\
    }


void check_megatron();

#endif
#endif










