//#include "logindialog.h"
//#include <QtWidgets/QApplication>
//
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    LoginDialog w;
//    w.show();
//    return a.exec();
//}

#include "main.h"
//#include "mainwindow.h"
#include "logindialog.h"
#include "loginmain.h"
#include <QApplication>
#include "mdquota.h"
#include <QDebug>
#include <QDir>
//#include <QSqlDatabase>


int requestId = 0;
LoginDialog* dlgTableSize;
//mdquota* t;
CTraderApi* C_TradeApi = new CTraderApi();


CTraderSpi* C_TradeSpi;
CMdApi* C_MdApi;
CMdSpi* C_MdSpi;
//QSqlDatabase db;
int frontid;
int sessionid;
char userid[16];
//mdquota* xxx;
int main(int argc, char* argv[])
{
    //SqliteOperator sqliteOperator;
   // sqliteOperator.CreatDb();
   // sqliteOperator.OpenDb();
   // sqliteOperator.CreateTable();
   //qliteOperator.InsertData();
   // sqliteOperator.QueryAllData();
    //C_TradeApi = new CTraderApi();

    C_TradeSpi = new CTraderSpi();
    C_MdApi = new CMdApi();
    C_MdSpi = new CMdSpi();
    //qDebug() << C_TradeApi;
    QDir* aDir = new QDir();
    if (!aDir->exists("flow"))
    {
        aDir->mkdir("flow");
    }
    C_TradeApi->CreateFtdcTraderApi("flow");
    C_TradeApi->RegisterSpi(C_TradeSpi);
    C_TradeApi->SubscribePublicTopic(THOST_TERT_QUICK);
    C_TradeApi->SubscribePrivateTopic(THOST_TERT_QUICK);
    
    //-----------------------------------------------------
    C_MdApi->CreateFtdcMdApi();
    C_MdApi->RegisterSpi(C_MdSpi);
   //// char*  serveraddress = (char*)"tcp://180.168.146.187:10212";
   // char* serveraddress = (char*)"tcp://180.168.146.187:10131";
   //// char* serveraddress = (char*)"tcp://180.168.146.187:10211";

   // //char* serveraddress = (char*)"tcp://218.202.237.33:10213"; 
   // C_MdApi->RegisterFront(serveraddress);
   // C_MdApi->Init();
   // Sleep(1000);
   // CThostFtdcReqUserLoginField userLoginField;
   // memset(&userLoginField, 0, sizeof(userLoginField));
   // strcpy(userLoginField.BrokerID, "9999");
   // strcpy(userLoginField.UserID, "090541");
   // strcpy(userLoginField.Password, "Lq890919");
    //-----------------------------------------------------------
   // Sleep(3000);
   
    QApplication a(argc, argv);
    loginmain w;
    
    //w.setTradeApi(C_TradeApi, C_TradeSpi);
    w.setTradeApi(C_TradeApi, C_TradeSpi);

    //Init_TraderA();
   // t = new mdquota();
   // t->setTradeApi(C_TradeApi, C_TradeSpi, C_MdSpi, C_MdApi);
   // C_MdApi->ReqUserLogin(&userLoginField, requestId++);
   // Sleep(3000);
    w.show();

   // xxx = new mdquota();
   // xxx->setTradeApi(C_TradeApi, C_TradeSpi);
    dlgTableSize = new LoginDialog();
    dlgTableSize->setTradeApi(C_TradeApi, C_TradeSpi, C_MdApi, C_MdSpi);
    Qt::WindowFlags    flags = dlgTableSize->windowFlags();
    //  dlgTableSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint); //设置对话框固定大小

    dlgTableSize->setWindowTitle("login");

    //int ret = dlgTableSize->exec();

    //if (ret == QDialog::Accepted)
    //{
    //     w.show();
    //     return a.exec();
    //}
    //else {
    //     a.exit();
    //   // w.show();
    //   // return a.exec();
    //}
    C_TradeApi->Join();
    C_MdApi->Join();

    /*delete C_TradeSpi;
    delete C_TradeApi;
    delete C_MdApi;
    delete C_MdSpi;
    delete aDir;*/
    return a.exec();
}

//   //dlgTableSize->show();
//
//    int ret = dlgTableSize->exec();
//    
//    if (ret == QDialog::Accepted)
//    {
//        dlgTableSize->show();
//
//        //dlgTableSize.exec();
//        return a.exec();
//    }
//    else {
//        a.exit();
//   //return a.exec();
//    //}
//}
