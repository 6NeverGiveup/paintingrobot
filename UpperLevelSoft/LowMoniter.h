#pragma once
//#include "ParkerCom/ReadStatus.h"
//#include"Resource.h"
//#include <atlstr.h>
#include <string>
//class ReadStatus;        // **ADDED** Avoids #include-ing the class header here
#define USE_CONTENT_IN_DEPENDENT_CLASS //�����屾�꣬�����ľ���ʵ�ַ�������һ������
// CLowMoniter �Ի���

class CLowMoniter : public CDialog
{
	DECLARE_DYNAMIC(CLowMoniter)

public:
	CLowMoniter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLowMoniter();

// �Ի�������
	enum { IDD = IDD_LOW_MONITER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnConnect();
public:
//	#ifndef USE_CONTENT_IN_DEPENDENT_CLASS
//	CComQIPtr<IChannel> m_Chan;
//	CComQIPtr<IContrl> m_Cntl;
//	CComQIPtr<IStatus> m_Stat;
//	CString m_pstr;
//	long m_pKey;
//#else
//	 CParkerMotionCardCommu m_cMotionCommu;					///<����ͨѶ��ʵ������
//#endif	
};
