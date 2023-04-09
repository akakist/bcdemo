#include "pconfig.h"
#include "objectHandler.h"
#include "tools_mt.h"
#include <stdint.h>
#ifdef __ANDROID__
#include <jni.h>
#include <android/log.h>
#endif
#include <string.h>
#include <inttypes.h>
#include <megatron_config.h>
#include <SQLiteCpp/Database.h>
#include "jsonHandler.h"
#include "lft_jni.h"
#ifdef __ANDROID__
#include "jni.h"
#endif
#ifdef __ANDROID__
#include "ISSL.h"
#include "__crc32.h"
#include "../Events/blockchain/BlockchainChanged.h"
#include "../Events/invoice/MakeInvoice.h"
#include "../Events/invoice/GetInvoice.h"
#include "../Events/blockchain/PublishBlock.h"
#include "../Events/blockchain/GetAmount.h"
#include "../Events/blockchain/GetAmount.h"
#include "../Events/blockchain/___blockchainEvent.h"
#include "st_rsa.h"
void ndk_stub()
{
}

std::string getString(JNIEnv * env,jstring s);
std::string getString(JNIEnv * env,jstring s)
{
    jboolean isCopy;
    std::string ret;
    const char *str=env->GetStringUTFChars(s, &isCopy);
    if(str)
    {
        ret=str;
    }
    if(isCopy==JNI_TRUE)
    {
        env->ReleaseStringUTFChars(s, str);
    }
    return ret;
}
jbyteArray fromString(JNIEnv * env, const std::string& s)
{
    jbyteArray result=env->NewByteArray(s.size());

    env->SetByteArrayRegion(result, 0, s.size(), (jbyte*)s.data());
    return result;

}
jintArray fromVectorInt(JNIEnv * env, const std::vector<int>& s)
{
    jintArray result=env->NewIntArray(s.size());

    env->SetIntArrayRegion(result, 0, s.size(), (jint *)s.data());
    return result;

}

blockchainData::KeyStore getKeystoreOrThrow()
{
    ConfigDB_private c;
    std::string sks=c.get_string("keystore","");
    if(sks.size()==0)
        throw CommonError("if(sks.size()==0)");
    inBuffer in(sks);
    blockchainData::KeyStore ks;
    in>>ks;
    return ks;
}


std::string getKeystoreName()
{
    ConfigDB_private c;
    std::string sks=c.get_string("keystore","");
    if(sks.size()==0) {
        return "???";
    }
    inBuffer in(sks);
    blockchainData::KeyStore ks;
    in>>ks;
    return ks.document.name;
}




extern "C"
JNICALL void Java_com_xdiscount_bcwallet_utils_NDKHelper_ping(JNIEnv * env, jobject _this)
{
    JBEGIN;
    JEND;
}
extern "C"
JNICALL void Java_com_xdiscount_bcwallet_utils_NDKHelper_setFileDir(JNIEnv * env, jobject _this,jstring filesDir)
{
//    __remote_host=CAPS_ADDRESS;
    __files_dir=getString(env,filesDir);
}

extern "C"
JNICALL void Java_com_xdiscount_bcwallet_utils_NDKHelper_createAccount(JNIEnv * env, jobject _this,jstring name,jstring password,jstring javaCookie)
{

    JBEGIN;
    XTRY;

    ndkHandler->createAccount(getString(env,name),getString(env,password),getString(env,javaCookie));

    XPASS;
    JEND;
}
extern "C"
JNICALL jbyteArray Java_com_xdiscount_bcwallet_utils_NDKHelper_getKeyStoreNameB64(JNIEnv * env, jobject _this,jstring ksB64)
{

    JBEGIN;
    XTRY;
//    ndkHandler->get
    std::string k=iUtils->Base64Decode(getString(env,ksB64));
    if(k.size()==0)
        throw CommonError("if(k.size()==0)");

    inBuffer in(k);
    blockchainData::KeyStore ks;
    in>>ks;
    return fromString(env,ks.document.name);
    XPASS;
    JEND;
    return NULL;
}
extern "C"
JNICALL void Java_com_xdiscount_bcwallet_utils_NDKHelper_addKeystore(JNIEnv * env, jobject _this,jstring ksB64)
{

    JBEGIN;
    XTRY;
    SQLite::Database d(sqlDbName(HANDLER_DB),SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    SQLite::Transaction tr(d);

    ndkHandler->addKeyStoreB64(tr,getString(env,ksB64));
    tr.commit();
    XPASS;
    JEND;
}





extern "C"
JNICALL jbyteArray Java_com_xdiscount_bcwallet_utils_NDKHelper_getAccountInfoFull(JNIEnv * env, jobject _this,jlong ksId)
{

    JBEGIN;
    XTRY;

    SQLite::Database d(sqlDbName(HANDLER_DB),SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    Json::Value j=ndkHandler->getAccountInfo(d,ksId);
    return fromString(env,j.toStyledString());
    XPASS;
    JEND;
    return NULL;
}




extern "C"
JNICALL jbyteArray Java_com_xdiscount_bcwallet_utils_NDKHelper_getKeystoreName(JNIEnv * env, jobject _this)
{

    JBEGIN;
    XTRY;
    auto z=getKeystoreName();
    return fromString(env,z);
    XPASS;
    JEND;
    return NULL;
}
extern "C"
JNICALL void Java_com_xdiscount_bcwallet_utils_NDKHelper_getAmountREQ(JNIEnv * env, jobject _this,jstring _javaCookie)
{


    JBEGIN;
    XTRY;
    blockchainData::KeyStore ks=getKeystoreOrThrow();
    ndkHandler->getAmountREQ(ks.document.publicKey.sha1(),getString(env,_javaCookie));

    XPASS;
    JEND;
}

extern "C"
JNICALL void Java_com_xdiscount_bcwallet_utils_NDKHelper_makeInvoice(JNIEnv * env, jobject _this,jstring _amount, jstring _comments,jstring _javaCookie)
{


    JBEGIN;
    XTRY;
    ndkHandler->makeInvoice(getString(env,_amount),getString(env,_comments),getString(env,_javaCookie));

    XPASS;
    JEND;
}
extern "C"
JNICALL jbyteArray Java_com_xdiscount_bcwallet_utils_NDKHelper_getInvoiceById(JNIEnv * env, jobject _this,jlong invoiceId)
{

    JBEGIN;
    XTRY;
    if(ndkHandler->invoices_cached.count(invoiceId)==0)
        throw CommonError("if(ndkHandler->invoices_cached.count(invoiceId)==0)");
    blockchainData::Invoice inv=ndkHandler->invoices_cached[invoiceId];
    Json::Value j;
    j["id"]=std::to_string(invoiceId);
    j["amount"]=std::to_string(inv.amount);
    j["comments"]=inv.comments;

    return fromString(env,j.toStyledString());
    XPASS;
    JEND;
    return NULL;
}
extern "C"
JNICALL void Java_com_xdiscount_bcwallet_utils_NDKHelper_getInvoiceREQ(JNIEnv * env, jobject _this,jlong invoiceId,jlong rnd,jstring javaCookie)
{

    JBEGIN;
    XTRY;
    ndkHandler->getInvoiceREQ(invoiceId,rnd,getString(env,javaCookie));
    XPASS;

    JEND;
}

extern "C"
JNICALL void Java_com_xdiscount_bcwallet_utils_NDKHelper_PublishBlock(JNIEnv * env, jobject _this,jlong invId, jstring  password,jstring javaCookie)
{

    MUTEX_INSPECTOR;
    JBEGIN;
    XTRY;
    ndkHandler->makePayment(invId,getString(env,password),getString(env,javaCookie));
    XPASS;
    JEND;
}


extern "C"
jobjectArray Java_com_xdiscount_bcwallet_utils_NDKHelper_getMessage(JNIEnv * env, jobject _this)
{
//    JBEGIN;
    std::pair<std::string,std::string>p=ndkHandler->getMessage();
    jobjectArray ret= (jobjectArray)env->NewObjectArray(2,env->FindClass("java/lang/String"),env->NewStringUTF(""));
    jstring  a1=env->NewStringUTF(p.first.c_str());
    jstring  a2=env->NewStringUTF(iUtils->Base64Encode(p.second).c_str());

    env->SetObjectArrayElement(ret,0,a1);
    env->SetObjectArrayElement(ret,1,a2);
    return ret;
//    JEND;
    return NULL;
}




#endif
extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_xdiscount_bcwallet_utils_NDKHelper_getInvoiceListItemInvId(JNIEnv *env, jclass type,
        jint n) {

    JBEGIN;
    XTRY;
    if(n<ndkHandler->invoices_cached.count(n))
    {
        auto i=ndkHandler->invoices_cached[n];
        Json::Value j;
        j["id"]=std::to_string(n);
        j["amount"]=std::to_string(i.amount);
        j["comments"]=i.comments;
        j["date"]=std::to_string(i.date);
        return fromString(env,j.toStyledString());
    }
    else throw CommonError("!if(n<ndkHandler->invoicesCurrentToPay.size())");
    XPASS;
    JEND;
    return NULL;


}
extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_xdiscount_bcwallet_utils_NDKHelper_getKeystores(JNIEnv *env, jclass type) {

    JBEGIN;
    XTRY;
    SQLite::Database d(sqlDbName(HANDLER_DB),SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    auto v=ndkHandler->getAccountIds(d);
    Json::Value jret;
    for(auto z:v)
    {
        Json::Value j;
        j["id"]=z;
        jret.append(j);
    }
    if(v.size())
        return fromString(env,jret.toStyledString());
    XPASS;
    JEND;
    return NULL;

}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_xdiscount_bcwallet_utils_NDKHelper_getKeyStoreInfo(JNIEnv *env, jclass type, jlong id) {

    JBEGIN;
    XTRY;
    SQLite::Database d(sqlDbName(HANDLER_DB),SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    Json::Value z=ndkHandler->getAccountInfo(d,id);
    return fromString(env,z.toStyledString());

    XPASS;
    JEND;
    return NULL;

}
extern "C"
JNIEXPORT void JNICALL
Java_com_xdiscount_bcwallet_utils_NDKHelper_getAmountREQforDefaultKeystore(JNIEnv *env,
        jclass type,jstring javaCookie) {
    JBEGIN;
    XTRY;
    ndkHandler->getAmountREQ_forDefaultKeystore(getString(env,javaCookie));
    XPASS;
    JEND;

}

extern "C"
JNIEXPORT void JNICALL
Java_com_xdiscount_bcwallet_utils_NDKHelper_getCreditLimitREQforDefaultKeystore(JNIEnv *env,
                                                                           jclass type,jstring javaCookie) {
    JBEGIN;
        XTRY;
            ndkHandler->getCreditLimitREQ_forDefaultKeystore(getString(env,javaCookie));
        XPASS;
    JEND;

}


extern "C"
JNIEXPORT void JNICALL
Java_com_xdiscount_bcwallet_utils_NDKHelper_setDefaultKeystore(JNIEnv *env, jclass type,
        jlong accountId) {

    JBEGIN;
    XTRY;
    ndkHandler->setDefaultKeystore(accountId);
    XPASS;
    JEND;


}
extern "C"
JNIEXPORT void JNICALL
Java_com_xdiscount_bcwallet_utils_NDKHelper_subscribeReferrerNotifications(JNIEnv *env,
        jclass type) {

    // TODO


}