#include "mdspi.h"
#include <stdio.h>
#include <QDebug>
void CMdSpi::OnFrontConnected()
{
    Status = MLSConnected;
    foreach(CThostFtdcMdSpi * mdSpi, m_SpiList)
    {
        qDebug("</CMdSpiOnFrontConnected>\n");

        mdSpi->OnFrontConnected();

    }
   // qDebug("</OnFrontConnected>\n");
};
void  CMdSpi::RegisterSpi(CThostFtdcMdSpi* pSpi) {
    qDebug("</CMdSpiRegisterSpi>\n");

    m_SpiList.append(pSpi);

};
void  CMdSpi::UnReisterSpi(CThostFtdcMdSpi* pSpi) {
    qDebug("</CMdSpiUnReisterSpi>\n");

    for (int i = 0; i < m_SpiList.size(); i++) {
        CThostFtdcMdSpi* mdSpi = m_SpiList.at(i);
        if (mdSpi == pSpi) {
            m_SpiList.removeAt(i);
            break;
        }
    }
};
void CMdSpi::OnFrontDisconnected(int nReason) {
    Status = MLSDisconnected;
    foreach(CThostFtdcMdSpi * mdSpi, m_SpiList)
    {
        mdSpi->OnFrontDisconnected(nReason);
    }
    qDebug("</CMdSpiOnFrontDisconnected>\n");

};

///心跳超时警告。当长时间未收到报文时，该方法被调用。
///@param nTimeLapse 距离上次接收报文的时间
void CMdSpi::OnHeartBeatWarning(int nTimeLapse) {

    foreach(CThostFtdcMdSpi * mdSpi, m_SpiList)
    {
        mdSpi->OnHeartBeatWarning(nTimeLapse);
    }
};


///登录请求响应
 void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
     qDebug("<CMdSpi OnRspUserLogin>\n");
     foreach(CThostFtdcMdSpi * mdSpi, m_SpiList)
     {
         mdSpi->OnRspUserLogin(pRspUserLogin, pRspInfo, nRequestID, bIsLast);
     }
     if (pRspUserLogin)
     {
 
     }
     if (pRspInfo)
     {
         if (pRspInfo->ErrorID == 0) {
             Status = MLSLogin_successful;
             qDebug("<OnRspUserLoginMLSLogin_successful>\n");

         }
         else
         {
             qDebug("<OnRspUserLoginMLSLogin_failed>\n");

             Status = MLSLogin_failed;
         }
    
     }
   
 };

///登出请求响应
 void CMdSpi::OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
     foreach(CThostFtdcMdSpi * mdSpi, m_SpiList)
     {
         mdSpi->OnRspUserLogout(pUserLogout, pRspInfo, nRequestID, bIsLast);
     } 
 };

///请求查询组播合约响应
 void CMdSpi::OnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField* pMulticastInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
     foreach(CThostFtdcMdSpi * mdSpi, m_SpiList)
     {
         mdSpi->OnRspQryMulticastInstrument(pMulticastInstrument, pRspInfo, nRequestID, bIsLast);
     }
 };

///错误应答
 void CMdSpi::OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
     foreach(CThostFtdcMdSpi * mdSpi, m_SpiList)
     {
         mdSpi->OnRspError(pRspInfo, nRequestID, bIsLast);
         qDebug("<CMdSpiOnRspError>\n");

     }
 };

///订阅行情应答
 void CMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
    // qDebug("<CMdSpiOnRspSubMarketData>\n");

     foreach(CThostFtdcMdSpi * mdSpi, m_SpiList)
     {
         mdSpi->OnRspSubMarketData(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
     }
   //  qDebug("<CMdSpiOnRspSubMarketData>\n");

 };

///取消订阅行情应答
 void CMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
     foreach(CThostFtdcMdSpi * mdSpi, m_SpiList)
     {
         mdSpi->OnRspUnSubMarketData(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
     }
 };

///订阅询价应答
 void CMdSpi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
     foreach(CThostFtdcMdSpi * mdSpi, m_SpiList)
     {
         mdSpi->OnRspSubForQuoteRsp(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
     }
 };

///取消订阅询价应答
 void CMdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
     foreach(CThostFtdcMdSpi * mdSpi, m_SpiList)
     {
         mdSpi->OnRspUnSubForQuoteRsp(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
     }
 };

///深度行情通知
 void CMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData) {
   //  qDebug("<CMdSpiOnRtnDepthMarketData>\n");

     foreach(CThostFtdcMdSpi * mdSpi, m_SpiList)
     {
         mdSpi->OnRtnDepthMarketData(pDepthMarketData);
     }

 };

///询价通知
 void CMdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField* pForQuoteRsp) {
     foreach(CThostFtdcMdSpi * mdSpi, m_SpiList)
     {
         mdSpi->OnRtnForQuoteRsp(pForQuoteRsp);
     }
 };