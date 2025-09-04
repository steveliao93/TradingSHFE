#pragma once

#include <QWidget>
#include "../TradingSHFE/x64/Debug/qt/uic/ui_mdquota.h"
#include "traderapi.h"
#include "traderspi.h"
#include "mdapi.h"
#include "mdspi.h"
#include "simplelinearregression.h"

#include "ThostFtdcTraderApi.h"
#include <QstandardItem>
#include <QTableView>
#include <semaphore.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <unordered_map>

namespace Ui {
	class mdquota;
}


class mdquota : public QWidget, public CThostFtdcTraderSpi,public CThostFtdcMdSpi
{
	Q_OBJECT
private:
	sem_t sem;
	sem_t sem1;
	sem_t sem2;

	sem_t sem3;
	sem_t sem4;
	sem_t sem6;
	sem_t sem5;
	sem_t sem7;




	CTraderApi* m_tradeApi;
	CTraderSpi* m_TradeSpi;
	CMdSpi* c_mdspi;
	CMdApi* c_mdapi;
	char Mdquotaname[20] = {0};
	char Exchangeid[9] = {0};
	int onrtnnumber=0;
	//QstandardItemModel* faf;
	QStandardItemModel* model;
	QStandardItemModel* model2;
	QStandardItemModel* model3;
	//QSortFilterProxyModel* m_pFilterModel;
	int rowquta=0;//最新价位置
	int rowbid = 0;//买一价格位置
	int rowask = 0; //卖一价位置
	int rowhi = 0; //最高价位置
	int rowlow = 0; //最新价位置
	double startprice;
	double endprice;
	int timeid;
	int timeid3;
	double priceTick;
	int chican[50] = {0};
	int baodanfrontid[20] = { 0 };
	int baodansessionid[20] = { 0 };
	string baodanorderref[20] = {string("0")};
	char baodandes[20] = { '2'};
	//int baodanchengjiaolast[20] = 0;
	double baodanprice[20] = { 0 };
	int baqodanduo = 0;
	int baodankong = 0;
	char chedanshu[100] = { 0 }; 
	char filename[50] = { 0 };
	QString Qfilename;
	int hangqingnum = 0;
	int hanqingtuisongnum = 0;
	int chengjiaoshu=0;
	double lastprice;
	char qutastatus = '2';
	int chicanduo = 0;
	int chicankong = 0;
	int yeschicanduo = 0;
	int yeschicankong = 0;
	CThostFtdcDepthMarketDataField PDepthMarketData;
	std::unordered_map<std::string, std::string> pInstExpiredate_map;
	std::unordered_map<std::string, double> pInstPrevalue_map;
	std::unordered_map<std::string, double> pInstLastprice_map;
	void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData);
	void OnFrontConnected();
	void OnRspOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* pInvestorPosition, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField* pInvestorPositionDetail, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	void OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	void OnRspQryOrder(CThostFtdcOrderField* pOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	void showtable(CThostFtdcDepthMarketDataField* pDepthMarketData);
	void OnRtnOrder(CThostFtdcOrderField* pOrder) ;
	void OnRtnTrade(CThostFtdcTradeField* pTrade) ;
	void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField* pInstrumentStatus);

	int chaxunmingxi();
	int chaxunchican();
	int chaxunbaodan();

	int datesDifference(std::string expiredate);
	void calculateProfit();

	//void InsertData(char* instrumentid, char* orderref, char direction, double limitprice);
	//void DeleteData(char orderref[13]);

	int i=0;
public:
	mdquota(char* mdquotaname, double PriceTick, char *exchangeid, QWidget* parent = Q_NULLPTR);
	~mdquota();
	void setTradeApi(CTraderApi* TradeApi, CTraderSpi* ATradeSpi, CMdSpi* Cmdspi , CMdApi* Cmdapi);
	void mdqutaqry(std::vector<std::string> instID_list, std::unordered_map<std::string, std::string> instExpiredate_map, char* ProductID);
	void setqstan();

protected:
	void timerEvent(QTimerEvent*);
	//void wheelEvent(QWheelEvent*);
	//void mousePressEvent(QMouseEvent* event);
	//bool eventFilter(QObject* object, QEvent* event);
	void keyPressEvent(QKeyEvent* event); //键盘按下事件

private slots:
	void onTableClicked(const QModelIndex& index);
	//void showtable(CThostFtdcDepthMarketDataField* pDepthMarketData);
	void rightcheck(QPoint pos);
	void slotdlgReturn(int a);
	void on_applyPreValue_clicked();
private:
	Ui::mdquota *ui;
};
