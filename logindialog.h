//#pragma once
//
//#include <QtWidgets/QDialog>
//#include "ui_logindialog.h"
//
//class LoginDialog : public QDialog
//{
//    Q_OBJECT
//
//public:
//    LoginDialog(QWidget *parent = Q_NULLPTR);
//
//private:
//    Ui::LoginDialogClass ui;
//};


#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
//#include <QtWidgets/QDialog>
#include "ui_logindialog.h"
#include <QDialog>
#include "traderapi.h"
#include "traderspi.h"
#include "ThostFtdcTraderApi.h"
#include "mdspi.h"
#include "mdapi.h"
//#include <semaphore.h>



namespace Ui {
    class LoginDialog;
}

class LoginDialog : public QDialog, public CThostFtdcTraderSpi, public CThostFtdcMdSpi
{
    Q_OBJECT

private:
    /*sem_t sem;
    sem_t sem1;*/


    CTraderApi* m_tradeApi;
    CTraderSpi* m_TradeSpi;
    CMdApi* m_cmapi;
    CMdSpi* m_cmspi;
    char tradeday[9] = { 0 };
    void OnFrontConnected();
    void OnFrontDisconnected(int nReason);
    //void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
    void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
    void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
    int ReqAuthenticate(CThostFtdcReqAuthenticateField* pReqAuthenticateField, int nRequestID) ;
    int Userauth();
    void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField* pUserPasswordUpdate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
    void LoginMessage();

    int UserLogin();
   // int Authenticate();

public:
    explicit LoginDialog(QWidget* parent = nullptr);
    ~LoginDialog();

    void setTradeApi(CTraderApi* TradeApi, CTraderSpi* ATradeSpi, CMdApi* Mcmapi , CMdSpi* Mcmspi);

private slots:
    void on_but_login_clicked();
    //void on_but_cancle_clicked();

private:
    Ui::LoginDialogClass* ui;
};

#endif // LOGINDIALOG_H
