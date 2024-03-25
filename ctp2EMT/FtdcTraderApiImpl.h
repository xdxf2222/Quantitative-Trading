#if !defined(_FTDCTRADERAPIIMPL_H)
#define _FTDCTRADERAPIIMPL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "emt_trader_api.h"
#include "ThostFtdcTraderApi.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <thread>

using namespace EMT::API;
///API�ӿ�ʵ��
class CFtdcTraderApiImpl : public CThostFtdcTraderApi, public TraderSpi
{
public:	
	///���캯��
	CFtdcTraderApiImpl(const char *pszFlowPath);

	const std::string time_to_string(int64_t tm);
	void OnTime(const boost::system::error_code& err);

	///��ȡAPI�İ汾��Ϣ
	///@retrun ��ȡ���İ汾��
	//const char *GetApiVersion(){return 0;};

	///ɾ���ӿڶ�����
	///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	virtual void Release();
	
	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	virtual void Init();
	
	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	virtual int Join();
	
	///��ȡ��ǰ������
	///@retrun ��ȡ���Ľ�����
	///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
	virtual const char *GetTradingDay();
	
	///ע��ǰ�û������ַ
	///@param pszFrontAddress��ǰ�û������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
	///@remark ��tcp����������Э�飬��127.0.0.1��������������ַ����17001�������������˿ںš�
	virtual void RegisterFront(char *pszFrontAddress);
	
	///ע�����ַ����������ַ
	///@param pszNsAddress�����ַ����������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
	///@remark ��tcp����������Э�飬��127.0.0.1��������������ַ����12001�������������˿ںš�
	///@remark RegisterFront������RegisterNameServer
	virtual void RegisterNameServer(char *pszNsAddress);


	///ע��ص��ӿ�
	///@param pSpi �����Իص��ӿ����ʵ��
	virtual void RegisterSpi(CThostFtdcTraderSpi *pSpi);

	///����˽������
	///@param nResumeType ˽�����ش���ʽ  
	///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        THOST_TERT_RESUME:���ϴ��յ�������
	///        THOST_TERT_QUICK:ֻ���͵�¼��˽����������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�˽���������ݡ�
	virtual void SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType);
	
	///���Ĺ�������
	///@param nResumeType �������ش���ʽ  
	///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        THOST_TERT_RESUME:���ϴ��յ�������
	///        THOST_TERT_QUICK:ֻ���͵�¼�󹫹���������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ������������ݡ�
	virtual void SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType);

	///�û���¼����
	virtual int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID);
	void HandleReqUserLogin(CThostFtdcReqUserLoginField& ReqUserLogin, int nRequestID);

	///�û��˳�����
	virtual int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID);
	void HandleReqUserLogout(CThostFtdcUserLogoutField& UserLogout, int nRequestID);

	///�û������޸�����
	virtual int ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID);
	void HandleReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField& UserPasswordUpdate, int nRequestID);

	///����¼������
	virtual int ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID);
	void HandleReqOrderInsert(CThostFtdcInputOrderField& InputOrder, int nRequestID);

	///������������
	virtual int ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID);
	void HandleReqOrderAction(CThostFtdcInputOrderActionField& InputOrderAction, int nRequestID);

	///������ѯ����
	virtual int ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID);

	///�ɽ�����ѯ����
	virtual int ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID);

	///�����ѯ�ʽ��˻�
	virtual int ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID);

	///��Լ��ѯ����
	virtual int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID);
	void HandleReqQryInstrument(CThostFtdcQryInstrumentField& QryInstrument, int nRequestID);

	///��������ѯ����
	virtual int ReqQryExchange(CThostFtdcQryExchangeField *pQryExchange, int nRequestID);
	void HandleReqQryExchange(CThostFtdcQryExchangeField& QryExchange, int nRequestID);

	///Ͷ���ֲֲ߳�ѯ����
	virtual int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID);

	///�����ѯ��Լ��֤����
	virtual int ReqQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField *pQryInstrumentMarginRate, int nRequestID);
	
	///�����ѯ��Լ��������
	virtual int ReqQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID);	

	///�����ѯͶ����
	virtual int ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID);

	///�����ѯ����
	virtual int ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID);

	///�����ѯ��Ʒ
	virtual int ReqQryProduct(CThostFtdcQryProductField *pQryProduct, int nRequestID);

	///Ͷ���߽�����ȷ��
	virtual int ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID);

	///�����ѯ���͹�˾���ײ���
	virtual int ReqQryBrokerTradingParams(CThostFtdcQryBrokerTradingParamsField *pQryBrokerTradingParams, int nRequestID);

	///�����ѯͶ���ֲ߳���ϸ
	virtual int ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID);

	///�����ѯͶ���ֲ߳���ϸ
	virtual int ReqQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail, int nRequestID);

	///�����ѯ������Ϣȷ��
	virtual int ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID);

	///�����ѯͶ���߽�����
	virtual int ReqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID);

	///�����ѯ��Ʒ��
	virtual int ReqQryProductGroup(CThostFtdcQryProductGroupField *pQryProductGroup, int nRequestID);

	///�����ѯ����ǩԼ��ϵ
	virtual int ReqQryAccountregister(CThostFtdcQryAccountregisterField *pQryAccountregister, int nRequestID);

	///�����ѯǩԼ����
	virtual int ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank, int nRequestID);

	///�����ѯ����֪ͨ
	virtual int ReqQryTradingNotice(CThostFtdcQryTradingNoticeField *pQryTradingNotice, int nRequestID);

	///�����ѯ�ͻ�֪ͨ
	virtual int ReqQryNotice(CThostFtdcQryNoticeField *pQryNotice, int nRequestID);
	
	///�ͻ�����֤����
	virtual int ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID);
	virtual void HandleReqAuthenticate(CThostFtdcReqAuthenticateField& AuthenticateField, int nRequestID);

	///�����ѯת����ˮ
	virtual int ReqQryTransferSerial(CThostFtdcQryTransferSerialField *pQryTransferSerial, int nRequestID);

	///�����ѯת������
	virtual int ReqQryTransferBank(CThostFtdcQryTransferBankField *pQryTransferBank, int nRequestID);

	///�����ѯѯ��
	virtual int ReqQryForQuote(CThostFtdcQryForQuoteField *pQryForQuote, int nRequestID);
	
	///ע�����ַ������û���Ϣ
	///@param pFensUserInfo���û���Ϣ��
	virtual void RegisterFensUserInfo(CThostFtdcFensUserInfoField * pFensUserInfo){return;};
	
	///�ʽ��˻������������
	virtual int ReqTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, int nRequestID){return -3;};

	///Ԥ��¼������
	virtual int ReqParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, int nRequestID){return -3;};

	///Ԥ�񳷵�¼������
	virtual int ReqParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, int nRequestID){return -3;};

	///��ѯ��󱨵���������
#ifdef V6_5_1
	virtual int ReqQueryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID){return -3;};
#else
	virtual int ReqQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID){return -3;};
#endif
	///����ɾ��Ԥ��
	virtual int ReqRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, int nRequestID){return -3;};

	///����ɾ��Ԥ�񳷵�
	virtual int ReqRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, int nRequestID){return -3;};

	///ִ������¼������
	virtual int ReqExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, int nRequestID);

	///ִ�������������
	virtual int ReqExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, int nRequestID);

	///ѯ��¼������
	virtual int ReqForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, int nRequestID);

	///����¼������
	virtual int ReqQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, int nRequestID);

	///���۲�������
	virtual int ReqQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, int nRequestID);

	///����������������
	virtual int ReqBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, int nRequestID){return -3;};

	///��Ȩ�ԶԳ�¼������
	virtual int ReqOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, int nRequestID);

	///��Ȩ�ԶԳ��������
	virtual int ReqOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, int nRequestID);

	///�������¼������
	virtual int ReqCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, int nRequestID){return -3;};

	///�����ѯ���ױ���
	virtual int ReqQryTradingCode(CThostFtdcQryTradingCodeField* pQryTradingCode, int nRequestID);

	///�����ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ
	virtual int ReqQryCFMMCTradingAccountKey(CThostFtdcQryCFMMCTradingAccountKeyField *pQryCFMMCTradingAccountKey, int nRequestID);

	///�����ѯ�ֵ��۵���Ϣ
	virtual int ReqQryEWarrantOffset(CThostFtdcQryEWarrantOffsetField *pQryEWarrantOffset, int nRequestID){return -3;};

	///�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
	virtual int ReqQryInvestorProductGroupMargin(CThostFtdcQryInvestorProductGroupMarginField *pQryInvestorProductGroupMargin, int nRequestID){return -3;};

	///�����ѯ��������֤����
	virtual int ReqQryExchangeMarginRate(CThostFtdcQryExchangeMarginRateField* pQryExchangeMarginRate, int nRequestID);

	///�����ѯ������������֤����
	virtual int ReqQryExchangeMarginRateAdjust(CThostFtdcQryExchangeMarginRateAdjustField *pQryExchangeMarginRateAdjust, int nRequestID){return -3;};

	///�����ѯ����
	virtual int ReqQryExchangeRate(CThostFtdcQryExchangeRateField *pQryExchangeRate, int nRequestID){return -3;};

	///�����ѯ������������Ա����Ȩ��
	virtual int ReqQrySecAgentACIDMap(CThostFtdcQrySecAgentACIDMapField *pQrySecAgentACIDMap, int nRequestID){return -3;};

	///�����ѯ��Ʒ���ۻ���
	virtual int ReqQryProductExchRate(CThostFtdcQryProductExchRateField *pQryProductExchRate, int nRequestID){return -3;};

	///�����ѯ�����̺�Լ��������
	virtual int ReqQryMMInstrumentCommissionRate(CThostFtdcQryMMInstrumentCommissionRateField *pQryMMInstrumentCommissionRate, int nRequestID) {return -3; };

	///�����ѯ��������Ȩ��Լ������
	virtual int ReqQryMMOptionInstrCommRate(CThostFtdcQryMMOptionInstrCommRateField *pQryMMOptionInstrCommRate, int nRequestID) {return -3; };

	///�����ѯ����������
	virtual int ReqQryInstrumentOrderCommRate(CThostFtdcQryInstrumentOrderCommRateField* pQryInstrumentOrderCommRate, int nRequestID);

	///�����ѯ�ʽ��˻�
	virtual int ReqQrySecAgentTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID) {return -3; };

	///�����ѯ�����������ʽ�У��ģʽ
	virtual int ReqQrySecAgentCheckMode(CThostFtdcQrySecAgentCheckModeField *pQrySecAgentCheckMode, int nRequestID) {return -3; };

	///�����ѯ��Ȩ���׳ɱ�
	virtual int ReqQryOptionInstrTradeCost(CThostFtdcQryOptionInstrTradeCostField* pQryOptionInstrTradeCost, int nRequestID);

	///�����ѯ��Ȩ��Լ������
	virtual int ReqQryOptionInstrCommRate(CThostFtdcQryOptionInstrCommRateField* pQryOptionInstrCommRate, int nRequestID);

	///�����ѯִ������
	virtual int ReqQryExecOrder(CThostFtdcQryExecOrderField* pQryExecOrder, int nRequestID);

	///�����ѯ����
	virtual int ReqQryQuote(CThostFtdcQryQuoteField* pQryQuote, int nRequestID);

	///�����ѯ��Ȩ�ԶԳ�
	virtual int ReqQryOptionSelfClose(CThostFtdcQryOptionSelfCloseField* pQryOptionSelfClose, int nRequestID);

	///�����ѯͶ�ʵ�Ԫ
	virtual int ReqQryInvestUnit(CThostFtdcQryInvestUnitField* pQryInvestUnit, int nRequestID);

	///�����ѯ��Ϻ�Լ��ȫϵ��
	virtual int ReqQryCombInstrumentGuard(CThostFtdcQryCombInstrumentGuardField* pQryCombInstrumentGuard, int nRequestID);

	///�����ѯ�������
	virtual int ReqQryCombAction(CThostFtdcQryCombActionField* pQryCombAction, int nRequestID);

	///�����ѯԤ��
	virtual int ReqQryParkedOrder(CThostFtdcQryParkedOrderField* pQryParkedOrder, int nRequestID);

	///�����ѯԤ�񳷵�
	virtual int ReqQryParkedOrderAction(CThostFtdcQryParkedOrderActionField* pQryParkedOrderAction, int nRequestID);

	///�����ѯ���͹�˾�����㷨
	virtual int ReqQryBrokerTradingAlgos(CThostFtdcQryBrokerTradingAlgosField* pQryBrokerTradingAlgos, int nRequestID);

	///�����ѯ��������û�����
	virtual int ReqQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField* pQueryCFMMCTradingAccountToken, int nRequestID);

	///�ڻ����������ʽ�ת�ڻ�����
	virtual int ReqFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID){return -3;};

	///�ڻ������ڻ��ʽ�ת��������
	virtual int ReqFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID){return -3;};

	///�ڻ������ѯ�����������
	virtual int ReqQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField* pReqQueryAccount, int nRequestID);

	///ע���û��ն���Ϣ�������м̷�����������ģʽ
	///��Ҫ���ն���֤�ɹ����û���¼ǰ���øýӿ�
	virtual int RegisterUserSystemInfo(CThostFtdcUserSystemInfoField *pUserSystemInfo) {return -3;};

	///�ϱ��û��ն���Ϣ�������м̷���������Ա��¼ģʽ
	///����Ա��¼�󣬿��Զ�ε��øýӿ��ϱ��ͻ���Ϣ
	virtual int SubmitUserSystemInfo(CThostFtdcUserSystemInfoField *pUserSystemInfo) {return -3;};

	///��ѯ�û���ǰ֧�ֵ���֤ģʽ
	virtual int ReqUserAuthMethod(CThostFtdcReqUserAuthMethodField* pReqUserAuthMethod, int nRequestID);

	///�û�������ȡͼ����֤������
	virtual int ReqGenUserCaptcha(CThostFtdcReqGenUserCaptchaField *pReqGenUserCaptcha, int nRequestID) {return -3;};

	///�û�������ȡ������֤������
	virtual int ReqGenUserText(CThostFtdcReqGenUserTextField *pReqGenUserText, int nRequestID) {return -3;};

	///�û���������ͼƬ��֤��ĵ�½����
	virtual int ReqUserLoginWithCaptcha(CThostFtdcReqUserLoginWithCaptchaField *pReqUserLoginWithCaptcha, int nRequestID) {return -3;};

	///�û��������ж�����֤��ĵ�½����
	virtual int ReqUserLoginWithText(CThostFtdcReqUserLoginWithTextField *pReqUserLoginWithText, int nRequestID) {return -3;};

	///�û��������ж�̬����ĵ�½����
	virtual int ReqUserLoginWithOTP(CThostFtdcReqUserLoginWithOTPField *pReqUserLoginWithOTP, int nRequestID) {return -3;};

	///�����ѯ������������Ϣ
	virtual int ReqQrySecAgentTradeInfo(CThostFtdcQrySecAgentTradeInfoField* pQrySecAgentTradeInfo, int nRequestID);

#ifdef V6_5_1
	///��ѯ��󱨵���������
	virtual int ReqQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField* pQryMaxOrderVolume, int nRequestID);
	void HandleReqQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField& QryMaxOrderVolume, int nRequestID);

	///�����ѯ�����Լ
	virtual int ReqQryClassifiedInstrument(CThostFtdcQryClassifiedInstrumentField* pQryClassifiedInstrument, int nRequestID);

	///��������Żݱ���
	virtual int ReqQryCombPromotionParam(CThostFtdcQryCombPromotionParamField* pQryCombPromotionParam, int nRequestID);
#endif

#ifdef V6_6_1_P1
	///Ͷ���߷��ս���ֲֲ�ѯ
	virtual int ReqQryRiskSettleInvstPosition(CThostFtdcQryRiskSettleInvstPositionField* pQryRiskSettleInvstPosition, int nRequestID);

	///���ս����Ʒ��ѯ
	virtual int ReqQryRiskSettleProductStatus(CThostFtdcQryRiskSettleProductStatusField* pQryRiskSettleProductStatus, int nRequestID);
#endif

private:
	virtual void OnDisconnected(uint64_t session_id, int reason);

	/*��Լ��ѯӦ��*/

	//Ͷ���ֲֲ߳�ѯ
	void OnQueryPosition(EMTQueryStkPositionRsp* position, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

	//������ѯ
	void OnQueryOrder(EMTQueryOrderRsp* order_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

	//�ɽ���ѯ
	void OnQueryTrade(EMTQueryTradeRsp* trade_info, EMTRI* error_info, int request_id, bool is_last, uint64_t session_idt);

	//�ʽ��˻���ѯ
	void OnQueryAsset(EMTQueryAssetRsp* asset, EMTRI* error_info, int request_id, bool is_last, uint64_t session_id);

	//�����ر�
	virtual void OnOrderEvent(EMTOrderInfo* order_info, EMTRI* error_info, uint64_t session_id);

	//����Ӧ��	
	virtual void OnCancelOrderError(EMTOrderCancelInfo* cancel_info, EMTRI* error_info, uint64_t session_id);

	//�ɽ��ر�
	virtual void OnTradeEvent(EMTTradeReport* trade_info, uint64_t session_id);

private:
	TThostFtdcInvestorIDType m_InvestorID;
	TThostFtdcUserIDType m_UserID;
	TThostFtdcBrokerIDType m_BrokerID;
	uint64_t m_emt_sessionid;
	EMT_PROTOCOL_TYPE m_protocol;

	TThostFtdcFrontIDType m_FrontID;
	TThostFtdcSessionIDType m_SessionID;
	CThostFtdcRspUserLoginField  ThostRspUserLogin;

	// ģ����Ӧ
	CThostFtdcRspInfoField  ThostRspInfo;
	CThostFtdcRspInfoField  ThostRspInfoNotSupported;
	CThostFtdcRspAuthenticateField RspAuthenticateField;
	CThostFtdcSettlementInfoConfirmField SettlementInfoConfirmField;
	CThostFtdcBrokerTradingParamsField BrokerTradingParamsField;

	TThostFtdcDateType	TradingDay;
	boost::asio::io_service m_io_service;
	std::thread* m_pthread;
	boost::asio::deadline_timer* m_pTimer;
	bool m_logined;
	char m_ip[16];
	unsigned short m_port;
	std::map<uint64_t, uint64_t> m_mOrderRefToXtpID; // ��OrderRefΪ����ID��Ϊ����CTP���ƶ���
	std::map<uint64_t, uint64_t> m_mXtpIDToOrderRef;
	uint32_t m_ctp_sessionid; // ����ID��Ϊ����CTP���ƶ���
	uint32_t m_ctp_orderref; // ����ID��Ϊ����CTP���ƶ���
	uint32_t m_ctp_sys_orderref; // ����ID��Ϊ����CTP���ƶ���


public:
	TraderApi *m_pUserApi;
	CThostFtdcTraderSpi *m_pSpi;
};


#endif