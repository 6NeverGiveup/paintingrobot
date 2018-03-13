
// UpperLevelSoftDlg.h : ͷ�ļ�
//
#pragma once
#include "RecognizePicture.h"
#include "Parm.h"
#include "DetailSettingDlg.h"
#include "ResultAdapter.h"
#include "CButtonST�ļ�/BtnST.h"
#include "./CButtonST�ļ�/WinXPButtonST.h"
#include "./CButtonST�ļ�/ShadeButtonST.h"
#include "..\upperlevelsoft\cbuttonst�ļ�\btnst.h"
#include "..\upperlevelsoft\cbuttonst�ļ�\btnst.h"
#include "mscomm.h"
#include "PlcCommu.h"
#include "afxwin.h"
#include "..\upperlevelsoft\cbuttonst�ļ�\btnst.h"
#include "..\upperlevelsoft\cbuttonst�ļ�\btnst.h"
#include "..\upperlevelsoft\cbuttonst�ļ�\btnst.h"
#include "..\upperlevelsoft\cbuttonst�ļ�\btnst.h"
#include "..\upperlevelsoft\cbuttonst�ļ�\btnst.h"
#include "..\upperlevelsoft\cbuttonst�ļ�\btnst.h"
#include "PaintDlg.h"
#include "DownParmValue.h"
#include "LowMoniter.h"
#include "SharpRed.h"
#include "math.h"
#include ".\pmac\runtime.h"
#include ".\pmac\Include\dialog.h"
#include ".\PMAC\Include\UtilDT.h"

//#include "ParkerMotionCardCommu.h"
UINT ServerRecvThread(LPVOID lpParm );
UINT ClientRecvThread(LPVOID lpParm );     //�����õ��߳�
struct JudgeIsOperationOrder
{
	BOOL ReadPicyureBtnDown;
	BOOL InvalidColorBtnDown;
	BOOL ReconfigureBtnDown;
	BOOL DrawAreaIdentificationResultsBtnDown;
	BOOL ConnectBtnDown;
	BOOL DesignatedWorkAreaBtnDown;
	BOOL IsWashGunBtnDown;
};
struct CameraPosition
{
	float FirstCameraX;
	float FirstCameraY;
	bool  Firstcameradignose;
	float SecondCameraX;
	float SecondCameraY;
	bool  Secondcameradignose;
};

// CUpperLevelSoftDlg �Ի���
class CUpperLevelSoftDlg : public CDialogEx
{
// ����
public:
	CUpperLevelSoftDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UPPERLEVELSOFT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1ReadPic();
private:
	bool InitSystemParm(bool ReInit=false);
	bool ReadPicture2(bool FirstUSE,bool bIsRead);
	void InitPaintMachineParm(bool ReInit=false);
	bool ShowBMP2(bool bFirstShow=true,bool bIsRead=true);
	long OnSetVelAndRealRatio(WPARAM CellRealWidth,LPARAM Vel);
	long OnSetGunParm (WPARAM GunP,LPARAM GunMode);
	bool DistinctMap(CDC* pTargetDC);
	void EraseAll(CDC* pTargetDC,CRect& rect);
	bool ShowRecResOfGivenReg(CPoint& ChosedPoint);
	bool SelectRegDownLoadParm(CPoint& ChosedPoint);
	bool ShowRecResOnMap(CDC* pTargetDC,unsigned IndexOfReg);
	void StorePictureToShow();               //��PICTUREͼƬ�ؼ���û�м���ͼƬʱ��������ʾ����ͼƬ���˺������ڼ���ͼƬ������һ��vector��
	int ShowRecResultDat(void);
	int ShowColorReced(void);
	void DownLoadPlcParm(unsigned RegIndex);
	bool DownLoadParmToMotionControlCard(void);
	void TranslateAllParmToNewStlye(void)
	{
		m_DownValue.GetDownValueMotion(m_itMotionParmVecBegin,m_itMotionParmVecEnd);           //17.12.19�޸�
		m_DownValue.GetDownValuePlc(m_Storage,m_cResAdapter.ReturnChangedColorPointBegin(),m_cResAdapter.ReturnChangedColorPointEnd(),m_uGunNum,m_fGunDis); //����λ����PLC����

	}
	CResultAdapter<CRecognizePicture,CPaintCell>::PLC_Parm_It_TYPE m_itPlcParmVecBegin;///<PLC��������ͷ
	CResultAdapter<CRecognizePicture,CPaintCell>::PLC_Parm_It_TYPE m_itPlcParmVecEnd;///<PLC��������β
	std::vector<int> m_Storage;///<PLC����ת��
	MotionParm_It_TYPE  m_itMotionParmVecBegin;//<�˶���������ͷ
	MotionParm_It_TYPE m_itMotionParmVecEnd;///<�˶���������β
	/**
*@brief ����ʵ���ٶ��Լ�ͼƬ���ص�ʵ�ʵı���
*
*�������н����˲�����ת����Vel��mm/sת��Ϊת/s,����������뵽CResultAdapter���С�ע����⸡�㵽���ε��µľ�����ʧ����Ԥ����1000
*
*@parm WPARAM CellRealWidth ʵ���е�����Ԫ�Ŀ�� mm,Ϊ���⸡�㵽���ε��µľ�����ʧ����Ԥ����1000��
*@parm WPARAM Vel ʵ���������ٶ�mm/s,Ϊ���⸡�㵽���ε��µľ�����ʧ����Ԥ����1000��
*
*@return
*@todo
*/
	
	/**
	*@brief ����ʵ��ǹ�Ĳ���
	*
	*�������н����˲�����ת����Vel��mm/sת��Ϊת/s,����������뵽CResultAdapter���С�ע����⸡�㵽���ε��µľ�����ʧ����Ԥ����1000
	*
	*@parm WPARAM GunNum ǹ��,Ϊ���⸡�㵽���ε��µľ�����ʧ����Ԥ����1000��
	*@parm WPARAM GunDisǹ��,Ϊ���⸡�㵽���ε��µľ�����ʧ����Ԥ����1000��
	*
	*@return
	*@todo
	*/
	//long OnSetGunParm (WPARAM GunNum,LPARAM GunDis);
	/*@brief ����ʵ��ǹ�Ĳ���
	*
	*��ǰһ�汾��ͬ�����ﴫ��Ĳ�����һ���ṹ���ָ�룬������ͨ����Ϣ���ݸ��������������һ��Ǳ������
	*����Ϣ����ʱҪ��ָ����Ч��Ȼ����㲻�ܱ�֤��
	*�������н����˲�����ת����Vel��mm/sת��Ϊת/s,����������뵽CResultAdapter���С�ע����⸡�㵽���ε��µľ�����ʧ����Ԥ����1000
	*
	*@parm WPARAM GunP GunParm�ṹ���ָ�룬ָ����Ϣ����һ��GunParm�ṹ��������������Ϊ���е�ǹ����������ǹ����ǹ��Ԥ�ȳ���1000��
	*@parm WPARAM GunMode��ǹѡ���ģʽ��1Ϊ����ǹ��2Ϊ����3Ϊ��Ѷ�ɫ��ǹ��
	*
	*@return
	*@todo
	*/
	long SavePmcDiretory(WPARAM Value_Gun,LPARAM descirble);
	long OnSetWorkRegParm (WPARAM WorkRegWidth,LPARAM WorkRegHeight);
	
private:
	float m_fRealRatio;//
	float m_fYRealRatio;     //Y����������ʵ�ʳߴ����ϵ��
	float m_fRealVel;
	CDC CPicDC;//ԭʼͼƬ
	CResultAdapter<CRecognizePicture,CPaintCell> m_cResAdapter;///<��ʶ������Ҫ���������ʵ��
	bool m_bLowerConnectStatu;///<����λ��������״̬��PLC,�˶����ƿ���������Ϊ�棬����Ϊ��
	void InterfaceBeautification();          //��������
	DownValue m_DownValue;                            //���ز�����
	#ifdef USE_CONTENT_IN_DEPENDENT_CLASS 
	//CParkerMotionCardCommu m_cMotionCommu;///<����ͨѶ��ʵ������
	#endif
public:
	JudgeIsOperationOrder m_JudgeIsOperationOrder;
	unsigned int m_uRegToBeDownLoad;///<��Ҫ���ز����Ĺ�����
	/*int m_iGUIValOfCellWidth;
	int m_iGUIValOfCellHeight;
	int m_iGUINumOfRecedCell;
	int m_iGUIColorNum;*/
	
public:
	unsigned m_uGunNum;
	float m_fGunDis;
	int m_PerGunColor;
	unsigned m_fWorkRegWidth;///<��������ȴ�С����λ����
	unsigned m_fWorkRegHeight;///<�������߶ȴ�С����λ����
	CRecognizePicture m_cRecgnizePic;
	/*CButtonST m_btnColor1;
	CButtonST m_btnColor2;
	CButtonST m_btnColor3;
	CButtonST m_btnColor4;
	CButtonST m_btnColor5;
	CButtonST m_btnColor6;*/
	CButtonST m_ReadPicture;
	CWinXPButtonST m_ReadPicture1;
	CShadeButtonST m_ReadPicture2;
	CWinXPButtonST m_HighDesign;
	/*CButtonST m_cNullColorBtn;*/
	#define CELL_COLOR RGB(0,10,0)
	CRect m_ClientRect;  
	std::vector<CString>::iterator m_StorePictureIterator;
	std::vector<CString> m_StorePicture;              //���������ʾ����ͼƬ�ĵ�ַ
private:
	struct SRatioOfShow2Map
	{
		double xRatio;///<��ʾ�ϵ�x����ͼƬ�е�X�õ��ı���
		double yRatio;///<��ʾ�ϵ�y����ͼƬ�е�y�õ��ı���
	}m_sSHow2MapRatio;///<��������ʾͼƬʱ�Ǿ������ŵģ������ʾ��������ʾ���������ͼ֮��ı�����ϵ��
	void TransforShowCoordIntoMapCoord(CPoint & PointOnShow)
	{
		PointOnShow.x=PointOnShow.x*m_sSHow2MapRatio.xRatio;
		PointOnShow.y=PointOnShow.y*m_sSHow2MapRatio.yRatio;
	}
	//double m_SHow2MapRatio;
	bool m_bSetNullColor;///<��ǰ��Ҫѡȡ��������Ч��ɫ
	bool m_bSelectRegToDown;///<����־λΪ���ʾ��������Ҫѡ�����������Խ����������
	bool m_bUSE_CRossCursor;///<��Ҫ���������Ϊʮ����
	bool m_bChoseRegToShow;///<Ҫָ��ʶ����Ĺ������Թ���ʾ
	bool m_bReadedPic;///<������ͼƬ�����Խ���ʶ��Ȳ�����
	bool m_bRecedPic;///<������ʶ�𡣱�����������InitSystemParm�����б���ʼ���������ˡ������������ʼ��
	//bool m_bRecedResultValid;
	//bool m_bFirstShow;///<�Ƿ��һ����ʾͼƬ��
	CBitmap m_cLoadedMap;///<װ�ص�ͼƬ
	double X_Correct;
	double Y_Correct;
	double Angle_Correct;
public:
	afx_msg void OnBnClickedDetailSetting();
	afx_msg void OnBnClickedButton2SetNullCollor();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CButtonST m_cNullColorBtn;
	CButtonST m_cGUI_ConectBtn;
	CPlcCommu m_cPlcCommu;///<PLCͨѶʵ��
	CMscomm m_cmscom;///<����ͨѶʵ��
	unsigned int m_uCommPortNum_PLC;///<��PLCͨѶ���õĴ��ڶ˿ں�
	int m_iGUISelectRegOrAll;///<ѡ������һ�����Ĳ���(0)��ȫ���������Ĳ�����
public:
	void GetOwnSelfIp();
	void CreateServer();
	bool m_bServerCreated;
	bool m_bTerminateThread;
	SOCKET m_sockServer;
	// �������˿ں�
	unsigned short m_nPortNO;
	struct sockaddr_in m_clientAddr;
	CString CompileCameraParm(CString InputMessage,int num);
	CButton m_RecButton;
	afx_msg void OnBnClickedRecgnizeForMachine();
	CButtonST m_btnColor1;
	CButtonST m_btnColor2;
	CButtonST m_btnColor3;
	CButtonST m_btnColor4;
	CButtonST m_btnColor5;
	CButtonST m_btnColor6;
	afx_msg void OnBnClickedButton2SetRegionToShow();
	afx_msg void OnBnClickedRaRegToDown();
	afx_msg void OnBnClickedBtnConnectDown();
	afx_msg void OnBnClickedSelectReg();
	afx_msg void OnBnClickedDownParm();
	afx_msg void OnBnClickedAction();
	int m_iGUINumOfRecedCell;
	int m_iGUIColorNum;
	int m_iGUIValOfCellWidth;
	int m_iGUIValOfCellHeight;
	CString SaveDirectoryUpFile; 
	SharpRedMeasure m_SharpRedMeasure; //���⴫������ʵ����
	afx_msg void OnBnClickedLowMoniter();
//#ifdef USE_CONTENT_IN_DEPENDENT_CLASS 
//	CParkerMotionCardCommu m_cMotionCommu;///<����ͨѶ��ʵ������
//#endif

	afx_msg void OnBnClickedOpensharp();
	int c;
	void JudgeFloorIsFlat(int FirstDistance,int SecondDistance,int ThirdDistance);
	CString m_JudgeFloorIsFlatL;
	int m_SharpJudgeThreshold; //������ֵ
private:
	////////////////////////////////////
	//�������еĺ����ͱ���������������λ��ͨ���õ�
	bool AGV_Init(DWORD* dwDevice);
	bool bAGV_InitState;//AGV��ʼ����־λ���ɹ�ΪTRUE,ʧ��ΪFALSE
	long OnBnClickedPumppowerOn (WPARAM ValueOne,LPARAM ValueTwo);  //���û�����
	long OnBnClickedStartmotorOn(WPARAM ValueOne,LPARAM ValueTwo); //��������� 
	long OnBnClickedPumppowerOff(WPARAM ValueOne,LPARAM ValueTwo);  //���û�����
	long OnBnClickedStartmotorOff(WPARAM ValueOne,LPARAM ValueTwo); //��������� 
	long OnBnClickedReturn(WPARAM ValueOne,LPARAM ValueTwo);
	long OnBnClickedQuit(WPARAM ValueOne,LPARAM ValueTwo);
	long OnBnClickedDownload(WPARAM ValueOne,LPARAM ValueTwo);
	long OnBnClickedRun(WPARAM ValueOne,LPARAM ValueTwo);
	long OnBnClickedStop(WPARAM ValueOne,LPARAM ValueTwo);     //��ͣ��Ӧ����
	long OnBnClickedStopall(WPARAM ValueOne,LPARAM ValueTwo);  //ֹͣ��Ӧ����
	long OnBnClickedContinue(WPARAM ValueOne,LPARAM ValueTwo); //������Ӧ����
	long OnBnClickedWash(WPARAM ValueOne,LPARAM ValueTwo);
	long OnBnClickedStopwash(WPARAM ValueOne,LPARAM ValueTwo);
	long OnBnClickedAlignment(WPARAM ValueOne,LPARAM ValueTwo);
	long OnBnReleaseAlignment(WPARAM ValueOne,LPARAM ValueTwo);
	//JudgeUnitIsOutOfRange()���������ж��ڵ�ǰ����ϵ�£�����Ϳ��Ԫ�Ƿ񳬳���Ϳ����,����ÿһ������Ϳ����������pmc�ļ�֮ǰ���������Ƿ񳬳��޳�
	CoordinateFrame JudgeUnitIsOutOfRange(float FirstCameraX,float FirstCameraY,float SecondCameraX,float SecondCameraY,int UintWidth,int Width,int Height,bool OneGun=true);
	CoordinateFrame m_CoordinateFrame;
	bool bInitState;
	DWORD mydwDevice;//AGV_Init�������β�
	CString m_Connect;
	bool m_Connected;
	//////////////////////////////////
public:
	afx_msg void OnBnClickedOk();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnBnClickedRaRegToDown1();
	int m_PointWorkSize;
	CameraPosition m_CameraPosition;
	float PerUnitWidth;
protected:
	double m_fGunDelay[4][2] ;//�ȿ������,ÿ��һ����ǹ�������˶�ʱ�ĵ�����ʱ
	double m_fRevGunDelay[4][2];//�ȿ������,ÿ��һ����ǹ,�����˶�ʱ�ĵ�����ʱ
	long OnSetGun0DelayParm (WPARAM OpenDelay,LPARAM CloseDelay);
	//float m_fGun0Delay[2] ;//�ȿ������
	long OnSetGun1DelayParm (WPARAM OpenDelay,LPARAM CloseDelay);
	//float m_fGun1Delay[2] ;//�ȿ������
	long OnSetGun2DelayParm (WPARAM OpenDelay,LPARAM CloseDelay);
	//float m_fGun2Delay[2] ;//�ȿ������
	long OnSetGun3DelayParm (WPARAM OpenDelay,LPARAM CloseDelay);
	//float m_fGun3Delay[2] ;//�ȿ������
	long OnSetGun0RevDelayParm (WPARAM OpenDelay,LPARAM CloseDelay);
	//float m_fGun0Delay[2] ;//�ȿ������
	long OnSetGun1RevDelayParm (WPARAM OpenDelay,LPARAM CloseDelay);
	//float m_fGun1Delay[2] ;//�ȿ������
	long OnSetGun2RevDelayParm (WPARAM OpenDelay,LPARAM CloseDelay);
	//float m_fGun2Delay[2] ;//�ȿ������
	long OnSetGun3RevDelayParm (WPARAM OpenDelay,LPARAM CloseDelay);
protected:
		bool UpdateAllTextOnColorRecBtn(void);
	/**
	*@brief �����֣����ҳ���������Ϊ���ݵ��ַ���������ָ��
	*
	*
	*@parm
	*
	*@return
	*@todo
	*/
	char *strFromUns(unsigned u)   
	{   
		static char strDigits[] = "987654321";  
		/* 5���ַ�+��\0�� */   
		char *pch;
		/* u ������Χ����ʹ��UlongToStr �� */  
		ASSERT(u<=65535);  
		/* ��ÿλ�����Ժ���ǰ�洢��strDigits�� */  
		pch = &strDigits[10];  
		ASSERT(*pch == '\0');  
		do   
		*--pch = u%10 + '0';  
		while((u/=10)>0);  
		return(pch);  
	}
	bool ShowColorIndexInButonText(unsigned IndexOfRecedColor);
	afx_msg void OnBnClickedButton2ColorReced2();
	//int ShowColorReced(void);
	afx_msg void OnBnClickedButton2ColorReced();
	afx_msg void OnBnClickedButton2ColorReced3();
	afx_msg void OnBnClickedButton2ColorReced4();
	afx_msg void OnBnClickedButton2ColorReced5();
	afx_msg void OnBnClickedButton2ColorReced6();
};
