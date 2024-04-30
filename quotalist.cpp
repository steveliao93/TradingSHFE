#include "quotalist.h"
#include <QstandardItem>
#include <QTableView>
#include "mdquota.h"
#include<QMessageBox>


extern CTraderApi* C_TradeApi;
extern CTraderSpi* C_TradeSpi;
extern CMdApi* C_MdApi;
extern CMdSpi* C_MdSpi;
extern int requestId;
extern char userid[16];

quotalist::quotalist(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::quotalist)

{
	//sem_init(&sem, 0, 1);
	//sem_init(&sem1, 0, 0);
	this->setAttribute(Qt::WA_DeleteOnClose, true);

	model = new QStandardItemModel(); 
	m_pInfoModel = new MusicInfoModel();
	m_pFilterModel = new QSortFilterProxyModel(this);
	m_pFilterModel->setSourceModel(m_pInfoModel);

	ui->setupUi(this);

	

	//connect(this, SIGNAL(dlgReturn(int)), this, SLOT(on_loginbtn_chick2(int)));
	connect(this->ui->tablelist, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableClicked(const QModelIndex&)));
	setTradeApi(C_TradeApi, C_TradeSpi, C_MdSpi, C_MdApi);
	QModelIndex index = model->index(0, 0); // whatever column you want to search in
	ui->tablelist->setCurrentIndex(index);
	ui->tablelist->setModel(m_pFilterModel);
	//connect(this->ui->lineEdit, SIGNAL(clicked(const QModelIndex&)))
		connect(this->ui->lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(searchAndFilterLocalSlot()));


	//m_TradeSpi->RegisterSpi(this);
}

quotalist::~quotalist()
{
	m_TradeSpi->UnReisterSpi(this);
	//c_mdspi->UnReisterSpi(this);
	//hook.unInstallHook();

	delete ui;
	delete model;
}
void quotalist::setTradeApi(CTraderApi* TradeApi, CTraderSpi* ATradeSpi, CMdSpi* Cmdspi, CMdApi* Cmdapi) {
	m_tradeApi = TradeApi;
	m_TradeSpi = ATradeSpi;
	c_mdspi = Cmdspi;
	c_mdapi = Cmdapi;
	m_TradeSpi->RegisterSpi(this);
//	//m_TradeSpi->RegisterSpi(this);
}

void quotalist::mdqutalist()
{

	//model->setItem(i++, 0, new QStandardItem("sn2205"));
	//model->setItem(i++, 0, new QStandardItem("sn2206"));
	//model->setItem(i++, 0, new QStandardItem("sn2207"));
	//model->setItem(i++, 0, new QStandardItem("sn2208"));
	//model->setItem(i++, 0, new QStandardItem("sn2209"));
	//model->setItem(i++, 0, new QStandardItem("sn2210"));
	//model->setItem(i++, 0, new QStandardItem("sn2211"));
	//model->setItem(i++, 0, new QStandardItem("sn2212"));
	//model->setItem(i++, 0, new QStandardItem("sn2301"));
	//model->setItem(i++, 0, new QStandardItem("sn2302"));
	//model->setItem(i++, 0, new QStandardItem("sn2303"));
	//model->setItem(i++, 0, new QStandardItem("zn2205"));
	//model->setItem(i++, 0, new QStandardItem("zn2206"));
	//model->setItem(i++, 0, new QStandardItem("zn2207"));
	//model->setItem(i++, 0, new QStandardItem("zn2208"));
	CThostFtdcQryInstrumentField qsif1;
	memset(&qsif1, 0, sizeof(qsif1));
	//strcpy(qsif1.ExchangeID, "SHFE");
	CThostFtdcQryInstrumentField qsif2;
	memset(&qsif2, 0, sizeof(qsif2));
	strcpy(qsif2.ExchangeID, "CFFEX");
	CThostFtdcQryInstrumentField qsif3;
	memset(&qsif3, 0, sizeof(qsif3));
	strcpy(qsif3.ExchangeID, "CZCE");
	CThostFtdcQryInstrumentField qsif4;
	memset(&qsif4, 0, sizeof(qsif4));
	strcpy(qsif4.ExchangeID, "DCE");
	CThostFtdcQryInstrumentField qsif5;
	memset(&qsif5, 0, sizeof(qsif5));
	//strcpy(qsif5.ExchangeID, "INE");
	//strcpy(qsif.InstrumentID, "sn2207");
	//strcpy(qsif.ExchangeInstID, "sn2207");

	//m_tradeApi->ReqQryInstrument(&qsif1, ++requestId);
	//m_tradeApi->ReqQryInstrument(&qsif2, ++requestId);
	//m_tradeApi->ReqQryInstrument(&qsif3, ++requestId);
	//m_tradeApi->ReqQryInstrument(&qsif4, ++requestId);
	m_tradeApi->ReqQryInstrument(&qsif1, ++requestId);


	//ui->tablelist->setModel(model);
	//ui->tablelist->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//ui->tablelist->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void quotalist::onTableClicked(const QModelIndex& index) {
	if (C_TradeSpi->Status == LSDisconnected) {
		QMessageBox::information(this, "Notice", "please login first!");
		return;
	}
	Sleep(3000);
	//sem_wait(&sem1);
	//if (sem_trywait(&sem1) != 0) {
	//	//	qDebug("<showtable  waiting............................................>\n");
	//		//continue;
	//	QMessageBox::information(this, "Notice", "data  loading please wait......");

	//	return;
	//}
	//sem_wait(&sem);

	/*if (index.isvalid()) {
		qstring celltext = index.data().tostring();
	}*/
	//virtual int ReqQryInstrument(CThostFtdcQryInstrumentField * pQryInstrument, int nRequestID) = 0;
	//CThostFtdcQryInstrumentField qsif;
	//memset(&qsif, 0, sizeof(qsif));
	//strcpy(qsif.ExchangeID, "SHFE");
	
	//strcpy(qsif.InstrumentID, model->data(model->index(index.row(), index.column())).toString().toLatin1().data());
	//strcpy(qsif.ExchangeInstID, model->data(model->index(index.row(), index.column())).toString().toLatin1().data());

	//m_tradeApi->ReqQryInstrument(&qsif, ++requestId);
	//sem_wait(&sem1);

	//quotalist* xxx = new quotalist();
	//xxx->show();
	//qDebug("<111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111>\n");
	//qDebug("<PriceTick[%f]>\n", PriceTick);

	//mdquota * t = new mdquota(model->data(model->index(index.row(),index.column())).toString().toLatin1().data());
	if (m_pFilterModel->data(m_pFilterModel->index(index.row(), index.column() + 1)).toDouble() < 0) {
		//QMessageBox::information(this, "Notice", "error");
		return;
	}
	if (m_pFilterModel->data(m_pFilterModel->index(index.row(), index.column() + 1)).toDouble() > 50000) {
		//QMessageBox::information(this, "Notice", "error");
		return;
	}
	mdquota* t = new mdquota(m_pFilterModel->data(m_pFilterModel->index(index.row(), index.column())).toString().toLatin1().data(), m_pFilterModel->data(m_pFilterModel->index(index.row(),index.column()+1)).toDouble(), m_pFilterModel->data(m_pFilterModel->index(index.row(), index.column() + 2)).toString().toLatin1().data());
	connect(this, SIGNAL(dlgReturn(int)), t, SLOT(slotdlgReturn(int)));

	//qDebug("<222>\n");

	//int a = model->item(index.row(), index.column()).;
	t->setTradeApi(C_TradeApi, C_TradeSpi, C_MdSpi, C_MdApi);
	//char* b[] = { (char*)"sn2205",(char*)"sn2206",(char*)"sn2207",(char*)"sn2208" };
	//qDebug("<333>\n");

	//int c = c_mdapi->SubscribeMarketData(b, 1);
	t->show();
	//qDebug("<444>\n");

	t->setWindowTitle(m_pFilterModel->data(m_pFilterModel->index(index.row(), index.column())).toString().toLatin1().data());
	//qDebug("<555>\n");

	t->mdqutaqry();
	//Sleep(3000);
	t->setqstan();
	//t->showtable();
	qDebug("<666>\n");

	// t->setTradeApi(C_TradeApi, C_TradeSpi, C_MdSpi, C_MdApi);
	//model->removeRow(index.row());
	//ui->tablelist->setModel(model);
	//sem_post(&sem1);

	//sem_post(&sem);
	delete t;

}
void quotalist::OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
	//if (bIsLast) {
	//	//qDebug("<55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555>\n");
	//	sem_post(&sem1);
	//}
//	// model->setItem(i++, 0, new QStandardItem("zn2208"));
//	qDebug("<55555555555555555555555555555555>\n");
//
	if (pInstrument->PriceTick <= 0) {
		//QMessageBox::information(this, "Notice", "error");
		return;
	}
	if (pInstrument->PriceTick > 500000) {
	//	QMessageBox::information(this, "Notice", "error");
		return;
	}
	if (pInstrument->InstLifePhase != THOST_FTDC_IP_Started) {
		return;
	}
	if (!pInstrument->IsTrading) {
		return;
	}
	if (pInstrument->PriceTick < 0.01) {
		return;
	}
	m_pInfoModel->setItem(ib, 0, new QStandardItem(pInstrument->ExchangeInstID));
	m_pInfoModel->setItem(ib, 1, new QStandardItem(QString::number(pInstrument->PriceTick)));
	m_pInfoModel->setItem(ib++, 2, new QStandardItem(pInstrument->ExchangeID));

//	QString::number(jfjfe))
	//QList<QStandardItem*> list;
	//list << new QStandardItem(pInstrument->ExchangeInstID) << new QStandardItem(pInstrument->PriceTick);
	//model->insertRow(0, list);

	////PriceTick = pInstrument->PriceTick;
	//LastPrice = pInstrument->StrikePrice;
	// InstrumentID = pInstrument->InstrumentID;
	 ////memcpy(InstrumentID, pInstrument->InstrumentID, strlen(pInstrument->InstrumentID));

}
void quotalist::searchAndFilterLocalSlot()
{
	QString strKeyword = ui->lineEdit->text();
	m_pFilterModel->setFilterFixedString(strKeyword);//根据字符串过滤
	ui->tablelist->scrollTo(ui->tablelist->model()->index(0, 0), QAbstractItemView::PositionAtTop);
}
//void quotalist::hookinstall() {
//	
//	hook.installHook(&hook);
//	qRegisterMetaType<Hook::Type>("Type");//为了信号中能传递自定义枚举类型，如果传递常规参数，可省略该行
//	connect(&hook, SIGNAL(sendKeyType(Type)), this, SLOT(checkType(Type)));
//	//sem_post(&sem1);
//}

//void quotalist::checkType(Hook::Type type) {
//	switch (type) {
//	case Hook::CHANGE:
//		//ui->plainTextEdit->appendPlainText("按下按钮 Ctrl+1 \n");
//		//qDebug() << "CHANGECHANGECHANGECHANGECHANGECHANGECHANGE";
//		emit dlgReturn(1);
//		break;
//	default:
//		break;
//	}
//}

   //   60 62 64 66 68       80         82 84 86 88 90

//62-60/2