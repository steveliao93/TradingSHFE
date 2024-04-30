#ifndef MDAPI_H
#define MDAPI_H


#include  "ThostFtdcMdApi.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <QList>

using namespace std;

//enum TLoginStatus { LSConnected, LSDisconnected, LSAuthenticate_successful, LSAuthenticate_failed, LSLogin_successful, LSLogin_failed };

class CMdApi : public CThostFtdcMdApi
{

private:
	//QList<CThostFtdcMdApi*> m_SpiList;
	CThostFtdcMdApi* mdm_pApi;
	//CThostFtdcTraderApi* m_pApi;


public:
	//TLoginStatus Status = LSDisconnected;

	CMdApi() {};
	~CMdApi() {};

public:
	///创建MdApi
		///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
		///@return 创建出的UserApi
		///modify for udp marketdata
	 CThostFtdcMdApi* CreateFtdcMdApi(const char* pszFlowPath = "", const bool bIsUsingUdp = false, const bool bIsMulticast = false);

	///获取API的版本信息
	///@retrun 获取到的版本号
	 const char* GetApiVersion();

	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release();

	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init();

	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join();

	///获取当前交易日
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	virtual const char* GetTradingDay();

	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char* pszFrontAddress);

	///注册名字服务器网络地址
	///@param pszNsAddress：名字服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
	///@remark RegisterNameServer优先于RegisterFront
	virtual void RegisterNameServer(char* pszNsAddress);

	///注册名字服务器用户信息
	///@param pFensUserInfo：用户信息。
	virtual void RegisterFensUserInfo(CThostFtdcFensUserInfoField* pFensUserInfo);

	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CThostFtdcMdSpi* pSpi);

	///订阅行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int SubscribeMarketData(char* ppInstrumentID[], int nCount);

	///退订行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeMarketData(char* ppInstrumentID[], int nCount);

	///订阅询价。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int SubscribeForQuoteRsp(char* ppInstrumentID[], int nCount);

	///退订询价。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeForQuoteRsp(char* ppInstrumentID[], int nCount);

	///用户登录请求
	virtual int ReqUserLogin(CThostFtdcReqUserLoginField* pReqUserLoginField, int nRequestID);


	///登出请求
	virtual int ReqUserLogout(CThostFtdcUserLogoutField* pUserLogout, int nRequestID);

	///请求查询组播合约
	virtual int ReqQryMulticastInstrument(CThostFtdcQryMulticastInstrumentField* pQryMulticastInstrument, int nRequestID);

};


#endif