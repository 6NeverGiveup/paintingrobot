
// CameraCorrectDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CameraCorrect.h"
#include "CameraCorrectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCameraCorrectDlg �Ի���




CCameraCorrectDlg::CCameraCorrectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCameraCorrectDlg::IDD, pParent)
	, m_Y_Correct(_T(""))
	, m_X_Correct(_T(""))
	, m_Angle_Correct(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_JudgeCameraFirst=FALSE;
	m_JudgeCameraTwoFirst=FALSE;
	m_nServerPortNo=100;            //ͨ�Ŷ˿ں�
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Acq   =  NULL;
	m_pMyDib = NULL;
	m_AcpTwo=NULL;
	m_pMyDibTwo=NULL;

	m_bIsGrab = FALSE;
	m_bIsGrabTwo=FALSE;
	m_bSoftTraggerOn = false;
	m_lWidth = 0;
	m_lHeight = 0;
	m_lWidthTwo=0;
	m_lHeightTwo=0;
	m_DibPict = NULL;
	m_bDestroyNow=false;
	m_bDestroyNowTwo=false;
	m_X_Correct="0.0";
	m_Y_Correct="0.0";
	m_Angle_Correct="0.0";
	m_CameraCorrectX_Y_Angle.X_Correct=0;
	m_CameraCorrectX_Y_Angle.Y_Correct=0;
	m_CameraCorrectX_Y_AngleTwo.X_Correct=0;
	m_CameraCorrectX_Y_AngleTwo.Y_Correct=0;
	m_Thresholderl.MinGreyThreshold=25;
	m_Thresholderl.MaxGreyThreshold=90;
	m_ThresholdSliderl.MinGreyThreshold=25;
	m_ThresholdSliderl.MaxGreyThreshold=90;
	m_ThresholdSliderlTwo.MinGreyThreshold=25;
	m_ThresholdSliderlTwo.MaxGreyThreshold=90;
	StreamBegin="Begin";
	StreamEnd="End";
}

void CCameraCorrectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC1, m_Y_Correct);
	DDX_Text(pDX, IDC_STATIC0, m_X_Correct);
	DDX_Text(pDX, IDC_STATIC2, m_Angle_Correct);
	DDX_Control(pDX, IDC_THRESHOLDMINGREY, m_ThresholdMinGrey);
	DDX_Control(pDX, IDC_THRESHOLDMAXGREY, m_ThresholdMaxGrey);
	DDX_Control(pDX, IDC_THRESHOLDMINTWO, m_ThresholdMinGreyTwo);
	DDX_Control(pDX, IDC_THREHSOLDMAXTWO, m_ThresholdMaxGreyTwo);
}

BEGIN_MESSAGE_MAP(CCameraCorrectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_CAMERA, &CCameraCorrectDlg::OnBnClickedOpenCamera)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_THRESHOLDMINGREY, &CCameraCorrectDlg::OnNMCustomdrawThresholdmingrey)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_THRESHOLDMAXGREY, &CCameraCorrectDlg::OnNMCustomdrawThresholdmaxgrey)
	ON_BN_CLICKED(IDOK, &CCameraCorrectDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CCameraCorrectDlg::OnBnClickedButton2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_THRESHOLDMINTWO, &CCameraCorrectDlg::OnNMCustomdrawThresholdmintwo)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_THREHSOLDMAXTWO, &CCameraCorrectDlg::OnNMCustomdrawThrehsoldmaxtwo)
END_MESSAGE_MAP()


// CCameraCorrectDlg ��Ϣ�������

BOOL CCameraCorrectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_ThresholdMinGrey.SetRange(0,255);
	m_ThresholdMinGrey.SetPos(25);
	m_ThresholdMinGrey.SetTicFreq(1);
	m_ThresholdMaxGrey.SetRange(0,255);
	m_ThresholdMaxGrey.SetPos(90);
	m_ThresholdMaxGrey.SetTicFreq(1);
	m_ThresholdMinGreyTwo.SetRange(0,255);
	m_ThresholdMinGreyTwo.SetPos(25);
	m_ThresholdMinGreyTwo.SetTicFreq(1);
	m_ThresholdMaxGreyTwo.SetRange(0,255);
	m_ThresholdMaxGreyTwo.SetPos(90);
	m_ThresholdMaxGreyTwo.SetTicFreq(1);

	m_bTerminateThread = false;
	//WSAStartup()
	WSADATA	wsaData;
	PHOSTENT hostinfo;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		MessageBox(_T("WSAStartup ERROR!"));
	}
	//******************************************************
	//���ÿͻ���IP��ַ���˿�
	//��ȡ����ip��ַ
	char gcTemp[255];
	if (0 == gethostname(gcTemp, 255))
	{
		hostinfo = gethostbyname(gcTemp);
		IP = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
		tempStr=IP;
		SetDlgItemText(IDC_IP_SELF,tempStr);
	}
	//create client socket
	//socket
	if ((m_sockClient = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		MessageBox(_T("ERROR: Create Client Socket Error!"));
		exit(-1);
	}
	ConnectServer();
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCameraCorrectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCameraCorrectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCameraCorrectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCameraCorrectDlg::OnBnClickedOpenCamera()
{
	if (m_JudgeCameraFirst==FALSE)
	{
		m_JudgeCameraFirst=TRUE;
		InitHalconDisp();
		ConnectCamera();
	}
	else
	{
		MessageBox(_T("�����ظ��������"),_T("��ʾ"),MB_ICONINFORMATION);
	}
}
bool CCameraCorrectDlg::InitHalconDisp(void)
{
	CRect re;
	GetDlgItem(IDC_PICTURE2)->GetWindowRect(&re); 
	ScreenToClient(&re);
	CWnd*pParent=GetDlgItem(IDC_PICTURE2)->GetParent();
	//typedef INT4_8  Hlong;
	Hlong MainWndID =(Hlong) m_hWnd;
	m_HalconRoadRec.Init(MainWndID,re);
	return false;
}
bool CCameraCorrectDlg::InitHalconDispTwo(void)           //��ʼ���ڶ�������
{
	CRect m_Rect;
	GetDlgItem(IDC_PICTURE4)->GetWindowRect(&m_Rect); 
	ScreenToClient(&m_Rect);
	CWnd*pParent=GetDlgItem(IDC_PICTURE4)->GetParent();
	Hlong MainWndID =(Hlong) m_hWnd;
	m_HalconRoadRec.InitTwo(MainWndID,m_Rect);
	return false;
}
void CCameraCorrectDlg::ConnectCamera()
{
	m_DibPict = new CMyDib();
	m_Acq = new scPTGrab2();
	m_Acq->SetOwner(this,GrabDisplayCallback);
	if (!m_Acq->InitFromIndex(0))
	{
		AfxMessageBox("�����ʼ��ʧ�ܣ�");
		m_Acq->Destroy();

	}
	else
	{
		m_lWidth = m_Acq->m_lWidth;
		m_lHeight = m_Acq->m_lHeight;
		m_Acq->CreateGrabThread();//////////////////////pointgray �Ĳɼ��߳�
		grab();
	}
}
void CCameraCorrectDlg::ConnectCameraTwo()             //���ӵڶ������
{
	m_DibPictTwo=new CMyDib();
	m_AcpTwo=new scPTGrab2();
	m_AcpTwo->SetOwner(this,GrabDisplayCallbackTwo);
	if (!m_AcpTwo->InitFromIndex(1))                      // ���������ų�ʼ�����
	{
		AfxMessageBox("�ڶ��������ʼ��ʧ�ܣ�");
		m_AcpTwo->Destroy();

	}
	else
	{
		m_lWidthTwo= m_AcpTwo->m_lWidth;
		m_lHeightTwo = m_AcpTwo->m_lHeight;
		m_AcpTwo->CreateGrabThread();					//�����ɼ��̣߳�һ���ɼ�����ֻ����һ���ɼ��߳�	
		grabTwo();
	}
}
void CCameraCorrectDlg::ConnectServer()
{
	//���÷�����ip��ַ�Լ��˿ں�
	m_serverAddr.sin_family = AF_INET;
	//��ȡ�������˵�ַ
	m_serverAddr.sin_port = htons(m_nServerPortNo);
	m_serverAddr.sin_addr.s_addr= inet_addr(IP);
	//�������������߳�
	m_bTerminateThread = false;
	m_CaptureThread=AfxBeginThread(ClientRecvThread, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
}
UINT ClientRecvThread(LPVOID lpParm )
{
	CCameraCorrectDlg *dlg = (CCameraCorrectDlg*)lpParm;
	char gcInBuffer[1027];
	int lenth;
	int size = sizeof(sockaddr_in);
	CString strReceive, tempStr;
	CString Begin="BEGIN";
	while(!dlg->m_bTerminateThread)
	{
		/*dlg->Angle=dlg->GetAngleBetweenCamera();
		CString ValueStream="";
		ValueStream.Format("%f",dlg->Angle);
		dlg->GetDlgItem(IDC_SHOWANSWER)->SetWindowText(ValueStream);
		dlg->m_strSendData=dlg->StreamBegin+','+ValueStream+','+dlg->StreamEnd;
		dlg->SendValue(dlg->m_strSendData);*/
		CString FirstCameraX;
		FirstCameraX.Format("%f",dlg->m_CameraCorrectX_Y_Angle.X_Correct);
		CString FirstCameraY;
		FirstCameraY.Format("%f",dlg->m_CameraCorrectX_Y_Angle.Y_Correct);
		CString Firstcameradignose;
		Firstcameradignose.Format("%d",dlg->m_CameraCorrectX_Y_Angle.dignose);
		CString SecondCameraX;
		SecondCameraX.Format("%f",dlg->m_CameraCorrectX_Y_AngleTwo.X_Correct);
		CString SecondCameraY;
		SecondCameraY.Format("%f",dlg->m_CameraCorrectX_Y_AngleTwo.Y_Correct);
		CString Secondcameradignose;
		Secondcameradignose.Format("%d",dlg->m_CameraCorrectX_Y_AngleTwo.dignose);
		CString ValueStream="";
		ValueStream=Begin+','+FirstCameraY+','+FirstCameraX+','+Firstcameradignose+','+SecondCameraY+','+SecondCameraX+','+Secondcameradignose+','+"FINALLY";
		dlg->SendValue(ValueStream);
	}
	return 0;
}
void CCameraCorrectDlg::SendValue(CString parm)
{
	//UpdateData(TRUE);
	/*m_strSendDatachar=(LPSTR)(LPCSTR)m_strSendData;*/
	char *m_strSendDatachar=(char *)m_strSendData.GetBuffer(m_strSendData.GetLength());
	m_strSendData.ReleaseBuffer();
	m_strSendDatachar=(LPSTR)(LPCSTR)parm;
	sendto(m_sockClient,m_strSendDatachar, strlen(m_strSendDatachar), 0,  (struct sockaddr*)&m_serverAddr, sizeof(sockaddr));
}
void CCameraCorrectDlg::GrabDisplayCallback(void* pOwner,PTStatus status, unsigned char* pImgData, long lWidth, long lHeight, PTPixelFormat pixelFormat)
{
	CCameraCorrectDlg *pDlg = (CCameraCorrectDlg*)pOwner;
	if (!pImgData) return;	
	if (pDlg->m_bDestroyNow)
	{return;}
	//double timeused = pDlg->m_time.GetTime(TRUE);
	/*CString str;*/
	//pDlg->str.Format("%4.2fms",timeused*1000);
	//pDlg->m_log.WriteLogFile(pDlg->str);
	pDlg->m_time.Reset();
	pDlg->CreateMyDibFromMemory(pImgData,lWidth, lHeight);
	if (pixelFormat==ePTRGB24/*ePTGrey8*/)
	{
		pDlg->RoadRec(pImgData,lWidth, lHeight);		//ʶ��
	}
}
void CCameraCorrectDlg::GrabDisplayCallbackTwo(void* pOwnerTwo,PTStatus statusTwo, unsigned char* pImgDataTwo, long lWidthTwo, long lHeightTwo, PTPixelFormat pixelFormatTwo)
{
	CCameraCorrectDlg *pDlg = (CCameraCorrectDlg*)pOwnerTwo;
	if (!pImgDataTwo) return;	
	if (pDlg->m_bDestroyNowTwo)
	{
		return;
	}
	pDlg->m_timeTwo.Reset();
	pDlg->CreateMyDibFromMemoryTwo(pImgDataTwo,lWidthTwo, lHeightTwo);
	if (pixelFormatTwo==ePTRGB24/*ePTGrey8*/)
	{
		pDlg->RoadRecTwo(pImgDataTwo,lWidthTwo, lHeightTwo);//ʶ��
	}
}
void CCameraCorrectDlg::grab()
{	
	if (!m_bIsGrab)
	{
		m_lWidth = m_Acq->m_lWidth;
		m_lHeight = m_Acq->m_lHeight;
		if (m_Acq->m_bIsGrabbing)
		{
			m_Acq->CloseTriggerMode();
			m_Acq->Freeze();
		}
		if (!m_Acq->Grab()) 
		{
			MessageBox(_T("�ɼ�ͼ��ʧ��"));
		}

		m_bIsGrab = TRUE;
	} 
	else
	{
		m_bIsGrab = FALSE;
		m_Acq->CloseTriggerMode();
		m_Acq->Freeze();
	}
}
void CCameraCorrectDlg::grabTwo()
{
	if (!m_bIsGrabTwo)
	{
		m_lWidthTwo =m_AcpTwo->m_lWidth;
		m_lHeight =m_AcpTwo->m_lHeight;
		if (m_AcpTwo->m_bIsGrabbing)
		{
			m_AcpTwo->CloseTriggerMode();
			m_AcpTwo->Freeze();
		}
		if (!m_AcpTwo->Grab()) 
		{
			MessageBox(_T("�ڶ�������ɼ�ͼ��ʧ��"));
		}

		m_bIsGrabTwo= TRUE;
	} 
	else
	{
		m_bIsGrabTwo = FALSE;
		m_AcpTwo->CloseTriggerMode();
		m_AcpTwo->Freeze();
	}
}
void CCameraCorrectDlg::CreateMyDibFromMemory(PBYTE pImage, int nWidth, int nHeight)
{
	if (m_pMyDib!=NULL)	
	{
		delete m_pMyDib;
		m_pMyDib = NULL;
	}
	if (m_Acq->m_pixelFormat == ePTRGB24)
		m_pMyDib= new CMyDib(m_Acq->GetImageWidth(),m_Acq->GetImageHeight(),CMyDib::FormatRgb,pImage,TRUE);	
	else	
		m_pMyDib= new CMyDib(m_Acq->GetImageWidth(),m_Acq->GetImageHeight(),CMyDib::FormatUByte,pImage,TRUE);
	DrawImage(nWidth,nHeight);
}
void CCameraCorrectDlg::CreateMyDibFromMemoryTwo(PBYTE pImageTwo, int nWidthTwo, int nHeightTwo)
{
	if (m_pMyDibTwo!=NULL)	
	{
		delete m_pMyDibTwo;
		m_pMyDibTwo = NULL;
	}
	if (m_AcpTwo->m_pixelFormat == ePTRGB24)
		m_pMyDibTwo= new CMyDib(m_AcpTwo->GetImageWidth(),m_AcpTwo->GetImageHeight(),CMyDib::FormatRgb,pImageTwo,TRUE);	
	else	
		m_pMyDibTwo= new CMyDib(m_AcpTwo->GetImageWidth(),m_AcpTwo->GetImageHeight(),CMyDib::FormatUByte,pImageTwo,TRUE);
	DrawImageTwo(nWidthTwo,nHeightTwo);
}
void CCameraCorrectDlg::DrawImage(int nWidth,int nHeight)
{
	CRect rcDIB;
	CRect rcDC;
	rcDIB = CRect(0, 0, nWidth, nHeight);
	rcDIB.OffsetRect(0, 0);	
	CDC* pDC = this->GetDlgItem(IDC_PICTURE)->GetDC();
	HDC hDispHdc = pDC->GetSafeHdc();
	pDC->GetWindow()->GetClientRect(rcDC);
	m_pMyDib->Paint(hDispHdc, rcDC, rcDIB);
	ReleaseDC(pDC);
}
void CCameraCorrectDlg::DrawImage2(int nWidth,int nHeight)
{
	CRect rcDIB;
	CRect rcDC;
	rcDIB = CRect(0, 0, nWidth, nHeight);
	rcDIB.OffsetRect(0, 0);	
	CDC* pDC = this->GetDlgItem(IDC_PICTURE2)->GetDC();
	HDC hDispHdc = pDC->GetSafeHdc();
	pDC->GetWindow()->GetClientRect(rcDC);
	m_pMyDib->Paint(hDispHdc, rcDC, rcDIB);
	ReleaseDC(pDC);
}
void CCameraCorrectDlg::DrawImageTwo(int nWidthTwo,int nHeightTwo)               // ��ʾԭͼ
{
	CRect rcDIB;
	CRect rcDC;
	rcDIB = CRect(0, 0, nWidthTwo, nHeightTwo);
	rcDIB.OffsetRect(0, 0);	
	CDC* pDC = this->GetDlgItem(IDC_PICTURE3)->GetDC();
	HDC hDispHdc = pDC->GetSafeHdc();
	pDC->GetWindow()->GetClientRect(rcDC);
	m_pMyDibTwo->Paint(hDispHdc, rcDC, rcDIB);
	ReleaseDC(pDC);
}
bool CCameraCorrectDlg::RoadRec(unsigned char* pImgData, long lWidth, long lHeight)          //ѭ��ͼƬ����
{
	m_CameraCorrectX_Y_Angle=m_HalconRoadRec.RecOneGrab(pImgData,lWidth,lHeight);
	CString m_X="";
	m_X.Format("%f",m_CameraCorrectX_Y_Angle.X_Correct);
	m_X_Correct=m_X;
	SetDlgItemText(IDC_X_CORRECT,m_X_Correct);
	CString m_Y="";
	m_Y.Format("%f",m_CameraCorrectX_Y_Angle.Y_Correct);
	m_Y_Correct=m_Y;
	SetDlgItemText(IDC_Y_CORRECT,m_Y_Correct);
	/*CString data;
	data=m_X+'A'+m_Y+'A'+m_Angle+'A';
	SendValue(data);*/
	//Invalidate();
	return false;
}
bool CCameraCorrectDlg::RoadRecTwo(unsigned char* pImgDataTwo, long lWidthTwo, long lHeightTwo)          //ѭ��ͼƬ����
{
	//UpdateData(FALSE);
	m_CameraCorrectX_Y_AngleTwo=m_HalconRoadRec.RecOneGrabTwo(pImgDataTwo,lWidthTwo,lHeightTwo);
	CString m_XTwo="";
	m_XTwo.Format("%f",m_CameraCorrectX_Y_AngleTwo.X_Correct);
	m_X_CorrectTwo=m_XTwo;
	SetDlgItemText(IDC_X_CORRECT_TWO,m_X_CorrectTwo);
	CString m_YTwo="";
	m_YTwo.Format("%f",m_CameraCorrectX_Y_AngleTwo.Y_Correct);
	m_Y_CorrectTwo=m_YTwo;
	SetDlgItemText(IDC_Y_CORRECT_TWO,m_Y_CorrectTwo);
	return false;
}
bool CCameraCorrectDlg::DestroyOtherThreadsObj(void)
{
	m_bDestroyNow=true;
	Sleep(50);
	if (m_Acq != NULL)
	{
		if (m_Acq->m_bIsGrabbing)
		{
			m_Acq->CloseTriggerMode();
			m_Acq->Freeze();
		}	
		Sleep(100);
		delete m_Acq;
		m_Acq = NULL;
	}
	return false;
}

void CCameraCorrectDlg::OnNMCustomdrawThresholdmingrey(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ThresholdSliderl.MinGreyThreshold=m_ThresholdMinGrey.GetPos();
	if (m_ThresholdSliderl.MinGreyThreshold>=m_ThresholdSliderl.MaxGreyThreshold)
	{
		m_ThresholdSliderl.MaxGreyThreshold=m_ThresholdSliderl.MinGreyThreshold;
		m_ThresholdMaxGrey.SetPos(m_ThresholdSliderl.MinGreyThreshold);
	}
	m_HalconRoadRec.ChangeThresholdSlider(m_ThresholdSliderl);
	*pResult = 0;
}


void CCameraCorrectDlg::OnNMCustomdrawThresholdmaxgrey(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	m_ThresholdSliderl.MaxGreyThreshold=m_ThresholdMaxGrey.GetPos();
	if (m_ThresholdSliderl.MaxGreyThreshold<=m_ThresholdSliderl.MinGreyThreshold)
	{
		m_ThresholdSliderl.MinGreyThreshold=m_ThresholdSliderl.MaxGreyThreshold;
		m_ThresholdMinGrey.SetPos(m_ThresholdSliderl.MaxGreyThreshold);

		UpdateData(FALSE);
	}
	m_HalconRoadRec.ChangeThresholdSlider(m_ThresholdSliderl);
	*pResult = 0;
}


void CCameraCorrectDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ��������
	//PostThreadMessage();
	//DestroyOtherThreadsObj();
	TerminateThread(m_CaptureThread->m_hThread,0);
	CloseHandle(m_CaptureThread->m_hThread);
	CDialogEx::OnClose();
	CDialogEx::OnOK();
	
}


void CCameraCorrectDlg::OnBnClickedButton2()           //�򿪵ڶ������
{
	if (m_JudgeCameraTwoFirst==FALSE)
	{
		m_JudgeCameraTwoFirst=TRUE;
		InitHalconDispTwo();
		ConnectCameraTwo();
	}
	else
	{
		MessageBox(_T("�����ظ��������"),_T("��ʾ"),MB_ICONINFORMATION);
	}
}
//float CCameraCorrectDlg::GetAngleBetweenCamera()
//{
//	double XDistance=DISTANCEBETWEENCAMERA+m_CameraCorrectX_Y_Angle.X_Correct+m_CameraCorrectX_Y_AngleTwo.X_Correct;
//	double YDistance=m_CameraCorrectX_Y_Angle.Y_Correct-m_CameraCorrectX_Y_AngleTwo.Y_Correct;
//	double AngleBetweenCamera=atan2(YDistance,XDistance);   
//	return AngleBetweenCamera;
//}

void CCameraCorrectDlg::OnNMCustomdrawThresholdmintwo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	m_ThresholdSliderlTwo.MinGreyThreshold=m_ThresholdMinGreyTwo.GetPos();
	if (m_ThresholdSliderlTwo.MinGreyThreshold>=m_ThresholdSliderlTwo.MaxGreyThreshold)
	{
		m_ThresholdSliderlTwo.MaxGreyThreshold=m_ThresholdSliderlTwo.MinGreyThreshold;
		m_ThresholdMaxGreyTwo.SetPos(m_ThresholdSliderlTwo.MinGreyThreshold);
	}
	m_HalconRoadRec.ChangeThresholdSliderTwo(m_ThresholdSliderlTwo);
	*pResult = 0;
}


void CCameraCorrectDlg::OnNMCustomdrawThrehsoldmaxtwo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	m_ThresholdSliderlTwo.MaxGreyThreshold=m_ThresholdMaxGreyTwo.GetPos();
	if (m_ThresholdSliderlTwo.MaxGreyThreshold<=m_ThresholdSliderlTwo.MinGreyThreshold)
	{
		m_ThresholdSliderlTwo.MinGreyThreshold=m_ThresholdSliderlTwo.MaxGreyThreshold;
		m_ThresholdMinGreyTwo.SetPos(m_ThresholdSliderlTwo.MaxGreyThreshold);

		UpdateData(FALSE);
	}
	m_HalconRoadRec.ChangeThresholdSliderTwo(m_ThresholdSliderlTwo);
	*pResult = 0;
}
