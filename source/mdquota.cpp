#include "mdquota.h"
#include "traderspi.h"
#include "traderapi.h"
#include <QstandardItem>
#include <QTableView>
#include<QMessageBox>
#include<QScrollBar>
#include <semaphore.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include "simplelinearregression.h"
//#include "SqliteOperator.h"
#include <mmsystem.h>
#include <Windows.h>
#include <quotalist.h>
#include <chrono>
#include <QKeyEvent>
#include <fstream>
#include <QtCore/QTextStream>
#include <QtCore/QFile> 
#include <QtCore/QIODevice>
#include <QFileInfo>


#pragma comment (lib,"winmm.lib")

extern int requestId;
extern int frontid;
extern int sessionid;
//extern QSqlDatabase db;
//extern SqliteOperator sqliteOperator;
extern char userid[16];
extern char tradeday[9];
mdquota::mdquota(char* mdquotaname, double PriceTick,char *exchangeid, QWidget* parent)
	: QWidget(parent),
	ui(new Ui::mdquota)
{
	model = new QStandardItemModel();
	model2 = new QStandardItemModel();
	model3 = new QStandardItemModel();

	//Mdquotaname = mdquotaname;
	strcpy(Mdquotaname, mdquotaname);
	strcpy(Exchangeid, exchangeid);

	priceTick = PriceTick;
	this->setAttribute(Qt::WA_DeleteOnClose, true);
	sem_init(&sem, 0, 1);
	sem_init(&sem1, 0, 1);
	sem_init(&sem2, 0, 1);
	sem_init(&sem3, 0, 0);
	sem_init(&sem4, 0, 1);
	sem_init(&sem5, 0, 1);
	sem_init(&sem6, 0, 0);
	sem_init(&sem7, 0, 1);



	int w;
	//startprice =329880 + 2000 * priceTick;
	//endprice = 32880 - 2000 * priceTick;
	//double jfjfe;
	//int a = 0;
	//for (jfjfe = startprice; jfjfe >= endprice; jfjfe = (jfjfe - priceTick)) {
	//	model->setItem(a, 2, new QStandardItem(QString::number(jfjfe)));
	//	a++;
	//}
	ui->setupUi(this);
	//this->grabKeyboard();
	//ui->tableView->setMouseTracking(true);
	//ui->tableView->viewport()->setMouseTracking(true);
	//ui->tableView->installEventFilter(this);
	//ui->tableView->viewport()->installEventFilter(this);
	//SqliteOperator sqliteOperator;
	//ui->tableView->viewport()->installEventFilter(this);
	//qDebug() << "installEventFilterinstallEventFilterinstallEventFilterinstallEventFilterinstallEventFilterinstallEventFilterinstallEventFilter";

	
	//qDebug() << "installEventFilterinstallEventFilterinstallEventFilterinstallEventFilterinstallEventFilterinstallEventFilterinstallEventFilter";

	ui->tableView_2->setModel(model2);
	//for (w = 0; w <= 200; w++) {
	//	model->setItem(w, 0, new QStandardItem(""));
	//	model->setItem(w, 1, new QStandardItem(""));
	//	model->setItem(w, 2, new QStandardItem(""));
	//	model->setItem(w, 3, new QStandardItem(""));
	//	model->setItem(w, 4, new QStandardItem(""));

	//}
	for (w = 0; w <= 4; w++) {
		model2->setItem(w, 0, new QStandardItem("waiting"));


	}
	//model->setItem(1, 1, new QStandardItem(""));
	model3->setColumnCount(3);
	model3->setHeaderData(0, Qt::Horizontal, QStringLiteral("合约ID"));
	model3->setHeaderData(1, Qt::Horizontal, QStringLiteral("预值"));
	model3->setHeaderData(2, Qt::Horizontal, QStringLiteral("Profit"));

	


	//ui->tableView->setModel(model);
	//ui-> tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	//ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);



	/*ui->tableView->horizontalHeader()->setVisible(false);
	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
	ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);*/
	//ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//ui->tableView->setModel(model);
	//model->setItem(0, 0, new QStandardItem("a"));
	//model->setItem(0, 1, new QStandardItem("b"));
	//model->setItem(0, 2, new QStandardItem("c"));
	//model->setItem(0, 3, new QStandardItem("d"));
	//model->setItem(0, 4, new QStandardItem("e"));
	
	//ui->tableView_2->setColumnWidth(0, 90);
	//ui->tableView_2->setRowHeight(0, 30);
		//ui->tableView->setRowHeight


	//ui->tableView->setModel(model);

	
	//model->setRowCount(5000);
	//ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	//ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
	//ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	//ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	//ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//	ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	ui->tableView->verticalHeader()->setDefaultSectionSize(15);
	ui->tableView_3->verticalHeader()->setDefaultSectionSize(7);


	timeid = startTimer(100);
	timeid3 = startTimer(5000);

	//connect(timeid, SIGNAL(timeout()), this, SLOT(showtable(CThostFtdcDepthMarketDataField * pDepthMarketData)));

	connect(this->ui->tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableClicked(const QModelIndex&)));
	//connect(timeid, SIGNAL(timeout()), this, SLOT(showtable(CThostFtdcDepthMarketDataField * pDepthMarketData)));
	//connect(this->ui->tableView, SIGNAL(viewport()), this, SLOT(mousePressEvent(QMouseEvent * event)));
	connect(this->ui->tableView, SIGNAL(customContextMenuRequested( QPoint)), this, SLOT(rightcheck( QPoint)));
	//const char* fname = "./chedan/abc";
	
	sprintf(filename, "%s%s%s%s", "chedan\\\\", Mdquotaname, QDateTime::currentDateTime().toString("yyyyMMdd").toLatin1().data(),".txt");
	qDebug("filenamefilenamefilenamefilename [%s]  ---   \n", filename);
	Qfilename = QString("chedan\\\\")+QString(Mdquotaname) + QDateTime::currentDateTime().toString("yyyyMMdd");
	qDebug("QfilenameQfilenameQfilenameQfilename [%s]  ---   \n", Qfilename.toStdString().c_str());

	QFile file(Qfilename);
	QFileInfo info(Qfilename);
	if (file.exists() == true){
		if (file.open(QIODevice::ReadWrite | QIODevice::Text))//只写的方式打开
		{
			file.readLine(chedanshu, sizeof(chedanshu));
			file.close();
			//return;
		}

	}
	else {
		if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)){
			file.write("0");
			chedanshu[0] = '0';
			file.close();
		}
	}
	


}
void mdquota::timerEvent(QTimerEvent* a ) {
	if (a->timerId() == timeid) {       // 判断是哪个定时器

		showtable(&PDepthMarketData);
	}
	if (a->timerId() == timeid3) {  
		// 判断是哪个定时器
		//qDebug("timeid3timeid3timeid3timeid3timeid3timeid3timeid3 [%s]  ---   \n");

		QFile file(Qfilename);

		if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
			file.write(ui->lineEdit_2->text().toStdString().c_str());
			//chedanshu[0] = 0;
			file.close();
		}
		//showtable(&PDepthMarketData);
	}
}
void mdquota::setqstan() {
	//self.model.setRowCount（80000）
	//qDebug("<setqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstansetqstan>\n");
	//model->setRowCount(5000);
	//ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	//ui->tableView->setColumnWidth(0, 35);
	//ui->tableView->setColumnWidth(1, 35);
	//ui->tableView->setColumnWidth(2, 50);
	//ui->tableView->setColumnWidth(3, 35);
	//ui->tableView->setColumnWidth(4, 35);
	//showtable(&PDepthMarketData);
}
//bool mdquota::eventFilter(QObject* object, QEvent* event) {
//
//	//qDebug() << "鼠标滚轮按下 in table" << ":" << event->type();
//
//	//if (object == ui->tableView)
//	//{
//		//qDebug() << "鼠标滚轮按下 in table" << ":" << event->type();
//
//		if (event->type() == QEvent::MouseButtonPress)  // 82  鼠标右击事件 ContextMenu
//		{
//			QMouseEvent* a = static_cast<QMouseEvent*>(event);
//			//qDebug() << "鼠标滚轮按下 in table";
//
//			if (a->button() == Qt::MouseButton::MiddleButton) {
//				qDebug() << "shubiao shubiaoshubiaoshubiaoshubiao eventFilter";
//
//				//qDebug() << "鼠标滚轮按下 in table";
//				if (rowask != 0 && rowbid !=0 ) {
//					ui->tableView->scrollTo(ui->tableView->model()->index(int((rowbid+rowask)/2), 0), QAbstractItemView::PositionAtCenter);
//				}
//			}
//
//		}
//		//if (event->type() == QEvent::KeyPress)  // 82  鼠标右击事件 ContextMenu
//		//{
//		//	QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
//		//	if ((keyEvent->key() == Qt::Key_Space)) {
//		//		qDebug() << "jianpan kongge shijian in table";
//
//		//	}
//
//		//}
//	//}
//
//	// 注意这里，未处理的事件，要返还给上一级的事件处理函数。
//	return QWidget::eventFilter(object, event);
//}

mdquota::~mdquota()
{
	//QMessageBox::information(this, "Notice", "You can't close the window");
	char* b[] = { Mdquotaname };

	int c = c_mdapi->UnSubscribeMarketData(b, 1);
	Sleep(1000);
	m_TradeSpi->UnReisterSpi(this);
	c_mdspi->UnReisterSpi(this);

	delete ui;
}

void mdquota::setTradeApi(CTraderApi* TradeApi, CTraderSpi* ATradeSpi, CMdSpi* Cmdspi, CMdApi* Cmdapi) {
	m_tradeApi = TradeApi;
	m_TradeSpi = ATradeSpi;
	c_mdspi = Cmdspi;
	c_mdapi = Cmdapi;
	c_mdspi->RegisterSpi(this);
	m_TradeSpi->RegisterSpi(this);
}

void mdquota::OnFrontConnected() {
	//ui->ddd->setText(ui->lbl_status->text() + "\n" + "connect sucess");
	// ui->lbl_status->repaint();
	qDebug("<mdquotaOnFrontConnected>\n");

	//  Authenticate();
 //	();
}

void mdquota::on_applyPreValue_clicked() {
	std::vector<double> trainData;
	std::vector<double> trainTarget;
	double prediction;
	double profit;
	for (int i = 0; i < model3->rowCount(); ++i) {
		QString contractName = model3->item(i, 0)->text();
		QStandardItem* item = model3->item(i, 1);
		double preValue;
		if (item) { preValue = item->text().toDouble(); }
		else { preValue = 0.0; }
		pInstPrevalue_map[contractName.toStdString()] = preValue;
	}
}

void mdquota::calculateProfit() {
	std::vector<double> trainData;
	std::vector<double> trainTarget;
	double prediction;
	double profit;

	for (int i = 0; i < model3->rowCount(); ++i) {
		QString contractName = model3->item(i, 0)->text();
		double preValue = pInstPrevalue_map[contractName.toStdString()];
		std::string rawDate = pInstExpiredate_map[contractName.toStdString()];
		double lastprice = pInstLastprice_map[contractName.toStdString()];
		int diffDays = datesDifference(rawDate);
		trainData.push_back(static_cast<double>(diffDays) / 365);
		trainTarget.push_back(std::log(lastprice + preValue));

	}

	slr regression = slr(trainData, trainTarget);

	for (int i = 0; i < model3->rowCount(); ++i) {
		prediction = regression.b0 + regression.b1 * trainData[i];
		profit = std::exp(trainTarget[i]) - std::exp(prediction);
		QStandardItem* profitItem = new QStandardItem(QString::number(profit));
		model3->setItem(i, 2, profitItem);
	}
}

int mdquota::datesDifference(std::string expiredate) {
	// 获取当前系统时间
	auto now = std::chrono::system_clock::now();

	// 将时间点转换为日期
	time_t tt = std::chrono::system_clock::to_time_t(now);
	tm local_tm = *localtime(&tt);

	// 将日期转换为 year_month_day
	int year_today = local_tm.tm_year + 1900;
	int year_month = local_tm.tm_mon + 1;
	int year_day = local_tm.tm_mday;
	std::tm time_in_today = { 0, 0, 0, local_tm.tm_mday, local_tm.tm_mon, local_tm.tm_year };
	std::time_t time_temp_today = std::mktime(&time_in_today);
	
	int year_expire = std::stoi(expiredate.substr(0, 4));
	int month_expire = std::stoi(expiredate.substr(4, 2));
	int day_expire = std::stoi(expiredate.substr(6, 2));
	
	std::tm time_in_expire = { 0, 0, 0, day_expire, month_expire - 1, year_expire - 1900 };
	std::time_t time_temp_expire = std::mktime(&time_in_expire);

	int days_in_between = std::difftime(time_temp_expire, time_temp_today) / (60 * 60 * 24);
	
	return days_in_between;

}

void mdquota::mdqutaqry(std::vector<std::string> instID_list, std::unordered_map < std::string, std::string > instExpiredate_map, char* ProductID) {
	ui->lineEdit->setText(userid);
	ui->ddd->setText("start.............");
	////ui->label
	//CThostFtdcQryDepthMarketDataField requestData;
	//memset(&requestData, 0, sizeof(requestData));
	//strcpy(requestData.InstrumentID, "zn2205");
	////strcpy(requestData.ExchangeID, "SHFE");
	//m_tradeApi->ReqQryDepthMarketData(&requestData, 10);

	//char* a[] = { (char*)"sn2206"};
	/*char* b[] = { Mdquotaname };

	int c = c_mdapi->SubscribeMarketData(b, 1);
	qDebug("<mdquotaSubscribeMarketData[%d]>\n", c);*/
	//ui->tableView->setModel(model);
	//virtual int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField * pQryInvestorPosition, int nRequestID) = 0;
	char* b[] = { Mdquotaname };
	pInstExpiredate_map = instExpiredate_map;
	
	char* futureArrays[20];
	int resultCount = 0;

	for (std::string& str : instID_list) {
		if ((str.substr(0, 1) == ProductID && str.length() == 5) || (str.substr(0, 2) == ProductID && str.length() == 6)) {
			futureArrays[resultCount] = new char[str.length() + 1];
			std::strcpy(futureArrays[resultCount], str.c_str());
			++resultCount;
		}
	}
	int c = c_mdapi->SubscribeMarketData(futureArrays, resultCount);
	

	std::vector<std::string> FA;
	for (i = 0; i < resultCount; i++) {
		FA.push_back(futureArrays[i]);
	}

	//int c = c_mdapi->SubscribeMarketData(b, 1);
	int futures_count = 0;
	for (std::string contractID: FA) {
		QStandardItem* contractIDItem = new QStandardItem(contractID.c_str());
		QStandardItem* prevalueitem = new QStandardItem();

		contractIDItem->setEditable(false);
		prevalueitem->setData(0, Qt::DisplayRole);
		model3->setItem(futures_count, 0, contractIDItem);
		model3->setItem(futures_count, 1, prevalueitem);
		pInstPrevalue_map[contractID] = 0.0;
		++futures_count;
	}
	
	qDebug("<mdquotaSubscribeMarketData[%d]>\n", c);
	ui->label_5->setText(QString::number(0));
	ui->label_6->setText(QString::number(0));
	ui->label_7->setText(QString::number(0));
	ui->label_8->setText(QString::number(0));
	QPalette pa;
	QPalette pa1;

	pa.setColor(QPalette::WindowText, Qt::red);
	pa1.setColor(QPalette::WindowText, Qt::blue);

	ui->label_5->setPalette(pa);
	ui->label_8->setPalette(pa);
	ui->label_6->setPalette(pa1);
	ui->label_7->setPalette(pa1);
	//ui->lineEdit->setPalette(pa);

	//Sleep(1000);

	if (chaxunchican() == 1) {
		chaxunchican();
	}
	Sleep(1000);
	//chaxunmingxi();
	////Sleep(5000);
	//Sleep(1000);

	if (chaxunbaodan() == 1) {
		chaxunbaodan();
	}
	//chaxunmingxi();

	/*char* b[] = { Mdquotaname };
		chaxunmingxi();

	int c = c_mdapi->SubscribeMarketData(b, 1);
	qDebug("<mdquotaSubscribeMarketData[%d]>\n", c);*/
	//showtable(&PDepthMarketData);
	//ui->tableView->setMouseTracking(true);
	//ui->tableView->viewport()->setMouseTracking(true);
	//ui->tableView->installEventFilter(this);
	//ui->tableView->viewport()->installEventFilter(this);
	
}
int  mdquota::chaxunchican() {
	int i;
	qDebug("<chaxunbaodan  waiting............................................>\n");
	for (i = 0; i < 8; i++) {
		if (sem_trywait(&sem4) != 0) {
			qDebug("<OnRtnDepthMarketData  waiting............................................>\n");
			Sleep(200);
			continue;

		}
		else {
			break;
		}


	}
	if (i >= 7) {
		sem_post(&sem4);
		return 1;
	}
	qDebug("<chaxunchican sem_wait sucess............................................>\n");

	CThostFtdcQryInvestorPositionField faf;
	memset(&faf, 0, sizeof(faf));
	strcpy(faf.BrokerID, "4020");
	strcpy(faf.ExchangeID, Exchangeid);
	strcpy(faf.InstrumentID, Mdquotaname);
	strcpy(faf.InvestorID, userid);
	m_tradeApi->ReqQryInvestorPosition(&faf, ++requestId);
	return 0;
}
int  mdquota::chaxunmingxi() {
	qDebug("<chaxunmingxi  waiting............................................>\n");

//	sem_wait(&sem4);
	qDebug("<chaxunmingxi sem_wait sucess............................................>\n");

	//sem_wait(&sem3);

	int faf;
	for (faf = 0; faf < 50; faf++) {
		if (chican[faf] != 0) {
			//if(chican[faf])
			qDebug("<chican  chicanchicanchicanchicanchican............................................>\n");
			//chican[faf] = 0;
			model->setItem(chican[faf], 0, new QStandardItem(NULL));
			model->item(chican[faf], 0)->setBackground(QBrush(QColor(180, 180, 180)));
			model->setItem(chican[faf], 4, new QStandardItem(NULL));
			model->item(chican[faf], 4)->setBackground(QBrush(QColor(180, 180, 180)));
			chican[faf] = 0;

		}
	}
	CThostFtdcQryInvestorPositionDetailField faew;
	//qDebug("<chaxunmingxichaxunmingxichaxunmingxichaxunmingxichaxunmingxichaxunmingxichaxunmingxichaxunmingxichaxunmingxichaxunmingxichaxunmingxichaxunmingxichaxunmingxichaxunmingxichaxunmingxichaxunmingxichaxunmingxichaxunmingxichaxunmingxi  waiting............................................>\n");

	memset(&faew, 0, sizeof(faew));
	strcpy(faew.BrokerID, "4020");
	strcpy(faew.InvestorID, userid);
	strcpy(faew.InstrumentID, Mdquotaname);
	strcpy(faew.ExchangeID, Exchangeid);
	//strcpy(faew.InvestUnitID, userid);
	m_tradeApi->ReqQryInvestorPositionDetail(&faew, ++requestId);
	//sem_post(&sem3);
	return 0;
}
int mdquota::chaxunbaodan() {
	int i;
	qDebug("<chaxunbaodan  waiting............................................>\n");
	for (i = 0; i < 8; i++) {
		if (sem_trywait(&sem4) != 0) {
			qDebug("<OnRtnDepthMarketData  waiting............................................>\n");
			Sleep(200);
			continue;
			
		}
		else {
			break;
		}

		
	}
	if (i >= 7) {
		sem_post(&sem4);
		return 1;
	}

	qDebug("<chaxunbaodan sem_wait sucess............................................>\n");

	int baodanlistint;
	for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
		baodanfrontid[baodanlistint] = 0;
		baodansessionid[baodanlistint] = 0;
		baodandes[baodanlistint] = '2';
		baodanprice[baodanlistint] = 0;
		baodanorderref[baodanlistint] = "";
	}
	baqodanduo = 0;
	baodankong = 0;
	CThostFtdcQryOrderField fagag;
	memset(&fagag, 0, sizeof(fagag));
	strcpy(fagag.BrokerID, "4020");
	strcpy(fagag.InvestorID, userid);
	strcpy(fagag.InstrumentID, Mdquotaname);
	strcpy(fagag.ExchangeID, Exchangeid);
	strcpy(fagag.InvestUnitID, userid);
	m_tradeApi->ReqQryOrder(&fagag, requestId++);
	return 0;
}

void mdquota::OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
	qDebug("< OnRspErrorOnRspErrorOnRspErrorOnRspErrorOnRspErrorOnRspErrorOnRspErrorOnRspErrorOnRspErrorOnRspErrorOnRspErrorOnRspErrorOnRspErrorOnRspErrorOnRspErrorOnRspErrorOnRspErrorOnRspError waiting............................................>\n");

	//QMessageBox::information(this, "Notice", "error form onrsperror");
	ui->ddd->setText(pRspInfo->ErrorMsg);


}
void mdquota::OnRspQryOrder(CThostFtdcOrderField* pOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
	if (bIsLast) {
		sem_post(&sem4);

	}

	if (pOrder == NULL) {
		return;
	}
	if (strcmp(pOrder->InstrumentID, Mdquotaname) != 0) {
		return;
	}
	if (pRspInfo != NULL && pRspInfo->ErrorID != 0) {
		PlaySound(TEXT("error3.wav"), NULL, SND_FILENAME | SND_ASYNC);

		return;
	}
	if (pOrder != NULL) {
		qDebug("<OnRspQryOrder OnRspQryOrderOnRspQryOrderOnRspQryOrderOnRspQryOrderOnRspQryOrderOnRspQryOrderOnRspQryOrder............................................>\n");

		//QMessageBox::information(this, "Notice", "error form onrsperror");
		if (pOrder->OrderStatus == '3' && pOrder->OrderSubmitStatus == '3') {
			if (pOrder->Direction == THOST_FTDC_D_Buy){
				baqodanduo = baqodanduo + pOrder->VolumeTotalOriginal;
			int baodanlistint;
			for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {

				if (baodanfrontid[baodanlistint] == 0 && baodansessionid[baodanlistint] == 0 && baodanorderref[baodanlistint].compare("") == 0) {
					baodanfrontid[baodanlistint] = pOrder->FrontID;
					baodansessionid[baodanlistint] = pOrder->SessionID;
					baodandes[baodanlistint] = pOrder->Direction;
					baodanprice[baodanlistint] = pOrder->LimitPrice;
					baodanorderref[baodanlistint] = (pOrder->OrderRef);
					qDebug("luruchengogngluruchengogngluruchengogngluruchengogngluruchengogng [%d]  [%d] ---   \n", baodanlistint, baqodanduo);
					break;


				}
			}
			int xy = (int(startprice * 100) - int(pOrder->LimitPrice * 100)) / int(priceTick * 100);
			//qDebug("xy xyxyxyxyxyxyxyxyxyxyxyxyxyxy[%lf]  [%lf]  [%lf]  [%d] ---   \n", startprice, pOrder->LimitPrice, priceTick, xy);
			//(model->data(model->index(Indexx.row(), Indexx.column() + 1))).toDouble();
			if (model->data(model->index(xy, 1)).toInt() == 0) {
				model->setItem(xy, 1, new QStandardItem(QString::number(pOrder->VolumeTotalOriginal)));
				model->item(xy, 1)->setBackground(QBrush(QColor(255, 215, 0)));
			}
			else {
				int a = model->data(model->index(xy, 1)).toInt() + pOrder->VolumeTotalOriginal;
				model->setItem(xy, 1, new QStandardItem(QString::number(a)));
				model->item(xy, 1)->setBackground(QBrush(QColor(255, 215, 0)));

				//model->item(xy, 1)->setBackground(QBrush(QColor(128, 128, 128)));
			}
		}
			if (pOrder->Direction == THOST_FTDC_D_Sell) {
				baodankong = baodankong + pOrder->VolumeTotalOriginal;
				int baodanlistint;
				for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {

					if (baodanfrontid[baodanlistint] == 0 && baodansessionid[baodanlistint] == 0 && baodanorderref[baodanlistint].compare("") == 0) {
						baodanfrontid[baodanlistint] = pOrder->FrontID;
						baodansessionid[baodanlistint] = pOrder->SessionID;
						baodandes[baodanlistint] = pOrder->Direction;
						baodanprice[baodanlistint] = pOrder->LimitPrice;
						baodanorderref[baodanlistint] = (pOrder->OrderRef);
						qDebug("luruchengogngluruchengogngluruchengogngluruchengogngluruchengogng [%d]  [%d] ---   \n", baodanlistint, baqodanduo);
						break;


					}
				}
				int xy = (int(startprice * 100) - int(pOrder->LimitPrice * 100)) / int(priceTick * 100);
				//(model->data(model->index(Indexx.row(), Indexx.column() + 1))).toDouble();
				if (model->data(model->index(xy, 3)).toInt() == 0) {
					model->setItem(xy, 3, new QStandardItem(QString::number(pOrder->VolumeTotalOriginal)));
					model->item(xy, 3)->setBackground(QBrush(QColor(255, 215, 0)));
				}
				else {
					int a = model->data(model->index(xy, 3)).toInt() + pOrder->VolumeTotalOriginal;
					model->setItem(xy, 3, new QStandardItem(QString::number(a)));
					model->item(xy, 3)->setBackground(QBrush(QColor(255, 215, 0)));

					//model->item(xy, 1)->setBackground(QBrush(QColor(128, 128, 128)));
				}
			}
		}
	}
}

void mdquota::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField* pInvestorPositionDetail, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
	//sem_wait(&sem2);
	
	//sem_wait(&sem3);
	if (pInvestorPositionDetail == NULL) {
	//	sem_post(&sem3);

		return;
	}
	
	if (strcmp(pInvestorPositionDetail->InstrumentID, Mdquotaname) !=0) {
		//sem_post(&sem3);

		return;
	}
	if (pRspInfo != NULL && pRspInfo->ErrorID != 0) {
		PlaySound(TEXT("error3.wav"), NULL, SND_FILENAME | SND_ASYNC);

		return;
	}
	int a;
	//qDebug("<OnRspQryInvestorPositionDetailOnRspQryInvestorPositionDetailOnRspQryInvestorPositionDetailOnRspQryInvestorPositionDetailOnRspQryInvestorPositionDetailOnRspQryInvestorPositionDetailOnRspQryInvestorPositionDetailOnRspQryInvestorPositionDetailOnRspQryInvestorPositionDetailOnRspQryInvestorPositionDetailOnRspQryInvestorPositionDetail  waiting............................................>\n");
	int faf;
	
	if (pInvestorPositionDetail != NULL) {
		if (pInvestorPositionDetail->OpenPrice > startprice && pInvestorPositionDetail->OpenPrice < endprice) {
			//sem_post(&sem3);

			return;
		}
		if (pInvestorPositionDetail->Volume == 0) {
			return;
		}
		int xy = (int(startprice*100) - int(pInvestorPositionDetail->OpenPrice*100)) / int(priceTick*100);
		int faf;
		if (pInvestorPositionDetail->Direction == THOST_FTDC_D_Buy) {
			if (pInvestorPositionDetail->Volume != 0) {
				//qDebug("<indexnull indexnullindexnullindexnullindexnullindexnullindexnull............................................>\n");

				if (model->data(model->index(xy, 0)).toInt() == 0) {
									qDebug("<indexnull indexnullindexnullindexnullindexnullindexnullindexnull............................................>\n");

					for (faf = 0; faf < 50; faf++) {
						if (chican[faf] == 0 || chican[faf] == xy) {
							if (chican[faf] == xy) {
								break;
							}
							else {
								chican[faf] = xy;
								break;
							}
						}
					}
					a = pInvestorPositionDetail->Volume;
					model->setItem(xy, 0, new QStandardItem(QString::number(a)));
					model->item(xy, 0)->setBackground(QBrush(QColor(0, 209, 255)));
				}
				else {
					 a = model->data(model->index(xy, 0)).toInt() + pInvestorPositionDetail->Volume;
					model->setItem(xy, 0, new QStandardItem(QString::number(a)));
					model->item(xy, 0)->setBackground(QBrush(QColor(0, 209, 255)));
				}
			}
		}
		if (pInvestorPositionDetail->Direction == THOST_FTDC_D_Sell) {
			if (pInvestorPositionDetail->Volume != 0) {
				if (model->data(model->index(xy, 4)).toInt() == 0) {
					for (faf = 0; faf < 50; faf++) {
						if (chican[faf] == 0 || chican[faf] == xy) {
							if (chican[faf] == xy) {
								break;
							}
							else {
								chican[faf] = xy;
								break;
							}
						}
					}
					a = pInvestorPositionDetail->Volume;
					model->setItem(xy, 4, new QStandardItem(QString::number(a)));
					model->item(xy, 4)->setBackground(QBrush(QColor(255, 0, 0)));
				}
				else {
					a = model->data(model->index(xy, 4)).toInt() + pInvestorPositionDetail->Volume;
					model->setItem(xy, 4, new QStandardItem(QString::number(a)));
					model->item(xy, 4)->setBackground(QBrush(QColor(255, 0, 0)));
				}
			}
		}

	}
	//sem_post(&sem3);

}

void mdquota::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* pInvestorPosition, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
	//kong
	if (bIsLast) {
		sem_post(&sem4);

	}
	if (pInvestorPosition == NULL) {
		return;
	}
	if (strcmp(pInvestorPosition->InstrumentID, Mdquotaname) != 0) {
		return;
	}
	if (pRspInfo != NULL && pRspInfo->ErrorID != 0) {
		PlaySound(TEXT("error3.wav"), NULL, SND_FILENAME | SND_ASYNC);

		return;
	}
	if (pInvestorPosition != NULL) {
		if (pInvestorPosition->PosiDirection == THOST_FTDC_PD_Short) {
			if (pInvestorPosition->YdPosition == 0) {
				chicankong = pInvestorPosition->TodayPosition;
				ui->label_8->setText(QString::number(pInvestorPosition->TodayPosition));
				//ui->label_5->setText(QString::number(pInvestorPosition->Position - pInvestorPosition->TodayPosition));

			}
			if (pInvestorPosition->YdPosition != 0) {
				ui->label_5->setText(QString::number(pInvestorPosition->Position - pInvestorPosition->TodayPosition));
				yeschicankong = pInvestorPosition->Position - pInvestorPosition->TodayPosition;
			}
		}
		//duo
		if (pInvestorPosition->PosiDirection == THOST_FTDC_PD_Long) {

			if (pInvestorPosition->YdPosition == 0) {
				chicanduo = pInvestorPosition->TodayPosition;
				ui->label_7->setText(QString::number(pInvestorPosition->TodayPosition));
				//ui->label_6->setText(QString::number(pInvestorPosition->Position - pInvestorPosition->TodayPosition));

			}
			if (pInvestorPosition->YdPosition != 0) {
				yeschicanduo = pInvestorPosition->Position - pInvestorPosition->TodayPosition;
				ui->label_6->setText(QString::number(pInvestorPosition->Position - pInvestorPosition->TodayPosition));
			
			}



		}
	}
}
void mdquota::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData) {
	if (pDepthMarketData == NULL) {
		return;
	}
	if (pDepthMarketData->AskPrice1 > pDepthMarketData->UpperLimitPrice * 100 || pDepthMarketData->AskPrice1 <= 0) {
		return;
	}
	if (pDepthMarketData->BidPrice1 > pDepthMarketData->UpperLimitPrice * 100 || pDepthMarketData->AskPrice1 <= 0) {
		return;
	}
	pInstLastprice_map[pDepthMarketData->InstrumentID] = pDepthMarketData->LastPrice;
	if (strcmp(pDepthMarketData->InstrumentID, Mdquotaname) == 0) {
		hangqingnum = 0;
		if (hanqingtuisongnum > 5000) {
			hanqingtuisongnum = 30;
		}
		hanqingtuisongnum = hanqingtuisongnum + 1;
		//sem_wait(&sem5);
		if (sem_trywait(&sem5) != 0) {
		//	qDebug("<OnRtnDepthMarketData  waiting............................................ %s>\n",Mdquotaname);
			return;
		}
		memcpy(&PDepthMarketData, pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
		sem_post(&sem6);

	}
}
void mdquota::showtable(CThostFtdcDepthMarketDataField* pDepthMarketData){

//void  mdquota::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData) {
	//sem_wait(&sem6);
	//while (1) {
		//if (sem_trywait(&sem6) != 0) {
		//	qDebug("<showtable  waiting............................................>\n");
		//	//continue;
		//	return;
		//}
		////sem_wait(&sem6);
		////ui->ddd->setText("starting.............");
		////printf("%s\n", "OnRtnDepthMarketData：callde");
		////printf("深度行情通知 合约代码:%s 最新价格：%f  买量一: %d   卖量一: %d\n", pDepthMarketData->InstrumentID, pDepthMarketData->LastPrice, pDepthMarketData->BidVolume1, pDepthMarketData->AskVolume1);
		//if (pDepthMarketData == NULL) {
		//	sem_post(&sem5);

		//	return;
		//}
		//if (pDepthMarketData->AskPrice1 > pDepthMarketData->UpperLimitPrice * 100 || pDepthMarketData->AskPrice1 <= 0) {
		//	sem_post(&sem5);

		//	return;
		//}
		//if (pDepthMarketData->BidPrice1 > pDepthMarketData->UpperLimitPrice * 100 || pDepthMarketData->AskPrice1 <= 0) {
		//	sem_post(&sem5);

		//	return;
		//}
	//ui->time
	QStringList list=QDateTime::currentDateTime().toString("hh:mm:ss").split(':');
	ui->timeEdit->setTime(QTime(list[0].toInt(), list[1].toInt(), list[2].toInt()));

		if (strcmp(pDepthMarketData->InstrumentID, Mdquotaname) == 0) {

		//	if (sem_trywait(&sem6) != 0) {
			//	qDebug("<OnRtnDepthMarketData  waiting............................................>\n");
			//	return;
			//}
			if (sem_trywait(&sem6) != 0) {
			//	qDebug("<showtable  waiting............................................%s  %d>\n", Mdquotaname,hangqingnum);
				if (hangqingnum >= 200 && hanqingtuisongnum>20) {
					hangqingnum = 0;
					if (qutastatus == '2') {
						char* b[] = { Mdquotaname };
					//	qDebug("<%s  SubscribeMarketData  return ............................................>\n", Mdquotaname);
						int c = c_mdapi->SubscribeMarketData(b, 1);
					}
				//	qDebug("<%s  drop SubscribeMarketData  return wiht qutastatus not 2  ............................................>\n", Mdquotaname);

					//return;
				}
			//	qDebug("<showtable  waiting............................................>\n");
				//continue;
				hangqingnum = hangqingnum + 1;
				return;
			}
			if (onrtnnumber == 0) {
				//绘制
					//32000.00
					/*ui->lineEdit_2->setText( QString::number(pDepthMarketData->PreClosePrice));

					ui->lineEdit_3->setText(QString::number(pDepthMarketData->OpenPrice));
					ui->lineEdit_4->setText(QString::number(pDepthMarketData->OpenInterest));
					ui->lineEdit_5->setText(QString::number(pDepthMarketData->OpenInterest- pDepthMarketData->PreOpenInterest));*/

				model2->setItem(0, 0, new QStandardItem(QString::number(pDepthMarketData->PreClosePrice)));
				model2->setItem(1, 0, new QStandardItem(QString::number(pDepthMarketData->OpenPrice)));
				if (pDepthMarketData->PreClosePrice > pDepthMarketData->OpenPrice) {
					model2->item(1, 0)->setForeground(QBrush(QColor(0, 209, 255)));
				}
				else {
					model2->item(1, 0)->setForeground(QBrush(QColor(255, 0, 0)));
				}

				//startprice = pDepthMarketData->LastPrice + 2000 * priceTick;
				//endprice = pDepthMarketData->LastPrice - 2000 * priceTick;
				int faf = 20;
				startprice = (int(pDepthMarketData->UpperLimitPrice * 100) + faf * int(priceTick * 100)) / 100;
				endprice = (int(pDepthMarketData->LowerLimitPrice * 100) - faf * int(priceTick * 100)) / 100;

				//endprice = pDepthMarketData->LowerLimitPrice - faf * priceTick;
			//	(startprice - endprice )/priceTick
				int xxx = (int(startprice * 100) - int(endprice * 100)) / int(priceTick * 100);
				qDebug("\tcheck [%d] ---  \n", xxx);

				double jfjfe;
				for (jfjfe = startprice; jfjfe >= endprice; jfjfe = (jfjfe - priceTick)) {
					model->setItem(i, 2, new QStandardItem(QString::number(jfjfe)));

					if (jfjfe >= pDepthMarketData->AskPrice1) {
						model->setItem(i, 0, new QStandardItem(NULL));
						model->setItem(i, 1, new QStandardItem(NULL));
						model->item(i, 2)->setBackground(QBrush(QColor(255, 0, 0)));
						model->setItem(i, 3, new QStandardItem(NULL));
						model->setItem(i, 4, new QStandardItem(NULL));


					}
					//if (jfjfe == pDepthMarketData->AskPrice1) {
					//	model->item(i, 0)->setBackground(QBrush(QColor(255, 0, 0)));
					//	model->setItem(i, 1, new QStandardItem(""));
					//	model->setItem(i, 2, new QStandardItem(""));

					//	//rowask = i;
					//}
					if (pDepthMarketData->AskPrice1 > jfjfe && jfjfe > pDepthMarketData->BidPrice1) {

						//model->item(i, 0)->setBackground(QBrush(QColor(255, 0, 0)));
						//model->
						model->setItem(i, 0, new QStandardItem(NULL));
						model->setItem(i, 1, new QStandardItem(NULL));
						model->setItem(i, 3, new QStandardItem(NULL));
						model->setItem(i, 4, new QStandardItem(NULL));
						model->item(i, 2)->setBackground(QBrush(QColor(255, 255, 255)));

					}
					if (jfjfe <= pDepthMarketData->BidPrice1) {
						model->setItem(i, 0, new QStandardItem(NULL));
						model->setItem(i, 1, new QStandardItem(NULL));
						model->item(i, 2)->setBackground(QBrush(QColor(0, 209, 255)));

						model->setItem(i, 3, new QStandardItem(NULL));
						model->setItem(i, 4, new QStandardItem(NULL));

					}
					//if (jfjfe == pDepthMarketData->BidPrice1) {

					//	model->item(i, 0)->setBackground(QBrush(QColor(0, 255, 0)));

					//	model->setItem(i, 1, new QStandardItem(""));
					//	model->setItem(i, 2, new QStandardItem(""));

					//	//rowbid = i;
					//}
					i = i + 1;
				}

				
				ui->tableView->setModel(model);
				ui->tableView_3->setModel(model3);
				ui->tableView_3->setColumnWidth(0, 35);
				ui->tableView_3->setColumnWidth(1, 35);
				ui->tableView_3->setColumnWidth(2, 35);
				
				onrtnnumber = onrtnnumber + 1;
				ui->tableView->setColumnWidth(0, 35);
				ui->tableView->setColumnWidth(1, 42);
				ui->tableView->setColumnWidth(2, 50);
				ui->tableView->setColumnWidth(3, 42);
				ui->tableView->setColumnWidth(4, 40);
				//ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
				int rowaskx = (int(startprice * 100) - int(pDepthMarketData->AskPrice1 * 100)) / int(priceTick * 100);
				int rowbidx = (int(startprice * 100) - int(pDepthMarketData->BidPrice1 * 100)) / int(priceTick * 100);

				if (rowaskx != 0) {
					ui->tableView->scrollTo(ui->tableView->model()->index(rowaskx - 30, 0), QAbstractItemView::PositionAtTop);
				}
				/*if (rowaskx != 0 && rowbidx != 0) {
					ui->tableView->scrollTo(ui->tableView->model()->index(int((rowbid + rowask) / 2), 0), QAbstractItemView::PositionAtCenter);

				}*/
				ui->lineEdit_2->setText(chedanshu);
				chengjiaoshu = pDepthMarketData->Volume;
				lastprice = pDepthMarketData->LastPrice;
			}
			else {
				//qDebug("\nRtnDepthMarketData LastPrice [%f] ---   \n", pDepthMarketData->LastPrice);
				//qDebug("\nRtnDepthMarketData BidPrice1 [%f] ---   \n", pDepthMarketData->BidPrice1);
				//qDebug("\nRtnDepthMarketData AskPrice1 [%f] ---   \n", pDepthMarketData->AskPrice1);
				//qDebug("\nRtnDepthMarketData startprice [%f] ---   \n", startprice);
				//qDebug("\nRtnDepthMarketData endprice [%f] ---   \n", endprice);

				//if(pDepthMarketData->AskPrice1>pDepthMarketData->)
				//	ui->lineEdit_6->setText(QString::number(((pDepthMarketData->LastPrice - pDepthMarketData->PreClosePrice) / (pDepthMarketData->PreClosePrice)*100),'f',2) + QString::fromStdString("%"));
				model2->setItem(2, 0, new QStandardItem(QString::number(pDepthMarketData->OpenInterest)));
				model2->setItem(3, 0, new QStandardItem(QString::number(pDepthMarketData->OpenInterest - pDepthMarketData->PreOpenInterest)));
				model2->setItem(4, 0, new QStandardItem(QString::number(((pDepthMarketData->LastPrice - pDepthMarketData->PreClosePrice) / (pDepthMarketData->PreClosePrice) * 100), 'f', 2) + QString::fromStdString("%")));
				model2->setItem(5, 0, new QStandardItem(QString::number(pDepthMarketData->Volume)));
				//char *a=  pDepthMarketData->ActionDay
				if (pDepthMarketData->PreOpenInterest > pDepthMarketData->OpenInterest) {
					model2->item(3, 0)->setForeground(QBrush(QColor(0, 209, 255)));
				}
				else {
					model2->item(3, 0)->setForeground(QBrush(QColor(255, 0, 0)));
				}
				if (pDepthMarketData->PreClosePrice > pDepthMarketData->LastPrice) {
					model2->item(4, 0)->setForeground(QBrush(QColor(0, 209, 255)));
				}
				else {
					model2->item(4, 0)->setForeground(QBrush(QColor(255, 0, 0)));
				}
				int rowbidx = (int(startprice * 100) - int(pDepthMarketData->BidPrice1 * 100)) / int(priceTick * 100);
				int tmp = 0;
				int rowaskx = (int(startprice * 100) - int(pDepthMarketData->AskPrice1 * 100)) / int(priceTick * 100);
				//qDebug("\rowbidx rowbidx [%d] ---   \n", rowbidx);
				//qDebug("\rowaskx rowaskx [%d] ---   \n", rowaskx);
				//qDebug("\rowask rowask [%d] ---   \n", rowask);
				//qDebug("\rowbid rowbid [%d] ---   \n", rowbid);
				//qDebug("\rowquta rowquta [%d] ---   \n", rowquta);

				//model->setItem(rowquta, 1, new QStandardItem(""));
				if (pDepthMarketData->Volume > chengjiaoshu) {

					if (rowquta != 0) {
						model->setItem(rowquta, 4, new QStandardItem(NULL));
						model->item(rowquta, 4)->setBackground(QBrush(QColor(180, 180, 180)));
					}
				}
				/*	if (rowquta >= rowbid) {
						model->item(rowquta, 2)->setBackground(QBrush(QColor(0, 209, 255)));

					}
					if (rowask < rowquta && rowquta < rowbid) {
						model->item(rowquta, 2)->setBackground(QBrush(QColor(180, 180, 180)));

					}
					if (rowquta <= rowask) {
						model->item(rowquta, 2)->setBackground(QBrush(QColor(255, 0, 0)));

					}*/

				model->setItem(rowask, 1, new QStandardItem(NULL));
				model->setItem(rowbid, 3, new QStandardItem(NULL));

				model->setItem(rowaskx, 1, new QStandardItem(QString::number(pDepthMarketData->AskVolume1)));
				model->item(rowaskx, 1)->setForeground(QBrush(QColor(255, 0, 0)));

				model->setItem(rowbidx, 3, new QStandardItem(QString::number(pDepthMarketData->BidVolume1)));
				model->item(rowbidx, 3)->setForeground(QBrush(QColor(255, 0, 0)));

				//QStandardItem* item = model->item(0, 0);
				//double xxxc = atof(item->text().toLatin1().data());
				//int w = (xxxc-pDepthMarketData->LastPrice ) / 10; 
				int w = (int(startprice * 100) - int(pDepthMarketData->LastPrice * 100)) / int(priceTick * 100);
				//ui->ddd->setText(QString::number(pDepthMarketData->LastPrice));
			//	ui->ddd->setText(QString::number(startprice));

				//ui->ddd->setText(QString::number(w));
				model->item(rowaskx, 2)->setBackground(QBrush(QColor(255, 0, 0)));
				model->item(rowbidx, 2)->setBackground(QBrush(QColor(0, 209, 255)));


				if (rowask < rowaskx) {
					//ui->ddd->setText("aaa");

					for (tmp = rowask; tmp <= rowaskx; tmp++) {
						//	ui->ddd->setText("aaa111");

						if (tmp < rowbidx) {
							QStandardItem* item = model->item(tmp, 2);
							if (item) { item->setBackground(QBrush(QColor(255, 0, 0))); }
						}
					}
				}
				if (rowask > rowaskx) {
					//ui->ddd->setText("bbb");

					for (tmp = rowaskx + 1; tmp < rowbidx; tmp++) {
						//if (tmp<rowbidx) {
						//	ui->ddd->setText("bbb111");
						QStandardItem* item = model->item(tmp, 2);
						if (item) { item->setBackground(QBrush(QColor(255, 255, 255))); }
					//	model->item(tmp, 0)->setBackground(QBrush(QColor(255, 0, 0)));

				//	}
					}
				}
				if (rowbid > rowbidx) {
					//ui->ddd->setText("ccc");

					for (tmp = rowbid; tmp >= rowbidx; tmp--) {
						if (tmp > rowaskx) {
							//	ui->ddd->setText("ccc111");
							QStandardItem* item = model->item(tmp, 2);
							if (item) { item->setBackground(QBrush(QColor(0, 209, 255))); }
						}
					}
				}
				if (rowbid < rowbidx) {
					//ui->ddd->setText("ddd");

					for (tmp = rowbidx - 1; tmp > rowaskx; tmp--) {

						//if (tmp > rowaskx) {
						//	ui->ddd->setText("ddd111");
						QStandardItem* item = model->item(tmp, 2);
						if (item) { item->setBackground(QBrush(QColor(255, 255, 255))); }
				//	}
					}
				}
				///int xxa;
				//xxa = (startprice-pDepthMarketData->AskPrice1) / 10.00;


			/*	xxa = (startprice - pDepthMarketData->BidPrice2) / 10.00;
				model->setItem(xxa, 1, new QStandardItem(QString::number(pDepthMarketData->BidVolume2)));
				model->item(xxa, 1)->setForeground(QBrush(QColor(255, 0, 0)));

				xxa = (startprice - pDepthMarketData->BidPrice3) / 10.00;
				model->setItem(xxa, 1, new QStandardItem(QString::number(pDepthMarketData->BidVolume3)));
				model->item(xxa, 1)->setForeground(QBrush(QColor(255, 0, 0)));

				xxa = (startprice - pDepthMarketData->BidPrice4) / 10.00;
				model->setItem(xxa, 1, new QStandardItem(QString::number(pDepthMarketData->BidVolume4)));
				model->item(xxa, 1)->setForeground(QBrush(QColor(255, 0, 0)));

				xxa = (startprice - pDepthMarketData->BidPrice5) / 10.00;
				model->setItem(xxa, 1, new QStandardItem(QString::number(pDepthMarketData->BidVolume5)));
				model->item(xxa, 1)->setForeground(QBrush(QColor(255, 0, 0)));*/
				if (pDepthMarketData->Volume > chengjiaoshu){
					model->setItem(w, 4, new QStandardItem(QString::number(pDepthMarketData->Volume - chengjiaoshu)));
				//model->item(w, 2)->setForeground(QBrush(QColor(255, 0, 0)));
				if (pDepthMarketData->LastPrice > lastprice) {
					model->item(w, 4)->setBackground(QBrush(QColor(255, 0, 0)));
				}
				else {
					model->item(w, 4)->setBackground(QBrush(QColor(0, 209, 255)));

				}
				}
				int rowhia = (int(startprice * 100) - int(pDepthMarketData->HighestPrice * 100)) / int(priceTick * 100);
				int rowlowa = (int(startprice * 100) - int(pDepthMarketData->LowestPrice * 100)) / int(priceTick * 100);
				//if (rowhia != rowhi) {
				model->item(rowhia, 2)->setBackground(QBrush(QColor(255, 228, 0)));
				//	//if(rowhi)

			//	}
				//if (rowlowa != rowlow) {
				model->item(rowlowa, 2)->setBackground(QBrush(QColor(255, 228, 0)));

				//}
				/*if (rowhi == 0 && rowlow == 0) {

					model->item(rowhia, 2)->setBackground(QBrush(QColor(255, 228, 0)));
					model->item(rowlowa, 2)->setBackground(QBrush(QColor(255, 228, 0)));

				}
				else {
					if(rwohia != rowhi)

				}*/
				rowhi = rowhia;
				rowlow = rowlowa;
				rowquta = w;
				chengjiaoshu = pDepthMarketData->Volume;
				rowbid = rowbidx;
				rowask = rowaskx;
				lastprice = pDepthMarketData->LastPrice;

				// Calculate Profit
				calculateProfit();
			}
			/*	model->setItem(i++, 1, new QStandardItem(QString::number(pDepthMarketData->LastPrice)));
				ui->tableView->setModel(model);
				ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);*/

				//	ui->tableView->scrollTo(ui->tableView->model()->index(rowaskx, 0));

		}
		sem_post(&sem5);
	//}
}
void mdquota::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
}
void mdquota::OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
	if (pSpecificInstrument == NULL) {
		return;
	}
	if (strcmp(pSpecificInstrument->InstrumentID, Mdquotaname) == 0) {
		hanqingtuisongnum = 0;
	}
	//printf("id: %d   %s price: %f\n", nRequestID, pDepthMarketData->InstrumentID, pDepthMarketData->LastPrice);

//ui->ddd->setText(ui->ddd->text() + "\n"+QString::fromLocal8Bit(pDepthMarketData->InstrumentID) + ":" + QString::number(pDepthMarketData->LastPrice));
//	model->setItem(0, 0, new QStandardItem("hello"));
	//model->setItem(0, 1, new QStandardItem("bbbb"));
	//model->setItem(0, 2, new QStandardItem("aaaa"));
	//model->setItem(i, 0, new QStandardItem(""));
	//model->setItem(i, 1, new QStandardItem(""));

	//model->setItem(i, 2, new QStandardItem(pDepthMarketData->InstrumentID));
	//model->setItem(i, 3, new QStandardItem(QString::number(pDepthMarketData->LastPrice)));
	//model->setItem(i, 4, new QStandardItem(""));
	//model->setItem(i++, 5, new QStandardItem(""));
	//model->setItem(i++, 1, new QStandardItem(QString::number(pDepthMarketData->LastPrice)));

	//model->appendRow()
	//ui->tableView->verticalHeader()->hide();


	qDebug("\tcolumnWidth0 [%d]\n", ui->tableView->columnWidth(0));
	qDebug("\tcolumnWidth1 [%d]\n", ui->tableView->columnWidth(1));
	qDebug("\tcolumnWidth2 [%d]\n", ui->tableView->columnWidth(2));
	qDebug("\tcolumnWidth3 [%d]\n", ui->tableView->columnWidth(3));
	qDebug("\tcolumnWidth4 [%d]\n", ui->tableView->columnWidth(4));


	//qDebug() << QString("ui->tableWidget的第%1列宽%2").arg(i + 1).arg(ui->tableWidget->columnWidth(i));




	//QstandardItemModel* model = new QStandardItemModel(this);
	//ui->textEdit->setText("start.............");

	//ui->lineEdit->setText(ui->lineEdit->text() + "/n"+QString::fromLocal8Bit(pDepthMarketData->InstrumentID,31));
	//ui->lineEdit->setText(ui->lineEdit->text() + "/n" + "aaaaaaaaaaaaaaaaa");
}
//void mdquota::InsertData(char instrumentid[31], char orderref[13], char direction, double limitprice)
//{
//	qDebug() << "InsertData InsertData!InsertData InsertData!InsertData InsertData!InsertData InsertData!InsertData InsertData!InsertData InsertData!";
//
//	QString insert_sql = "insert into student values (?, ?, ?,?)";
//	QSqlQuery sql_query;
//	sql_query.prepare(insert_sql);
//	sql_query.addBindValue(instrumentid);
//	sql_query.addBindValue(orderref);
//	sql_query.addBindValue(direction);
//	sql_query.addBindValue(limitprice);
//
//	if (!sql_query.exec())
//	{
//		qDebug() << "InsertData error!InsertData error!InsertData error!InsertData error!InsertData error!InsertData error!";
//
//		// qDebug() << sql_query.lastError();
//	}
//	else
//	{
//		qDebug() << "inserted Wang!";
//	}
//
//}
//void mdquota::DeleteData(char orderref[13])
//{
//	QString insert_sql = "delete from student where orderref =  :orderfef";
//	QSqlQuery sql_query;
//	sql_query.prepare(insert_sql);
//	sql_query.bindValue(":orderfef", orderref);
//
//
//	if (!sql_query.exec())
//	{
//		qDebug() << "DeleteData error!DeleteData error!DeleteData error!DeleteData error!DeleteData error!DeleteData error!";
//
//		// qDebug() << sql_query.lastError();
//	}
//	else
//	{
//		qDebug() << "inserted Wang!";
//	}
//
//}
void mdquota::OnRspOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
	if (pInputOrder == NULL) {
		return;
	}

	if (strcmp(pInputOrder->InstrumentID, Mdquotaname) != 0) {
		return;
	}
	printf("%s\n", "交易OnRspOrderInsert:called");
	if (pRspInfo != NULL && pRspInfo->ErrorID == 0) {

		printf("OnRspOrderInsert订单提交成功\n");
		//InsertData(pInputOrder->InstrumentID, pInputOrder->OrderRef, pInputOrder->Direction, pInputOrder->LimitPrice);
	}
	else {
		PlaySound(TEXT("error3.wav"), NULL, SND_FILENAME | SND_ASYNC);

		printf("  OnRspOrderInsert订单提交失败:%s\n", pRspInfo->ErrorMsg);

	}

}
void  mdquota::OnRtnOrder(CThostFtdcOrderField* pOrder) {
	if (pOrder == NULL) {
		return;
	}
	if (strcmp(pOrder->InstrumentID, Mdquotaname) != 0) {
		return;
	}

	int faf;

	sem_wait(&sem2);
	//sem_wait(&sem3);

	if (pOrder->Direction == THOST_FTDC_D_Buy) {
		//if (pOrder->OrderSubmitStatus == THOST_FTDC_OSS_InsertSubmitted ) {//已提交
		if (pOrder->OrderSubmitStatus == THOST_FTDC_OSS_InsertSubmitted && (pOrder->OrderStatus == THOST_FTDC_OST_NoTradeQueueing || pOrder->OrderStatus == THOST_FTDC_OST_NoTradeNotQueueing || pOrder->OrderStatus == THOST_FTDC_OST_Unknown || pOrder->OrderStatus == THOST_FTDC_OST_NotTouched || pOrder->OrderStatus == THOST_FTDC_OST_Touched)) {//部分成交还在队列

			if (pOrder->SequenceNo != 0) {
				sem_post(&sem2);
				//sem_post(&sem3);

				return;
			}
			baqodanduo = baqodanduo + pOrder->VolumeTotalOriginal;
			int baodanlistint;
			for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
				qDebug("\n baodanlistintbaodanlistintbaodanlistintbaodanlistint  [%d]  [%d] [%d]  [%f] [%s]  [%c]---   \n", baodanlistint, baodanfrontid[baodanlistint], baodansessionid[baodanlistint], baodanprice[baodanlistint], baodanorderref[baodanlistint].c_str(),baodandes[baodanlistint]);

			}
			for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {

				if (baodanfrontid[baodanlistint] == 0 && baodansessionid[baodanlistint] == 0 && baodanorderref[baodanlistint].compare("")==0) {
					baodanfrontid[baodanlistint] = pOrder->FrontID;
					baodansessionid[baodanlistint] = pOrder->SessionID;
					baodandes[baodanlistint] = pOrder->Direction;
					baodanprice[baodanlistint] = pOrder->LimitPrice;
					baodanorderref[baodanlistint]=(pOrder->OrderRef);
					qDebug("luruchengogngluruchengogngluruchengogngluruchengogngluruchengogng [%d]  [%d] ---   \n", baodanlistint, baqodanduo);
					break;


				}
			}
			//InsertData(pOrder->InstrumentID, pOrder->OrderRef, pOrder->Direction, pOrder->LimitPrice);
			int xy = (int(startprice*100) - int(pOrder->LimitPrice* 100)) / int(priceTick* 100);
			qDebug("xy xyxyxyxyxyxyxyxyxyxyxyxyxyxy[%lf]  [%lf]  [%lf]  [%d] ---   \n", startprice,pOrder->LimitPrice ,priceTick, xy);
			//(model->data(model->index(Indexx.row(), Indexx.column() + 1))).toDouble();
			if (model->data(model->index(xy,1)).toInt() == 0) {
				model->setItem(xy, 1, new QStandardItem(QString::number(pOrder->VolumeTotalOriginal)));
				model->item(xy, 1)->setBackground(QBrush(QColor(255, 215, 0)));
			}
			else {
				int a = model->data(model->index(xy,1)).toInt() + pOrder->VolumeTotalOriginal;
				model->setItem(xy, 1, new QStandardItem(QString::number(a)));
				model->item(xy, 1)->setBackground(QBrush(QColor(255, 215, 0)));

				//model->item(xy, 1)->setBackground(QBrush(QColor(128, 128, 128)));
			}
			qDebug("\aaaaaaaaaaaaaaaaTHOST_FTDC_OSS_InsertSubmitted [%d] ---   \n", model->data(model->index(xy, 1)).toInt());
			PlaySound(NULL, NULL, SND_FILENAME | SND_SYNC);

			if (!PlaySound(TEXT("cashreg.wav"), NULL, SND_FILENAME | SND_ASYNC)) {
				qDebug("bofangcashreg error\n ");
			}
		}
		if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled) {//已撤单
		//	DeleteData(pOrder->OrderRef);
			baqodanduo = baqodanduo - pOrder->VolumeTotal;
			if (baqodanduo < 0) {
				baqodanduo = 0;
			}
			int baodanlistint;
			for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
				if (baodanfrontid[baodanlistint] == pOrder->FrontID && baodansessionid[baodanlistint] == pOrder->SessionID && baodanorderref[baodanlistint].compare(pOrder->OrderRef) == 0) {
					baodanfrontid[baodanlistint] = 0;
					baodansessionid[baodanlistint] = 0;
					baodandes[baodanlistint] = '2';
					baodanprice[baodanlistint] = 0;
					baodanorderref[baodanlistint]="";
					//break;


				}
			}
			int xy = (int(startprice*100) - int(pOrder->LimitPrice*100)) / int(priceTick*100);
			int a = model->data(model->index(xy, 1)).toInt() -  pOrder->VolumeTotal;
			if (a <= 0) {
				model->setItem(xy, 1, new QStandardItem(NULL));
				model->item(xy, 1)->setBackground(QBrush(QColor(180, 180, 180)));

			}
			else {
				model->setItem(xy, 1, new QStandardItem(QString::number(a)));
				model->item(xy, 1)->setBackground(QBrush(QColor(255, 215, 0)));

			}
			//PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
			sem_post(&sem3);

			PlaySound(TEXT("Cancellation.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP| SND_NOWAIT);
			ui->lineEdit_2->setText(QString::number(ui->lineEdit_2->text().toInt() + 1));

		
		}
		//if (pOrder->OrderStatus == THOST_FTDC_OST_AllTraded) {//全部成交
		//	int xy = (startprice - pOrder->LimitPrice) / priceTick;
		//	model->setItem(xy, 0, new QStandardItem(QString::number(pOrder->VolumeTraded)));
		//	model->item(xy, 0)->setBackground(QBrush(QColor(0, 255, 0)));
		//	model->setItem(xy, 1, new QStandardItem(""));
		//	model->item(xy, 1)->setBackground(QBrush(QColor(255, 255, 255)));

		//}
		if (pOrder->OrderStatus == THOST_FTDC_OST_PartTradedQueueing || pOrder->OrderStatus == THOST_FTDC_OST_PartTradedNotQueueing|| pOrder->OrderStatus == THOST_FTDC_OST_AllTraded) {//部分成交还在队列
			/*if (pOrder->OrderStatus == THOST_FTDC_OST_AllTraded) {
				chaxunchican();

			}*/
		/*	baqodanduo = baqodanduo - pOrder->VolumeTotalOriginal;
			if (baqodanduo < 0) {
				baqodanduo = 0;
			}*/
			if (pOrder->OrderStatus == THOST_FTDC_OST_PartTradedNotQueueing || pOrder->OrderStatus == THOST_FTDC_OST_AllTraded) {
				int baodanlistint;
				for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
					if (baodanfrontid[baodanlistint] == pOrder->FrontID && baodansessionid[baodanlistint] == pOrder->SessionID && baodanorderref[baodanlistint].compare(pOrder->OrderRef) == 0) {
						baodanfrontid[baodanlistint] = 0;
						baodansessionid[baodanlistint] = 0;
						baodandes[baodanlistint] = '2';
						baodanprice[baodanlistint] = 0;
						baodanorderref[baodanlistint]="";
						//break;


					}
				}
			}
			
			int xy = (int(startprice * 100) - int(pOrder->LimitPrice * 100)) / int(priceTick * 100);
			int a;
			if (model->data(model->index(xy, 1)).toInt() == 0) {
				a = 0;
			}
			else {
				//qDebug("\aaaaaaaaaaaaaaaa [%d] ---   \n", model->data(model->index(xy, 1)).toInt());
				//	Sleep(5000);
			//	qDebug("\aaaaaaaaaaaaaaaa [%d] ---   \n", pOrder->VolumeTotalOriginal);

				a = model->data(model->index(xy, 1)).toInt() - pOrder->VolumeTotalOriginal;
			}
			qDebug("\aaaaaaaaaaaaaaaa [%d] ---   \n", a);

			if (a <= 0) {

				model->setItem(xy, 1, new QStandardItem(NULL));
				model->item(xy, 1)->setBackground(QBrush(QColor(180, 180, 180)));

			}
			else {
				model->setItem(xy, 1, new QStandardItem(QString::number(a)));
				model->item(xy, 1)->setBackground(QBrush(QColor(255, 215, 0)));


			}
			
		}

	}
	if (pOrder->Direction == THOST_FTDC_D_Sell) {
		//if (pOrder->OrderSubmitStatus == THOST_FTDC_OSS_InsertSubmitted) {//已提交
		if (pOrder->OrderSubmitStatus == THOST_FTDC_OSS_InsertSubmitted && (pOrder->OrderStatus == THOST_FTDC_OST_NoTradeQueueing || pOrder->OrderStatus == THOST_FTDC_OST_NoTradeNotQueueing || pOrder->OrderStatus == THOST_FTDC_OST_Unknown || pOrder->OrderStatus == THOST_FTDC_OST_NotTouched || pOrder->OrderStatus == THOST_FTDC_OST_Touched)) {//部分成交还在队列
			if (pOrder->SequenceNo != 0) {
				sem_post(&sem2);
			//	sem_post(&sem3);


				return;
			}
			baodankong = baodankong + pOrder->VolumeTotalOriginal;
			int baodanlistint;
			for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
				if (baodanfrontid[baodanlistint] == 0 && baodansessionid[baodanlistint] == 0 && baodanorderref[baodanlistint].compare("") == 0) {
					baodanfrontid[baodanlistint] = pOrder->FrontID;
					baodansessionid[baodanlistint] = pOrder->SessionID;
					baodandes[baodanlistint] = pOrder->Direction;
					baodanprice[baodanlistint] = pOrder->LimitPrice;
					baodanorderref[baodanlistint]=pOrder->OrderRef;

					break;

				}
			}
			//InsertData(pOrder->InstrumentID, pOrder->OrderRef, pOrder->Direction, pOrder->LimitPrice);
			int xy = (int(startprice*100) - int(pOrder->LimitPrice*100)) / int(priceTick*100);
			//(model->data(model->index(Indexx.row(), Indexx.column() + 1))).toDouble();
			if (model->data(model->index(xy, 3)).toInt() == 0) {
				model->setItem(xy, 3, new QStandardItem(QString::number(pOrder->VolumeTotalOriginal)));
				model->item(xy, 3)->setBackground(QBrush(QColor(255, 215, 0)));
			}
			else {
				int a = model->data(model->index(xy, 3)).toInt() + pOrder->VolumeTotalOriginal;
				model->setItem(xy, 3, new QStandardItem(QString::number(a)));
				model->item(xy, 3)->setBackground(QBrush(QColor(255, 215, 0)));

				//model->item(xy, 1)->setBackground(QBrush(QColor(128, 128, 128)));
			}
			PlaySound(NULL, NULL, SND_FILENAME | SND_SYNC);

			if (!PlaySound(TEXT("cashreg.wav"), NULL, SND_FILENAME | SND_ASYNC)) {
				qDebug("bofangcashreg error\n ");
			}

		}
		if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled) {//已撤单
		//	DeleteData(pOrder->OrderRef);
			baodankong = baodankong - pOrder->VolumeTotal;
			if (baodankong < 0) {
				baodankong = 0;
			}
			int baodanlistint;
			for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
				if (baodanfrontid[baodanlistint] == pOrder->FrontID && baodansessionid[baodanlistint] == pOrder->SessionID && baodanorderref[baodanlistint].compare(pOrder->OrderRef) == 0) {
					baodanfrontid[baodanlistint] = 0;
					baodansessionid[baodanlistint] = 0;
					baodandes[baodanlistint] = '2';
					baodanprice[baodanlistint] = 0;
					baodanorderref[baodanlistint]="";
					//break;


				}
			}
			int xy = (int(startprice*100) - int(pOrder->LimitPrice*100)) / int(priceTick*100);
			int a = model->data(model->index(xy, 3)).toInt() - pOrder->VolumeTotal;
			if (a <= 0) {
				model->setItem(xy, 3, new QStandardItem(NULL));
				model->item(xy, 3)->setBackground(QBrush(QColor(180, 180, 180)));

			}
			else {
				model->setItem(xy, 3, new QStandardItem(QString::number(a)));
				model->item(xy, 3)->setBackground(QBrush(QColor(255, 215, 0)));

			}
			sem_post(&sem3);

			//PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
			PlaySound(TEXT("Cancellation.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP| SND_NOWAIT);
			ui->lineEdit_2->setText(QString::number(ui->lineEdit_2->text().toInt() + 1));

		}
		//if (pOrder->OrderStatus == THOST_FTDC_OST_AllTraded) {//全部成交
		//	int xy = (startprice - pOrder->LimitPrice) / priceTick;
		//	model->setItem(xy, 0, new QStandardItem(QString::number(pOrder->VolumeTraded)));
		//	model->item(xy, 0)->setBackground(QBrush(QColor(0, 255, 0)));
		//	model->setItem(xy, 1, new QStandardItem(""));
		//	model->item(xy, 1)->setBackground(QBrush(QColor(255, 255, 255)));

		//}
		if (pOrder->OrderStatus == THOST_FTDC_OST_PartTradedQueueing || pOrder->OrderStatus == THOST_FTDC_OST_PartTradedNotQueueing || pOrder->OrderStatus == THOST_FTDC_OST_AllTraded) {//部分成交还在队列
			/*if (pOrder->OrderStatus == THOST_FTDC_OST_AllTraded) {
				chaxunchican();

			}*/
			/*if (pOrder->CombOffsetFlag[0] = THOST_FTDC_OF_Open) {
				chicankong=chicankong+(pOrder->VolumeTraded-baodanchengjiaolast)
			}*/
		/*	baodankong = baodankong - pOrder->VolumeTotalOriginal;
			if (baodankong < 0) {
				baodankong = 0;
			}*/
			if (pOrder->OrderStatus == THOST_FTDC_OST_PartTradedNotQueueing || pOrder->OrderStatus == THOST_FTDC_OST_AllTraded) {
				int baodanlistint;
				for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
					if (baodanfrontid[baodanlistint] == pOrder->FrontID && baodansessionid[baodanlistint] == pOrder->SessionID && baodanorderref[baodanlistint].compare(pOrder->OrderRef) == 0) {
						baodanfrontid[baodanlistint] = 0;
						baodansessionid[baodanlistint] = 0;
						baodandes[baodanlistint] = '2';
						baodanprice[baodanlistint] = 0;
						baodanorderref[baodanlistint]="";
						//break;



					}
				}
			}
			int xy = (int(startprice*100) - int(pOrder->LimitPrice*100)) / int(priceTick*100);
			int a;
			if (model->data(model->index(xy, 3)).toInt() == 0) {
				a = 0;
			}
			else {
				a = model->data(model->index(xy, 3)).toInt() - pOrder->VolumeTotalOriginal;
			}
			if (a <= 0) {

				model->setItem(xy, 3, new QStandardItem(NULL));
				model->item(xy, 3)->setBackground(QBrush(QColor(180, 180, 180)));

			}
			else {
				model->setItem(xy, 3, new QStandardItem(QString::number(a)));
				model->item(xy, 3)->setBackground(QBrush(QColor(255, 215, 0)));


			}
			
			/*int b;
			if (model->data(model->index(xy, 4)).toInt() == 0) {
				for (faf = 0; faf < 50; faf++) {
					if (chican[faf] == 0) {
						chican[faf] = xy;
						break;
					}
				}
				b = pOrder->VolumeTotalOriginal;
			}
			else {
				b = model->data(model->index(xy, 4)).toInt() + pOrder->VolumeTotalOriginal;
			}
			model->setItem(xy, 4, new QStandardItem(QString::number(b)));
			model->item(xy, 4)->setBackground(QBrush(QColor(0, 255, 0)));
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);

			PlaySound(TEXT("chimes.wav"), NULL, SND_FILENAME | SND_ASYNC);*/

		}
	}
	
	sem_post(&sem2);
	//sem_post(&sem3);


}

void mdquota::OnRtnTrade(CThostFtdcTradeField* pTrade) {
	if (pTrade == NULL) {
		return;
	}
	if (strcmp(pTrade->InstrumentID, Mdquotaname) != 0) {
		return;
	}
	sem_wait(&sem7);

	if (pTrade->Direction == THOST_FTDC_D_Buy) {
		baqodanduo = baqodanduo - pTrade->Volume;
		if (baqodanduo < 0) {
			baqodanduo = 0;
		}
		if (pTrade->OffsetFlag == THOST_FTDC_OF_Open) {
			chicanduo = chicanduo + pTrade->Volume;
		}
		if (pTrade->OffsetFlag == THOST_FTDC_OF_Close) {
			if (strcmp("SHFE", Exchangeid) == 0) {
			yeschicankong = yeschicankong - pTrade->Volume;
			}
			else {
				if (yeschicankong <= pTrade->Volume) {
					chicankong = chicankong - (pTrade->Volume - yeschicankong);

					yeschicankong = 0;
					//4  5 
				}
				else {
					yeschicankong = yeschicankong - pTrade->Volume;
				}
				//chicanduo = chicanduo - pTrade->Volume;
			}
		}
		if (pTrade->OffsetFlag == THOST_FTDC_OF_CloseToday) {
			if (strcmp("SHFE", Exchangeid) == 0) {
				chicankong = chicankong - pTrade->Volume;

			}
			else {
				if (yeschicankong <= pTrade->Volume) {
					chicankong = chicankong - (pTrade->Volume - yeschicankong);

					yeschicankong = 0;
					//4  5 
				}
				else {
					yeschicankong = yeschicankong - pTrade->Volume;
				}
			}

		}
		if (pTrade->OffsetFlag == THOST_FTDC_OF_CloseYesterday) {
			if (strcmp("SHFE", Exchangeid) == 0) {
				yeschicankong = yeschicankong - pTrade->Volume;

			}
			else {
				if (yeschicankong <= pTrade->Volume) {
					chicankong = chicankong - (pTrade->Volume - yeschicankong);

					yeschicankong = 0;
					//4  5 
				}
				else {
					yeschicankong = yeschicankong - pTrade->Volume;
				}
			}
		}
		
		int b;
		int faf;
		int xy = (int(startprice * 100) - int(pTrade->Price * 100)) / int(priceTick * 100);

		if (model->data(model->index(xy, 0)).toInt() == 0) {
			for (faf = 0; faf < 50; faf++) {
				if (chican[faf] == 0 || chican[faf] == xy) {
					if (chican[faf] == xy) {
						break;
					}
					else {
						chican[faf] = xy;
						break;
					}
				}
			}
			b = pTrade->Volume;
		}
		else {
			b = model->data(model->index(xy, 0)).toInt() + pTrade->Volume;
		}
		model->setItem(xy, 0, new QStandardItem(QString::number(b)));
		model->item(xy, 0)->setBackground(QBrush(QColor(0, 209, 255)));
		PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC );

		PlaySound(TEXT("chimes.wav"), NULL, SND_FILENAME | SND_ASYNC );
		if (pTrade->OffsetFlag == THOST_FTDC_OF_Close || pTrade->OffsetFlag == THOST_FTDC_OF_CloseYesterday || pTrade->OffsetFlag == THOST_FTDC_OF_CloseToday) {
			chaxunmingxi();
		}
	}
	if (pTrade->Direction == THOST_FTDC_D_Sell) {
		baodankong = baodankong - pTrade->Volume;
		if (baodankong < 0) {
			baodankong = 0;
		}
		if (pTrade->OffsetFlag == THOST_FTDC_OF_Open) {
			chicankong = chicankong + pTrade->Volume;
		}
		if (pTrade->OffsetFlag == THOST_FTDC_OF_Close) {
			if (strcmp("SHFE", Exchangeid) == 0) {
				yeschicanduo = yeschicanduo - pTrade->Volume;
			}
			else {
				if (yeschicanduo <= pTrade->Volume) {
					chicanduo = chicanduo - (pTrade->Volume - yeschicanduo);

					yeschicanduo = 0;
					//4  5 
				}
				else {
					yeschicanduo = yeschicanduo - pTrade->Volume;
				}
				//chicanduo = chicanduo - pTrade->Volume;
			}
		}
		if (pTrade->OffsetFlag == THOST_FTDC_OF_CloseToday) {
			if (strcmp("SHFE", Exchangeid) == 0) {
				chicanduo = chicanduo - pTrade->Volume;

			}
			else {
				if (yeschicanduo <= pTrade->Volume) {
					chicanduo = chicanduo - (pTrade->Volume - yeschicanduo);

					yeschicanduo = 0;
					//4  5 
				}
				else {
					yeschicanduo = yeschicanduo - pTrade->Volume;
				}
			}

		}
		if (pTrade->OffsetFlag == THOST_FTDC_OF_CloseYesterday) {
			if (strcmp("SHFE", Exchangeid) == 0) {
				yeschicanduo = yeschicanduo - pTrade->Volume;

			}
			else {
				if (yeschicanduo <= pTrade->Volume) {
					chicanduo = chicanduo - (pTrade->Volume - yeschicanduo);

					yeschicanduo = 0;
					//4  5 
				}
				else {
					yeschicanduo = yeschicanduo - pTrade->Volume;
				}
			}
		}
	/*	int afx = 0;
		int afxx = 0;
		for (afx = 0; afx < 50; afx++) {
			if (chican[afx] != 0) {
				afxx = afxx + (model->data(model->index(chican[afx], 0)).toInt()) + (model->data(model->index(chican[afx], 4)).toInt());
			}
		}
		if (afxx > (yeschicanduo + yeschicankong + chicanduo + chicankong)) {
			chaxunmingxi();
		}*/
		//int xy = (int(startprice * 100) - int(pTrade->Price * 100)) / int(priceTick * 100);
		//int a;
		//if (model->data(model->index(xy, 1)).toInt() == 0) {
		//	a = 0;
		//}
		//else {
		//	//qDebug("\aaaaaaaaaaaaaaaa [%d] ---   \n", model->data(model->index(xy, 1)).toInt());
		//	//	Sleep(5000);
		////	qDebug("\aaaaaaaaaaaaaaaa [%d] ---   \n", pOrder->VolumeTotalOriginal);

		//	a = model->data(model->index(xy, 1)).toInt() - pTrade->Volume;
		//}
		//qDebug("\aaaaaaaaaaaaaaaa [%d] ---   \n", a);

		//if (a <= 0) {

		//	model->setItem(xy, 3, new QStandardItem(NULL));
		//	model->item(xy, 3)->setBackground(QBrush(QColor(180, 180, 180)));

		//}
		//else {
		//	model->setItem(xy, 3, new QStandardItem(QString::number(a)));
		//	model->item(xy, 3)->setBackground(QBrush(QColor(255, 215, 0)));


		//}
		int b;
		int faf;
		int xy = (int(startprice * 100) - int(pTrade->Price * 100)) / int(priceTick * 100);

		if (model->data(model->index(xy, 0)).toInt() == 0) {
			for (faf = 0; faf < 50; faf++) {
				if (chican[faf] == 0 || chican[faf] == xy) {
					if (chican[faf] == xy) {
						break;
					}
					else {
						chican[faf] = xy;
						break;
					}
				}
			}
			b = pTrade->Volume;
		}
		else {
			b = model->data(model->index(xy, 4)).toInt() + pTrade->Volume;
		}
		model->setItem(xy, 4, new QStandardItem(QString::number(b)));
		model->item(xy, 4)->setBackground(QBrush(QColor(255, 0, 0)));
		PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);

		PlaySound(TEXT("chimes.wav"), NULL, SND_FILENAME | SND_ASYNC );
		if (pTrade->OffsetFlag == THOST_FTDC_OF_Close || pTrade->OffsetFlag == THOST_FTDC_OF_CloseYesterday || pTrade->OffsetFlag == THOST_FTDC_OF_CloseToday) {
			chaxunmingxi();
		}
	}
	//if ((chicanduo + chicankong + yeschicanduo + yeschicankong) == 0) {
	//	int faf;
	//	for (faf = 0; faf < 50; faf++) {
	//		if (chican[faf] != 0) {
	//			//if(chican[faf])
	//			qDebug("<chican  chicanchicanchicanchicanchican............................................>\n");
	//			//chican[faf] = 0;
	//			model->setItem(chican[faf], 0, new QStandardItem(NULL));
	//			model->item(chican[faf], 0)->setBackground(QBrush(QColor(180, 180, 180)));
	//			model->setItem(chican[faf], 4, new QStandardItem(NULL));
	//			model->item(chican[faf], 4)->setBackground(QBrush(QColor(180, 180, 180)));
	//			chican[faf] = 0;

	//		}
	//	}
	//}
	ui->label_8->setText(QString::number(chicankong));

	ui->label_5->setText(QString::number(yeschicankong));
	ui->label_7->setText(QString::number(chicanduo));
	ui->label_6->setText(QString::number(yeschicanduo));
	sem_post(&sem7);


	//chaxunchican();
	//chaxunmingxi();
}


void mdquota::onTableClicked(const QModelIndex& Indexx) {
	sem_wait(&sem);
	qDebug("\tcheck [%d] ---   [%d]\n", Indexx.row(), Indexx.column());
	//chaxunmingxi();
	// 0 1 2 3 4 
	//chaxunmingxi();
	if (Indexx.column() == 0) {
		//chaxunmingxi();
		if (baqodanduo > 0) {
			qDebug("you dan ke che\n");

			int baodanlistint;
			for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
				if (int(baodanprice[baodanlistint]*100) == int(((model->data(model->index(Indexx.row(), Indexx.column() + 2))).toDouble())*100)) {
					CThostFtdcInputOrderActionField deord;
					memset(&deord, 0, sizeof(deord));
					strcpy(deord.BrokerID, "4020");
					strcpy(deord.InvestorID, userid);
					strcpy(deord.InstrumentID, Mdquotaname);
					strcpy(deord.OrderRef, baodanorderref[baodanlistint].c_str());
					deord.FrontID = baodanfrontid[baodanlistint];
					deord.SessionID = baodansessionid[baodanlistint];
					deord.ActionFlag = THOST_FTDC_AF_Delete;
					deord.LimitPrice = 0;
					deord.VolumeChange = 0;
					strcpy(deord.UserID, userid);
					strcpy(deord.ExchangeID, Exchangeid);
					sem_init(&sem3, 0, 0);

					m_tradeApi->ReqOrderAction(&deord, requestId++);
					int valp;
					sem_getvalue(&sem3, &valp);
					qDebug("<sem_trywait  sem3 start............................................%d>\n", valp);

					int xa;
					for (xa = 0; xa < 8; xa++) {
						if (sem_trywait(&sem3) != 0) {
							qDebug("<sem_trywait  sem3 ............................................%d>\n", valp);
							Sleep(50);
							continue;

						}
						else {
							break;
						}


					}
					if (i >= 7) {
						sem_post(&sem3);
						//return 1;
					}

					qDebug("fasong chedan\n");



				}
			}
		}
		else {
			//qDebug("\tcheck [%d] ---   [%d]\n", Indexx.row(), Indexx.column());
			qDebug("wu dan ke che[%d]\n", baqodanduo);

		}
	}
	if (Indexx.column() == 1)
	{//买入
		//if (ui->checkBox_3->isChecked()) {//  需要撤单
			//ui->label_8->text().toInt()
		//chaxunmingxi();
		CThostFtdcInputOrderField ord;
		memset(&ord, 0, sizeof(ord));
		strcpy(ord.BrokerID, "4020");
		strcpy(ord.InvestorID, userid);
		strcpy(ord.InstrumentID, Mdquotaname);
		strcpy(ord.OrderRef, "");//报单引用
		ord.Direction = THOST_FTDC_D_Buy;
		if (ui->checkBox_3->isChecked() && baqodanduo > 0) {
			int baodanlistint;
			for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
				if (baodandes[baodanlistint]  == '0') {
					qDebug("abel_8label_8label_8label_8label_8label_8label_8label_8 [%d]   [%d] [%d]]\n", ui->label_8->text().toInt(), baqodanduo, baodandes[baodanlistint]);

					CThostFtdcInputOrderActionField deord;
					memset(&deord, 0, sizeof(deord));
					strcpy(deord.BrokerID, "4020");
					strcpy(deord.InvestorID, userid);
					strcpy(deord.InstrumentID, Mdquotaname);
					strcpy(deord.OrderRef, baodanorderref[baodanlistint].c_str());
					deord.FrontID = baodanfrontid[baodanlistint];
					deord.SessionID = baodansessionid[baodanlistint];
					deord.ActionFlag = THOST_FTDC_AF_Delete;
					deord.LimitPrice = 0;
					deord.VolumeChange = 0;
					strcpy(deord.UserID, userid);
					strcpy(deord.ExchangeID, Exchangeid);
					sem_init(&sem3, 0, 0);

					m_tradeApi->ReqOrderAction(&deord, requestId++);
					int valp;
					sem_getvalue(&sem3, &valp);
					qDebug("<sem_trywait  sem3 start............................................%d>\n", valp);
					int xa;
					for (xa = 0; xa < 8; xa++) {
						if (sem_trywait(&sem3) != 0) {
							qDebug("<sem_trywait  sem3 ............................................%d>\n", valp);
							Sleep(50);
							continue;

						}
						else {
							break;
						}


					}
					if (i >= 7) {
						sem_post(&sem3);
						//return 1;
					}
				}
			}
		
		}
		//sem_wait(&sem3);
		if (chicankong != 0 || yeschicankong != 0) {//需要平仓
			if (ui->radioButton->isChecked()){//锁仓
				ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//组合开平标志
				ord.VolumeTotalOriginal = ui->spinBox->value();
			}
			else {
				/*while (1) {
					if (baqodanduo >= ((ui->label_5->text().toInt()) + (ui->label_8->text().toInt()))) {
						continue;
					}
					else {
						break;
					}
				}*/
				if (strcmp("SHFE", Exchangeid) == 0) {
					if (yeschicankong != 0) {
						ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseYesterday;//组合开平标志
						if (yeschicankong <= ui->spinBox->value()) {
							ord.VolumeTotalOriginal = yeschicankong;
						}
						else {
							ord.VolumeTotalOriginal = ui->spinBox->value();
						}
					}
					else {
						ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;//组合开平标志
						if (chicankong <= ui->spinBox->value()) {
							ord.VolumeTotalOriginal = chicankong;
						}
						else {
							ord.VolumeTotalOriginal = ui->spinBox->value();
						}
					}
				}
				else {
					ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;//组合开平标志
					if (chicankong <= ui->spinBox->value()) {
						ord.VolumeTotalOriginal = chicankong;
					}
					else {
						ord.VolumeTotalOriginal = ui->spinBox->value();
					}
				}
				//ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;//组合开平标志

			}
		}
		else {
			ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//组合开平标志
			ord.VolumeTotalOriginal = ui->spinBox->value();
		}
		//}
		
	//	ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//组合开平标志
		ord.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;//组合投机套保标志
		//ord.VolumeTotalOriginal = ui->spinBox->value();
		ord.ContingentCondition = THOST_FTDC_CC_Immediately;///触发条件
		ord.VolumeCondition = THOST_FTDC_VC_AV;//成交量类型
		ord.MinVolume = 1;///最小成交量
		ord.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;//强平原因
		ord.IsAutoSuspend = 0; //自动挂起标志
		ord.UserForceClose = 0;//用户强评标志
		ord.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
		//ord.LimitPrice = (startprice - (10.00 * Indexx.row())); // place a price in double here
		//mdquota* t = new mdquota(model->data(model->index(index.row(), index.column())).toString().toLatin1().data(), PriceTick);

		ord.LimitPrice = (model->data(model->index(Indexx.row(),Indexx.column()+1))).toDouble();
		ord.TimeCondition = THOST_FTDC_TC_GFD; // 当日有效
		m_tradeApi->ReqOrderInsert(&ord, requestId++);
		
		//	model->data(Indexx).toString().toInt
	}
	if (Indexx.column() == 2) {
		//撤单
		chaxunmingxi();
		//chaxunchican();
		//chaxunbaodan();

	}
	if (Indexx.column() == 3) {
		//卖出
		if (ui->checkBox_3->isChecked() && baodankong > 0) {
			int baodanlistint;
			for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
				qDebug("baodankongcheck [%d]   [%d] [%d]]\n", ui->label_8->text().toInt(), baodankong, baodandes[baodanlistint]);

				if (baodandes[baodanlistint] == '1') {
					CThostFtdcInputOrderActionField deord;
					memset(&deord, 0, sizeof(deord));
					strcpy(deord.BrokerID, "4020");
					strcpy(deord.InvestorID, userid);
					strcpy(deord.InstrumentID, Mdquotaname);
					strcpy(deord.OrderRef, baodanorderref[baodanlistint].c_str());
					deord.FrontID = baodanfrontid[baodanlistint];
					deord.SessionID = baodansessionid[baodanlistint];
					deord.ActionFlag = THOST_FTDC_AF_Delete;
					deord.LimitPrice = 0;
					deord.VolumeChange = 0;
					strcpy(deord.UserID, userid);
					strcpy(deord.ExchangeID, Exchangeid);
					sem_init(&sem3, 0, 0);

					m_tradeApi->ReqOrderAction(&deord, requestId++);
					int valp;
					sem_getvalue(&sem3, &valp);
					qDebug("<sem_trywait  sem3 start............................................%d>\n", valp);
					int xa;
					for (xa = 0; xa < 8; xa++) {
						if (sem_trywait(&sem3) != 0) {
							qDebug("<sem_trywait  sem3 ............................................%d>\n", valp);
							Sleep(50);
							continue;

						}
						else {
							break;
						}


					}
					if (i >= 7) {
						sem_post(&sem3);
						//return 1;
					}

				}
			}

		}
		CThostFtdcInputOrderField ord;
		memset(&ord, 0, sizeof(ord));
		strcpy(ord.BrokerID, "4020");
		strcpy(ord.InvestorID, userid);
		strcpy(ord.InstrumentID, Mdquotaname);
		strcpy(ord.OrderRef, "");//报单引用
		ord.Direction = THOST_FTDC_D_Sell;
		//sem_wait(&sem3);

		if (yeschicanduo != 0 || chicanduo != 0) {//需要平仓
		
			if (ui->radioButton->isChecked()) {//锁仓
				ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//组合开平标志
				ord.VolumeTotalOriginal = ui->spinBox->value();

			}
			else {
				/*while (1) {
					if (baodankong >= ((ui->label_6->text().toInt()) + (ui->label_7->text().toInt()))) {
						continue;
					}
					else {
						break;
					}
				}*/
				if (strcmp("SHFE", Exchangeid) == 0) {
					if (yeschicanduo != 0) {
						ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseYesterday;//组合开平标志
						if (yeschicanduo <= ui->spinBox->value()) {
							ord.VolumeTotalOriginal = yeschicanduo;
						}
						else {
							ord.VolumeTotalOriginal = ui->spinBox->value();
						}
					}
					else {
						ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;//组合开平标志
						if (chicanduo <= ui->spinBox->value()) {
							ord.VolumeTotalOriginal = chicanduo;
						}
						else {
							ord.VolumeTotalOriginal = ui->spinBox->value();
						}
					}
				}
				else {
					ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;//组合开平标志
					if (chicanduo <= ui->spinBox->value()) {
						ord.VolumeTotalOriginal = chicanduo;
					}
					else {
						ord.VolumeTotalOriginal = ui->spinBox->value();
					}
				}
				//ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;//组合开平标志

			}
		}
		else {
			ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//组合开平标志
			ord.VolumeTotalOriginal = ui->spinBox->value();

		}
		//ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//组合开平标志
		ord.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;//组合投机套保标志
		//ord.VolumeTotalOriginal = ui->spinBox->value();
		ord.ContingentCondition = THOST_FTDC_CC_Immediately;///触发条件
		ord.VolumeCondition = THOST_FTDC_VC_AV;//成交量类型
		ord.MinVolume = 1;///最小成交量
		ord.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;//强平原因
		ord.IsAutoSuspend = 0; //自动挂起标志
		ord.UserForceClose = 0;//用户强评标志
		ord.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
		//ord.LimitPrice = (startprice - (10.00 * Indexx.row())); // place a price in double here
		//mdquota* t = new mdquota(model->data(model->index(index.row(), index.column())).toString().toLatin1().data(), PriceTick);

		ord.LimitPrice = (model->data(model->index(Indexx.row(), Indexx.column() - 1))).toDouble();
		ord.TimeCondition = THOST_FTDC_TC_GFD; // 当日有效
		m_tradeApi->ReqOrderInsert(&ord, requestId++);
	}

	if (Indexx.column() == 4) {
		//chaxunchican();

		if (baodankong > 0) {
			qDebug("you dan ke che\n");

			int baodanlistint;
			for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
				if (int(baodanprice[baodanlistint] * 100) == int(((model->data(model->index(Indexx.row(), Indexx.column() - 2))).toDouble()) * 100)) {
					CThostFtdcInputOrderActionField deord;
					memset(&deord, 0, sizeof(deord));
					strcpy(deord.BrokerID, "4020");
					strcpy(deord.InvestorID, userid);
					strcpy(deord.InstrumentID, Mdquotaname);
					strcpy(deord.OrderRef, baodanorderref[baodanlistint].c_str());
					deord.FrontID = baodanfrontid[baodanlistint];
					deord.SessionID = baodansessionid[baodanlistint];
					deord.ActionFlag = THOST_FTDC_AF_Delete;
					deord.LimitPrice = 0;
					deord.VolumeChange = 0;
					strcpy(deord.UserID, userid);
					strcpy(deord.ExchangeID, Exchangeid);
					sem_init(&sem3, 0, 0);

					m_tradeApi->ReqOrderAction(&deord, requestId++);
					int valp;
					sem_getvalue(&sem3, &valp);
					qDebug("<sem_trywait  sem3 start............................................%d>\n", valp);
					int xa;
					for (xa = 0; xa < 8; xa++) {
						if (sem_trywait(&sem3) != 0) {
							qDebug("<sem_trywait  sem3 ............................................%d>\n", valp);
							Sleep(50);
							continue;

						}
						else {
							break;
						}


					}
					if (i >= 7) {
						sem_post(&sem3);
						//return 1;
					}
					qDebug("fasong chedan\n");


				}
			}
		}
		else {
		//	qDebug("\tcheck [%d] ---   [%d]\n", Indexx.row(), Indexx.column());
			qDebug("wu dan ke che [%d]\n", baodankong);

		}
	}
	/*if (index.isvalid()) {
		qstring celltext = index.data().tostring();
	}*/
	//QMessageBox::information(this, "Notice", "You can't close the window",);
	//quotalist* xxx = new quotalist();
	//xxx->show();
	//mdquota* t = new mdquota(model->data(model->index(index.row(), index.column())).toString().toLatin1().data());
	//int a = model->item(index.row(), index.column()).;
	//ui->ddd->setText(QString::number(index.row()));

	//t->setTradeApi(C_TradeApi, C_TradeSpi, C_MdSpi, C_MdApi);
	//char* b[] = { (char*)"sn2205",(char*)"sn2206",(char*)"sn2207",(char*)"sn2208" };

	//int c = c_mdapi->SubscribeMarketData(b, 1);
	//t->show();
	//t->setWindowTitle(model->data(model->index(index.row(), index.column())).toString().toLatin1().data());
	//t->mdqutaqry();
	// t->setTradeApi(C_TradeApi, C_TradeSpi, C_MdSpi, C_MdApi);
	//model->removeRow(index.row());
	//ui->tablelist->setModel(model);

	sem_post(&sem);
}
void mdquota::rightcheck(const QPoint pos) {
	auto Indexx = ui->tableView->indexAt(pos);
	qDebug("\tright check [%d] ---   [%d]\n", Indexx.row(), Indexx.column());
	sem_wait(&sem);
	//qDebug("\tcheck [%d] ---   [%d]\n", Indexx.row(), Indexx.column());
	//chaxunmingxi();
	// 0 1 2 3 4 
	//chaxunmingxi();
	if (Indexx.column() == 0) {
		//chaxunmingxi();

		if (baqodanduo > 0) {
			int baodanlistint;
			for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
				if (int(baodanprice[baodanlistint] * 100) == int(((model->data(model->index(Indexx.row(), Indexx.column() + 2))).toDouble()) * 100)) {
					CThostFtdcInputOrderActionField deord;
					memset(&deord, 0, sizeof(deord));
					strcpy(deord.BrokerID, "4020");
					strcpy(deord.InvestorID, userid);
					strcpy(deord.InstrumentID, Mdquotaname);
					strcpy(deord.OrderRef, baodanorderref[baodanlistint].c_str());
					deord.FrontID = baodanfrontid[baodanlistint];
					deord.SessionID = baodansessionid[baodanlistint];
					deord.ActionFlag = THOST_FTDC_AF_Delete;
					deord.LimitPrice = 0;
					deord.VolumeChange = 0;
					strcpy(deord.UserID, userid);
					strcpy(deord.ExchangeID, Exchangeid);
					sem_init(&sem3, 0, 0);

					m_tradeApi->ReqOrderAction(&deord, requestId++);
					int valp;
					sem_getvalue(&sem3, &valp);
					qDebug("<sem_trywait  sem3 start............................................%d>\n", valp);

					int xa;
					for (xa = 0; xa < 8; xa++) {
						if (sem_trywait(&sem3) != 0) {
							qDebug("<sem_trywait  sem3 ............................................%d>\n", valp);
							Sleep(50);
							continue;

						}
						else {
							break;
						}


					}
					if (i >= 7) {
						sem_post(&sem3);
						//return 1;
					}

				}
			}
		}
		else {
			//qDebug("\tcheck [%d] ---   [%d]\n", Indexx.row(), Indexx.column());

		}
	}
	if (Indexx.column() == 1)
	{//买入
		//if (ui->checkBox_3->isChecked()) {//  需要撤单
			//ui->label_8->text().toInt()
		//chaxunmingxi();
		CThostFtdcInputOrderField ord;
		memset(&ord, 0, sizeof(ord));
		strcpy(ord.BrokerID, "4020");
		strcpy(ord.InvestorID, userid);
		strcpy(ord.InstrumentID, Mdquotaname);
		strcpy(ord.OrderRef, "");//报单引用
		ord.Direction = THOST_FTDC_D_Buy;
		if (ui->checkBox_3->isChecked() && baqodanduo > 0) {
			int baodanlistint;
			for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
				if (baodandes[baodanlistint] == '0') {
					qDebug("abel_8label_8label_8label_8label_8label_8label_8label_8 [%d]   [%d] [%d]]\n", ui->label_8->text().toInt(), baqodanduo, baodandes[baodanlistint]);

					CThostFtdcInputOrderActionField deord;
					memset(&deord, 0, sizeof(deord));
					strcpy(deord.BrokerID, "4020");
					strcpy(deord.InvestorID, userid);
					strcpy(deord.InstrumentID, Mdquotaname);
					strcpy(deord.OrderRef, baodanorderref[baodanlistint].c_str());
					deord.FrontID = baodanfrontid[baodanlistint];
					deord.SessionID = baodansessionid[baodanlistint];
					deord.ActionFlag = THOST_FTDC_AF_Delete;
					deord.LimitPrice = 0;
					deord.VolumeChange = 0;
					strcpy(deord.UserID, userid);
					strcpy(deord.ExchangeID, Exchangeid);
					sem_init(&sem3, 0, 0);

					m_tradeApi->ReqOrderAction(&deord, requestId++);
					int valp;
					sem_getvalue(&sem3, &valp);
					qDebug("<sem_trywait  sem3 start............................................%d>\n", valp);

					int xa;
					for (xa = 0; xa < 8; xa++) {
						if (sem_trywait(&sem3) != 0) {
							qDebug("<sem_trywait  sem3 ............................................%d>\n", valp);
							Sleep(50);
							continue;

						}
						else {
							break;
						}


					}
					if (i >= 7) {
						sem_post(&sem3);
						//return 1;
					}

				}
			}

		}

		if (yeschicankong != 0 || chicankong != 0) {//需要平仓
			if (ui->radioButton->isChecked()) {//锁仓
				ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//组合开平标志
				ord.VolumeTotalOriginal = ui->spinBox_2->value();

			}
			else {
				/*while (1) {
					if (baqodanduo >= ((ui->label_5->text().toInt()) + (ui->label_8->text().toInt()))) {
						continue;
					}
					else {
						break;
					}
				}*/
				if (strcmp("SHFE", Exchangeid) == 0) {
					if (yeschicankong != 0) {
						ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseYesterday;//组合开平标志
						if (yeschicankong <= ui->spinBox_2->value()) {
							ord.VolumeTotalOriginal = yeschicankong;
						}
						else {
							ord.VolumeTotalOriginal = ui->spinBox_2->value();
						}
					}
					else {
						ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;//组合开平标志
						if (chicankong <= ui->spinBox_2->value()) {
							ord.VolumeTotalOriginal = chicankong;
						}
						else {
							ord.VolumeTotalOriginal = ui->spinBox_2->value();
						}
					}
				}
				else {
					ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;//组合开平标志
					if (chicankong <= ui->spinBox_2->value()) {
						ord.VolumeTotalOriginal = chicankong;
					}
					else {
						ord.VolumeTotalOriginal = ui->spinBox_2->value();
					}
				}
				//ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;//组合开平标志

			}
		}
		else {
			ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//组合开平标志
			ord.VolumeTotalOriginal = ui->spinBox_2->value();

		}
		//}

	//	ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//组合开平标志
		ord.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;//组合投机套保标志
		//ord.VolumeTotalOriginal = ui->spinBox_2->value();
		ord.ContingentCondition = THOST_FTDC_CC_Immediately;///触发条件
		ord.VolumeCondition = THOST_FTDC_VC_AV;//成交量类型
		ord.MinVolume = 1;///最小成交量
		ord.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;//强平原因
		ord.IsAutoSuspend = 0; //自动挂起标志
		ord.UserForceClose = 0;//用户强评标志
		ord.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
		//ord.LimitPrice = (startprice - (10.00 * Indexx.row())); // place a price in double here
		//mdquota* t = new mdquota(model->data(model->index(index.row(), index.column())).toString().toLatin1().data(), PriceTick);

		ord.LimitPrice = (model->data(model->index(Indexx.row(), Indexx.column() + 1))).toDouble();
		ord.TimeCondition = THOST_FTDC_TC_GFD; // 当日有效
		m_tradeApi->ReqOrderInsert(&ord, requestId++);

		//	model->data(Indexx).toString().toInt
	}
	if (Indexx.column() == 2) {
		//撤单
		chaxunmingxi();
		//chaxunchican();
		//chaxunbaodan();

	}
	if (Indexx.column() == 3) {
		//卖出
		if (ui->checkBox_3->isChecked() && baodankong > 0) {
			int baodanlistint;
			for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
				qDebug("baodankongcheck [%d]   [%d] [%d]]\n", ui->label_8->text().toInt(), baodankong, baodandes[baodanlistint]);

				if (baodandes[baodanlistint] == '1') {
					CThostFtdcInputOrderActionField deord;
					memset(&deord, 0, sizeof(deord));
					strcpy(deord.BrokerID, "4020");
					strcpy(deord.InvestorID, userid);
					strcpy(deord.InstrumentID, Mdquotaname);
					strcpy(deord.OrderRef, baodanorderref[baodanlistint].c_str());
					deord.FrontID = baodanfrontid[baodanlistint];
					deord.SessionID = baodansessionid[baodanlistint];
					deord.ActionFlag = THOST_FTDC_AF_Delete;
					deord.LimitPrice = 0;
					deord.VolumeChange = 0;
					strcpy(deord.UserID, userid);
					strcpy(deord.ExchangeID, Exchangeid);
					sem_init(&sem3, 0, 0);

					m_tradeApi->ReqOrderAction(&deord, requestId++);
					int valp;
					sem_getvalue(&sem3, &valp);
					qDebug("<sem_trywait  sem3 start............................................%d>\n", valp);

					int xa;
					for (xa = 0; xa < 8; xa++) {
						if (sem_trywait(&sem3) != 0) {
							qDebug("<sem_trywait  sem3 ............................................%d>\n", valp);
							Sleep(50);
							continue;

						}
						else {
							break;
						}


					}
					if (i >= 7) {
						sem_post(&sem3);
						//return 1;
					}

				}
			}

		}
		CThostFtdcInputOrderField ord;
		memset(&ord, 0, sizeof(ord));
		strcpy(ord.BrokerID, "4020");
		strcpy(ord.InvestorID, userid);
		strcpy(ord.InstrumentID, Mdquotaname);
		strcpy(ord.OrderRef, "");//报单引用
		ord.Direction = THOST_FTDC_D_Sell;
		if (chicanduo != 0 || yeschicanduo != 0) {//需要平仓

			if (ui->radioButton->isChecked()) {//锁仓
				ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//组合开平标志
				ord.VolumeTotalOriginal = ui->spinBox_2->value();

			}
			else {
				/*while (1) {
					if (baodankong >= ((ui->label_6->text().toInt()) + (ui->label_7->text().toInt()))) {
						continue;
					}
					else {
						break;
					}
				}*/
				if (strcmp("SHFE", Exchangeid) == 0) {
					if (yeschicanduo != 0) {
						ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseYesterday;//组合开平标志
						if (yeschicanduo <= ui->spinBox_2->value()) {
							ord.VolumeTotalOriginal = yeschicanduo;
						}
						else {
							ord.VolumeTotalOriginal = ui->spinBox_2->value();
						}

					}
					else {
						ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;//组合开平标志
						if (chicanduo <= ui->spinBox_2->value()) {
							ord.VolumeTotalOriginal = chicanduo;
						}
						else {
							ord.VolumeTotalOriginal = ui->spinBox_2->value();
						}
					}
				}
				else {
					ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;//组合开平标志
					if (chicanduo <= ui->spinBox_2->value()) {
						ord.VolumeTotalOriginal = chicanduo;
					}
					else {
						ord.VolumeTotalOriginal = ui->spinBox_2->value();
					}
				}
				//ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;//组合开平标志

			}
		}
		else {
			ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//组合开平标志
			ord.VolumeTotalOriginal = ui->spinBox_2->value();
		}
		//ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//组合开平标志
		ord.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;//组合投机套保标志
		ord.ContingentCondition = THOST_FTDC_CC_Immediately;///触发条件
		ord.VolumeCondition = THOST_FTDC_VC_AV;//成交量类型
		ord.MinVolume = 1;///最小成交量
		ord.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;//强平原因
		ord.IsAutoSuspend = 0; //自动挂起标志
		ord.UserForceClose = 0;//用户强评标志
		ord.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
		//ord.LimitPrice = (startprice - (10.00 * Indexx.row())); // place a price in double here
		//mdquota* t = new mdquota(model->data(model->index(index.row(), index.column())).toString().toLatin1().data(), PriceTick);

		ord.LimitPrice = (model->data(model->index(Indexx.row(), Indexx.column() - 1))).toDouble();
		ord.TimeCondition = THOST_FTDC_TC_GFD; // 当日有效
		m_tradeApi->ReqOrderInsert(&ord, requestId++);
	}

	if (Indexx.column() == 4) {
		//chaxunchican();
		if (baodankong > 0) {
			int baodanlistint;
			for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
				if (int(baodanprice[baodanlistint] * 100) == int(((model->data(model->index(Indexx.row(), Indexx.column() - 2))).toDouble()) * 100)) {
					CThostFtdcInputOrderActionField deord;
					memset(&deord, 0, sizeof(deord));
					strcpy(deord.BrokerID, "4020");
					strcpy(deord.InvestorID, userid);
					strcpy(deord.InstrumentID, Mdquotaname);
					strcpy(deord.OrderRef, baodanorderref[baodanlistint].c_str());
					deord.FrontID = baodanfrontid[baodanlistint];
					deord.SessionID = baodansessionid[baodanlistint];
					deord.ActionFlag = THOST_FTDC_AF_Delete;
					deord.LimitPrice = 0;
					deord.VolumeChange = 0;
					strcpy(deord.UserID, userid);
					strcpy(deord.ExchangeID, Exchangeid);
					sem_init(&sem3, 0, 0);

					m_tradeApi->ReqOrderAction(&deord, requestId++);
					int valp;
					sem_getvalue(&sem3, &valp);
					qDebug("<sem_trywait  sem3 start............................................%d>\n", valp);

					int xa;
					for (xa = 0; xa < 8; xa++) {
						if (sem_trywait(&sem3) != 0) {
							qDebug("<sem_trywait  sem3 ............................................%d>\n", valp);
							Sleep(50);
							continue;

						}
						else {
							break;
						}


					}
					if (i >= 7) {
						sem_post(&sem3);
						//return 1;
					}

				}
			}
		}
		else {
			//qDebug("\tcheck [%d] ---   [%d]\n", Indexx.row(), Indexx.column());

		}
	}
	

	sem_post(&sem);
}
//void mdquota::wheelEvent(QWheelEvent* event) {
//	//qDebug("wheelEventwheelEventwheelEventwheelEventwheelEventwheelEventwheelEventwheelEventwheelEventwheelEventwheelEventwheelEventwheelEventwheelEvent");
//	//if (event->buttons() == Qt::MiddleButton ) {
//	if ((event->buttons() & Qt::MiddleButton) != 0)
//	{ 
//		qDebug("righewheeleventrighewheeleventrighewheeleventrighewheeleventrighewheeleventrighewheeleventrighewheeleventrighewheeleventrighewheeleventrighewheeleventrighewheeleventrighewheeleventrighewheeleventrighewheelevent");
////
//	}
//
//}
//void mdquota::mousePressEvent(QMouseEvent* event) {
//	{
//		if (event->button() == Qt::MouseButton::LeftButton)
//			qDebug() << "鼠标左键按下" << ":" << event->pos();
//		if (event->button() == Qt::MouseButton::RightButton)
//			qDebug() << "鼠标右键按下" << ":" << event->pos();
//		if (event->button() == Qt::MouseButton::MiddleButton) {
//			qDebug() << "shubiao shubiaoshubiaoshubiaoshubiao mousePressEvent";
//
//			qDebug() << "鼠标滚轮按下" << ":" << event->pos();
//			if (rowask != 0 && rowbid!=0) {
//							ui->tableView->scrollTo(ui->tableView->model()->index(int((rowbid + rowask) / 2), 0), QAbstractItemView::PositionAtCenter);
//						}
//		}
//
//	}
//
//}
void mdquota::keyPressEvent(QKeyEvent* event) {
	//QWidget* ww = keyboardGrabber(); // 返回正在捕获键盘输入的部件，若没有则返回 0

	if (event->key() == Qt::Key_Space) {
		//qDebug() << "jianpan kongge shijian";

		int baodanlistint;
		for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
			if (baodandes[baodanlistint] == '0') {
				qDebug("abel_8label_8label_8label_8label_8label_8label_8label_8 [%d]   [%d] [%d]]\n", ui->label_8->text().toInt(), baqodanduo, baodandes[baodanlistint]);

				CThostFtdcInputOrderActionField deord;
				memset(&deord, 0, sizeof(deord));
				strcpy(deord.BrokerID, "4020");
				strcpy(deord.InvestorID, userid);
				strcpy(deord.InstrumentID, Mdquotaname);
				strcpy(deord.OrderRef, baodanorderref[baodanlistint].c_str());
				deord.FrontID = baodanfrontid[baodanlistint];
				deord.SessionID = baodansessionid[baodanlistint];
				deord.ActionFlag = THOST_FTDC_AF_Delete;
				deord.LimitPrice = 0;
				deord.VolumeChange = 0;
				strcpy(deord.UserID, userid);
				strcpy(deord.ExchangeID, Exchangeid);
				m_tradeApi->ReqOrderAction(&deord, requestId++);


			}
		}
		for (baodanlistint = 0; baodanlistint < 20; baodanlistint++) {
			qDebug("baodankongcheck [%d]   [%d] [%d]]\n", ui->label_8->text().toInt(), baodankong, baodandes[baodanlistint]);

			if (baodandes[baodanlistint] == '1') {
				CThostFtdcInputOrderActionField deord;
				memset(&deord, 0, sizeof(deord));
				strcpy(deord.BrokerID, "4020");
				strcpy(deord.InvestorID, userid);
				strcpy(deord.InstrumentID, Mdquotaname);
				strcpy(deord.OrderRef, baodanorderref[baodanlistint].c_str());
				deord.FrontID = baodanfrontid[baodanlistint];
				deord.SessionID = baodansessionid[baodanlistint];
				deord.ActionFlag = THOST_FTDC_AF_Delete;
				deord.LimitPrice = 0;
				deord.VolumeChange = 0;
				strcpy(deord.UserID, userid);
				strcpy(deord.ExchangeID, Exchangeid);
				m_tradeApi->ReqOrderAction(&deord, requestId++);


			}
		}
	}
	else {
		//qDebug() << "jianpan qita shijian" ;

	}
	//this->releaseKeyboard();   // 释放捕获的键盘输入

}
void mdquota::slotdlgReturn(int a) {
	if (rowask != 0 && rowbid != 0) {
		 //qDebug() << "shubiao shubiaoshubiaoshubiaoshubiao slotdlgReturn";

		ui->tableView->scrollTo(ui->tableView->model()->index(int((rowbid + rowask) / 2), 0), QAbstractItemView::PositionAtCenter);
	}
}
void mdquota::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField* pInstrumentStatus) {
	if (strcmp(pInstrumentStatus->InstrumentID, Mdquotaname) == 0) {
		qutastatus = pInstrumentStatus->InstrumentStatus;
	
	}
}
