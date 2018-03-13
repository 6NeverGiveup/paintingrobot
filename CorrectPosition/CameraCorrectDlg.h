
// CameraCorrectDlg.h : ͷ�ļ�
//

#pragma once
#include  "windows.h"

//#include ".\CameraCorrect\MyDib.h"
//#include ".\CameraCorrect\256Dib.h"
#include "MyDib.h"
#include "256Dib.h"
#include "svPTGrab2.h"
#include "RoadLineDetect.h"
#include "RoadRecOnHalconWithPtgrey.h"
#include "ProTime.h"
#include "afxcmn.h"
UINT ClientRecvThread(LPVOID lpParm );
// CCameraCorrectDlg �Ի���
class CCameraCorrectDlg : public CDialogEx
{
// ����
public:
	CCameraCorrectDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CameraCorrect_DIALOG };

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
	//float m_X_Correct;
	BOOL m_JudgeCameraFirst;
	BOOL m_JudgeCameraTwoFirst;
	CString m_Y_Correct;
	CString m_X_Correct;
	CString m_Angle_Correct;
	CString m_Y_CorrectTwo;
	CString m_X_CorrectTwo;
	ThresholdSlide m_Thresholderl;
	afx_msg void OnBnClickedOpenCamera();
	bool InitHalconDisp(void);
	bool InitHalconDispTwo(void);  //��ʼ���ڶ������
	void ConnectCamera();          //���ӣ���򿪣����
	void ConnectCameraTwo();       //���ӣ���򿪣��ڶ������
	void ConnectServer();
	void SendValue(CString parm);
	static void WINAPI GrabDisplayCallback(void* pOwner,PTStatus status, unsigned char* pImgData, long lWidth, long lHeight, PTPixelFormat pixelFormat);
	static void WINAPI GrabDisplayCallbackTwo(void* pOwnerTwo,PTStatus statusTwo, unsigned char* pImgDataTwo, long lWidthTwo, long lHeightTwo, PTPixelFormat pixelFormatTwo);
	void grab();
	void grabTwo();
	void DrawImage(int nWidth,int nHeight);
	void DrawImage2(int nWidth,int nHeight);
	void DrawImageTwo(int nWidthTwo,int nHeightTwo);   //�ڶ��������ʾԭͼ
	void CreateMyDibFromMemory(PBYTE pImage, int nWidth, int nHeight);
	void CreateMyDibFromMemoryTwo(PBYTE pImageTwo, int nWidthTwo, int nHeightTwo);     //�ڶ��������ʾԭͼ
	bool RoadRec(unsigned char* pImgData, long lWidth, long lHeight);
	bool RoadRecTwo(unsigned char* pImgDataTwo, long lWidthTwo, long lHeightTwo);
	// �ر��������̵߳�ʵ�壬��������߳��˳�ʱ�䲻ͬ�����µĴ���
	bool DestroyOtherThreadsObj(void);
public:
	bool m_bTerminateThread;
	char * IP;
	CString tempStr;
	// �ͻ���socket
	SOCKET m_sockClient;
	struct sockaddr_in m_serverAddr;
	unsigned short m_nServerPortNo;
	CString m_strSendData;  //�������ݴ������
	char *m_strSendDatachar;
	int m_lWidth;
	int m_lHeight;
	int m_lWidthTwo;        //�ڶ���������ؿ��
	int m_lHeightTwo;		//�ڶ���������ظ߶�
	C256Dib m_dib1;
	CMyDib  *m_DibPict;
	scPTGrab2* m_Acq;
	CMyDib  *m_DibPictTwo;                //�ڶ������ʵ��������
	scPTGrab2 *m_AcpTwo;
	BOOL m_bIsGrab;	
	BOOL m_bIsGrabTwo;
	bool m_bDestroyNow;///<���ɼ��������߳̿�ʼ�˳�ʱ��ֵΪ�棬��������߳��˳���ͬ�����µ����⡣
	bool m_bDestroyNowTwo; ///<���ɼ��������߳̿�ʼ�˳�ʱ��ֵΪ�棬��������߳��˳���ͬ�����µ����⡣
	CMyDib*			m_pMyDib;								//DIBָ��
	CMyDib*         m_pMyDibTwo;                            //DIBָ��
	LocationCorrect m_CameraCorrectX_Y_Angle;
	LocationCorrect m_CameraCorrectX_Y_AngleTwo;
	CProTime  m_time;
	CProTime m_timeTwo;
	CRoadRecOnHalconWithPtgrey m_HalconRoadRec;//ʶ��ģ��
	CRoadLineDetect  m_HalconRoadDet;
	bool m_bSoftTraggerOn;
	CSliderCtrl m_ThresholdMinGrey;
	CSliderCtrl m_ThresholdMaxGrey;
	ThresholdSlide m_ThresholdSliderl;
	ThresholdSlide m_ThresholdSliderlTwo;
	afx_msg void OnNMCustomdrawThresholdmingrey(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawThresholdmaxgrey(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
	CString StreamBegin;
	CString StreamEnd;
	CWinThread *m_CaptureThread;
	afx_msg void OnNMCustomdrawThresholdmintwo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawThrehsoldmaxtwo(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_ThresholdMinGreyTwo;
	CSliderCtrl m_ThresholdMaxGreyTwo;
	double Angle;
};
