#include "IInstance.h"
#include "colorOutput.h"
#include "configObj.h"
#include "version_mega.h"
#include "CUtils.h"
#include "ISSL.h"
#include "st_rsa.h"
//bool done_test_http=false;
void registerRPCService(const char* pn);
void registerSocketModule(const char* pn);
void registerTimerService(const char* pn);
void registerSSL(const char* pn);
void registerOscarModule(const char* pn);
void registerOscarSecureModule(const char* pn);
void registertestServerWebService(const char* pn);
void registerHTTPModule(const char* pn);
int mainParseKeystore.cpp(int argc, char** argv )
{
    try {
        iUtils=new CUtils(argc, argv, "generateRSA");

        if(argc!=3)
        {
            printf("usege: generateRSA N name\n");
            exit(0);
        }
        int rsa_size=atoi(argv[1]);
        std::string name=argv[2];
        registerSSL(NULL);
        st_rsa rsa;
        rsa.generate_key(rsa_size);


        FILE* f=fopen(name.c_str(),"w");
        if(!f)
        {
            fprintf(stderr,"cannot open %s\n",name.c_str());
            exit(1);
        }
        fprintf(f,"public_key %s\n",iUtils->bin2hex(rsa.getPublicKey()).c_str());
        fprintf(f,"private_key %s\n",iUtils->bin2hex(rsa.getPrivateKey()).c_str());
        fclose(f);



        delete iUtils;
        return 0;

    } catch (CommonError& e)
    {
        printf("CommonError %s\n",e.what());
    }
    return 1;
}
