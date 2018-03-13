#include "StdAfx.h"
#include "PlcCommu.h"
CMscomm* CPlcCommu::m_Mscomm;///<�Դ�Ĵ���ͨѶʵ������
CPlcCommu::CPlcCommu(void):m_cEnter(13),m_csCommandTail("*"),m_csDataWriteCommandHeader("@00WD")
{
	//char a= 13;
	m_csCommandTail=m_csCommandTail+m_cEnter;
	CPlcCommu::m_Mscomm=NULL;
	m_bWaitForResponse=false;
}

CPlcCommu::~CPlcCommu(void)
{
}
bool CPlcCommu::InitComm(unsigned PortNum,CMscomm* Mscomm)
{
	if (!Mscomm)
	{
		MessageBoxA(NULL,("��������������鴮��ͨѶʵ��"),NULL,NULL);
		return false;
	}
	Mscomm->put_CommPort(PortNum);//com1
	if(Mscomm->get_PortOpen())
	{
		MessageBoxA(NULL,("�����Ѵ򿪣����ȹر�"),NULL,NULL);
		return false;
	}

	Mscomm->put_InBufferSize(1024);
	Mscomm->put_OutBufferSize(512);
	/*if(!Mscomm->get_PortOpen())
	{
		Mscomm->put_PortOpen(TRUE);
		MessageBox(NULL,("���ڴ򿪳ɹ�"),"�ɹ�",NULL);
	}
	else
		MessageBox(NULL,("�޷��򿪴��ڶ˿�"),NULL,NULL);*/
	//	m_mscomm1.SetSettings(chSet);//"4800,n,8,1"
	Mscomm->put_Settings(_T("9600,e,7,2"));
	//Mscomm->put_InputMode(Mscomm->comInputModeText);//�����Ƽ�ȡ����
	Mscomm->put_InputMode(Mscomm->comInputModeBinary);//�����Ƽ�ȡ����
	Mscomm->put_RThreshold(1);//�����¼��ֽ���
//	Mscomm.put_SThreshold(0);//�����ʹ�ô���ʱ���е��Զ�������ֻҪ��һ������0 ����ֵ ���ͻ�һֱ����ֱ������512�ֽ� 
	Mscomm->put_InputLen(0);//ȫ������
	//Mscomm.put_Input();
	return true;
}
bool CPlcCommu::OnReceieveCom(CMscomm* Mscomm)
{
	int CommEvent=Mscomm->get_CommEvent();
	if(CommEvent == 2)
	{
		
		//clearData();//���ԭ��������
		COleVariant varInput;//VARIANT 
		COleSafeArray sfarrInput;
		static long len,k;		
		static CString strTemp;
		len = Mscomm->get_InBufferCount();
		varInput = Mscomm->get_Input();
		return false;//����
		//sfarrInput.Attach(varInput);
	/*	varInput.ChangeType((VT_BSTR));
		CString sfarrInput = varInput.bstrVal;*/
		sfarrInput = varInput;
		len = sfarrInput.GetOneDimSize();
		if (len<=4)//��֡���͵��м�֡,�лظ����У������
		{	m_bWaitForResponse=false;
			return true;
		}
		CString strTmp;	
		CString reced;	
		//double SingleDis;
//sfarrInput.ChangeType()
		for(k =0; k < len; k++)//��ȥ����ͷ����β
		{
			sfarrInput.GetElement( &k, m_rxdata+k);
		//	BYTE bt=*(char*)(m_rxdata+k);
			strTmp.Format(_T("%c"),*(m_rxdata+k));
			 reced+=strTmp;
		}

		m_rxdata[len]='\0';//�����ַ�����β����ʾ
		return true;
		//m_ReceviedDat=m_rxdata;
		std::string ReceivedStr(&m_rxdata[1],&m_rxdata[len-4]); //�м�ת��Ϊstring,��ȥ����ͷ����β
		std::string strFCSVal(&m_rxdata[len-4],&m_rxdata[len]);
		//std::string ReceivedStr(reced.GetBuffer()+1,&m_rxdata[len-4]); //�м�ת��Ϊstring,��ȥ����ͷ����β
		///////////////////////////////////////�����⣬����ͨ����///////////////////////////////////
		//CString CommandFCSVal=(strFCSVal.c_str());//�����⣬����ͨ����

		//std::string EndCode=ReceivedStr.substr(4,2);
		//m_ReceviedDat.Format(_T("%s"),ReceivedStr.c_str());//ת��ΪCString
		//if (CheckFCS(m_ReceviedDat,CommandFCSVal))
		//{
		//	if (EndCode!="00")//����ִ������
		//	{
		//		EndCode.insert(0,_T("�������Ϊ��"));
		//		MessageBox(NULL,_T(EndCode.data()),_T("PLCִ���������"),NULL);
		//	}
		//	else
		//	{
		//		m_bWaitForResponse=false;//ִ����ȷ
		//	}			
		//}
		//else
		//{			
		//	return false;
		//}
		return true;
		//FCS(m_ReceviedDat);		
		//SendOnceCommand(Mscomm);//��������
	}
		//����β
		//UpdateData(FALSE);
	return true;//����У����󶼷�����
}

bool CPlcCommu::CloseComm(CMscomm* Mscomm)
{
	if(!Mscomm->get_PortOpen())
	{
		//	MessageBoxA(NULL,("com1 already close"),NULL,NULL);
		MessageBox(NULL,_T("com�˿����ѹر�"),_T("����"),NULL);

		return false;
	}
	else
	{
		Mscomm->put_PortOpen(FALSE);
		//	MessageBox("com1 close sucessfully");
	}
	return true;
}
CString CPlcCommu::FCS(CString& strFrame)
{
	int i ,count ;
	unsigned int intMidData = 0;
	count =strFrame.GetLength() ;
	for (i = 0;i<count;i++)
		intMidData = intMidData^strFrame.GetAt(i) ;
	CString FrameFCS;
	 FrameFCS.Format (_T("%02X"),intMidData);//2��ʾ���Ϊ2,ʵ��λ����������ʵ���ߣ�0��ʾ�ڲ���λ��0,
	return FrameFCS;
}

void CPlcCommu::SendSingleFrameData(CString& strToSend, CString& Address,CMscomm* Mscomm)
{
	//CString m_strSendData;

//	strToSend="@00WD00050080";
	//strToSend.Insert(0,'@');
	m_uReSendCound=0;
	CString m_strSendData=FormatCommand(strToSend, Address);
	TRACE(m_strSendData);
	Mscomm->put_Output(COleVariant( m_strSendData));
	m_bWaitForResponse=true;
	//return 0;
}
void CPlcCommu::SendMultiFrameData(CString& strToSend, CString& Address,unsigned FramePos,CMscomm* Mscomm)
{
		CString strSendData;
		m_uReSendCound=0;
		switch (FramePos)
		{
		case 0://ͷ֡
			strSendData=FormHeaderFrameOfMutiFrameCommand(strToSend, Address);
			break;
		case 2://β֡
			strSendData=FormFinalFrameOfMutiFrameCommand(strToSend, Address);
			break;
		default:
			strSendData=FormMiddleFrameOfMutiFrameCommand(strToSend, Address);
			break;
		}

		TRACE(strSendData);
		Mscomm->put_Output(COleVariant(strSendData));
	m_bWaitForResponse=true;
}
bool CPlcCommu::CheckFCS(CString& strToCheck,CString RetrunFCSVal)
{
	
	CString FCSVal= FCS(strToCheck);
	return FCSVal==RetrunFCSVal;
}

bool CPlcCommu::openComm(CMscomm* Mscomm)
{
	if (!Mscomm)
	{
		MessageBoxA(NULL,("��������������鴮�ڳ�ʼ��"),NULL,NULL);
		return false;
	}
	if(!Mscomm->get_PortOpen())
	{
		Mscomm->put_PortOpen(TRUE);
		MessageBox(NULL,_T("���ڴ򿪳ɹ�"),_T("�ɹ�"),NULL);
		return true;
	}
	else
		MessageBox(NULL,_T("�޷��򿪴��ڶ˿�"),NULL,NULL);
	return false;
}

bool CPlcCommu::CheckCommandResponse(CMscomm* Mscomm)
{
	if (!m_bWaitForResponse)
	{
		return true;
	}
	else
	{
		if (m_uReSendCound<MAX_RESEND_TIMES)
		{ 
			ResendCommand(Mscomm);
			m_uReSendCound++;
			Sleep(30);//�ȴ���Ӧ
			return CheckCommandResponse(Mscomm);//�ݹ����
		}
		else
		{
			MessageBox(NULL,_T("�ظ����Ͷ�����ݾ�δ���PLC��ȷ��Ӧ"),_T("Error"),NULL);
		}
	}	
	return false;
}
