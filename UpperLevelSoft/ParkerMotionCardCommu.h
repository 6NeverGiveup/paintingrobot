#pragma once
/** @file 
*@brief ���ļ����ڶ����˶�����ͨѶ�������
������λ���˶����ƿ�ͨ����
* @author 
* @date 
* @version 1.0
*
* 
*/
#include "ParkerCom/ReadStatus.h"
//#include"Resource.h"
#include <atlstr.h>
#include <string>
#include "ResultAdapter.h"
#define L_COMACRSERVER_PROGID L"ComACRServer.Channel.1"

class ReadStatus;											// **ADDED** Avoids #include-ing the class header here
class CUpperLevelSoftDlg;									//�������ñ�����ôŪ
class CLowMoniter;											//�������ñ�����ôŪ
#define  P_NUM_BEGIN 48										//52��ʼ�������ݣ�֮ǰ��4�������ݵ�ͷ����
#define  P_NUM_END 10000
class CParkerMotionCardCommu
{
public:
	CParkerMotionCardCommu(void);
	~CParkerMotionCardCommu(void);

	bool  UpdateStats(UINT,LONG);							///<�Զ�����˿ؿ�ͨѶ��Ϣ,CComQIPtrΪ�ģ�������ָ��
	CComQIPtr<IChannel> m_Chan;								///<����ͨ��
	CComQIPtr<IContrl> m_Cntl;								///<����������
	CComQIPtr<IStatus> m_Stat;								///<״̬������
	ReadStatus * m_workerEvent;
/**
*@brief ��ʾ������Ϣ
*
*��ע����connect�����������ִ�����ܻ�ʹ��m_cnt->isoffline ʧʵ
*@parm
*
*@return
*@todo
*/
	void ShowControlErr(long errCode);
	bool InitComWithParker(void);
	void DestroyComWithParker(void);
/**
*@brief ɾ�������ʵ��
*
*
*@parm
*
*@return
*@todo
*/
	void Destroy(bool DestroyOnly=false);
	CString m_isOffline;///<��ʾ����״̬�ľ�̬�ı���������
	bool m_bisOffline;///<δ���ӳɹ���Ϊ�棬connect�����������ִ�����ܻ�ʹ��m_cnt->isoffline ʧʵ��������Ӵ˱���
	void Disconnect();
/**
*@brief �鿴���ƿؼ��Ƿ����ӣ�����Ϊ��
*
*
*@parm
*
*@return
*@todo
*/
	bool QueryCntConectStat()
	{		
		//bool bIsOf=m_Cntl->get_isOffline();
		return !m_bisOffline;
	}
/**
*@brief ����������������
*
*
*@parm
*
*@return
*@todo
*/
	bool DownLoadParmFlow(MotionParm_It_TYPE ItBegin,MotionParm_It_TYPE ItEnd);
/**
*@brief �뿨ʵ�����ӣ�ͨѶǰ��������
*
*
*@parm DLG* pTargetDlg  ���ܷ��������Ĳ����Ի���
*
*@return
*@todo
*/

	bool Connect(void* pTargetDlg);
/**
*@brief ��ʾ������ʾ
*
*
*@parm
*
*@return
*@todo
*/
	void ShowCacthedControlErr(long errCode);
	//bool Connect(CUpperLevelSoftDlg* pTargetDlg);
	unsigned m_chooseAxis;
	//float m_jogVel;
	void SelectAxis(unsigned Axis)
	{
		m_chooseAxis= Axis;
	}
	void SetVel(float Vel);
	//m_jogVel
	void Motionfwd();
	void MotionStop();
	void MotionReverse();
	long M_axisXSecPo;
	long M_axisY1SecPos;
	long M_axisY2SecPo;
	long M_axisZSecPos;
	long M_axisXAcrPo;
	long M_axisY1AcrPo;
	long M_axisY2AcrPo;
	long M_axisZAcrPo;
	long M_axisXFowEr;
	long M_axisY1FowEr;
	long M_axisY2FowEr;
	long M_axisZFowErr;
	CString m_pstr;
	long m_pKey;
	void QueryParmFromACR(void);
	//afx_msg void OnBnClickedButton7();
	//afx_msg void OnBnClickedButton8();
	void EnableDrive();
	void DisableDrive();
	void SetPval(unsigned PIndex,float Pval);
	
	bool SetAutoResPonse(void * pTargetDlg);
	int connect_Wraped(void);
};
