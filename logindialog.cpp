//#include "logindialog.h"
//
//LoginDialog::LoginDialog(QWidget *parent)
//    : QDialog(parent)
//{
//    ui.setupUi(this);
//}


#include "logindialog.h"
#include "ui_logindialog.h"
#include "traderspi.h"
#include <QtDebug>
#include <QMessageBox>
#include <QLabel>

//using std::LoginDialog;
extern int requestId;
extern int frontid;
extern int sessionid;
extern char userid[16];
LoginDialog::LoginDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::LoginDialogClass)
{
    sem_init(&sem, 0, 1);
    sem_init(&sem1, 0, 1);

    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    m_TradeSpi->UnReisterSpi(this);
    m_cmspi->UnReisterSpi(this);

    delete ui;
}
void LoginDialog::setTradeApi(CTraderApi* TradeApi, CTraderSpi* ATradeSpi, CMdApi* Mcmapi, CMdSpi* Mcmspi) {
    m_tradeApi = TradeApi;
    m_TradeSpi = ATradeSpi;
    m_cmapi = Mcmapi;
    m_cmspi = Mcmspi;
    m_TradeSpi->RegisterSpi(this);
    m_cmspi->RegisterSpi(this);

}

//void LoginDialog::setTradeApi(CTraderApi* TradeApi, CTraderSpi* ATradeSpi) {
//    m_tradeApi = TradeApi;
//    m_TradeSpi = ATradeSpi;
//    m_TradeSpi->RegisterSpi(this);
//}

void LoginDialog::OnFrontConnected() {
    ui->lbl_status->setText(ui->lbl_status->text() + "\n"+"connect sucess");

   // ui->lbl_status->repaint();
    Userauth();
  //  Authenticate();
}
void LoginDialog::OnFrontDisconnected(int nReason) {
    ui->lbl_status->setText(ui->lbl_status->text() + "\n" + "connect error");
  //  ui->lbl_status->repaint();


}
void LoginDialog::OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
    if (pRspAuthenticateField) {
        if (pRspInfo->ErrorID == 0) {
            qDebug("<OnRspAuthenticate sucess111111111111111111111111111111111111\n");
            UserLogin();

        }
        else {
            qDebug("<OnRspAuthenticate faild\n");

        }

    }
}
void LoginDialog::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField* pUserPasswordUpdate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {

    if (pUserPasswordUpdate) {
        if (pRspInfo->ErrorID == 0) {
            qDebug("<pUserPasswordUpdate sucess111111111111111111111111111111111111\n");
           // UserLogin();

        }
        else {
            qDebug("<pUserPasswordUpdate faild\n");

        }

    }
}

//void LoginDialog::OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
//    if (pRspAuthenticateField) {
//        if (pRspInfo->ErrorID == 0) {
//
//            ui->lbl_status->setText("认证:" + QString::fromLocal8Bit(pRspInfo->ErrorMsg));
//            UserLogin();
//        }
//        else {
//
//            ui->lbl_status->setText("认证:" + QString::fromLocal8Bit(pRspInfo->ErrorMsg));
//        }
//
//    }
//}

void LoginDialog::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
    if (pRspUserLogin && pRspInfo) {
        if (pRspInfo->ErrorID == 0) {
            //this->accept();
            strcpy(tradeday, pRspUserLogin->TradingDay);
            qDebug("tradedaytradedaytradedaytradeday  tradeday tradeday [%s]  ---   \n", tradeday);
            qDebug("SysVersionSysVersionSysVersionSysVersionSysVersionSysVersionSysVersion [%s]\n",pRspUserLogin->SysVersion);
          // ui->lbl_status->setText("登陆:" + QString::fromLocal8Bit(pRspInfo->ErrorMsg));
            ui->lbl_status->setText(ui->lbl_status->text()+ "\n" + "login sucess");
           // ui->lbl_status->repaint();
            frontid = pRspUserLogin->FrontID;
            sessionid = pRspUserLogin->SessionID;
        }
        else {
            //ui->lbl_status->setText("登陆:" + QString::fromLocal8Bit(pRspInfo->ErrorMsg));
            ui->lbl_status->setText(ui->lbl_status->text() + "\n" + "login failed");
           // ui->lbl_status->repaint();
            qDebug("login faild errorid : [%d]\n", pRspInfo->ErrorID);


        }
    }
}
int LoginDialog::Userauth() {
    if (sem_trywait(&sem1) != 0) {
        return 0;
    }
    else {
        ui->lbl_status->setText(ui->lbl_status->text() + "\n" + "login1111");
        // ui->lbl_status->repaint();

         //Sleep(3000);
         //	virtual int ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID) = 0;
        QString sUserid = ui->edt_user->text();
        QString sPassWord = ui->edt_password->text();
        CThostFtdcReqAuthenticateField ReqAuthentLogin;
        memset(&ReqAuthentLogin, 0, sizeof(ReqAuthentLogin));
        strcpy_s(ReqAuthentLogin.BrokerID, "4020");
        ///strcpy_s(ReqAuthentLogin.UserID, "00096");
         strcpy_s(ReqAuthentLogin.UserID, sUserid.toStdString().c_str());

        strcpy_s(ReqAuthentLogin.AuthCode, "L6HTO9EXQ83ASX36");
        strcpy_s(ReqAuthentLogin.AppID, "client_family_1.1");
        //strcpy_s(ReqAuthentLogin.UserProductInfo, "family");



        return  m_tradeApi->ReqAuthenticate(&ReqAuthentLogin, requestId++);
        sem_post(&sem1);

    }
}

void LoginDialog::LoginMessage() {
    // QApplication::setQuitOnLastWindowClosed(false);
    QMessageBox::StandardButton reply;
    QLabel* informationLabel;
    
    reply = QMessageBox::information(this, tr("Error Message"),"Info");
    /*if (reply == QMessageBox::Ok)
        informationLabel->setText(tr("OK"));
    else
        informationLabel->setText(tr("Escape"));*/
}

int LoginDialog::UserLogin() {
    if (sem_trywait(&sem) != 0) {
        return 0;
    }
    else {
        // qDebug() << "用户登陆" << endl;
        ui->lbl_status->setText(ui->lbl_status->text() + "\n" + "login1111");
        // ui->lbl_status->repaint();

         //Sleep(3000);
         //	virtual int ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID) = 0;
        QString sUserid = ui->edt_user->text();
        QString sPassWord = ui->edt_password->text();
        qDebug() << "用户登陆1";

        //Sleep(20000);
        qDebug() << "用户登陆2";

        CThostFtdcReqUserLoginField reqUserLogin;
        memset(&reqUserLogin, 0, sizeof(reqUserLogin));



        strcpy_s(reqUserLogin.BrokerID, "4020");
       // strcpy_s(reqUserLogin.UserID, "00096");
         strcpy_s(reqUserLogin.UserID, sUserid.toStdString().c_str());

        //strcpy_s(reqUserLogin.Password, "Lq890919");
         strcpy_s(reqUserLogin.Password, sPassWord.toStdString().c_str());
       // strcpy_s(reqUserLogin.UserProductInfo, "client_family_1.1");

        
        m_cmapi->ReqUserLogin(&reqUserLogin, requestId++);
        Sleep(100);
       return m_tradeApi->ReqUserLogin(&reqUserLogin, requestId++);
        //virtual int ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField * pUserPasswordUpdate, int nRequestID) = 0;
        /*CThostFtdcUserPasswordUpdateField aaa;
        memset(&aaa, 0, sizeof(aaa));
        strcpy_s(aaa.BrokerID, "4020");

        strcpy_s(aaa.UserID, "00096");

        strcpy_s(aaa.OldPassword, "testdce");
        strcpy_s(aaa.NewPassword, "Lq890919");
        m_tradeApi->ReqUserPasswordUpdate(&aaa, requestId++);
        Sleep(20000);*/
       
        
        sem_post(&sem);
        return 0;

    }
}
//
//int LoginDialog::Authenticate() {
//    CThostFtdcReqAuthenticateField field;
//    memset(&field, 0, sizeof(field));
//    QString sUserid = ui->edt_user->text();
//    QString sPassWord = ui->edt_password->text();
//  //  strcpy_s(field.BrokerID, CTP_BrokerID);
//    strcpy_s(field.UserID, sUserid.toStdString().c_str());
//  //  strcpy_s(field.AppID, CTP_APPID);
//  //  strcpy_s(field.AuthCode, CTP_AUTHCODE);
//    return m_tradeApi->ReqAuthenticate(&field, 2);
//}

void LoginDialog::on_but_login_clicked()
{
   // ui
    //this->setResult(QDialog::Accepted);
   // ui->lbl_status->setText(ui->lbl_status->text() + "\n" + "clicked\n");
    Sleep(200);
    strcpy_s(userid, ui->edt_user->text().toStdString().c_str());

    ui->lbl_status->setText(ui->lbl_status->text() + "\n" + "on_but_login_clicked\n");
 //   ui->lbl_status->repaint();

   // qDebug() << m_tradeApi;
    //qDebug() << m_tradeApi->GetApiVersion();
    if (m_TradeSpi->Status == LSDisconnected) {
        ui->lbl_status->setText(ui->lbl_status->text() + "\n" +"LSDisconnected");
       // ui->lbl_status->repaint();

     //  m_tradeApi->RegisterFront(const_cast<char*>("tcp://180.168.146.187:10130"));
      // m_cmapi->RegisterFront(const_cast<char*>("tcp://180.168.146.187:10131"));
        if (strcmp(ui->comboBox->currentText().toStdString().c_str(), "1")==0) {
            qDebug("<218.202.237.33218.202.237.33218.202.237.33218.202.237.33218.202.237.33218.202.237.33218.202.237.33218.202.237.33218.202.237.33............................................>\n");

            m_cmapi->RegisterFront(const_cast<char*>("tcp://180.166.12.248:42213"));
            m_tradeApi->RegisterFront(const_cast<char*>("tcp://180.166.12.248:42205"));

        
        }
        if (strcmp(ui->comboBox->currentText().toStdString().c_str(), "2") == 0) {
            qDebug("<180.168.146.187180.168.146.187180.168.146.187180.168.146.187180.168.146.187180.168.146.187............................................>\n");

            m_tradeApi->RegisterFront(const_cast<char*>("tcp://101.230.185.213:43205"));
            m_cmapi->RegisterFront(const_cast<char*>("tcp://101.230.185.213:43213"));


        }
        if (strcmp(ui->comboBox->currentText().toStdString().c_str(), "3") == 0) {
           // qDebug("<180.168.146.187180.168.146.187180.168.146.187180.168.146.187180.168.146.187180.168.146.187............................................>\n");

            m_tradeApi->RegisterFront(const_cast<char*>("tcp://127.0.0.1:41205"));
            m_cmapi->RegisterFront(const_cast<char*>("tcp://127.0.0.1:41213"));


        }
     // m_cmapi->RegisterFront(const_cast<char*>("tcp://218.202.237.33:10213"));

       // m_tradeApi->RegisterFront(const_cast<char*>("tcp://180.168.146.187:10201"));

      //  m_tradeApi->RegisterFront(const_cast<char*>("tcp://218.202.237.33:10203"));
       // m_tradeApi->RegisterFront(const_cast<char*>("tcp://180.168.146.187:10202"));


        m_tradeApi->Init();
        m_cmapi->Init();
       // Sleep(1000);
    }
    else {
        Userauth();
    }

    Sleep(1000);


    //
    if (m_TradeSpi->Status == LSLogin_successful) {
        this->accept();

    }
    else if ((m_TradeSpi->Status == LSDisconnected) || (m_TradeSpi->Status == LSAuthenticate_failed) || (m_TradeSpi->Status == LSLogin_failed)) {
        this->LoginMessage();
      //  this->accept();

    }





  

}
//void LoginDialog::on_but_cancle_clicked() {
  //  ui->lbl_status->setText(ui->lbl_status->text() + "\n" + "on_but_cancle_clicked");
   // ui->lbl_status->repaint();


    //this->reject();

//}
