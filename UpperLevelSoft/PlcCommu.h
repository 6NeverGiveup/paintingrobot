#pragma once
#include "mscomm.h"
#include <string>
#define MAX_RESEND_TIMES 5///<���ִ���ʱ���ظ�������һ��������������������򱨴�
class CPlcCommu
{
public:
	CPlcCommu(void);
	~CPlcCommu(void);
	void InsertMsCom(CMscomm* Mscomm)
	{	 m_Mscomm=Mscomm;	}
	static CMscomm* m_Mscomm;///<�Դ�Ĵ���ͨѶʵ������
	/**
	*@brief ����CMscomm�࣬�����ʼ��
	*
	* 
	*@param CMscomm1& Mscomm ��Ҫ��ʼ����mscomm�� 
	*@param PortNum �˿ں�
	*
	*@return 
	*@todo 
	*/
	bool InitComm(unsigned PortNum,CMscomm* Mscomm= m_Mscomm);
	/**
	*@brief ����CMscomm�࣬����رն˿�
	*
	* 
	*@param CMscomm1& Mscomm ��Ҫ�رն˿ڵ�mscomm�� 
	*
	*@return �ɹ��رշ����� 
	*@todo 
	*/
	bool  CloseComm(CMscomm* Mscomm= m_Mscomm);
	/**
	*@brief ����ͨѶ���ܣ������˽����¼����ж����յ��ˣ����н���
	*
	*@param CMscomm1& Mscomm ����ͨѶ��ʵ��
	*@return �������������ݾ�FCSУ�飬��ʾ�Ե�ʱ�򣬷����棬���򷵻ؼ�
	*@todo ����ֻ�����˽�������������ݣ������¼������һ������
	*/
	bool OnReceieveCom(CMscomm* Mscomm= m_Mscomm);
	char m_rxdata[100];///<��������յ��Ļظ�
	CString m_ReceviedDat;///<��������յ��Ļظ�
	/**
	*@brief ��������֡����FCSֵ������β
	*
	*
	*@parm strToSend �������ݣ�������ͷβ
	*
	*@return �������Ӻ������֡
	*@todo
	*/
	CString FCS(CString& strFrame);
	/**
	*@brief ������֡����FCSֵ������β��ͷ
	*
	*
	*@parm strToSend �������ݣ�������ͷβ
	*
	*@return �������Ӻ������֡
	*@todo
	*/
	CString FormatCommand(CString& strFrame,CString& Address)
	{		
		SendCommand.Empty();
		SendCommand=Address+strFrame;
		SendCommand.Insert(0,m_csDataWriteCommandHeader);//00��UnitNumber
		//SendCommand=SendCommand+FCS(SendCommand)+'*'+'\r';
		SendCommand=SendCommand+FCS(SendCommand)+m_csCommandTail;
		//CString FrameEnd;
		//FrameEnd.Format ("%02X",intMidData,'*','\n');//2��ʾ���Ϊ2,ʵ��λ����������ʵ���ߣ�0��ʾ�ڲ���λ��0,
		
		return SendCommand;
	}
/**
*@brief �γɶ�֡�������֡����
*
*
*@parm
*
*@return
*@todo
*/
	CString FormHeaderFrameOfMutiFrameCommand(CString& strFrame,CString& Address)
	{
		SendCommand.Empty();
		SendCommand=Address+strFrame;
		SendCommand.Insert(0,m_csDataWriteCommandHeader);//00��UnitNumber
		//SendCommand=SendCommand+FCS(SendCommand)+'*'+'\r';
		SendCommand=SendCommand+FCS(SendCommand)+m_cEnter;
		return SendCommand;
	}
	CString FormMiddleFrameOfMutiFrameCommand(CString& strFrame,CString& Address)
	{
		SendCommand.Empty();
		//SendCommand=Address+strFrame;
		SendCommand=strFrame;		
		SendCommand=SendCommand+FCS(SendCommand)+m_cEnter;
		return SendCommand;
	}
	CString FormFinalFrameOfMutiFrameCommand(CString& strFrame,CString& Address)
	{
		SendCommand.Empty();
		SendCommand=strFrame;
		//SendCommand.Insert(0,m_csDataWriteCommandHeader);//00��UnitNumber
		//SendCommand=SendCommand+FCS(SendCommand)+'*'+'\r';
		SendCommand=SendCommand+FCS(SendCommand)+m_csCommandTail;
		return SendCommand;
	}
	/*CString FormHeaderOfCommand(CString& Address)
	{
		CString Header="@00WD";
		return Header;
	}*/
	//CString FormTailOfCommand()
	//{
	//	return CString Tail("*/r");
	//}

	/**
	*@brief ���·�������
	*
	*���·�������SendCommand�е����ݣ�����m_uReSendCound��+1
	*@parm 
	*
	*@return 
	*@todo
	*/
	void ResendCommand(CMscomm* Mscomm= m_Mscomm)
	{
		Mscomm->put_Output(COleVariant(SendCommand));
		m_uReSendCound++;
	}
/**
*@brief ����ӿں�������������֡
*
*
*@parm Mscomm ����ͨѶ��
*@parm strToSend �������ݣ�������ͷβ
*
*@return
*@todo
*/
	void SendSingleFrameData(CString& strToSend, CString& Address,CMscomm* Mscomm= m_Mscomm);
	/**
	*@brief ����ӿں��������Ͱ����������֡������
	*
	*�򵥸���������ƣ��Գ������������ݣ��ֽ�Ϊ��֡��
	*@parm Mscomm ����ͨѶ��
	*@parm strToSend �������ݣ�������ͷβ
	*@parm FramePos ��ǰ����֡���������������е�λ�ã���ͷΪ0����βΪ2���м�Ϊ1��Ĭ�ϣ�
	*
	*@return
	*@todo
	*/

	void SendMultiFrameData(CString& strToSend, CString& Address,unsigned FramePos=1,CMscomm* Mscomm= m_Mscomm);
	/**
	*@brief ��鷴��������FCS�Ƿ�У����ȷ��
	*
	*
	*@parm Mscomm ����ͨѶ��
	*@parm strToSend �������ݣ�������ͷβ
	*
	*@return
	*@todo
	*/
	bool CheckFCS(CString& strToCheck,CString FCSVal);
protected:
	CString SendCommand;///<��Ҫ���͵�������ڴ�
	const CString m_csDataWriteCommandHeader;///<д��������ָ��ͷ
	const char m_cEnter;///<�س���
	CString m_csCommandTail;///<����β
	unsigned m_uReSendCound;///<��FCSʧ�����·�������Ĵ���
	bool m_bWaitForResponse;///<�����˵ȴ��ظ��������з��;��лظ�����ȷ����Ϊ�٣�����Ϊ��
public:
/**
*@brief �򿪴���
*
*
*@parm
*
*@return �򿪳ɹ��򷵻���
*@todo
*/
	bool openComm(CMscomm* Mscomm= m_Mscomm);
/**
*@brief ���PLC���ͻ�������Ӧ�����������ظ�������������
*
* ���PLC���ͻ�������Ӧ������Ӧ�����ʾ�������ظ������������� MAX_RESEND_TIMES �Σ�
*ֱ���ﵽ������������Ӧ��ȷ
*@parm
*
*@return
*@todo
*/
	bool CheckCommandResponse(CMscomm* Mscomm= m_Mscomm);
};
