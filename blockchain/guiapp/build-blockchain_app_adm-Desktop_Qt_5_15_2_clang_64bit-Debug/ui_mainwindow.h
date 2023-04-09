/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_test_wnd;
    QWidget *centralWidget;
    QGridLayout *gridLayout_5;
    QTabWidget *tabWidget;
    QWidget *tab_create_account;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_accountName;
    QLabel *label_11;
    QLabel *label_10;
    QLineEdit *lineEdit_keyStorePassword;
    QPushButton *pushButton_createAccount;
    QSpacerItem *verticalSpacer;
    QWidget *tab_choose_account;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_keystore_emitent_code;
    QLineEdit *lineEdit_keystore_name;
    QLabel *label_2;
    QLineEdit *lineEdit_keystore_public_account_code;
    QLabel *label_7;
    QLabel *label_6;
    QComboBox *comboBox_keystores;
    QLabel *label_5;
    QPlainTextEdit *plainTextEdit_keystore_content;
    QWidget *tab_makeInvoice;
    QGridLayout *gridLayout_3;
    QPlainTextEdit *plainTextEdit_invoiceComments;
    QPushButton *pushButton_invoice_create;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *lineEdit_invoiceAmount;
    QWidget *tab_pay;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QLabel *label_invoiceInfo;
    QPushButton *pushButtonGetInvoice;
    QPushButton *pushButtonPay;
    QLineEdit *lineEditInvoiceId;
    QPushButton *pushButton_scan;
    QWidget *tab_genCards;
    QLineEdit *lineEdit_genCardCount;
    QPushButton *pushButton_genCards;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(834, 422);
        actionOpen_test_wnd = new QAction(MainWindow);
        actionOpen_test_wnd->setObjectName(QString::fromUtf8("actionOpen_test_wnd"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_5 = new QGridLayout(centralWidget);
        gridLayout_5->setSpacing(2);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(2, 2, 2, 2);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_create_account = new QWidget();
        tab_create_account->setObjectName(QString::fromUtf8("tab_create_account"));
        gridLayout = new QGridLayout(tab_create_account);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEdit_accountName = new QLineEdit(tab_create_account);
        lineEdit_accountName->setObjectName(QString::fromUtf8("lineEdit_accountName"));

        gridLayout->addWidget(lineEdit_accountName, 0, 1, 1, 1);

        label_11 = new QLabel(tab_create_account);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 0, 0, 1, 1);

        label_10 = new QLabel(tab_create_account);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 1, 0, 1, 1);

        lineEdit_keyStorePassword = new QLineEdit(tab_create_account);
        lineEdit_keyStorePassword->setObjectName(QString::fromUtf8("lineEdit_keyStorePassword"));

        gridLayout->addWidget(lineEdit_keyStorePassword, 1, 1, 1, 1);

        pushButton_createAccount = new QPushButton(tab_create_account);
        pushButton_createAccount->setObjectName(QString::fromUtf8("pushButton_createAccount"));

        gridLayout->addWidget(pushButton_createAccount, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 2, 1, 1);

        tabWidget->addTab(tab_create_account, QString());
        tab_choose_account = new QWidget();
        tab_choose_account->setObjectName(QString::fromUtf8("tab_choose_account"));
        gridLayout_2 = new QGridLayout(tab_choose_account);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lineEdit_keystore_emitent_code = new QLineEdit(tab_choose_account);
        lineEdit_keystore_emitent_code->setObjectName(QString::fromUtf8("lineEdit_keystore_emitent_code"));

        gridLayout_2->addWidget(lineEdit_keystore_emitent_code, 2, 1, 1, 1);

        lineEdit_keystore_name = new QLineEdit(tab_choose_account);
        lineEdit_keystore_name->setObjectName(QString::fromUtf8("lineEdit_keystore_name"));

        gridLayout_2->addWidget(lineEdit_keystore_name, 1, 1, 1, 1);

        label_2 = new QLabel(tab_choose_account);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_keystore_public_account_code = new QLineEdit(tab_choose_account);
        lineEdit_keystore_public_account_code->setObjectName(QString::fromUtf8("lineEdit_keystore_public_account_code"));

        gridLayout_2->addWidget(lineEdit_keystore_public_account_code, 3, 1, 1, 1);

        label_7 = new QLabel(tab_choose_account);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 3, 0, 1, 1);

        label_6 = new QLabel(tab_choose_account);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        comboBox_keystores = new QComboBox(tab_choose_account);
        comboBox_keystores->setObjectName(QString::fromUtf8("comboBox_keystores"));

        gridLayout_2->addWidget(comboBox_keystores, 0, 0, 1, 2);

        label_5 = new QLabel(tab_choose_account);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);

        plainTextEdit_keystore_content = new QPlainTextEdit(tab_choose_account);
        plainTextEdit_keystore_content->setObjectName(QString::fromUtf8("plainTextEdit_keystore_content"));

        gridLayout_2->addWidget(plainTextEdit_keystore_content, 4, 1, 1, 1);

        tabWidget->addTab(tab_choose_account, QString());
        tab_makeInvoice = new QWidget();
        tab_makeInvoice->setObjectName(QString::fromUtf8("tab_makeInvoice"));
        gridLayout_3 = new QGridLayout(tab_makeInvoice);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        plainTextEdit_invoiceComments = new QPlainTextEdit(tab_makeInvoice);
        plainTextEdit_invoiceComments->setObjectName(QString::fromUtf8("plainTextEdit_invoiceComments"));

        gridLayout_3->addWidget(plainTextEdit_invoiceComments, 3, 1, 1, 1);

        pushButton_invoice_create = new QPushButton(tab_makeInvoice);
        pushButton_invoice_create->setObjectName(QString::fromUtf8("pushButton_invoice_create"));

        gridLayout_3->addWidget(pushButton_invoice_create, 4, 0, 1, 1);

        label_4 = new QLabel(tab_makeInvoice);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 3, 0, 1, 1);

        label_3 = new QLabel(tab_makeInvoice);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_invoiceAmount = new QLineEdit(tab_makeInvoice);
        lineEdit_invoiceAmount->setObjectName(QString::fromUtf8("lineEdit_invoiceAmount"));

        gridLayout_3->addWidget(lineEdit_invoiceAmount, 2, 1, 1, 1);

        tabWidget->addTab(tab_makeInvoice, QString());
        tab_pay = new QWidget();
        tab_pay->setObjectName(QString::fromUtf8("tab_pay"));
        gridLayout_4 = new QGridLayout(tab_pay);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label = new QLabel(tab_pay);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        label_invoiceInfo = new QLabel(tab_pay);
        label_invoiceInfo->setObjectName(QString::fromUtf8("label_invoiceInfo"));

        gridLayout_4->addWidget(label_invoiceInfo, 1, 0, 1, 4);

        pushButtonGetInvoice = new QPushButton(tab_pay);
        pushButtonGetInvoice->setObjectName(QString::fromUtf8("pushButtonGetInvoice"));

        gridLayout_4->addWidget(pushButtonGetInvoice, 0, 3, 1, 1);

        pushButtonPay = new QPushButton(tab_pay);
        pushButtonPay->setObjectName(QString::fromUtf8("pushButtonPay"));

        gridLayout_4->addWidget(pushButtonPay, 2, 0, 1, 1);

        lineEditInvoiceId = new QLineEdit(tab_pay);
        lineEditInvoiceId->setObjectName(QString::fromUtf8("lineEditInvoiceId"));

        gridLayout_4->addWidget(lineEditInvoiceId, 0, 2, 1, 1);

        pushButton_scan = new QPushButton(tab_pay);
        pushButton_scan->setObjectName(QString::fromUtf8("pushButton_scan"));

        gridLayout_4->addWidget(pushButton_scan, 2, 1, 1, 1);

        tabWidget->addTab(tab_pay, QString());
        tab_genCards = new QWidget();
        tab_genCards->setObjectName(QString::fromUtf8("tab_genCards"));
        lineEdit_genCardCount = new QLineEdit(tab_genCards);
        lineEdit_genCardCount->setObjectName(QString::fromUtf8("lineEdit_genCardCount"));
        lineEdit_genCardCount->setGeometry(QRect(270, 50, 113, 21));
        pushButton_genCards = new QPushButton(tab_genCards);
        pushButton_genCards->setObjectName(QString::fromUtf8("pushButton_genCards"));
        pushButton_genCards->setGeometry(QRect(270, 110, 113, 32));
        tabWidget->addTab(tab_genCards, QString());

        gridLayout_5->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 834, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\220\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 bcwallet", nullptr));
        actionOpen_test_wnd->setText(QCoreApplication::translate("MainWindow", "open_test_wnd", nullptr));
        lineEdit_accountName->setPlaceholderText(QCoreApplication::translate("MainWindow", "Account name", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Account name", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "key store password", nullptr));
        lineEdit_keyStorePassword->setPlaceholderText(QCoreApplication::translate("MainWindow", "key store password", nullptr));
        pushButton_createAccount->setText(QCoreApplication::translate("MainWindow", "Create", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_create_account), QCoreApplication::translate("MainWindow", "Create account", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Public account", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Emitent code", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Keystore", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_choose_account), QCoreApplication::translate("MainWindow", "Choose account", nullptr));
        pushButton_invoice_create->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\274\320\274\320\265\320\275\321\202\320\260\321\200\320\270\320\271", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\241\321\203\320\274\320\274\320\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_makeInvoice), QCoreApplication::translate("MainWindow", "MakeInvoice", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Invoice ID", nullptr));
        label_invoiceInfo->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButtonGetInvoice->setText(QCoreApplication::translate("MainWindow", "Get Info", nullptr));
        pushButtonPay->setText(QCoreApplication::translate("MainWindow", "Pay", nullptr));
        pushButton_scan->setText(QCoreApplication::translate("MainWindow", "scan", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_pay), QCoreApplication::translate("MainWindow", "Pay", nullptr));
        lineEdit_genCardCount->setPlaceholderText(QCoreApplication::translate("MainWindow", "Card count", nullptr));
        pushButton_genCards->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_genCards), QCoreApplication::translate("MainWindow", "GenCards", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
