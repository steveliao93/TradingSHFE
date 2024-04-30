/////////////////////////////////////////////////////////////////////////
///@system ?????????????
///@company ???????????????????
///@file ThostFtdcMdApi.h
///@brief ????????????
///@history 
///20060106	????		?????????
/////////////////////////////////////////////////////////////////////////

#if !defined(THOST_FTDCMDAPI_H)
#define THOST_FTDCMDAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ThostFtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_MD_API_EXPORT
#define MD_API_EXPORT __declspec(dllexport)
#else
#define MD_API_EXPORT __declspec(dllimport)
#endif
#else
#define MD_API_EXPORT 
#endif

class CThostFtdcMdSpi
{
public:
	///???????????????????????????????��?????????��????????��?
	virtual void OnFrontConnected(){};
	
	///??????????????????????????��????????��???????????????API????????????????????????????
	///@param nReason ???????
	///        0x1001 ????????
	///        0x1002 ????��???
	///        0x2001 ???????????
	///        0x2002 ???????????
	///        0x2003 ?????????
	virtual void OnFrontDisconnected(int nReason){};
		
	///??????????��???????��???????????��????????��?
	///@param nTimeLapse ??????��??????????
	virtual void OnHeartBeatWarning(int nTimeLapse){};
	

	///??????????
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///??????????
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///???????��??????
	virtual void OnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField *pMulticastInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///???????
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///???????????
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///??????????????
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///??????????
	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///?????????????
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///?????????
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {};

	///?????
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {};
};

class MD_API_EXPORT CThostFtdcMdApi
{
public:
	///????MdApi
	///@param pszFlowPath ?????????????????????????????
	///@return ????????UserApi
	///modify for udp marketdata
	static CThostFtdcMdApi *CreateFtdcMdApi(const char *pszFlowPath = "", const bool bIsUsingUdp=false, const bool bIsMulticast=false);
	
	///???API??��???
	///@retrun ???????��??
	static const char *GetApiVersion();
	
	///???????????
	///@remark ???????????????,????��????????????
	virtual void Release() = 0;
	
	///?????
	///@remark ????????��???,??��??��?,??????????
	virtual void Init() = 0;
	
	///????????????????
	///@return ??????????
	virtual int Join() = 0;
	
	///????????????
	///@retrun ????????????
	///@remark ??��???????,????????????????
	virtual const char *GetTradingDay() = 0;
	
	///?????????????
	///@param pszFrontAddress??????????????
	///@remark ???????????????protocol://ipaddress:port?????��??tcp://127.0.0.1:17001???? 
	///@remark ??tcp?????????��?�??127.0.0.1??????????????????17001????????????????
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///??????????????????
	///@param pszNsAddress???????????????????
	///@remark ???????????????protocol://ipaddress:port?????��??tcp://127.0.0.1:12001???? 
	///@remark ??tcp?????????��?�??127.0.0.1??????????????????12001????????????????
	///@remark RegisterNameServer??????RegisterFront
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	///??????????????????
	///@param pFensUserInfo??????????
	virtual void RegisterFensUserInfo(CThostFtdcFensUserInfoField * pFensUserInfo) = 0;
	
	///????????
	///@param pSpi ?????????????????
	virtual void RegisterSpi(CThostFtdcMdSpi *pSpi) = 0;
	
	///???????�
	///@param ppInstrumentID ???ID  
	///@param nCount ?????/??????????????
	///@remark 
	virtual int SubscribeMarketData(char *ppInstrumentID[], int nCount) = 0;

	///??????�
	///@param ppInstrumentID ???ID  
	///@param nCount ?????/??????????????
	///@remark 
	virtual int UnSubscribeMarketData(char *ppInstrumentID[], int nCount) = 0;
	
	///????????
	///@param ppInstrumentID ???ID  
	///@param nCount ?????/??????????????
	///@remark 
	virtual int SubscribeForQuoteRsp(char *ppInstrumentID[], int nCount) = 0;

	///???????
	///@param ppInstrumentID ???ID  
	///@param nCount ?????/??????????????
	///@remark 
	virtual int UnSubscribeForQuoteRsp(char *ppInstrumentID[], int nCount) = 0;

	///??????????
	virtual int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;
	

	///???????
	virtual int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID) = 0;

	///???????��???
	virtual int ReqQryMulticastInstrument(CThostFtdcQryMulticastInstrumentField *pQryMulticastInstrument, int nRequestID) = 0;
protected:
	~CThostFtdcMdApi(){};
};

#endif
