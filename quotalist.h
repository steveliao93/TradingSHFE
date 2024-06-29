#pragma once
#include "ThostFtdcTraderApi.h"
#include  "ThostFtdcMdApi.h"
#include <QWidget>
#include "ui_quotalist.h"
#include <QstandardItem>
#include <QTableView>
#include <semaphore.h>
#include "mdapi.h"
#include "mdspi.h"
#include "traderapi.h"
#include "traderspi.h"
#include <QSortFilterProxyModel>
#include <vector>
#include <unordered_map>

//#include "Hook.h"

namespace Ui {
	class quotalist;
}
class MusicInfoModel : public QStandardItemModel
{
public:
	void loadData(const QString& strKeyword);//用于加载网上搜索得到的数据
};
class quotalist : public QWidget ,public CThostFtdcTraderSpi, public CThostFtdcMdSpi
{
	Q_OBJECT
private:
	sem_t sem;
	sem_t sem1;

	CTraderApi* m_tradeApi;
	CTraderSpi* m_TradeSpi;
	CMdSpi* c_mdspi;
	CMdApi* c_mdapi;
	QStandardItemModel* model;
	MusicInfoModel* m_pInfoModel;			//数据模型
	QSortFilterProxyModel* m_pFilterModel;	//过滤代理模型

	std::vector<CThostFtdcInstrumentField> vec;
	// Hook hook;
	int i = 0;
	int ib = 0;
	double PriceTick;
	//double LastPrice;
	//void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) ;
	void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
public:
	quotalist(QWidget *parent = Q_NULLPTR);
	~quotalist();
	void mdqutalist();
	void setTradeApi(CTraderApi* TradeApi, CTraderSpi* ATradeSpi, CMdSpi* Cmdspi, CMdApi* Cmdapi);
	void saveContractList();
	void readContractList();
	char InstrumentID[31];
	std::vector<std::string> instID_list;
	std::unordered_map<std::string, char*> instExpiredate_map;
	char* subscribed_futures[20];
	int subscribed_numbers = 0;
	//void searchAndFilterLocalSlot();
	//void hookinstall();


private slots:
	void onTableClicked(const QModelIndex& index);
	void searchAndFilterLocalSlot();
	void on_updateQuotalist_clicked();
	//void checkType(Hook::Type);
signals:
	void dlgReturn(int);

private:
	Ui::quotalist *ui;
};
