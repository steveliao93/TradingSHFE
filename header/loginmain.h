#pragma once

#include <QMainWindow>
#include "../TradingSHFE/x64/Debug/qt/uic/ui_loginmain.h"
#include "loginmain.h"
#include "main.h"
//#include "mainwindow.h"
#include "logindialog.h"
#include "loginmain.h"
#include <QApplication>
#include "../TradingSHFE/x64/Debug/qt/uic/ui_loginmain.h"
#include <QDebug>
#include "../TradingSHFE/x64/Debug/qt/uic/ui_logindialog.h"
#include <QDateTime>
#include <QTimer>
class loginmain : public QMainWindow
{

	Q_OBJECT

private:
	CTraderApi* m_tradeApi;
	CTraderSpi* m_TradeSpi;
	QTimer* myTimer = new QTimer(this);

	///void OnFrontConnected();
	//void OnFrontDisconnected(int nReason);
	//void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	//void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);


	//int UserLogin();
	// int Authenticate();
	//Q_OBJECT

public:
	loginmain(QWidget *parent = Q_NULLPTR);
	~loginmain();
	void setTradeApi(CTraderApi* TradeApi, CTraderSpi* ATradeSpi);

private slots:
	void on_mainloginbut_clicked();
	void on_checktime_clicked();
	void on_mainquotabut_clicked();
	void TimerResponse();

	//void slot_about();
//	void on_but_cancle_clicked();
private:
	Ui::loginmain ui;
};
