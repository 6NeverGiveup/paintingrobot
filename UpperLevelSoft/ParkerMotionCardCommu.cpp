//#include "StdAfx.h"
#include "stdafx.h"
#include "ParkerMotionCardCommu.h"
#include "LowMoniter.h"
#include "UpperLevelSoftDlg.h"

CParkerMotionCardCommu::CParkerMotionCardCommu(void): m_isOffline(_T(""))
, m_chooseAxis(0)
, M_axisXSecPo(0)
, M_axisY1SecPos(0)
, M_axisY2SecPo(0)
, M_axisZSecPos(0)
, M_axisXAcrPo(0)
, M_axisY1AcrPo(0)
, M_axisY2AcrPo(0)
, M_axisZAcrPo(0)
, M_axisXFowEr(0)
, M_axisY1FowEr(0)
, M_axisY2FowEr(0)
, M_axisZFowErr(0)
{
	//InitComWithParker();
}

CParkerMotionCardCommu::~CParkerMotionCardCommu(void)
{
}

bool CParkerMotionCardCommu::Connect(void* pTargetDlg)
{


	//UpdateData();
		CComBSTR ip("192.168.10.40");
		m_Chan->put_bstrIP(ip);

		m_Cntl->bstrIP="192.168.10.40";		//��Ӧ�ó��������������ӵĿ�������IP��ַ
		m_Stat->bstrIP="192.168.10.40";     //״̬
		/*m_Cntl->isOffline=true;
		m_Cntl->*/
		m_Cntl->Connect(3,0);               //�������ͨ����̫����������
		m_Stat->Connect(3,0);  
		m_Chan->Connect(3,0);
		if(!m_Cntl->isOffline && !m_Stat->isOffline)   //�жϿ������Ƿ�����(���ӳɹ�)
		{
			//Sleep(100);
			m_isOffline="���������ӳɹ�!";//+m_Stat->GetBstrVersion();  //������ӳɹ�����Ի�������ʾ
			m_bisOffline=false;
			////�����������ӳɹ������汾��
			//m_Stat->DelStatus(-1);//ɾ�����ж�������
			//Sleep(100);
			////�����ӳɹ�����Ի�������ʾ�����������ӳɹ������汾��
			////m_Stat->SetNStatusWaitRate(10); //���ÿ�������Ӧ�ó�������
			////����Ϣ����С���Ϊ10m
			//m_pstr="P12289,P12545,P12801,P13057,P12290,P12546,P12802,P13056,P12291,P12547,P12803,P13059";
			//m_pKey=m_Stat->AddACRCustom(m_pstr.GetBuffer()); //����AddACRCustom������֪������Ӧ�ó���Ҫʵʱ��ȡ��P�����������ò����ķ���ֵ�洢��m_pKey�С�
			//Sleep(100);
			//QueryParmFromACR();
		}
		else
		{
			m_isOffline="δ����!";
			return false;
		}
		//m_workerEvent = new ReadStatus(pTargetDlg); //����ReadStatus�����
	return true;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
bool CParkerMotionCardCommu::SetAutoResPonse(void * pTargetDlg)
{
	if(!m_Cntl->isOffline && !m_Stat->isOffline)				//�жϿ������Ƿ�����(���ӳɹ�)
	{
		//Sleep(100);
		m_Stat->DelStatus(-1);									//ɾ�����ж�������
		Sleep(100);
		//m_Stat->SetNStatusWaitRate(10);						//���ÿ�������Ӧ�ó�������
		//����Ϣ����С���Ϊ10m
		m_pstr="P12289,P12545,P12801,P13057,P12290,P12546,P12802,P13056,P12291,P12547,P12803,P13059";
		m_pKey=m_Stat->AddACRCustom(m_pstr.GetBuffer()); //����AddACRCustom������֪������Ӧ�ó���Ҫʵʱ��ȡ��P�����������ò����ķ���ֵ�洢��m_pKey�С�
		//m_Stat->
		Sleep(100);
		QueryParmFromACR();

	}
	else
	{
		m_isOffline="δ����!";
		return false;
	}
	m_workerEvent = new ReadStatus(pTargetDlg); //����ReadStatus�����
	return true;
}

//bool CParkerMotionCardCommu::Connect(CUpperLevelSoftDlg* pTargetDlg)
//{
//
//
//	//UpdateData();
//	CComBSTR ip("192.168.10.40");
//	m_Chan->put_bstrIP(ip);
//
//	m_Cntl->bstrIP="192.168.10.40"; //��Ӧ�ó��������������ӵĿ�������IP��ַ
//	m_Stat->bstrIP="192.168.10.40";
//	m_Cntl->Connect(3,0);               //�������ͨ����̫����������
//	m_Stat->Connect(3,0);  
//	m_Chan->Connect(3,0);
//	if(!m_Cntl->isOffline && !m_Stat->isOffline)   //�жϿ������Ƿ�����(���ӳɹ�)
//	{
//		//Sleep(100);
//		m_isOffline="���������ӳɹ�!";//+m_Stat->GetBstrVersion();  //������ӳɹ�����Ի�������ʾ
//		//�����������ӳɹ������汾��
//		m_Stat->DelStatus(-1);//ɾ�����ж�������
//		Sleep(100);
//		//�����ӳɹ�����Ի�������ʾ�����������ӳɹ������汾��
//		//m_Stat->SetNStatusWaitRate(10); //���ÿ�������Ӧ�ó�������
//		//����Ϣ����С���Ϊ10m
//		m_pstr="P12289,P12545,P12801,P13057,P12290,P12546,P12802,P13056,P12291,P12547,P12803,P13059";
//		m_pKey=m_Stat->AddACRCustom(m_pstr.GetBuffer()); //����AddACRCustom������֪������Ӧ�ó���Ҫʵʱ��ȡ��P�����������ò����ķ���ֵ�洢��m_pKey�С�
//		Sleep(100);
//		QueryParmFromACR();
//
//	}
//	else
//	{
//		m_isOffline="δ����!";
//		return false;
//	}
//	m_workerEvent = new ReadStatus(pTargetDlg); //����ReadStatus�����
//	return true;
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}
bool CParkerMotionCardCommu::InitComWithParker(void)
{
	CComPtr<IUnknown> spUnknown;
	spUnknown.CoCreateInstance(L"ComACRServer.Channel.1");
	if (spUnknown)
	{
		spUnknown.QueryInterface(&m_Stat);
		spUnknown.QueryInterface(&m_Cntl);
		spUnknown.QueryInterface(&m_Chan);
	}
	m_workerEvent = NULL;
	m_bisOffline=true;
	return false;
}
void CParkerMotionCardCommu::DestroyComWithParker(void)
{

	if(m_workerEvent){
		delete m_workerEvent;
		m_workerEvent=NULL;		
	} 
	if(m_Cntl){
		m_Cntl->Disconnect();
		m_Cntl.Release();
		//delete m_Cntl;
	}
	if(m_Stat){
		m_Stat->Disconnect();
		m_Stat.Release();
	}
	if(m_Chan){
		m_Chan->Disconnect();
		m_Chan.Release();
	}
}
bool CParkerMotionCardCommu::UpdateStats(UINT nID, LONG xMsgid)
{
	CComVariant vaxis;
	CComVariant *buf;
	if(xMsgid==m_pKey)
	{
		if(m_Stat->isOffline)
		{	return false;  }
		vaxis = m_Stat->GetStatus(m_pKey);
		::SafeArrayAccessData(vaxis.parray,(void**)&buf);
		M_axisXSecPo=buf[0].lVal;
		M_axisY1SecPos=buf[1].lVal;
		M_axisY2SecPo=buf[2].lVal;
		M_axisZSecPos=buf[3].lVal;
		M_axisXAcrPo=buf[4].lVal;
		M_axisY1AcrPo=buf[5].lVal;
		M_axisY2AcrPo=buf[6].lVal;
		M_axisZAcrPo=buf[7].lVal;
		M_axisXFowEr=buf[8].lVal;
		M_axisY1FowEr=buf[9].lVal;
		M_axisY2FowEr=buf[10].lVal;
		M_axisZFowErr=buf[11].lVal;
		::SafeArrayUnaccessData(vaxis.parray);	
		return true;
	}
	return false;
}
void CParkerMotionCardCommu::Disconnect()
{
	bool bOffLine=false;
	if (m_Stat)
	{
		if(!m_Stat->isOffline)   //�жϿ������Ƿ�����(���ӳɹ�)
		{m_Stat->DelStatus(-1);}
		Sleep(100);		
		m_Stat->Disconnect();
		if(m_Stat->isOffline)
		{bOffLine=true;	}
	}
	else
	{bOffLine=true;	}

	if (m_Cntl){
		m_Cntl->Disconnect();
		if(m_Cntl->isOffline)
		{bOffLine=true;	}
		else{bOffLine=false;}
	}//�Ͽ�����
	else
	{bOffLine=true;	}
	if (bOffLine)
	{m_isOffline="δ����";	
		m_bisOffline=true;
	}
	if(m_workerEvent){
		delete m_workerEvent;
		m_workerEvent=NULL;		
	} 
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CParkerMotionCardCommu::SetVel(float Vel)
{
	if(m_Cntl->isOffline)
	{
		return;
	}
	//������ѡ����Ĳ�ͬ������JOG�˶��ٶ�
	if(m_Cntl->isOffline)
	{
		return;
	}
	switch(m_chooseAxis)
	{
	case 0:
		{
			m_Cntl->SetParmFloat(12346, Vel, true);
			//����Control���SetParaFloat������ACR�������ĸ�����P��
			//����ֵ
			break;
		}
	case 1:
		{
			m_Cntl->SetParmFloat(12602, Vel, true);
			break;
		}
	case 2:
		{
			m_Cntl->SetParmFloat(12858, Vel, true);
			break;
		}
	case 3:
		{
			m_Cntl->SetParmFloat(13114, Vel, true);
			break;
		}
	default:
		break;
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CParkerMotionCardCommu::Motionfwd()
{
		//������ѡ����Ĳ�ͬ�����Ƹ����JOG�����˶�
		if(m_Cntl->isOffline)
		{
			return;
		}
		switch(m_chooseAxis)
		{
		case 0:
			{
				m_Cntl->SetFlag(797,false,true);
				//����Control���SetFlag������ĳһ��BITλ��λ��λ
				m_Cntl->SetFlag(796,true,true);
				break;
			}
		case 1:
			{
				m_Cntl->SetFlag(829,false,true);
				m_Cntl->SetFlag(828,true,true);
				break;
			}
		case 2:
			{
				m_Cntl->SetFlag(861,false,true);
				m_Cntl->SetFlag(860,true,true);
				break;
			}
		case 3:
			{
				m_Cntl->SetFlag(893,false,true);
				m_Cntl->SetFlag(892,true,true);
				break;
			}
		default:
			break;
		}
}
void CParkerMotionCardCommu::MotionStop()
{
	// TODO: Add your control notification handler code here
	if(m_Cntl->isOffline)
	{
		return;
	}
	switch(m_chooseAxis)
	{
	case 0:
		{
			m_Cntl->SetFlag(797,false,true);
			m_Cntl->SetFlag(796,false,true);
			break;
		}
	case 1:
		{
			m_Cntl->SetFlag(829,false,true);
			m_Cntl->SetFlag(828,false,true);
			break;
		}
	case 2:
		{
			m_Cntl->SetFlag(861,false,true);
			m_Cntl->SetFlag(860,false,true);
			break;
		}
	case 3:
		{
			m_Cntl->SetFlag(893,false,true);
			m_Cntl->SetFlag(892,false,true);
			break;
		}
	default:
		break;
	}
}
void CParkerMotionCardCommu::MotionReverse()
{
	// TODO: Add your control notification handler code here
	if(m_Cntl->isOffline)
	{
		return;
	}
	switch(m_chooseAxis)
	{
	case 0:
		{
			m_Cntl->SetFlag(796,false,true);
			m_Cntl->SetFlag(797,true,true);
			break;
		}
	case 1:
		{
			m_Cntl->SetFlag(828,false,true);
			m_Cntl->SetFlag(829,true,true);
			break;
		}
	case 2:
		{
			m_Cntl->SetFlag(860,false,true);
			m_Cntl->SetFlag(861,true,true);
			break;
		}
	case 3:
		{
			m_Cntl->SetFlag(892,false,true);
			m_Cntl->SetFlag(893,true,true);
			break;
		}
	default:
		break;
	}
}
void CParkerMotionCardCommu::QueryParmFromACR(void)
{
	CComVariant vaxis;   
	CComVariant *buf;
	vaxis = m_Stat->GetACRCustom(m_pstr.GetBuffer());
	::SafeArrayAccessData(vaxis.parray,(void**)&buf);          //��SafeArrayAccessDataֱ�Ӷ�дSafeArray��������
	M_axisXSecPo=buf[0].lVal;
	M_axisY1SecPos=buf[1].lVal;
	M_axisY2SecPo=buf[2].lVal;
	M_axisZSecPos=buf[3].lVal;
	M_axisXAcrPo=buf[4].lVal;
	M_axisY1AcrPo=buf[5].lVal;
	M_axisY2AcrPo=buf[6].lVal;
	M_axisZAcrPo=buf[7].lVal;
	M_axisXFowEr=buf[8].lVal;
	M_axisY1FowEr=buf[9].lVal;
	M_axisY2FowEr=buf[10].lVal;
	M_axisZFowErr=buf[11].lVal;
	::SafeArrayUnaccessData(vaxis.parray);
}
void CParkerMotionCardCommu::EnableDrive()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_Cntl->isOffline)
	{
		return;
	}
	switch(m_chooseAxis)
	{
	case 0:
		{
			m_Cntl->SetFlag(8465,true,true);
			break;
		}
	case 1:
		{
			m_Cntl->SetFlag(8497,true,true);
			break;
		}
	case 2:
		{
			m_Cntl->SetFlag(8529,true,true);
			break;
		}
	case 3:
		{
			m_Cntl->SetFlag(8561,true,true);
			break;
		}
	default:
		break;
	}
}

void  CParkerMotionCardCommu::DisableDrive()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_Cntl->isOffline)
	{
		return;
	}
	switch(m_chooseAxis)
	{
	case 0:
		{
			m_Cntl->SetFlag(8465,false,true);
			break;
		}
	case 1:
		{
			m_Cntl->SetFlag(8497,false,true);
			break;
		}
	case 2:
		{
			m_Cntl->SetFlag(8529,false,true);
			break;
		}
	case 3:
		{
			m_Cntl->SetFlag(8561,false,true);
			break;
		}
	default:
		break;
	}
}

void  CParkerMotionCardCommu::Destroy(bool DestroyOnly)
{
	if(m_Cntl){	
		if(!m_Cntl->isOffline)
		{
			if (!DestroyOnly)
			{DisableDrive();}		
			Disconnect();//�Ⱥ󲻿ɸ��	
		}
	}
	DestroyComWithParker();
}

void  CParkerMotionCardCommu::SetPval(unsigned PIndex,float Pval)
{
	if(m_Cntl->isOffline)
	{
		return;
	}
	m_Cntl->SetParmFloat(PIndex,Pval, true);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
bool CParkerMotionCardCommu::DownLoadParmFlow(MotionParm_It_TYPE ItBegin,MotionParm_It_TYPE ItEnd)
{
	unsigned PNum=P_NUM_BEGIN;
	for (ItBegin;ItBegin<ItEnd;ItBegin++)
	{
		if (PNum<P_NUM_END)
		{
			SetPval(PNum,*ItBegin);
			PNum++;
		}	
		else
		{
			return false;///<������������õķ�Χ������
		}
	}
	return true;
}


int CParkerMotionCardCommu::connect_Wraped(void)
{
	if (!m_isOffline)//��ֹ�ظ�����
	{
		return 0;
	}
	try
	{
		Connect(this);
	}catch(_com_error &e) {
		long m_errCode;
		m_errCode=m_Chan->GetnLastErrorCode();
		e;
		ShowCacthedControlErr(m_errCode);
	}
	catch(CException *e) { 
		TCHAR szCause[1024];
		e->GetErrorMessage(szCause, 1024);   
		//MessageBox(szCause, "non-COM Error", MB_OK);
	}

	return 0;
}
void CParkerMotionCardCommu::ShowCacthedControlErr(long errCode)
{
	switch(errCode)
	{
	case 17056:
		{
			::MessageBox(NULL,_T("�ӿ�������ȡ�����������д������ǰ���������������������!"),_T("���Ӵ���"),MB_OK);
			break;
		}
	case 17083:
		{
			MessageBox(NULL,_T("�����������ʧ��!"),_T("ͨѶ����"),MB_OK);
			break;
		}
	default:
		{
			MessageBox(NULL,_T("δ֪�Ĵ���!"),NULL,MB_OK);
			break;
		}
	}
}