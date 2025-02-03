#include "mdapi.h"

//#include "stdafx.h"
#include <stdio.h>
#include <QDebug>
//#include "define.h"


CThostFtdcMdApi* CMdApi::CreateFtdcMdApi(const char* pszFlowPath  ,const bool bIsUsingUdp,  const bool bIsMulticast) {
    return mdm_pApi = CThostFtdcMdApi::CreateFtdcMdApi(pszFlowPath, bIsUsingUdp, bIsMulticast);
    return 0;
}

const char* CMdApi::GetApiVersion()
{
    return mdm_pApi->GetApiVersion();
    return 0;
}


void CMdApi::Release()
{

    mdm_pApi->Release();
};

void CMdApi::Init()
{
  
    mdm_pApi->Init();
};

int CMdApi::Join()
{
  

    return mdm_pApi->Join();
};

const char* CMdApi::GetTradingDay()
{
 

    return mdm_pApi->GetTradingDay();
};
void CMdApi::RegisterFront(char* pszFrontAddress)
{
  
    mdm_pApi->RegisterFront(pszFrontAddress);
}

void CMdApi::RegisterNameServer(char* pszNsAddress)
{
 

    mdm_pApi->RegisterNameServer(pszNsAddress);
}

void CMdApi::RegisterFensUserInfo(CThostFtdcFensUserInfoField* pFensUserInfo)
{
https://news.jxcn.cn/p/20211219/33644892.html?from=jx60

    mdm_pApi->RegisterFensUserInfo(pFensUserInfo);
};

void CMdApi::RegisterSpi(CThostFtdcMdSpi* pSpi)
{
    mdm_pApi->RegisterSpi(pSpi);
};
int CMdApi::SubscribeMarketData(char* ppInstrumentID[], int nCount) {

    return mdm_pApi->SubscribeMarketData(ppInstrumentID, nCount);

};

int CMdApi::UnSubscribeMarketData(char* ppInstrumentID[], int nCount) {
    return mdm_pApi->UnSubscribeMarketData(ppInstrumentID, nCount);
};

///订阅询价。
///@param ppInstrumentID 合约ID  
///@param nCount 要订阅/退订行情的合约个数
///@remark 
int CMdApi::SubscribeForQuoteRsp(char* ppInstrumentID[], int nCount) {
    return mdm_pApi->SubscribeForQuoteRsp(ppInstrumentID, nCount);
};

///退订询价。
///@param ppInstrumentID 合约ID  
///@param nCount 要订阅/退订行情的合约个数
///@remark 
int CMdApi::UnSubscribeForQuoteRsp(char* ppInstrumentID[], int nCount) {
    return  mdm_pApi->UnSubscribeForQuoteRsp(ppInstrumentID, nCount);
};

///用户登录请求
int CMdApi::ReqUserLogin(CThostFtdcReqUserLoginField* pReqUserLoginField, int nRequestID) {
    return mdm_pApi->ReqUserLogin(pReqUserLoginField, nRequestID);
};


///登出请求
int CMdApi::ReqUserLogout(CThostFtdcUserLogoutField* pUserLogout, int nRequestID) {
    return mdm_pApi->ReqUserLogout(pUserLogout, nRequestID);
};

///请求查询组播合约
int CMdApi::ReqQryMulticastInstrument(CThostFtdcQryMulticastInstrumentField* pQryMulticastInstrument, int nRequestID) {

    return  mdm_pApi->ReqQryMulticastInstrument(pQryMulticastInstrument, nRequestID);
};
