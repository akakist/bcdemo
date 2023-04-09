#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "blockchainHandler.h"
#include "GuiBlockchainHandler.h"
#include "blockchainHandler.h"

#include "Events/DFS/Referrer/InitClient.h"
#include "../Events/blockchain/PublishBlock.h"

#define KS_DB_NAME "ks"
namespace Ui {
    class MainWindow;
}
struct auth2
{

};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent, int argc, char **argv);
    ~MainWindow();

private slots:
    void onTimer();




    void connected();
    void disconnected();
    void connect_failed();



    void onMakeInvoiceRSP(const invoiceEvent::MakeInvoiceRSP*);
    void onGetInvoiceRSP(const invoiceEvent::GetInvoiceRSP*);

    void onPublishBlockRSP(const blockchainEvent::PublishBlockRSP*);


    void onPaymentReceived(std::string block);



    void on_tabWidget_currentChanged(int index);


    void on_comboBox_keystores_currentIndexChanged(int index);

    void on_pushButton_createAccount_clicked();

    void on_pushButton_invoice_create_clicked();

    void on_pushButtonGetInvoice_clicked();

    void on_pushButtonPay_clicked();

    void on_pushButton_scan_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;


    void loadKeyStores();

    void connectToHandler();
    bool checkHandler();

    GuiBlockChainHandler *handler;


    std::map<int,blockchainData::KeyStore> combo2keystore;
    std::map<int,std::string> combo2contact;

    REF_getter<invoiceEvent::GetInvoiceRSP> lastInvoice;

};

#endif // MAINWINDOW_H
