// LowMoniter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UpperLevelSoft.h"
#include "LowMoniter.h"
#include "afxdialogex.h"


// CLowMoniter �Ի���

IMPLEMENT_DYNAMIC(CLowMoniter, CDialog)

CLowMoniter::CLowMoniter(CWnd* pParent /*=NULL*/)
	: CDialog(CLowMoniter::IDD, pParent)
{

}

CLowMoniter::~CLowMoniter()
{
}

void CLowMoniter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLowMoniter, CDialog)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CLowMoniter::OnBnClickedBtnConnect)
END_MESSAGE_MAP()


// CLowMoniter ��Ϣ�������


void CLowMoniter::OnBnClickedBtnConnect()
{
//	try
//	{
//#ifndef USE_CONTENT_IN_DEPENDENT_CLASS
//		UpdateData();
//		CComBSTR ip("192.168.10.40");
//		m_Chan->put_bstrIP(ip);
//		m_Cntl->bstrIP="192.168.10.40"; //��Ӧ�ó��������������ӵĿ�������IP��ַ
//		m_Stat->bstrIP="192.168.10.40";
//		m_Cntl->Connect(3,0);               //�������ͨ����̫����������
//		m_Stat->Connect(3,0);  
//		m_Chan->Connect(3,0);
//		if(!m_Cntl->isOffline && !m_Stat->isOffline)   //�жϿ������Ƿ�����(���ӳɹ�)
//		{
//			//Sleep(100);
//			m_isOffline="���������ӳɹ�!";//+m_Stat->GetBstrVersion();  //������ӳɹ�����Ի�������ʾ
//			//�����������ӳɹ������汾��
//			m_Stat->DelStatus(-1);//ɾ�����ж�������
//			Sleep(100);
//			//������ӳɹ�����Ի�������ʾ�����������ӳɹ������汾��
//			//m_Stat->SetNStatusWaitRate(10); //���ÿ�������Ӧ�ó�������
//			//����Ϣ����С���Ϊ10m
//			m_pstr="P12289,P12545,P12801,P13057,P12290,P12546,P12802,P13056,P12291,P12547,P12803,P13059";
//			m_pKey=m_Stat->AddACRCustom(m_pstr.GetBuffer()); //����AddACRCustom������֪������Ӧ�ó���Ҫʵʱ��ȡ��P�����������ò����ķ���ֵ�洢��m_pKey�С�
//			Sleep(100);
//			QueryParmFromACR();
//
//		}
//		else
//		{
//			m_isOffline="δ����!";
//		}
//		UpdateData(false);                    //����
//		m_workerEvent = new ReadStatus(this); //����ReadStatus�����
//#else
//		m_cMotionCommu.Connect(this);
//		m_isOffline=m_cMotionCommu.m_isOffline;
//		UpdateData(FALSE);
//		m_cMotionCommu.SetAutoResPonse(this);
//#endif
//		
//
//	}catch(_com_error &e) {
//		long m_errCode;
//#ifdef  USE_CONTENT_IN_DEPENDENT_CLASS
//		m_errCode=m_cMotionCommu.m_Chan->GetnLastErrorCode();
//		e;
//#else
//			m_errCode=m_Chan->GetnLastErrorCode();
//			e;
//#endif
//	
//		ShowControlErr(m_errCode);
//	}
//	catch(CException *e) { 
//		TCHAR szCause[1024];
//		e->GetErrorMessage(szCause, 1024);   
//		MessageBox(szCause, _T("non-COM Error"), MB_OK);
//	}

}
