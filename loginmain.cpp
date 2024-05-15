#include "loginmain.h"
//#include "mainwindow.h"
#include <QApplication>
#include "ui_loginmain.h"
#include <QDebug>
#include "mdquota.h"
#include <QDir>
#include "quotalist.h"
extern LoginDialog* dlgTableSize;
extern mdquota* t;
extern int requestId;
//extern mdquota* xxx;

loginmain::loginmain(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//QObject::connect(ui.actionlogin, SIGNAL(triggerred()), this, SLOT(slot_about()));
	connect(myTimer, SIGNAL(timeout()),this, SLOT(TimerResponse()));
	myTimer->start(3000);
}
void loginmain::TimerResponse() //不断检查是否 定时时间到
{
	QTime Temp1 = QTime::fromString("10:14:00", "hh:mm:ss");
	QTime Temp2 = QTime::fromString("14:59:00", "hh:mm:ss");
	QTime Temp3 = QTime::fromString("11:29:00", "hh:mm:ss");
	//QTime Temp4 = QTime::fromString("23:45:00", "hh:mm:ss");

	//Temp = ui->timeEdit->time();
	if (Temp1.hour() == QTime::currentTime().hour() &&
		Temp1.minute() == QTime::currentTime().minute())
	{
	
		PlaySound(TEXT("phone.wav"), NULL, SND_FILENAME | SND_ASYNC);

	}
	if (Temp2.hour() == QTime::currentTime().hour() &&
		Temp2.minute() == QTime::currentTime().minute())
	{

		PlaySound(TEXT("phone.wav"), NULL, SND_FILENAME | SND_ASYNC);

	}
	if (Temp3.hour() == QTime::currentTime().hour() &&
		Temp3.minute() == QTime::currentTime().minute())
	{

		PlaySound(TEXT("phone.wav"), NULL, SND_FILENAME | SND_ASYNC);

	}

}

loginmain::~loginmain()
{
}

void loginmain::on_mainloginbut_clicked(){

//void loginmain::on_mainloginbut_clicked(TraderApi* C_TradeApi, CTraderSpi* C_TradeSpi) {
	
	int ret = dlgTableSize->exec();
	if (ret == QDialog::Accepted) {
		ui.label->setText("login sucess");
	}
}

void loginmain::on_mainquotabut_clicked() {
	quotalist *xxx = new quotalist();
	xxx->show();
	//xxx->setTradeApi()
	//t->show();
	//xxx->hookinstall();
	Sleep(200);
	xxx->mdqutalist();
	//Sleep(2000);
	//xxx->searchAndFilterLocalSlot();
	//mdquota::mdqutaqry();
	//t->mdqutaqry();
	//xxx->show();
	
}
void loginmain::on_checktime_clicked() {

	//void loginmain::on_mainloginbut_clicked(TraderApi* C_TradeApi, CTraderSpi* C_TradeSpi) {

	//int ret = dlgTableSize->exec();
	//if (ret == QDialog::Accepted) {
	ui.label->setText("checktime");
	//if (m_TradeSpi->Status == LSDisconnected) {
	ui.label->setText(ui.label->text()+m_tradeApi->GetTradingDay());

		//m_tradeApi->GetTradingDay();
	//}
}
//void loginmain::slot_about() {
//
//	//void loginmain::on_mainloginbut_clicked(TraderApi* C_TradeApi, CTraderSpi* C_TradeSpi) {
//	ui.label->setText("slot_about chick login");
//
//}
void loginmain::setTradeApi(CTraderApi* TradeApi, CTraderSpi* ATradeSpi) {
	m_tradeApi = TradeApi;
	m_TradeSpi = ATradeSpi;
	//m_TradeSpi->RegisterSpi(this);
}
