#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include "tools_mt.h"
#include <QFileDialog>
#include "url.h"
#include "st_rsa.h"
#include "js_utils.h"
#include "_QUERY.h"
#include "st_FILE.h"
#include "configDB.h"
#include "blockchain_version.h"
#include "gTry.h"
#ifndef __ANDROID__
#endif
#include "megatron_config.h"
#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Transaction.h"
#include <QDesktopServices>
#include <QInputDialog>
#include "megatronClient.h"
#include "../Events/invoice/MakeInvoice.h"
#include "../Events/invoice/GetInvoice.h"
#include "../Events/blockchain/PublishBlock.h"
#include <sys/stat.h>


MainWindow::MainWindow(QWidget *parent, int argc, char** argv) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),handler(NULL),lastInvoice(NULL)
{
    GTRY;
    ui->setupUi(this);
    setlocale(LC_ALL,"en_US.UTF-8");
    auto instance=BlockchainHandler::init(argc,argv,"");
    srand(iUtils->getNow().get()%0xffffffff);
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(100);

    if(!handler)
    {

        handler=new GuiBlockChainHandler(instance);
    }

    loadKeyStores();




    GCATCH;
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::onTimer()
{

    MUTEX_INSPECTOR;
    XTRY;
    IObjectProxyPolled* op=dynamic_cast<IObjectProxyPolled*>
                           (handler->instance->getServiceOrCreate(ServiceEnum::ObjectProxyPolled)/*->cast(UnknownCast::IObjectProxyPolled)*/);
    if(!op)
        throw  CommonError("if(!op)");
    op->poll();
    XPASS;
}



void MainWindow::connected()
{


}
void MainWindow::disconnected()
{
}
void MainWindow::connect_failed()
{
}


void MainWindow::connectToHandler()
{
    GTRY;
    if(!checkHandler())return;
    connect(handler,SIGNAL(connected()),this,SLOT(connected()));
    connect(handler,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(handler,SIGNAL(connect_failed()),this,SLOT(connect_failed()));
    connect(handler,SIGNAL(onMakeInvoiceRSP(const invoiceEvent::MakeInvoiceRSP*)),this,SLOT(onMakeInvoiceRSP(const invoiceEvent::MakeInvoiceRSP*)));
    connect(handler,SIGNAL(onGetInvoiceRSP(const invoiceEvent::GetInvoiceRSP*)),this,SLOT(onGetInvoiceRSP(const invoiceEvent::GetInvoiceRSP*)));
    connect(handler,SIGNAL(onPublishBlockRSP(const blockchainEvent::PublishBlockRSP*)),this,SLOT(onPublishBlockRSP(const blockchainEvent::PublishBlockRSP*)));
    connect(handler,SIGNAL(onPaymentReceived(std::string)),this,SLOT(onPaymentReceived(std::string)));

    GCATCH;
}
bool MainWindow::checkHandler()
{
    if(!handler)
    {
        QMessageBox::warning(this,"Ошибка","Не выполнен вход");
        return false;
    }
    return true;
}

void MainWindow::onMakeInvoiceRSP(const invoiceEvent::MakeInvoiceRSP* e)
{
    QMessageBox::warning(this,"new invoice",QString("id: %1").arg(e->newid));
}

void MainWindow::onPublishBlockRSP(const blockchainEvent::PublishBlockRSP *e)
{
    if(e->errcode)
    {
        QMessageBox::warning(this,"onPublishBlockRSP error",QString("%1").arg(e->errstr.c_str()));
        return;
    }
    QMessageBox::warning(this,"onPublishBlockRSP OK","OK");

}
void MainWindow::onGetInvoiceRSP(const invoiceEvent::GetInvoiceRSP* e)
{
    //QMessageBox::warning(this,"onGetInvoiceRSP new invoice",QString("id: "));
    if(e->errcode)
    {
        QMessageBox::warning(this,"onGetInvoiceRSP error",QString("%1").arg(e->errstr.c_str()));
        return;
    }
    const blockchainData::Invoice &inv=e->invoice;
//    inBuffer in(e->invoice);
//    in>>inv;
    lastInvoice=e;
    std::string report=
        "Emitent key hash: "+inv.emitentPublicKeySHA1.hex()+"\n"+
        "Creditor key hash: "+inv.creditorPublicKeySHA1.hex()+"\n"+
        "Amount: "+std::to_string(inv.amount)+"\n"+
        "Comments: "+inv.comments+"\n";


    ui->label_invoiceInfo->setText(QString::fromStdString(report));
}









void MainWindow::loadKeyStores()
{
    XTRY;
    SQLite::Database d(sqlDbName(HANDLER_DB),SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
//    SQLite::Transaction tr(d);

//    Sqlite3Wrapper dbh(KS_DB_NAME);
    SQLite::Statement q(d,"select id,data from tbl_keystore order by id");
    ui->comboBox_keystores->clear();
    //ui->comboBox_payer->clear();
    ConfigDB_private c;
    int currentIdx=c.get_uint64_t("def_keystore_idx",0);
    logErr2("get def_keystore_idx %d",currentIdx);
    logErr2("currentIdx %d",currentIdx);
    int i=0;
    while(q.executeStep())
    {
//        auto& z=r->values[i];
//        if(z.size()!=3)
//            throw CommonError("if(z.size()!=3)");
        std::string id=q.getColumn(0).getString();
        std::string buf=q.getColumn(1);

        inBuffer in(buf);
        blockchainData::KeyStore ks;
        in>>ks;
        ui->comboBox_keystores->addItem((id+"@"+ks.document.name).c_str());
        combo2keystore[i]=ks;
        //handler->publicKeys.insert(ks.document.publicKey);
        i++;
    }

    ui->comboBox_keystores->setCurrentIndex(currentIdx);
    XPASS;

}
void MainWindow::on_tabWidget_currentChanged(int index)
{
    GTRY;
    logErr2("void MainWindow::on_tabWidget_currentChanged(int index) %d",index);
    if(index==1)
    {
        return;
    }
    if(index==3)
    {

    }
    GCATCH;

}


void MainWindow::on_comboBox_keystores_currentIndexChanged(int index)
{
    GTRY;
    logErr2("void MainWindow::on_comboBox_keystores_currentIndexChanged(int index) %d",index);
    {
        ui->lineEdit_keystore_name->setText(combo2keystore[index].document.name.c_str());
        ui->lineEdit_keystore_emitent_code->setText(combo2keystore[index].getEmitentCode().c_str());
        ui->lineEdit_keystore_public_account_code->setText(combo2keystore[index].getPublicAccountCode().c_str());
        ui->plainTextEdit_keystore_content->setPlainText(combo2keystore[index].dump().c_str());


        ConfigDB_private c;
        outBuffer o;
        o<<combo2keystore[index];
        c.set("keystore",o.asString()->asString());
        c.set("def_keystore_idx",std::to_string(index));
        logErr2("set def_keystore_idx %d",index);
        return;
    }

    GCATCH;
}



void MainWindow::on_pushButton_createAccount_clicked()
{
    GTRY;
    try {
        logErr2("void MainWindow::on_pushButton_createAccount_clicked()");


        handler->createAccount(ui->lineEdit_accountName->text().toStdString(),ui->lineEdit_keyStorePassword->text().toStdString(),"mainWindow");
        loadKeyStores();

    }
    catch(CommonError& e)
    {
        logErr2("CommonError: %s",e.what());
    }
    GCATCH;

}



void MainWindow::on_pushButton_invoice_create_clicked()
{

    bool ok=true;
    double amount=ui->lineEdit_invoiceAmount->text().toDouble(&ok);
    if(!ok) throw CommonError("!ok");
    std::string comments=ui->plainTextEdit_invoiceComments->toPlainText().toStdString();
    handler->makeInvoice(std::to_string(amount),comments,"");

//    int idx=ui->comboBox_keystores->currentIndex();
//    blockchainData::KeyStore ks=combo2keystore[idx];

//    blockchainData::Invoice invoice;
//    invoice.amount=amount;
//    invoice.comments=comments;
//    invoice.date=time(NULL);
//    invoice.creditorPublicKey=ks.document.publicKey;
//    //invoice.emitentPublicKey=std::string((char*)emitent_key_pub,emitent_key_pub_size);

//    outBuffer o;
//    o<<invoice;
//    REF_getter<Event::Base> e=new invoiceEvent::MakeInvoiceREQ(o.asString()->asString(),"gui");
//    REF_getter<Event::Base> et=new dfsReferrerEvent::ToplinkDeliverREQ(ServiceEnum::IMInvoicer,e,handler);
//    handler->sendEvent(ServiceEnum::ReferrerClient,et);

}

void MainWindow::on_pushButtonGetInvoice_clicked()
{
    GTRY;
    bool ok=true;
    std::string line=ui->lineEditInvoiceId->text().toStdString();
    std::vector<std::string> v=iUtils->splitString(".",line);
    if(v.size()==2)
    {
        int64_t invId=atoll(v[0].c_str());
        int64_t invRnd=atoll(v[1].c_str());
        REF_getter<Event::Base> e=new invoiceEvent::GetInvoiceREQ(invId,invRnd);

        REF_getter<Event::Base> et=new dfsReferrerEvent::ToplinkDeliverREQ(ServiceEnum::IMInvoicer,e,handler);
        handler->sendEvent(ServiceEnum::ReferrerClient,et);

    }
    else ok=false;

    if(!ok)
        throw CommonError("if(!ok) %s",__PRETTY_FUNCTION__);

    GCATCH;
}

void MainWindow::on_pushButtonPay_clicked()
{
    GTRY;
    if(!lastInvoice.valid())
    {
        QMessageBox::warning(this,"Error","Not found invoice");
    }
    bool ok=false;
    QString pass=QInputDialog::getText(this,"Enter password","password:",QLineEdit::PasswordEchoOnEdit,"",&ok);
    if(ok)
    {
        ConfigDB_private c;

        int idx=ui->comboBox_keystores->currentIndex();
        ui->lineEdit_keystore_name->setText(combo2keystore[idx].document.name.c_str());

        blockchainData::KeyStore keystore=combo2keystore[idx];

        blockchainData::Payment payment;
//        std::vector<blockchainData::PaymentSet::Document::Payment> pays;
//        blockchainData::PaymentSet::Document::Payment pay;

//        inBuffer in(lastInvoice->invoice);
        const blockchainData::Invoice &linv=lastInvoice->invoice;
//        in>>linv;
        payment.document.amount=linv.amount;
        payment.document.creditorPublicKeySHA1=linv.creditorPublicKeySHA1;
        payment.document.invoiceId=std::to_string(lastInvoice->invoiceId);
//        pay.amount=linv.amount;
//        pay.creditorPublicKey=linv.creditorPublicKey;
//        pay.invoiceId=lastInvoice->invoiceId;
//        pays.push_back(pay);


        /// TODO

        payment.create(linv.emitentPublicKeySHA1,
                       keystore.document.publicKey.sha1(),
                       linv.creditorPublicKeySHA1,
                       linv.amount,std::to_string(lastInvoice->invoiceId),
                       time(NULL),
                       keystore.getPrivateKey(pass.toStdString())
                      );

        outBuffer o;
        o<<blockchainData::BLOCK_PAYMENT<<payment;
        REF_getter<Event::Base> e=new blockchainEvent::PublishBlockREQ(o.asString()->asString());
        REF_getter<Event::Base> et=new dfsReferrerEvent::ToplinkDeliverREQ(ServiceEnum::BlockchainTop,e,handler);
        handler->sendEvent(ServiceEnum::ReferrerClient,et);

    }
    GCATCH;
}
void MainWindow::onPaymentReceived(std::string block)
{

    QMessageBox::warning(this,"payment received",QString("zzzzzzz")
                        );
}

void MainWindow::on_pushButton_scan_clicked()
{

        auto lst=iUtils->load_file("/Users/sergejbelalov/ira/z");

        auto v=iUtils->splitString("\r\n",lst);
        logErr2("v size %d",v.size());
        std::map<std::string,std::vector<std::string> > cache;
        for(auto& z:v)
        {
            struct stat st;
            if(!stat(z.c_str(),& st))
            {
                logErr2("%x",st.st_mode);
                if(st.st_mode&S_IFREG)
                {
                    logErr2("file %s",z.c_str());
                    auto body=iUtils->load_file(z);
                    I_ssl *ssl=(I_ssl*)iUtils->queryIface(Ifaces::SSL);
                    auto sha=ssl->sha256(body);
                    cache[sha].push_back(z);

                }
            }
        }
        for(auto& z:cache)
        {
            if(z.second.size()>1)
            {
                for(size_t i=1;i<z.second.size();i++)
                {

                    unlink(z.second[i].c_str());
                    logErr2("@rem %s",z.second[i].c_str());
                }
            }
        }

}
