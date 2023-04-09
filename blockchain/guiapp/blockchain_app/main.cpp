#include "mainwindow.h"
#include <QApplication>
#include <signal.h>

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
    }
    catch (...)
    {
        printf("--Error: unknow error in on_term()\n");
    }
    exit(0);
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

int main(int argc, char *argv[])
{

    setupSignals();

//    mega=new megatron;


//    mega->run(argc,argv);


    QApplication a(argc, argv);

    int z;
    {
        MainWindow w(NULL,argc, argv);
        w.show();
        z= a.exec();
    }
//    usleep(100000);
//    delete mega;
    return z;

}
