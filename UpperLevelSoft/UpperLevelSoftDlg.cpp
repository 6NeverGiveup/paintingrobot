
// UpperLevelSoftDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UpperLevelSoft.h"
#include "UpperLevelSoftDlg.h"
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


// CUpperLevelSoftDlg �Ի���




CUpperLevelSoftDlg::CUpperLevelSoftDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpperLevelSoftDlg::IDD, pParent)
	, m_iGUINumOfRecedCell(0)
	, m_iGUIColorNum(0)
	, m_iGUIValOfCellWidth(0)
	, m_iGUIValOfCellHeight(0)
	, m_JudgeFloorIsFlatL(_T(""))
	, m_SharpJudgeThreshold(1)
	, m_PointWorkSize(0)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_JudgeIsOperationOrder.ReadPicyureBtnDown=FALSE;
	m_JudgeIsOperationOrder.InvalidColorBtnDown=FALSE;
	m_JudgeIsOperationOrder.ReconfigureBtnDown=FALSE;
	m_JudgeIsOperationOrder.DrawAreaIdentificationResultsBtnDown=FALSE;
	m_JudgeIsOperationOrder.ConnectBtnDown=FALSE;
	m_JudgeIsOperationOrder.DesignatedWorkAreaBtnDown=FALSE;
	m_JudgeIsOperationOrder.IsWashGunBtnDown=FALSE;
	m_nPortNO=100;     //����˶˿�
	X_Correct=0.0;     //ƫ���ʼֵ
	Y_Correct=0.0;
	Angle_Correct=0.0;
	SaveDirectoryUpFile="";
	m_Connect="��";
	m_Connected=false;
	PerUnitWidth=100;

}

void CUpperLevelSoftDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON2_SET_NULL_COLLOR, m_cNullColorBtn);
	DDX_Control(pDX, IDC_BTN_CONNECT_DOWN, m_cGUI_ConectBtn);
	DDX_Control(pDX, IDC_RECGNIZE_FOR_MACHINE, m_RecButton);
	DDX_Control(pDX, IDC_BUTTON2_COLOR_RECED, m_btnColor1);
	DDX_Control(pDX, IDC_BUTTON2_COLOR_RECED2, m_btnColor2);
	DDX_Control(pDX, IDC_BUTTON2_COLOR_RECED3, m_btnColor3);
	DDX_Control(pDX, IDC_BUTTON2_COLOR_RECED4, m_btnColor4);
	DDX_Control(pDX, IDC_BUTTON2_COLOR_RECED5, m_btnColor5);
	DDX_Control(pDX, IDC_BUTTON2_COLOR_RECED6, m_btnColor6);
	DDX_Text(pDX, IDC_STATIC_PAINT_NUM, m_iGUINumOfRecedCell);
	DDX_Text(pDX, IDC_STATIC_COLOR_NUM, m_iGUIColorNum);
	DDX_Text(pDX, IDC_EDIT3_CELL_WIDTH, m_iGUIValOfCellWidth);
	DDX_Text(pDX, IDC_EDIT3_CELL_HEIGHT, m_iGUIValOfCellHeight);
	//DDX_Text(pDX, IDC_SHARPTHREASHOLD, m_SharpJudgeThreshold);
	DDX_Text(pDX, IDC_FLOORISFLAT, m_JudgeFloorIsFlatL);
	DDX_Text(pDX, IDC_SHARPTHREASHOLD, m_SharpJudgeThreshold);
}

BEGIN_MESSAGE_MAP(CUpperLevelSoftDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1_READ_PIC, &CUpperLevelSoftDlg::OnBnClickedButton1ReadPic)
	ON_MESSAGE(WMU_SetRealToMapRatioAndVel,OnSetVelAndRealRatio)
	ON_MESSAGE(WMU_SetGunParm,OnSetGunParm)                  //�����Ϣӳ��
	ON_MESSAGE(WMU_SetWorkRegParm,OnSetWorkRegParm)

	ON_MESSAGE(WMU_GUN0_DELAY,OnSetGun0DelayParm)
	ON_MESSAGE(WMU_GUN1_DELAY,OnSetGun1DelayParm)
	ON_MESSAGE(WMU_GUN2_DELAY,OnSetGun2DelayParm)
	ON_MESSAGE(WMU_GUN3_DELAY,OnSetGun3DelayParm)

	ON_MESSAGE(WMU_GUN0_REV_DELAY,OnSetGun0RevDelayParm)
	ON_MESSAGE(WMU_GUN1_REV_DELAY,OnSetGun1RevDelayParm)
	ON_MESSAGE(WMU_GUN2_REV_DELAY,OnSetGun2RevDelayParm)
	ON_MESSAGE(WMU_GUN3_REV_DELAY,OnSetGun3RevDelayParm)


	ON_MESSAGE(WMU_SAVEPMCDIRECTORY,SavePmcDiretory)
	ON_MESSAGE(WMU_PUMPPOWEROFF,OnBnClickedPumppowerOff)
	ON_MESSAGE(WMU_MOTOROFF,OnBnClickedStartmotorOff)
	ON_MESSAGE(WMU_PUMPPOWERON,OnBnClickedPumppowerOn)
	ON_MESSAGE(WMU_MOTORON,OnBnClickedStartmotorOn)
	ON_MESSAGE(WMU_RETURNZEROPOINT,OnBnClickedReturn)
	ON_MESSAGE(WMU_STOPALLFUNCTION,OnBnClickedQuit)
	ON_MESSAGE(WMU_DOWNLOADFILE,OnBnClickedDownload)
	ON_MESSAGE(WMU_RUN,OnBnClickedRun)
	ON_MESSAGE(WMU_TEMPORARYSTOP,OnBnClickedStop)
	ON_MESSAGE(WMU_STOPNOW,OnBnClickedStopall)
	ON_MESSAGE(WMU_AGAINRUN,OnBnClickedContinue)
	ON_MESSAGE(WMU_BEGINWASHGUN,OnBnClickedWash)
	ON_MESSAGE(WMU_STOPWASHGUN,OnBnClickedStopwash)
	ON_MESSAGE(WMU_ALIGNMENTCLICKED,OnBnClickedAlignment)
	ON_MESSAGE(WMU_ALIGNMENTLOOSEN,OnBnReleaseAlignment)

	ON_BN_CLICKED(IDC_DETAIL_SETTING, &CUpperLevelSoftDlg::OnBnClickedDetailSetting)
	ON_BN_CLICKED(IDC_BUTTON2_SET_NULL_COLLOR, &CUpperLevelSoftDlg::OnBnClickedButton2SetNullCollor)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_RECGNIZE_FOR_MACHINE, &CUpperLevelSoftDlg::OnBnClickedRecgnizeForMachine)
	ON_BN_CLICKED(IDC_BUTTON2_SET_REGION_TO_SHOW, &CUpperLevelSoftDlg::OnBnClickedButton2SetRegionToShow)
	ON_BN_CLICKED(IDC_RA_REG_TO_DOWN, &CUpperLevelSoftDlg::OnBnClickedRaRegToDown)
	ON_BN_CLICKED(IDC_BTN_CONNECT_DOWN, &CUpperLevelSoftDlg::OnBnClickedBtnConnectDown)
	ON_BN_CLICKED(IDC_SELECT_REG, &CUpperLevelSoftDlg::OnBnClickedSelectReg)
	ON_BN_CLICKED(IDC_DOWN_PARM, &CUpperLevelSoftDlg::OnBnClickedDownParm)
	ON_BN_CLICKED(IDC_ACTION, &CUpperLevelSoftDlg::OnBnClickedAction)
	ON_BN_CLICKED(IDC_LOW_MONITER, &CUpperLevelSoftDlg::OnBnClickedLowMoniter)
	ON_BN_CLICKED(IDC_OPENSHARP, &CUpperLevelSoftDlg::OnBnClickedOpensharp)
	ON_BN_CLICKED(IDOK, &CUpperLevelSoftDlg::OnBnClickedOk)
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_RA_REG_TO_DOWN1, &CUpperLevelSoftDlg::OnBnClickedRaRegToDown1)

	ON_BN_CLICKED(IDC_BUTTON2_COLOR_RECED2, &CUpperLevelSoftDlg::OnBnClickedButton2ColorReced2)
	ON_BN_CLICKED(IDC_BUTTON2_COLOR_RECED, &CUpperLevelSoftDlg::OnBnClickedButton2ColorReced)
	ON_BN_CLICKED(IDC_BUTTON2_COLOR_RECED3, &CUpperLevelSoftDlg::OnBnClickedButton2ColorReced3)
	ON_BN_CLICKED(IDC_BUTTON2_COLOR_RECED4, &CUpperLevelSoftDlg::OnBnClickedButton2ColorReced4)
	ON_BN_CLICKED(IDC_BUTTON2_COLOR_RECED5, &CUpperLevelSoftDlg::OnBnClickedButton2ColorReced5)
	ON_BN_CLICKED(IDC_BUTTON2_COLOR_RECED6, &CUpperLevelSoftDlg::OnBnClickedButton2ColorReced6)

END_MESSAGE_MAP()


// CUpperLevelSoftDlg ��Ϣ�������

BOOL CUpperLevelSoftDlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	ShowWindow(SW_SHOW);
	GetClientRect(&m_ClientRect);    //��ȡ�Ի���Ĵ�С
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitSystemParm();
	m_cNullColorBtn.SetFlat(FALSE);
	m_cGUI_ConectBtn.SetFlat(FALSE);
	
	InterfaceBeautification();
	StorePictureToShow();
	m_StorePictureIterator=m_StorePicture.begin();
	SetTimer(1,500,NULL);             //������ʱ����������PICTURE����ʾ��̬ͼƬ

//#ifdef USE_CONTENT_IN_DEPENDENT_CLASS 
//	m_cMotionCommu.InitComWithParker();///<����ͨѶ��ʵ������
//#endif
//	m_cPlcCommu.InsertMsCom(&m_cmscom);
//	m_cPlcCommu.InitComm(m_uCommPortNum_PLC);
	/*m_btnColor1.SubclassDlgItem(IDC_BUTTON2_COLOR_RECED,this);
	m_btnColor2.SubclassDlgItem(IDC_BUTTON2_COLOR_RECED2,this);
	m_btnColor3.SubclassDlgItem(IDC_BUTTON2_COLOR_RECED3,this);
	m_btnColor4.SubclassDlgItem(IDC_BUTTON2_COLOR_RECED4,this);*/
	GetOwnSelfIp();         //�õ�����IP
	CreateServer();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CUpperLevelSoftDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUpperLevelSoftDlg::OnPaint()
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
HCURSOR CUpperLevelSoftDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUpperLevelSoftDlg::OnBnClickedButton1ReadPic()
{
	m_JudgeIsOperationOrder.ReadPicyureBtnDown=TRUE;
	KillTimer(1);         //�رն�ʱ������ʱPICTUREҪ��ʾҪ��Ϳ��ͼƬ
	static bool FirstShow=true;//ֻ�ڵ�һ�ε�ʱ���ʼ������ʾ��һ�����У���Ҫ���������ʾ��Դ
	//m_bFirstShow==true?;
	bool bIsRead=true;
	InitSystemParm(true);
	m_bReadedPic=ReadPicture2( FirstShow,true);
	if (m_bReadedPic)
	{
		m_bRecedPic=false;
		FirstShow=false;//���ȥ���������������Ժ�����Ҫ���������ʾ��Դ
	}
	//else{
	//	FirstShow=true;//û��ʾ�ɹ���ȡ���ˣ��Ժ���Ҫ���������Դ
	//}
	/*CWnd*pRecedWnd=GetDlgItem(IDC_RECGNIZE_FOR_MACHINE);
	pRecedWnd*/
	(AfxGetMainWnd()->GetDlgItem(IDC_RECGNIZE_FOR_MACHINE))->EnableWindow();
	
}
bool CUpperLevelSoftDlg::InitSystemParm(bool ReInit)
{
	InitPaintMachineParm(ReInit);
	m_bUSE_CRossCursor=false;
	m_bChoseRegToShow=false;
	m_bSetNullColor=false;
	m_bReadedPic=false;
	memset( m_fGunDelay,0,sizeof(m_fGunDelay));
	memset( m_fRevGunDelay,0,sizeof(m_fRevGunDelay));
	
	/*m_fGun0Delay[0]=0;
	m_fGun0Delay[1]=0;
	m_fGun1Delay[0]=0;
	m_fGun1Delay[1]=0;
	m_fGun2Delay[0]=0;
	m_fGun2Delay[1]=0;
	m_fGun3Delay[0]=0;
	m_fGun3Delay[1]=0;*/
	/* m_bRecedPic=false;*/
	 m_bSelectRegToDown=false;
	return false;
}
bool CUpperLevelSoftDlg::ReadPicture2(bool FirstUSE,bool bIsRead)
{
	CFileDialog dlg(TRUE,_T("*.BMP"), NULL, NULL,_T("λͼ�ļ�(*.BMP))|_T(*.bmp;*.BMP|"));
	CString strFileName;
	CFile file;
	
	if (dlg.DoModal() == IDOK)
	{             
		strFileName = dlg.GetPathName();
		HBITMAP hBitmap = (HBITMAP)LoadImage(NULL,strFileName,
			IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		m_cLoadedMap.DeleteObject();//ɾ�������Ѿ����ص����ݣ������ظ���ͼ�����
		if (!m_cLoadedMap.Attach(hBitmap))
		{
			MessageBox(_T("ͼƬ���س���","����"));
			return false;
		}
		ShowBMP2(FirstUSE,bIsRead);
		return true;
	}
	return false;
}
unsigned CRect_Work_Region::WidthOfWorkRegion;
unsigned CRect_Work_Region::HeightofWorkRegion;
void CUpperLevelSoftDlg::InitPaintMachineParm(bool ReInit)
{
	if (!ReInit)//�ظ���ʼ������Ҫ�����趨ֵ
	{
		g_cWorkRegionParm.WidthOfWorkRegion=WIDTH_OF_REGION_IN_MM/MM_PER_PIXEL;
		g_cWorkRegionParm.HeightofWorkRegion=HEIGHT_OF_REGION_IN_MM/MM_PER_PIXEL;		
		m_fWorkRegWidth=WIDTH_OF_REGION_IN_MM;
		m_fWorkRegHeight=HEIGHT_OF_REGION_IN_MM;
		gRowWidth=WIDTH_OF_ROW_IN_MM/MM_PER_PIXEL;
		gHeightOfEveryPaintCell=HEIGHT_OF_PAINT_CELL_IN_MM/MM_PER_PIXEL;
		OnSetVelAndRealRatio(100*PRE_MULTIED_FACTOR_FOR_REAL_PARM,200*PRE_MULTIED_FACTOR_FOR_REAL_PARM);
		//////////����ǹ����////////////////////////////////////////////////////////////////
		//OnSetGunParm(2*PRE_MULTIED_FACTOR_FOR_REAL_PARM,120*PRE_MULTIED_FACTOR_FOR_REAL_PARM);
		GunParm CurGunParm;
		CurGunParm.GunNum=2*PRE_MULTIED_FACTOR_FOR_REAL_PARM;
		CurGunParm.GunDis=120*PRE_MULTIED_FACTOR_FOR_REAL_PARM;
		CurGunParm.CurgunMode=GunParm::MultiGun;
		GunParm*pGunParm=&CurGunParm;
		OnSetGunParm((WPARAM)pGunParm,1);
		m_PerGunColor=1;
		//////////////////////////////////////////////////////////////////////////
		m_bRecedPic=false;///<���ǳ��γ�ʼ������������һ��
	}
	else
	{
		g_cWorkRegionParm.WidthOfWorkRegion=m_fWorkRegWidth/m_fRealRatio;
		g_cWorkRegionParm.HeightofWorkRegion=m_fWorkRegHeight/m_fYRealRatio;
	}

	geAreaPartitionFlag=GRID_PARTION_BY_INTELLIGENCE;
	gbOnePixelBetweenWorkReg=false;	
	gCellSizePreRecFlag=AVERAGE_SIZE_OF_CELL;
	
	//OnSetWorkRegParm()
}
bool CUpperLevelSoftDlg::ShowBMP2(bool bFirstUSE,bool bIsRead)
{
	CDC *pDC;
	CRect rect; 
	CWnd *pWnd = GetDlgItem(IDC_STATIC_SHOW);
	BITMAP LoadedBitMapInfo;
	pWnd->GetClientRect(&rect);
//	CBitmap Bmp;
//	CPicDC.ReleaseAttribDC();
	//rect.
	
	//pWnd->InvalidateRect(NULL,TRUE);
	if (pWnd)
	{
		

			pDC = pWnd->GetDC(); //Ŀ��DC
			
			//CDC CDCSource;//ԭʼͼƬ
			// CDCSource.CreateCompatibleDC(pDC);//����������Ŀ����ʾ����DC
			// CDCSource.SelectObject(&m_cLoadedMap);
		/*	m_cLoadedMap.DeleteTempMap();*/
			m_cLoadedMap.GetBitmap(&LoadedBitMapInfo);
		//	m_cLoadedMap.CreateCompatibleBitmap(pDC,LoadedBitMapInfo.bmWidth,LoadedBitMapInfo.bmHeight);
			
		if (bFirstUSE)
		{
			CPicDC.CreateCompatibleDC(pDC);//����������Ŀ����ʾ����DC
			CPicDC.SelectObject(&m_cLoadedMap);
		}	
		else
		{
			//OnPrepareDC()
			//CPicDC.DeleteTempMap();
		//	Bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
			//pDC->SelectObject(Bmp);
			//pWnd->InvalidateRect(NULL,TRUE);
			//CPicDC.FillSolidRect(0,0,LoadedBitMapInfo.bmWidth,LoadedBitMapInfo.bmHeight,pDC->GetBkColor());//�ƺ���ֱ�Ӱ�ѡ�뵽���е�m_cLoadedMapҲ�����ˡ�ѡ��ʵ���Ϸ�����Ǹ���ַ��������
			CPicDC.SelectObject(&m_cLoadedMap);
			if (!bIsRead)
			{
				DistinctMap(& CPicDC);//���ڴ��л���
			}			
			//CPicDC.DeleteDC();
			//ReleaseDC(&CPicDC);
		}

		//EraseAll(pDC,rect);
		SetStretchBltMode(pDC->m_hDC,HALFTONE);//��ֹ����Ӧ����ͼ����ʾʧ��
		//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&CPicDC,0,0,SRCCOPY);
		 m_sSHow2MapRatio.xRatio=(double)LoadedBitMapInfo.bmWidth/rect.Width();
		 m_sSHow2MapRatio.yRatio=(double)LoadedBitMapInfo.bmHeight/rect.Height();
		StretchBlt(pDC->m_hDC,rect.left, rect.top,rect.Width(),rect.Height(),CPicDC.m_hDC,0,0,LoadedBitMapInfo.bmWidth,LoadedBitMapInfo.bmHeight,SRCCOPY);
		//pWnd->InvalidateRect(NULL,TRUE);
	//	pDC->DeleteDC();
		ReleaseDC(pDC);
		/*int W=rect.Width();
		int H=rect.Height();
		int Top=rect.right;
		int Height=rect.bottom;*/
			//DistinctMap(pDC);
		/*StretchDIBits(pDC->m_hDC,rect.left, rect.top, rect.right, rect.bottom, 0, 0, 
			lWidth, lHeight, m_pDibBits, (BITMAPINFO*)m_bmpInfoHeader, BI_RGB, SRCCOPY);*/
		return true;
	} 
	return false;
}


bool CUpperLevelSoftDlg::DistinctMap(CDC* pTargetDC)
{
	CPen Pen(PS_SOLID, 1, RGB(255,255,0));

	pTargetDC->SelectObject(Pen);
	pTargetDC->SelectStockObject(NULL_BRUSH);//�ڲ������
	for (unsigned i=0;i<m_cRecgnizePic.NumOfRecedPic();i++)
	{
		pTargetDC->Rectangle(m_cRecgnizePic.RectOfReg(i));
	}
	return false;
}


void CUpperLevelSoftDlg::OnBnClickedDetailSetting()
{
	float RealSize=m_fRealRatio*gRowWidth/10;//ʵ�ʿ�ȣ�����
	float RealVel=m_fRealVel*INDUCE_LENGTH/1000;
	float WorkRegWid=g_cWorkRegionParm.WidthOfWorkRegion*m_fRealRatio;
	float WorkRegHeight=g_cWorkRegionParm.HeightofWorkRegion*m_fYRealRatio;
	int PerGunColor=m_PerGunColor;
//	CDetailSettingDlg  SettingDlg(RealSize,RealVel,m_uGunNum,m_fGunDis,WorkRegWid,WorkRegHeight,PerGunColor,this);
	CDetailSettingDlg  SettingDlg(this);
	if (SettingDlg.DoModal()==IDOK)
	{
		
	}
}


void CUpperLevelSoftDlg::OnBnClickedButton2SetNullCollor()
{
	if (m_JudgeIsOperationOrder.ReadPicyureBtnDown==FALSE)
	{
		MessageBox(_T("���ȶ�ȡͼƬ��"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	m_JudgeIsOperationOrder.InvalidColorBtnDown=TRUE;
	//SetCursor(AfxGetApp()-> LoadStandardCursor(IDC_CROSS));
	m_bSetNullColor=true;
	m_bUSE_CRossCursor=true;
}


void CUpperLevelSoftDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect ShowRect;
	GetDlgItem(IDC_STATIC_SHOW)->GetWindowRect( ShowRect);// ��ȡ��������������������
	ScreenToClient( ShowRect);         // ����ڵ�ǰ dialog �����꣬ScreenToClient( )�ǰ���Ļ����ת��Ϊ��������
	point.x=point.x-ShowRect.left;
	point.y=point.y-ShowRect.top;
	if (m_bUSE_CRossCursor&&m_bSetNullColor)
	{
		CWnd *pWnd = GetDlgItem(IDC_STATIC_SHOW);
		 CDC* pDC = pWnd->GetDC();
		 if (pDC)
		 {
			// TransforShowCoordIntoMapCoord(point);
			//GetPixel���������ܣ��ú�������ָ�����������ص�RGB��ɫֵ
			gNULLCOLOR=pDC->GetPixel(point);//�����õľ�����ʾ�ϵ����ص���ɫ������
		 }
		ReleaseDC(pDC);
		//pWnd->r
		SetCursor(AfxGetApp()-> LoadStandardCursor(IDC_ARROW));   //HCURSOR SetCursor(HCURSOR hCursor)�ú���ȷ��������״
		m_cNullColorBtn.SetColor(CButtonST::BTNST_COLOR_BK_OUT, gNULLCOLOR);
		m_cNullColorBtn.SetColor(CButtonST::BTNST_COLOR_BK_IN, gNULLCOLOR);
		m_cNullColorBtn.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, gNULLCOLOR);
		m_bUSE_CRossCursor=false;
		m_bSetNullColor=false;
	}
	if (m_bUSE_CRossCursor&&m_bChoseRegToShow)
	{		
		//if (m_cRecgnizePic.NumOfRecedPic()>0)
		if (m_bRecedPic)
		{
			TransforShowCoordIntoMapCoord(point);
			ShowRecResOfGivenReg(point);
		}		
		m_bChoseRegToShow=false;
		m_bUSE_CRossCursor=false;
	}
	if (m_bUSE_CRossCursor&&m_bSelectRegToDown)
	{
		if (!SelectRegDownLoadParm(point))
		{    ::MessageBoxA(NULL, "ѡ���������ش���", "��ʾ", MB_OK);		}		
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}
bool CUpperLevelSoftDlg::ShowRecResOfGivenReg(CPoint& ChosedPoint)
{
	if (!m_cRecgnizePic.FoundCellToBePaint())
	{
		MessageBox(_T("����û��ʶ���ɫ��","����"));
		return false;
	}
	CDC *pDC;
	CRect rect; 
	CWnd *pWnd = GetDlgItem(IDC_STATIC_SHOW);
	BITMAP LoadedBitMapInfo;
	pWnd->GetClientRect(&rect);
	pWnd->InvalidateRect(NULL,TRUE);
	if (pWnd)
	{
		pDC = pWnd->GetDC(); //Ŀ��DC
		m_cLoadedMap.GetBitmap(&LoadedBitMapInfo);
		if (LoadedBitMapInfo.bmWidth<1)
		{
			return false;
		}	
		else
		{
			{ShowRecResOnMap(& CPicDC,m_cRecgnizePic.LocGivenPointInRegs(ChosedPoint));	}			
			SetStretchBltMode(pDC->m_hDC,HALFTONE);//��ֹ����Ӧ����ͼ����ʾʧ��
			//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&CPicDC,0,0,SRCCOPY);
			StretchBlt(pDC->m_hDC,rect.left, rect.top,rect.Width(),rect.Height(),CPicDC.m_hDC,0,0,LoadedBitMapInfo.bmWidth,LoadedBitMapInfo.bmHeight,SRCCOPY);
			pWnd->InvalidateRect(NULL,TRUE);
		//	pDC->DeleteDC();
			ReleaseDC(pDC);
			return true;
		}
		
	} 
	return false;
}
bool CUpperLevelSoftDlg::SelectRegDownLoadParm(CPoint& ChosedPoint)
{
//	if (m_cRecgnizePic.NumOfRecedPic()>0)
	(AfxGetMainWnd()->GetDlgItem(IDC_DOWN_PARM))->EnableWindow();//������Ӧɾ��
	if (m_bRecedPic)
	{
		TransforShowCoordIntoMapCoord(ChosedPoint);
		m_uRegToBeDownLoad=m_cRecgnizePic.LocGivenPointInRegs(ChosedPoint);
	}
	m_bSelectRegToDown=false;
	m_bUSE_CRossCursor=false;
	if (m_uRegToBeDownLoad<m_cRecgnizePic.NumOfRecedPic())
	{
		if (m_bLowerConnectStatu)
		{
			(AfxGetMainWnd()->GetDlgItem(IDC_DOWN_PARM))->EnableWindow();
		}		
		return true;
	}
	else
		(AfxGetMainWnd()->GetDlgItem(IDC_DOWN_PARM))->EnableWindow(0);
	return false;
}
bool CUpperLevelSoftDlg::ShowRecResOnMap(CDC* pTargetDC,unsigned IndexOfReg)
{
	CPen Pen(PS_SOLID, 1,CELL_COLOR);
	CRect RTec;
	pTargetDC->SelectObject(Pen);
	pTargetDC->SelectStockObject(NULL_BRUSH);//�ڲ������
	for (unsigned Row=0;Row<m_cRecgnizePic.m_vWorkRegionPationed[IndexOfReg].NumOfRow;Row++)
	{
		for (unsigned Line=0;Line<m_cRecgnizePic.m_vWorkRegionPationed[IndexOfReg].NumOfCellInGivenRow(Row);Line++)
		{
			RTec=m_cRecgnizePic.m_vWorkRegionPationed[IndexOfReg].RecedCell(Line,Row);
			//RTec.top-=0;//������
			pTargetDC->Rectangle(RTec);
		}
	}		
	return false;
}
void CUpperLevelSoftDlg::InterfaceBeautification()
{
	//CBitmap bitmap;  
	//bitmap.LoadBitmap(IDB_BITMAP2);   //����λͼ  
	//CClientDC cdc(this);              //ѡ��DC  
	//CDC comdc;  
	//comdc.CreateCompatibleDC(&cdc);  
	//comdc.SelectObject(&bitmap);  
	//BITMAP bit;               //����BITMAP  
	//bitmap.GetBitmap(&bit);  
	//CRect rect;  
	//GetClientRect(rect);  	//�ͻ�����  
	//SetStretchBltMode(comdc.m_hDC,HALFTONE);
	//cdc.StretchBlt(0,0,rect.Width(),rect.Height(),&comdc,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);  
	
	//CDC *pDC;
	//CRect rect; 
	//CWnd *pWnd = GetDlgItem(IDC_BUTTON1_READ_PIC);//���ش�����ָ������ID����Ԫ�صľ��������ͨ�����صľ���Դ����ڵ���Ԫ�ؽ��в���
	//pWnd->GetClientRect(&rect);              //�ú�����ȡ���ڿͻ���������
	//pDC = pWnd->GetDC();
	//SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE);
	//HICON m_read=AfxGetApp()->LoadIcon(IDI_ICON4);
	//ICONINFO m_readinfo;
	//GetIconInfo(m_read,&m_readinfo);
	//StretchBlt((HDC)pWnd->m_hWnd,rect.left, rect.top, rect.right, rect.bottom,pDC,0,0,m_readinfo.xHotspot,m_readinfo.yHotspot,SRCCOPY);
	/*HICON m_read=AfxGetApp()->LoadIcon(IDI_ICON4);
	CButton *m_button=(CButton*)GetDlgItem(IDC_BUTTON1_READ_PIC);
	m_button->SetIcon(m_read);*/
	//m_ReadPicture1.SetButtonStyle(TBBS_SEPARATOR);
	m_ReadPicture1.SubclassDlgItem(IDC_BUTTON1_READ_PIC,this); 
	m_ReadPicture1.SetIcon(IDI_ICON4); 
	m_ReadPicture1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(255,0,0));
	m_ReadPicture1.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255,0,0));
	m_ReadPicture1.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255,0,0));
	m_ReadPicture1.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0,0,0));
	m_ReadPicture1.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0,255,0));
	m_ReadPicture1.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(0,0,255));
	m_ReadPicture1.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_ReadPicture1.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);
	m_ReadPicture1.SetRounded(TRUE);

	m_cNullColorBtn.SetIcon(IDI_ICON1); 
	m_cNullColorBtn.SetColor(CButtonST::BTNST_COLOR_FG_OUT,RGB(255,0,0));
	m_cNullColorBtn.SetColor(CButtonST::BTNST_COLOR_FG_IN,RGB(255,0,0));
	m_cNullColorBtn.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS,RGB(255,0,0));
	m_cNullColorBtn.SetColor(CButtonST::BTNST_COLOR_BK_OUT,RGB(0,0,0));
	m_cNullColorBtn.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0,255,0));
	m_cNullColorBtn.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT); 
	
	m_HighDesign.SubclassDlgItem(IDC_DETAIL_SETTING,this); 
	m_HighDesign.SetIcon(IDI_ICON2); 
	m_HighDesign.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(255,0,0));
	m_HighDesign.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255,0,0));
	m_HighDesign.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255,0,0));
	m_HighDesign.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0,0,0));
	m_HighDesign.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0,255,0));
	m_HighDesign.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(0,0,255));
	m_HighDesign.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_HighDesign.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);
	m_HighDesign.SetRounded(TRUE);
	
	//m_ReadPicture.DrawFlatFocus(TRUE);
}
void CUpperLevelSoftDlg::StorePictureToShow()
{
	CFileFind fileFinder;//��CFileFindִ�б����ļ�����  
	CString strPicFile ;  
	HMODULE hm=GetModuleHandle(0);
	char buf[MAX_PATH];
	GetModuleFileName(hm,buf,strlen(buf));
	CString PATH_str=CString(buf,strlen(buf));
	PATH_str=PATH_str.Left(PATH_str.ReverseFind('\\'));
	PATH_str=PATH_str.Left(PATH_str.ReverseFind('\\'));
	CString strFilePath=/*"D:\\PaintRobot2\\UpperLevelSoft\\Picture"*/PATH_str+"\\Picture";//�����ļ�·��  
	CString strFileName;//�����ļ���  
	if (strFilePath.Right(1)!=TEXT("\\"))  
	{  
		strFilePath+="\\";
	}  
	strPicFile.Format(TEXT("%s%s"),strFilePath,TEXT("*.jpg"));//ֻѡ��jpg��ʽ��ͼƬ  
	BOOL bWorking = fileFinder.FindFile(strPicFile);  
	while (bWorking)  
	{     
		if (fileFinder.FindNextFile()==FALSE)
		{
			strFilePath = fileFinder.GetFilePath();			//ͼƬ������·��  
			strFileName = fileFinder.GetFileName();			//ͼƬ�ļ������� 
			m_StorePicture.push_back(strFilePath);
			break;
		}
		else
		{
			strFilePath = fileFinder.GetFilePath();			//ͼƬ������·��  
			strFileName = fileFinder.GetFileName();			//ͼƬ�ļ������� 
			m_StorePicture.push_back(strFilePath);
		}
		if (fileFinder.IsDots()||fileFinder.IsDirectory()||fileFinder.IsHidden())//IsDots�ж��Ƿ�Ϊ��,��CFileFind��������IsDots����˼�ǣ�����һ��Ŀ¼���Ҳ������Ŀ¼��������ϲ�Ŀ¼  
		{  
			continue;  
		}  
		//else  
		//{     
		//	int nPos = strFilePath.ReverseFind(TEXT('.'));    //���ش�CString��������Ҫ����ַ�ƥ������һ���ַ�������
		//	CString strExt = strFilePath.Right(strFilePath.GetLength() - nPos - 1);    //ʹ��lstrcmpi������һ��CString����һ��CString���бȽ�
		//	if (strExt.CompareNoCase(TEXT("jpg"))== 0||strExt.CompareNoCase(TEXT("jpeg")) == 0||strExt.CompareNoCase(TEXT("bmp"))  == 0)  
		//	{     
		//		
		//	}  
		//}  
	}  
	fileFinder.Close();  
}
void CUpperLevelSoftDlg::GetOwnSelfIp()
{
	WSADATA	wsaData;
	PHOSTENT hostinfo;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		MessageBox(_T("WSAStartup ERROR!"));
	}
	//���÷�����IP��ַ
	char gcTemp[255];
	char * IP;
	if (0 == gethostname(gcTemp, 255))
	{
		hostinfo = gethostbyname(gcTemp);
		//tempStr.Format("%s", gcTemp);
		//MessageBox(tempStr);
		IP = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
		//tempStr.Format(IP);
		//MessageBox(IP);
		//SetDlgItemText(IDC_STATIC_SERVER_ADDRESS, tempStr);
		//m_addServerAddress.SetAddress();
	}
	//���÷�����Ĭ�϶˿ں�Ϊ100
	//SetDlgItemText(IDC_EDIT_SERVER_PORT, "100");
	m_bServerCreated = false;
	m_bTerminateThread = false;
}
void CUpperLevelSoftDlg::CreateServer()
{
	//��ȡ��������ַ�Լ��˿ں�
	//socket
	if ((m_sockServer = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		MessageBox(_T("ERROR: Create Server Socket Error!"));
		exit(-1);
	}
	//bind
	struct sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(m_nPortNO);
	(serAddr.sin_addr).s_addr = htonl(INADDR_ANY);
	if ((bind(m_sockServer, (LPSOCKADDR)&serAddr, sizeof(serAddr)))==SOCKET_ERROR)
	{
		MessageBox(_T("ERROR: Bind Socket Error!"));
		exit(-1);
	}
	//disable portno
	m_bServerCreated = true;
    //�����̵߳ȴ�
	m_bTerminateThread = false;
	AfxBeginThread(ServerRecvThread, this, THREAD_PRIORITY_NORMAL, 0, 0);
}
UINT ServerRecvThread(LPVOID lpParm )
{
	FILE *m_p=fopen("E:\\Dee.txt","w");
	CUpperLevelSoftDlg *dlg = (CUpperLevelSoftDlg*)lpParm;
	char gcInBuffer[1027];
	int lenth;
	int size = sizeof(sockaddr_in);
	CString strReceive, tempStr;
	char*gcClientIP; 
	bool bSendEnable = false;
	while(!dlg->m_bTerminateThread)
	{
		 memset(gcInBuffer,0,sizeof(gcInBuffer));
		if ((lenth = recvfrom(dlg->m_sockServer, gcInBuffer, 1024, 0, (struct sockaddr *)&dlg->m_clientAddr, &size) )>0)
		{
			CString TemporaryData=_T("");
			TemporaryData.Format("%s",gcInBuffer);
			dlg->m_CameraPosition.FirstCameraY=atof(dlg->CompileCameraParm(TemporaryData,1));
			dlg->m_CameraPosition.FirstCameraX=atof(dlg->CompileCameraParm(TemporaryData,2));
			dlg->m_CameraPosition.Firstcameradignose=atoi(dlg->CompileCameraParm(TemporaryData,3));
			dlg->m_CameraPosition.SecondCameraY=atof(dlg->CompileCameraParm(TemporaryData,4));
			dlg->m_CameraPosition.SecondCameraX=atof(dlg->CompileCameraParm(TemporaryData,5));
			dlg->m_CameraPosition.Secondcameradignose=atoi(dlg->CompileCameraParm(TemporaryData,6));
			TemporaryData=TemporaryData+'\n';
			fwrite(TemporaryData,1,strlen(TemporaryData),m_p);
			/*dlg->MessageBox(TemporaryData);*/
			//if(TemporaryData.Find('A',0)!=-1)
			//{
			//	int FirstA=TemporaryData.Find('A',0);
			//	CString X_C=TemporaryData.Mid(0,FirstA);
			//	//dlg->MessageBox(X_C);
			//	dlg->X_Correct=atof(X_C);
			//	int SecondA=TemporaryData.Find('A',FirstA);
			//	CString Y_C=TemporaryData.Mid(FirstA+1,SecondA);
			//	//dlg->MessageBox(Y_C);
			//	dlg->Y_Correct=atof(Y_C);
			//	int ThirdA=TemporaryData.Find('A',SecondA);
			//	CString Angle_C=TemporaryData.Mid(SecondA+1,ThirdA);
			//	//dlg->MessageBox(Angle_C);
			//	dlg->Angle_Correct=atof(Angle_C);
			//}
			//if (!bSendEnable)
			//{
			//	//CWnd *cwnd = dlg->GetDlgItem(IDC_BUTTON_SEND);
			//	//cwnd->EnableWindow(TRUE);
			//	bSendEnable = true;
			//}
			//gcClientIP = inet_ntoa((dlg->m_clientAddr).sin_addr);
			//tempStr.Format("%s", gcClientIP);
			////dlg->SetDlgItemText(IDC_STATIC_CLINET_ADDRESS, tempStr);
			//tempStr.Format("%hu", dlg->m_clientAddr.sin_port);
			////dlg->SetDlgItemText(IDC_STATIC_CLIENT_PORTNO, tempStr);
			//tempStr.Format("%s:%hu: ", gcClientIP, dlg->m_clientAddr.sin_port);
			//strReceive += tempStr;
			//gcInBuffer[lenth] = '\r';
			//gcInBuffer[lenth+1] = '\n';
			//gcInBuffer[lenth+2] = '\0';
			//strReceive += gcInBuffer;
		}
	}
	return 0;
	fclose(m_p);
}
CString CUpperLevelSoftDlg::CompileCameraParm(CString InputMessage,int num)
{
	int start=0;
	for(int i=0;i<num;i++)
	{
		int find_ok=InputMessage.Find(",",start);
		if(find_ok>=0)
			start=find_ok+1;
		else break;
	}
	int end=InputMessage.Find(",",start);
	if(end>start)
		return InputMessage.Mid(start,end-start);
	else 
		return _T("");
}

void CUpperLevelSoftDlg::OnBnClickedRecgnizeForMachine()
{
	if (m_JudgeIsOperationOrder.ReadPicyureBtnDown==FALSE)
	{
		MessageBox(_T("���ȶ�ȡͼƬ��"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	if (m_JudgeIsOperationOrder.InvalidColorBtnDown==FALSE)
	{
		MessageBox(_T("����ָ����Ч��ɫ��"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	m_JudgeIsOperationOrder.ReconfigureBtnDown=TRUE;
	if (m_bRecedPic)
	{
		MessageBox(_T("ͬһ��ͼƬ�����ظ�ʶ������������ͼƬ"));
		return;
	}
	
	BITMAP LoadedBitMapInfo;
	m_cRecgnizePic.InitAll();
	m_cLoadedMap.GetBitmap(&LoadedBitMapInfo);	
	unsigned gRowWidthPreVal=gRowWidth;//ʶ��֮ǰ��ֵ
	if (m_cRecgnizePic.PreReggnizeForParm(&CPicDC,LoadedBitMapInfo.bmWidth,LoadedBitMapInfo.bmHeight))//����Ԥʶ��
	{
		m_fYRealRatio=m_fRealRatio*gRowWidthPreVal/gHeightOfEveryPaintCell; //Y��ϵ��
		m_fRealRatio=m_fRealRatio*gRowWidthPreVal/gRowWidth;//���¼������ϵ���Է������ı�

		g_cWorkRegionParm.WidthOfWorkRegion=Floor4_Ceil5(m_fWorkRegWidth/m_fRealRatio);//���¼�������Է������ı�
		g_cWorkRegionParm.HeightofWorkRegion=Floor4_Ceil5(m_fWorkRegHeight/m_fYRealRatio);//���¼�������Է������ı�
		m_cResAdapter.SetRatioOfPixel(m_fRealRatio,m_fYRealRatio);
		
	}
	if (m_cRecgnizePic.RecgnizePic(&CPicDC,LoadedBitMapInfo.bmWidth,LoadedBitMapInfo.bmHeight))
	{
		ShowBMP2(false,false);
		ShowRecResultDat();
		m_bRecedPic=true;
		ShowColorReced();
		m_cResAdapter.ImportRecedRes(&m_cRecgnizePic);
		

	}
	else
	{
		MessageBox(_T("ʶ��ʧ��"));
	}
}
int CUpperLevelSoftDlg::ShowRecResultDat(void)
{
	m_iGUIValOfCellWidth=gRowWidth;
	m_iGUIValOfCellHeight=gHeightOfEveryPaintCell;
	m_iGUINumOfRecedCell=m_cRecgnizePic.NumOfRecedCell();
	m_iGUIColorNum=m_cRecgnizePic.QueryNumOfColorToBePainted();
	UpdateData(FALSE);
	return 0;
}
int CUpperLevelSoftDlg::ShowColorReced(void)
{
	std::vector<CButtonST*>vPWnd;
	vPWnd.push_back(&m_btnColor1);
	vPWnd.push_back(&m_btnColor2);
	vPWnd.push_back(&m_btnColor3);
	vPWnd.push_back(&m_btnColor4);
	vPWnd.push_back(&m_btnColor5);
	vPWnd.push_back(&m_btnColor6);
	//pButton1->m_hWnd;	
	unsigned num=min(m_cRecgnizePic.QueryNumOfColorToBePainted(),6);
	for (unsigned i=0;i<num;i++)
	{	
		vPWnd[i]->SetColor(CButtonST::BTNST_COLOR_BK_OUT, m_cRecgnizePic.QueryColorByIndex(i));
		vPWnd[i]->SetColor(CButtonST::BTNST_COLOR_BK_IN, m_cRecgnizePic.QueryColorByIndex(i));
		vPWnd[i]->SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, m_cRecgnizePic.QueryColorByIndex(i));
		vPWnd[i]->SetColor(CButtonST::BTNST_COLOR_FG_IN,gNULLCOLOR);
		vPWnd[i]->SetColor(CButtonST::BTNST_COLOR_FG_OUT,gNULLCOLOR);
		vPWnd[i]->SetColor(CButtonST::BTNST_COLOR_FG_FOCUS,gNULLCOLOR);

	}
	
	return 0;
}


void CUpperLevelSoftDlg::OnBnClickedButton2SetRegionToShow()
{
	if (m_JudgeIsOperationOrder.ReadPicyureBtnDown==FALSE)
	{
		MessageBox(_T("���ȶ�ȡͼƬ��"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	if (m_JudgeIsOperationOrder.InvalidColorBtnDown==FALSE)
	{
		MessageBox(_T("����ָ����Ч��ɫ��"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	if (m_JudgeIsOperationOrder.ReconfigureBtnDown==FALSE)
	{
		MessageBox(_T("����ʶ����"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	m_JudgeIsOperationOrder.DrawAreaIdentificationResultsBtnDown=TRUE;
	m_bUSE_CRossCursor=true;
	m_bChoseRegToShow=true;
}


void CUpperLevelSoftDlg::OnBnClickedRaRegToDown()
{
	m_iGUISelectRegOrAll=0;///<û��������Ͳ���Ҫ
	if (m_uRegToBeDownLoad>0)//ѡ��������
	{
		(AfxGetMainWnd()->GetDlgItem(IDC_DOWN_PARM))->EnableWindow();
	}
	else
	{
		(AfxGetMainWnd()->GetDlgItem(IDC_DOWN_PARM))->EnableWindow(0);
	}
}


void CUpperLevelSoftDlg::OnBnClickedBtnConnectDown()
{
	m_JudgeIsOperationOrder.ConnectBtnDown=TRUE;
	const static COLORREF GreenColor=RGB(0,255,5);
	const static COLORREF RedColor=RGB(255,0,0);
	if (m_Connected==false)
	{
		bInitState=AGV_Init(&mydwDevice);
		if(!bInitState)
		{
			PostQuitMessage(0);
			m_Connect="��";
			m_Connected=false;
			return ;
		}
		TCHAR strtmp[255];
		TCHAR buftmp[255];
		FillMemory(strtmp, 255, '\0');
		FillMemory(buftmp, 255, '\0');
		sprintf((char *)strtmp, "K");
		PmacGetResponseA(mydwDevice, (PCHAR)buftmp, 255, (PCHAR)strtmp);// ͨѶ״̬,��������Ǹ���ַ���ڣ�����Ϊ�ɹ�
		m_Connect="ͨ";
		m_Connected=true;
		OnBnClickedPumppowerOn(0,0);  //����λ������
		OnBnClickedStartmotorOn(0,0);
	}
	else
	{
		MessageBox(_T("��λ�������ӣ�"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
	}

}


void CUpperLevelSoftDlg::OnBnClickedSelectReg()
{
	if (m_JudgeIsOperationOrder.ReadPicyureBtnDown==FALSE)
	{
		MessageBox(_T("���ȶ�ȡͼƬ��"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	if (m_JudgeIsOperationOrder.InvalidColorBtnDown==FALSE)
	{
		MessageBox(_T("����ָ����Ч��ɫ��"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	if (m_JudgeIsOperationOrder.ReconfigureBtnDown==FALSE)
	{
		MessageBox(_T("����ʶ����"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	if (m_JudgeIsOperationOrder.DrawAreaIdentificationResultsBtnDown==FALSE)
	{
		MessageBox(_T("����ѡ�����ʶ����������"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	m_JudgeIsOperationOrder.ConnectBtnDown=TRUE;
	if (m_JudgeIsOperationOrder.ConnectBtnDown==FALSE)
	{
		MessageBox(_T("����������λ����"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	m_DownValue.CheckHeight(g_cWorkRegionParm.HeightofWorkRegion*m_fYRealRatio); //��ÿ�е�����ĸ߶�������ȥ
	m_JudgeIsOperationOrder.DesignatedWorkAreaBtnDown=TRUE;
	m_bSelectRegToDown=true;
	m_bUSE_CRossCursor=true;
}


void CUpperLevelSoftDlg::OnBnClickedDownParm()
{
	if (m_JudgeIsOperationOrder.ReadPicyureBtnDown==FALSE)
	{
		MessageBox(_T("���ȶ�ȡͼƬ��"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	if (m_JudgeIsOperationOrder.InvalidColorBtnDown==FALSE)
	{
		MessageBox(_T("����ָ����Ч��ɫ��"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	if (m_JudgeIsOperationOrder.ReconfigureBtnDown==FALSE)
	{
		MessageBox(_T("����ʶ����"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	if (m_JudgeIsOperationOrder.DrawAreaIdentificationResultsBtnDown==FALSE)
	{
		MessageBox(_T("����ѡ�����ʶ����������"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	if (m_JudgeIsOperationOrder.ConnectBtnDown==FALSE)
	{
		MessageBox(_T("����������λ����"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	if (m_JudgeIsOperationOrder.DesignatedWorkAreaBtnDown==FALSE)
	{
		MessageBox(_T("����ָ����������"),_T("��ʾ"),/*MB_ICONERROR*/MB_ICONINFORMATION);
		return;
	}
	if (m_iGUISelectRegOrAll==1)//ȫ����Ϳ�������Ĳ���ͳһ����
	{
		//m_cResAdapter.ImportRecedRes(&m_cRecgnizePic);
#ifdef USE_CONTENT_IN_DEPENDENT_CLASS
		DownLoadParmToMotionControlCard();
#endif
		DownLoadPlcParm(-1);
		//m_DownValue.GetDownValueMotion(Itbegin,ItEnd);           //�����˶�����
		//m_cResAdapter.ExtendMotionRangeForInsertedNullCell();//���䷶Χ���������ǰ��������������������
	}
	else//������������
	{
		
#ifdef USE_CONTENT_IN_DEPENDENT_CLASS
		DownLoadParmToMotionControlCard();
#endif
		DownLoadPlcParm(m_uRegToBeDownLoad);		
	}
	m_cResAdapter.ExtendMotionRangeForInsertedNullCell();//���䷶Χ���������ǰ��������������������
	TranslateAllParmToNewStlye();
	CoordinateFrame m_Frame;
	m_Frame.BeginXPoint=0;
	m_Frame.BeginYPoint=0;
	m_Frame.FrameRange=0;
	m_Frame.IsRequireCanGet=true;
	if (m_uGunNum!=1)             //����ǹ
	{
		//m_Frame=JudgeUnitIsOutOfRange(m_CameraPosition.FirstCameraX,m_CameraPosition.FirstCameraY,m_CameraPosition.SecondCameraX,m_CameraPosition.SecondCameraY,PerUnitWidth,m_fWorkRegWidth,m_fWorkRegHeight,false);
	
	}
	else                          //����ǹ
	{   
		if(m_CameraPosition.Firstcameradignose&&m_CameraPosition.Secondcameradignose)
		       m_Frame=JudgeUnitIsOutOfRange(m_CameraPosition.FirstCameraX,m_CameraPosition.FirstCameraY,m_CameraPosition.SecondCameraX,m_CameraPosition.SecondCameraY,PerUnitWidth,m_fWorkRegWidth,m_fWorkRegHeight,true);
		else{
			if(!m_CameraPosition.Firstcameradignose&&m_CameraPosition.Secondcameradignose)
			    {
					MessageBox("��һ�������ʶ����");
			        return ;
			    }
			else if(m_CameraPosition.Firstcameradignose&&!m_CameraPosition.Secondcameradignose)
			    {
					MessageBox("�ڶ��������ʶ����");
					return ;
			    }
			else
			    {
					MessageBox("�����������ʶ����");
					return ;
			    }					
		    }
			
	}
	/*if (m_Frame.IsRequireCanGet==false)
	{
		return;
	}*/

	if (!m_DownValue.StartOpenPlc("E:\\",m_Frame,m_fGunDelay,m_fRevGunDelay))
	{
		MessageBox(_T("���󣬴򲻿���Ҫд��Ĳ����ļ�,����㲻�ɹ�"));
	}
	
}
void CUpperLevelSoftDlg::DownLoadPlcParm(unsigned RegIndex)
{
//#ifdef USE_COMPLEX_PLC_PARM_TYPE
	//m_cResAdapter.SetParmOfGunForPlcParm();
	long t1=GetTickCount();
	m_itPlcParmVecBegin=m_cResAdapter.ExporComplexPLCParmVec(RegIndex);
	m_itPlcParmVecEnd=m_cResAdapter.ExportComplexPLC_ParmVecEnd(RegIndex);
	
	m_Storage.clear();
	FILE *m_Pfile=fopen("E:\\ValueParml.txt","w");
	for (m_itPlcParmVecBegin;m_itPlcParmVecBegin<m_itPlcParmVecEnd;m_itPlcParmVecBegin++)
	{
		m_Storage.push_back(*m_itPlcParmVecBegin);
		CString t3;
		t3.Format("%d\n",*m_itPlcParmVecBegin);
		fwrite(t3,1,strlen(t3),m_Pfile);
	}
	
	int c=g_cWorkRegionParm.HeightofWorkRegion;
	/*FILE *m_Pfile=fopen("E:\\ValueParml.txt","w");
	CString t2;
	t2.Format("%ld\n",RegIndex);
	fwrite(t2,1,strlen(t2),m_Pfile);
	for (itBegin;itBegin<itEnd;itBegin++)
	{
		CString t3;
		t3.Format("%d\n",*itBegin);
		fwrite(t3,1,strlen(t3),m_Pfile);
	}*/
	//fclose(m_Pfile);
	//long t2=GetTickCount();//����ν�����ȡ��ϵͳ����ʱ��(ms)  
	//CString str; 
//	str.Format(_T("time:%dms"),(t2-t1));//ǰ��֮���������ʱ��        

	/*AfxMessageBox(str); */

//	CResultAdapter<CRecognizePicture,CPaintCell>::PLC_Parm_It_TYPE itFinalDat=itEnd-1;
//
//#else
//	CResultAdapter<CRecognizePicture,CPaintCell>::PLC_Parm_It_TYPE itBegin=m_cResAdapter.ExporPLCParmVec(RegIndex);
//	CResultAdapter<CRecognizePicture,CPaintCell>::PLC_Parm_It_TYPE itEnd=m_cResAdapter.ExportPLC_ParmVecEnd(RegIndex);
//	CResultAdapter<CRecognizePicture,CPaintCell>::PLC_Parm_It_TYPE itFinalDat=itEnd-1;
//
//#endif
//	CString RecResultToSend;
//	CString strTmp;
//	int Addr=99;//100��ַ��ʼ�����ݣ�100ǰ�и��ļ�ͷ
//	///////////////////////////////ͷ///////////////////////////////////////////
//	RecResultToSend.Format(_T("%04x"),*itBegin);		
//	//RecResultToSend=strTmp;//����֮��û�мӷָ�����ע����
//	strTmp.Format(_T("%04d"),Addr);
//	m_cPlcCommu.SendSingleFrameData(RecResultToSend,strTmp);
//	//m_cPlcCommu.SendMultiFrameData(RecResultToSend,strTmp,0);//1������һ��
//	//Sleep(5000);
//	//if (!m_cPlcCommu.CheckCommandResponse())//PLC��������Ӧ��ʾ�����������Ӧ
//	//{
//	//	MessageBox("PLC��Ӧ���󣬳����ط������Ȼ���ɹ�����ֹ���ݴ���");
//	//	return;
//	//}
//	itBegin++;
//	for (itBegin;itBegin<itFinalDat;itBegin++)
//	{
//		Addr++;
//		RecResultToSend.Format(_T("%04x"),*itBegin);	
//		strTmp.Format(_T("%04d"),Addr);
//		//m_cPlcCommu.SendMultiFrameData(RecResultToSend,strTmp);//1������һ��
//		m_cPlcCommu.SendSingleFrameData(RecResultToSend,strTmp);
//		//Sleep(20);
//		//if (!m_cPlcCommu.CheckCommandResponse())//PLC��������Ӧ��ʾ�����������Ӧ
//		//{
//		//	MessageBox("PLC��Ӧ���󣬳����ط������Ȼ���ɹ�����ֹ���ݴ���");
//		//	return;
//		//}
//	}	
//	Addr++;
//	RecResultToSend.Format(_T("%04x"),*itFinalDat);	
//	strTmp.Format(_T("%04d"),Addr);
//	//m_cPlcCommu.SendMultiFrameData(RecResultToSend,strTmp,2);//1������һ��
//	m_cPlcCommu.SendSingleFrameData(RecResultToSend,strTmp);
////	Sleep(20);
//	//if (!m_cPlcCommu.CheckCommandResponse())//PLC��������Ӧ��ʾ�����������Ӧ
//	//{
//	//	MessageBox("PLC��Ӧ���󣬳����ط������Ȼ���ɹ�����ֹ���ݴ���");
//	//	return;
//	//}
//	::MessageBox(NULL,_T("��PLC���ݴ���ɹ�"),_T("�ɹ�"),MB_OK);
//	//////////////////////////////////////////////////////////////////////////
//	//strTmp.Format("%04x",Addr);
//	//RecResultToSend.Format("%04x",187);	
//	//m_cPlcCommu.SendMultiFrameData(RecResultToSend,strTmp,0);//��������һ��
//	//for (int i=1;i<40;i++)
//	//{
//	//	Addr=Addr+i;
//	//	strTmp.Format("%04x",Addr);
//	//	RecResultToSend.Format("%04x",187+i);	
//	//	m_cPlcCommu.SendMultiFrameData(RecResultToSend,strTmp);//��������һ��
//	//}

	//strTmp.Format("%04x",Addr+2);
	//RecResultToSend.Format("%04x",189);	
	//m_cPlcCommu.SendMultiFrameData(RecResultToSend,strTmp,2);//��������һ��
	//m_cPlcCommu.SendSingleFrameData(RecResultToSend,strTmp);//��������һ��
}

void CUpperLevelSoftDlg::OnBnClickedAction()
{
	/*if (m_PaintDlg.DoModal()==IDOK)
	{

	}*/
	CPaintDlg m_PaintDlg(m_Connect,m_Connected,this);             //����λ���������ʼ��
	if(m_PaintDlg.DoModal()==IDOK)
	{
	}
}


void CUpperLevelSoftDlg::OnBnClickedLowMoniter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
bool CUpperLevelSoftDlg::DownLoadParmToMotionControlCard(void)
{
	/*if (m_uRegToBeDownLoad==0)
	{ MessageBox(_T("��ȷ����ѡ��������"));
	}*/
	//m_cMotionCommu.connect_Wraped();	
	m_cResAdapter.ImportRecedRes(&m_cRecgnizePic);//�Ƶ�����17.12.19�޸�
	m_itMotionParmVecBegin=m_cResAdapter.ExportMotionParmVec(m_uRegToBeDownLoad);
	m_itMotionParmVecEnd=m_cResAdapter.ExportMotionParmVecEnd(m_uRegToBeDownLoad);
	
	//m_DownValue.GetDownValueMotion(Itbegin,ItEnd);           //�����˶�����,�Ƶ�����17.12.19�޸�
	/*FILE *m_Pfole=fopen("E:\\ValueParm.txt","w");
	for (Itbegin;Itbegin<ItEnd;Itbegin++)
	{
		CString tt;
		tt.Format("%lf\n",*Itbegin);
		fwrite(tt,1,strlen(tt),m_Pfole);
	}
	fclose(m_Pfole);*/
	/*if (!m_cMotionCommu.QueryCntConectStat())
	{
		MessageBox(_T("���˶����ƿ����Ӳ��ɹ�������ʧ��"));
		return false;
	}
	
	if (m_cMotionCommu.DownLoadParmFlow(Itbegin,ItEnd))
	{
		MessageBox(_T("���سɹ�"));
	}*/
//	m_cMotionCommu.Disconnect();
	return true;
}
long CUpperLevelSoftDlg::OnSetVelAndRealRatio(WPARAM CellRealWidth,LPARAM Vel)
{
	PerUnitWidth=(float)CellRealWidth/PRE_MULTIED_FACTOR_FOR_REAL_PARM;
	m_fRealRatio=(float)CellRealWidth/gRowWidth/PRE_MULTIED_FACTOR_FOR_REAL_PARM;//
	m_fYRealRatio=m_fRealRatio;
	m_fRealVel=(float)Vel/INDUCE_LENGTH/PRE_MULTIED_FACTOR_FOR_REAL_PARM;//

	m_cResAdapter.SetRatioOfPixel(m_fRealRatio,m_fYRealRatio);
	m_cResAdapter.SetRealVel(m_fRealVel);
	/*m_DownValue.GetDownMotionSpeed(m_fRealVel);*/
	return 0;
}
long CUpperLevelSoftDlg::OnSetGunParm (WPARAM GunP,LPARAM GunMode)
{
	GunParm* pGunParm=(GunParm*)GunP;

	m_uGunNum=pGunParm->GunNum/PRE_MULTIED_FACTOR_FOR_REAL_PARM;
	m_fGunDis=(float)pGunParm->GunDis/PRE_MULTIED_FACTOR_FOR_REAL_PARM;
	m_PerGunColor=pGunParm->ColoPerGun;
#ifdef USE_COMPLEX_PLC_PARM_TYPE
	m_cResAdapter.SetParmOfGunForParm(m_uGunNum,m_fGunDis,(float)pGunParm->CurgunMode,(float)pGunParm->ColoPerGun);
#endif
	m_DownValue.GetGunModelAndGunDistance(m_uGunNum,m_fGunDis);
	return 0;
}

long CUpperLevelSoftDlg::OnSetWorkRegParm (WPARAM WorkRegWidth,LPARAM WorkRegHeight)
{
	m_fWorkRegWidth=(float)WorkRegWidth/PRE_MULTIED_FACTOR_FOR_REAL_PARM;
	g_cWorkRegionParm.WidthOfWorkRegion=Floor4_Ceil5(m_fWorkRegWidth/m_fRealRatio);
	m_fWorkRegHeight=(float)WorkRegHeight/PRE_MULTIED_FACTOR_FOR_REAL_PARM;
	g_cWorkRegionParm.HeightofWorkRegion=Floor4_Ceil5(m_fWorkRegHeight/m_fRealRatio);
	return 0;
}
long CUpperLevelSoftDlg::OnSetGun0DelayParm (WPARAM OpenDelay,LPARAM CloseDelay)
{
	m_fGunDelay[0][0]=((float) OpenDelay-20000)/100;
	m_fGunDelay[0][1]=((float) CloseDelay-20000)/100;
	return 0;
}
long CUpperLevelSoftDlg::OnSetGun1DelayParm(WPARAM OpenDelay,LPARAM CloseDelay)
{
	m_fGunDelay[1][0]=((float) OpenDelay-20000)/100;
	m_fGunDelay[1][1]=((float) CloseDelay-20000)/100;
	return 0;
}
long CUpperLevelSoftDlg::OnSetGun2DelayParm (WPARAM OpenDelay,LPARAM CloseDelay)
{
	m_fGunDelay[2][0]=((float) OpenDelay-20000)/100;
	m_fGunDelay[2][1]=((float) CloseDelay-20000)/100;
	return 0;
}
long CUpperLevelSoftDlg::OnSetGun3DelayParm (WPARAM OpenDelay,LPARAM CloseDelay)
{
	m_fGunDelay[3][0]=((float) OpenDelay-20000)/100;
	m_fGunDelay[3][1]=((float) CloseDelay-20000)/100;
	return 0;
}

long CUpperLevelSoftDlg::OnSetGun0RevDelayParm (WPARAM OpenDelay,LPARAM CloseDelay)
{
	m_fRevGunDelay[0][0]=((float) OpenDelay-20000)/100;
	m_fRevGunDelay[0][1]=((float) CloseDelay-20000)/100;
	return 0;
}
long CUpperLevelSoftDlg::OnSetGun1RevDelayParm(WPARAM OpenDelay,LPARAM CloseDelay)
{
	m_fRevGunDelay[1][0]=((float) OpenDelay-20000)/100;
	m_fRevGunDelay[1][1]=((float) CloseDelay-20000)/100;
	return 0;
}
long CUpperLevelSoftDlg::OnSetGun2RevDelayParm (WPARAM OpenDelay,LPARAM CloseDelay)
{
	m_fRevGunDelay[2][0]=((float) OpenDelay-20000)/100;
	m_fRevGunDelay[2][1]=((float) CloseDelay-20000)/100;
	return 0;
}
long CUpperLevelSoftDlg::OnSetGun3RevDelayParm (WPARAM OpenDelay,LPARAM CloseDelay)
{
	m_fRevGunDelay[3][0]=((float) OpenDelay-20000)/100;
	m_fRevGunDelay[3][1]=((float) CloseDelay-20000)/100;
	return 0;
}

long CUpperLevelSoftDlg::SavePmcDiretory(WPARAM Value_Gun,LPARAM descirble)
{
	/*BSTR b = (BSTR)descirble;
	CString s(b);*/
	//SysFreeString(b);
	//SaveDirectoryUpFile=b;
	SaveDirectoryUpFile=(char*)descirble;
	m_DownValue.StartOpen(SaveDirectoryUpFile);
	m_DownValue.StartOpenPlc(SaveDirectoryUpFile,m_CoordinateFrame,m_fGunDelay,m_fRevGunDelay);
	return 0;
}

void CUpperLevelSoftDlg::OnBnClickedOpensharp()   //�򿪺��⴫����
{
	if (m_Connected==true)
	{
		m_SharpRedMeasure.Init();
		AfxBeginThread(ClientRecvThread, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	}
	
}
UINT ClientRecvThread(LPVOID lpParm )
{
	CUpperLevelSoftDlg* pParentSharp = (CUpperLevelSoftDlg*)lpParm;
	for(;;)
	{
		if (pParentSharp->m_SharpRedMeasure.m_OpenOrNot==0)
		{
			;
		}
		else
		{
			pParentSharp->m_SharpRedMeasure.GetCapyture();
			pParentSharp->JudgeFloorIsFlat(pParentSharp->m_SharpRedMeasure.m_SharpDistance,pParentSharp->m_SharpRedMeasure.m_SharpDistance1,pParentSharp->m_SharpRedMeasure.m_SharpDistance2);
		}
		//UpdateData(FALSE);
	}
	return 0;
}
void CUpperLevelSoftDlg::JudgeFloorIsFlat(int FirstDistance,int SecondDistance,int ThirdDistance)
{
	CString threadl;

	GetDlgItem(IDC_SHARPTHREASHOLD)->GetWindowText(threadl);
	m_SharpJudgeThreshold=atoi(threadl);
	if (((fabs((double)(FirstDistance-SecondDistance))<m_SharpJudgeThreshold))&&((fabs((double)(FirstDistance-ThirdDistance))<m_SharpJudgeThreshold)))
	{
		m_JudgeFloorIsFlatL="ƽ��";
	}
	else
		m_JudgeFloorIsFlatL="��ƽ��";
	GetDlgItem(IDC_FLOORISFLAT)->SetWindowText(m_JudgeFloorIsFlatL);
}
bool CUpperLevelSoftDlg::AGV_Init(DWORD* dwDevice)
{
	(*dwDevice)=PmacSelect(NULL);
	if ((*dwDevice)>=0&&(*dwDevice)<=7)
	{
		if(!OpenPmacDevice(*dwDevice))
		{
			bAGV_InitState=false;
			return false;
		}
	}
	else
	{
		bAGV_InitState=false;
		return false;
	}
	TCHAR strtmp[255];
	TCHAR buftmp[255];

	FillMemory(strtmp,255,'\0');	
	FillMemory(buftmp,255,'\0');

	sprintf((char *)strtmp,"#1o0 #2o0 #3o0 #4o0 m7917=1 m7918=1 m7937=1 m7938=0");
	PmacGetResponseA(*dwDevice,(PCHAR)buftmp,255,(PCHAR)strtmp);
	bAGV_InitState = true;
	mydwDevice = (*dwDevice);
	return true;
}
long CUpperLevelSoftDlg::OnBnClickedPumppowerOn(WPARAM ValueOne,LPARAM ValueTwo)  //���û�����
{
	if(m_Connected==true)
	{
		TCHAR strtmp[255];
		TCHAR buftmp[255];
		FillMemory(strtmp, 255, '\0');
		FillMemory(buftmp, 255, '\0');
		sprintf((char *)strtmp, "m4008=1 ");
		PmacGetResponseA(mydwDevice, (PCHAR)buftmp, 255, (PCHAR)strtmp);
	}
	else
		MessageBox(_T("��������λ����"));
	return 0;
}
long CUpperLevelSoftDlg::OnBnClickedStartmotorOn(WPARAM ValueOne,LPARAM ValueTwo) //��������� 
{
	if(m_Connected==true)
	{
		TCHAR strtmp[255];
		TCHAR buftmp[255];
		FillMemory(strtmp, 255, '\0');
		FillMemory(buftmp, 255, '\0');
		sprintf((char *)strtmp, "m4000=1 m4001=1 m4002=1");
		PmacGetResponseA(mydwDevice, (PCHAR)buftmp, 255, (PCHAR)strtmp);
	}
	else
		MessageBox(_T("��������λ����"));
	return 0;
}
long CUpperLevelSoftDlg::OnBnClickedPumppowerOff(WPARAM ValueOne,LPARAM ValueTwo)  //���û�����
{
	if (m_Connected==true)
	{
		TCHAR strtmp[255];
		TCHAR buftmp[255];
		FillMemory(strtmp, 255, '\0');
		FillMemory(buftmp, 255, '\0');
		sprintf((char *)strtmp,"m4008=0 ");
		PmacGetResponseA(mydwDevice,(PCHAR)buftmp, 255,(PCHAR)strtmp);
	}
	
	return 0;
}
long CUpperLevelSoftDlg::OnBnClickedStartmotorOff(WPARAM ValueOne,LPARAM ValueTwo) //��������� 
{
	if (m_Connected==true)
	{
		TCHAR strtmp[255];
		TCHAR buftmp[255];
		FillMemory(strtmp, 255, '\0');
		FillMemory(buftmp, 255, '\0');
		sprintf((char *)strtmp, "m4000=0 m4001=0 m4002=0");
		PmacGetResponseA(mydwDevice, (PCHAR)buftmp, 255, (PCHAR)strtmp);
	}
	
	return 0;
}
long  CUpperLevelSoftDlg::OnBnClickedReturn(WPARAM ValueOne,LPARAM ValueTwo)
{
	if (m_Connected==true)
	{
		TCHAR strtmp[255];
		TCHAR buftmp[255];
		FillMemory(strtmp, 255, '\0');
		FillMemory(buftmp, 255, '\0');
		sprintf((char *)strtmp, "&1a  &1b10r ");
		PmacGetResponseA(mydwDevice, (PCHAR)buftmp, 255, (PCHAR)strtmp);
	}
	
	return 0;
}
long  CUpperLevelSoftDlg::OnBnClickedQuit(WPARAM ValueOne,LPARAM ValueTwo)
{
	if (m_Connected==true)
	{
		TCHAR strtmp[255];
		TCHAR buftmp[255];
		FillMemory(strtmp, 255, '\0');
		FillMemory(buftmp, 255, '\0');
		sprintf((char *)strtmp, "m4008=0 ");
		sprintf((char *)strtmp, "m4000=0 m4001=0 m4002=0");
		PmacGetResponseA(mydwDevice, (PCHAR)buftmp, 255, (PCHAR)strtmp);
		ClosePmacDevice(mydwDevice);
	}
	
	return 0;
}
long CUpperLevelSoftDlg::OnBnClickedDownload(WPARAM ValueOne,LPARAM ValueTwo)
{
	if (m_Connected==true)
	{
		CString path;
		char *pathname;
		path="E:\\DownPlcAndMotion.pmc";
		pathname=(char *)path.GetBuffer(0);	
		PmacDownloadA(mydwDevice,NULL,NULL,NULL,pathname,1,1,1,1);
	}
	
	return 0;
}
long CUpperLevelSoftDlg::OnBnClickedRun(WPARAM ValueOne,LPARAM ValueTwo)
{
	if(m_Connected==true)
	{
		TCHAR strtmp[255];
		TCHAR buftmp[255];
		FillMemory(strtmp, 255, '\0');
		FillMemory(buftmp, 255, '\0');
		sprintf((char *)strtmp, "&1a   &1b30r");
		PmacGetResponseA(mydwDevice, (PCHAR)buftmp, 255, (PCHAR)strtmp);
	}
	
	return 0;
}
long CUpperLevelSoftDlg::OnBnClickedStop(WPARAM ValueOne,LPARAM ValueTwo)
{
	if (m_Connected==true)
	{
		TCHAR strtmp[255];
		TCHAR buftmp[255];
		FillMemory(strtmp, 255, '\0');
		FillMemory(buftmp, 255, '\0');
		sprintf((char *)strtmp, "&1b30h");
		PmacGetResponseA(mydwDevice, (PCHAR)buftmp, 255, (PCHAR)strtmp);
	}
	
	return 0;
}
long CUpperLevelSoftDlg::OnBnClickedStopall(WPARAM ValueOne,LPARAM ValueTwo)
{
	if (m_Connected==true)
	{
		TCHAR strtmp[255];
		TCHAR buftmp[255];
		FillMemory(strtmp, 255, '\0');
		FillMemory(buftmp, 255, '\0');
		sprintf((char *)strtmp, "&1b30a");
		PmacGetResponseA(mydwDevice, (PCHAR)buftmp, 255, (PCHAR)strtmp);
	}
	
	return 0;
}
long CUpperLevelSoftDlg::OnBnClickedContinue(WPARAM ValueOne,LPARAM ValueTwo)
{
	if (m_Connected==true)
	{
		TCHAR strtmp[255];
		TCHAR buftmp[255];
		FillMemory(strtmp, 255, '\0');
		FillMemory(buftmp, 255, '\0');
		sprintf((char *)strtmp, "&1b30r");
		PmacGetResponseA(mydwDevice, (PCHAR)buftmp, 255, (PCHAR)strtmp);
	}
	
	return 0;
}
long  CUpperLevelSoftDlg::OnBnClickedWash(WPARAM ValueOne,LPARAM ValueTwo)
{
	if(m_Connected==true)
	{
		TCHAR strtmp[255];
		TCHAR buftmp[255];
		FillMemory(strtmp, 255, '\0');
		FillMemory(buftmp, 255, '\0');
		CString Parm="";
		Parm=(char*)ValueTwo;
		sprintf((char *)strtmp, Parm);
		PmacGetResponseA(mydwDevice, (PCHAR)buftmp, 255, (PCHAR)strtmp);
	}
	return 0;
}
long CUpperLevelSoftDlg::OnBnClickedStopwash(WPARAM ValueOne,LPARAM ValueTwo)
{
	if (m_Connected==true)
	{
		TCHAR strtmp[255];
		TCHAR buftmp[255];
		FillMemory(strtmp, 255, '\0');
		FillMemory(buftmp, 255, '\0');
		sprintf((char *)strtmp, "M4009=0 M4010=0 M4011=0 M4012=0");
		PmacGetResponseA(mydwDevice, (PCHAR)buftmp, 255, (PCHAR)strtmp);
	}
	
	return 0;
}
long CUpperLevelSoftDlg::OnBnClickedAlignment(WPARAM ValueOne,LPARAM ValueTwo)
{
	AlignmentButton *m_Answer=(AlignmentButton *)ValueOne;
	if (m_Answer->Button_AddX==true)
	{
	}
	else if (m_Answer->Button_AddY==true)
	{
	}
	else if (m_Answer->Button_ReduceX==true)
	{
	}
	else if (m_Answer->Button_ReduceY==true)
	{
	}
	return 0;
}
long CUpperLevelSoftDlg::OnBnReleaseAlignment(WPARAM ValueOne,LPARAM ValueTwo)
{
	return 0;
}
void CUpperLevelSoftDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_Connected==true)
	{
		OnBnClickedReturn(0,0);
		OnBnClickedPumppowerOff(0,0);
		OnBnClickedStartmotorOff(0,0);
	}
	
	CDialogEx::OnOK();
}


BOOL CUpperLevelSoftDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	HCURSOR hcursor;
	if (m_bUSE_CRossCursor)
	{
		hcursor=AfxGetApp()-> LoadStandardCursor(IDC_CROSS);
	}
	else
	{
		hcursor=AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	}
	SetCursor(hcursor);	
	return	TRUE;
}


void CUpperLevelSoftDlg::OnBnClickedRaRegToDown1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

CoordinateFrame CUpperLevelSoftDlg::JudgeUnitIsOutOfRange(float FirstCameraX,float FirstCameraY,float SecondCameraX,float SecondCameraY,int UintWidth,int Width,int Heigh,bool OneGun)
{	
	m_CoordinateFrame.IsRequireCanGet=false;
	float CameraCoordinatesX=SecondCameraX-FirstCameraX;
	float CameraCoordinatesY=SecondCameraY-FirstCameraY;
	float CameraCoordinatesAngle=atan2(CameraCoordinatesY,CameraCoordinatesX+SECONDCAMERAXORIGINPOINT-FIRSTCAMERAXORIGINPOINT); //ƫ��
	if (fabs(CameraCoordinatesAngle)>ANGLELIMIT)
	{
		MessageBox("ƫ�ǹ�����Ҫ�ֶ�����");
		return m_CoordinateFrame;
	}
	//�����жϴ���Ϳ�������½ǵ��Ƿ񳬳����ޣ����������Ҫ
	float LowerLeftXPoint=0;
	if (OneGun==true)
	{
		LowerLeftXPoint=FIRSTCAMERAXORIGINPOINT+FirstCameraX;
	}
	else
		LowerLeftXPoint=FIRSTCAMERAXORIGINPOINT+FirstCameraX+FINALLYGUNPOINTY*sin(CameraCoordinatesAngle);   //����ǹ
	float LowerLeftXAllowancePoint=FRAMEX-UintWidth*0.5;
	float LowerLeftYAllowance=0;
	if (OneGun==true)
	{
		LowerLeftYAllowance=FIRSTCAMERAYORIGINPOINT+FirstCameraY;       //��ǰ���½�������ϵ�µ�����ֵ
	}
	else
		LowerLeftYAllowance=FIRSTCAMERAYORIGINPOINT+FirstCameraY-FINALLYGUNPOINTY*cos(CameraCoordinatesAngle);       //��ǰ���½�������ϵ�µ�����ֵ
	float LowerLeftYAllowancePoint=MAXPAINTRANGEY+FRAMEY;                 //������Y�����ܴﵽ�ļ�������
	if (fabs(LowerLeftXPoint-LowerLeftXAllowancePoint)>FRAMEXLIMIT&&fabs(LowerLeftYAllowance-LowerLeftYAllowancePoint)>FRAMEYLIMIT)
	{
		MessageBox("�������½���X���Y���ϳ�������");
		return m_CoordinateFrame;
	}
	if (fabs(LowerLeftXPoint-LowerLeftXAllowancePoint)>FRAMEXLIMIT)
	{
		MessageBox("�������½���X���ϳ�������");
		return m_CoordinateFrame;
	}
	if (fabs(LowerLeftYAllowance-LowerLeftYAllowancePoint)>FRAMEYLIMIT)
	{
		MessageBox("�������½���Y���ϳ�������");
		return m_CoordinateFrame;
	}
	if (LowerLeftYAllowance>=LowerLeftYAllowancePoint||LowerLeftXPoint<=LowerLeftXAllowancePoint)
	{
		m_CoordinateFrame.IsRequireCanGet=false;
		MessageBox("�������½ǳ�����Ϳ����");
		return m_CoordinateFrame;
	}
	//�����жϴ���Ϳ�������Ͻǵ��Ƿ񳬳����ޣ��������Ҫ
	float TopLeftXPoint=0;
	if (OneGun==true)
	{
		TopLeftXPoint=FIRSTCAMERAXORIGINPOINT+FirstCameraX+Heigh*sin(CameraCoordinatesAngle);
	}
	else
		TopLeftXPoint=FIRSTCAMERAXORIGINPOINT+FirstCameraX+(Heigh+FIRSTGUNPOINTY)*sin(CameraCoordinatesAngle);       //����ǹ
	float TopLeftXAllowancePoint=FRAMEX-UintWidth*0.5;
	float TopLeftYPoint=0;
	if (OneGun==true)
	{
		TopLeftYPoint=FIRSTCAMERAYORIGINPOINT+FirstCameraY-Heigh*cos(CameraCoordinatesAngle);
	}
	else 
		TopLeftYPoint=FIRSTCAMERAYORIGINPOINT+FirstCameraY-(Heigh+FIRSTGUNPOINTY)*cos(CameraCoordinatesAngle);        //����ǹ
	float TopLeftYAllowancePoint=FRAMEY;
	if (TopLeftYPoint<=TopLeftYAllowancePoint||TopLeftXPoint<=TopLeftXAllowancePoint)
	{
		m_CoordinateFrame.IsRequireCanGet=false;
		MessageBox("�������Ͻǳ�����Ϳ����");
		return m_CoordinateFrame;
	}
	//�����жϴ���Ϳ�������½ǵ��Ƿ񳬳����ޣ��������Ҫ
	float LowRightXPoint=0;
	if (OneGun==true)
	{
		LowRightXPoint=FIRSTCAMERAXORIGINPOINT+FirstCameraX+Width*cos(CameraCoordinatesAngle);
	}
	else
		LowRightXPoint=FIRSTCAMERAXORIGINPOINT+FirstCameraX+Width*cos(CameraCoordinatesAngle)+FINALLYGUNPOINTY*sin(CameraCoordinatesAngle);
	float LowRightXAllowance=MAXPAINTRANGEX+UintWidth*0.5+FRAMEX;
	float LowRightYPoint=0;
	if (OneGun==true)
	{
		LowRightYPoint=FIRSTCAMERAYORIGINPOINT+FirstCameraY+Width*sin(CameraCoordinatesAngle);
	}
	else
		LowRightYPoint=FIRSTCAMERAYORIGINPOINT+FirstCameraY+Width*sin(CameraCoordinatesAngle)-FINALLYGUNPOINTY*cos(CameraCoordinatesAngle);
	float LowRightYAllowance=MAXPAINTRANGEY+FRAMEY;
	if (LowRightXPoint>=LowRightXAllowance||LowRightYPoint>=LowRightYAllowance)	
	{
		m_CoordinateFrame.IsRequireCanGet=false;
		MessageBox("�������½ǳ�����Ϳ����");
		return m_CoordinateFrame;
	}
	//�����жϴ���Ϳ�������Ͻǵ��Ƿ񳬳����ޣ��������Ҫ
	float TopRightXPoint=0;
	if (OneGun==true)
	{
		TopRightXPoint=FIRSTCAMERAXORIGINPOINT+FirstCameraX+Width*cos(CameraCoordinatesAngle)+Heigh*sin(CameraCoordinatesAngle);
	}
	else
		TopRightXPoint=FIRSTCAMERAXORIGINPOINT+FirstCameraX+Width*cos(CameraCoordinatesAngle)+(Heigh+FIRSTGUNPOINTY)*sin(CameraCoordinatesAngle);
	float TopRightXAllowance=MAXPAINTRANGEX+UintWidth*0.5+FRAMEX;
	float TopRightYPoint=0;
	if (OneGun==true)
	{
		TopRightYPoint=FIRSTCAMERAYORIGINPOINT+FirstCameraY-Heigh*cos(CameraCoordinatesAngle)-Width*sin(CameraCoordinatesAngle);
	}
	else
		TopRightYPoint=FIRSTCAMERAYORIGINPOINT+FirstCameraY-(Heigh+FIRSTGUNPOINTY)*cos(CameraCoordinatesAngle)-Width*sin(CameraCoordinatesAngle);
	float TopRightYAllowance=FRAMEY;
	if (TopRightXPoint>=TopRightXAllowance||TopRightYPoint<=TopRightYAllowance)
	{
		m_CoordinateFrame.IsRequireCanGet=false;
		MessageBox("�������Ͻǳ�����Ϳ����");
		return m_CoordinateFrame;
	}
	float BeginXPoint=TopLeftXPoint+UintWidth*0.5-FRAMEX;
	float BeginYPoint=TopLeftYPoint-FRAMEY;
	m_CoordinateFrame.IsRequireCanGet=true;
	m_CoordinateFrame.BeginXPoint=BeginXPoint;
	m_CoordinateFrame.BeginYPoint=BeginYPoint;
	m_CoordinateFrame.FrameRange=CameraCoordinatesAngle;
	return m_CoordinateFrame;
}

void CUpperLevelSoftDlg::OnBnClickedButton2ColorReced()
{
	if (m_bRecedPic)
	{
		m_cResAdapter.AddMachineIndexOnRule(0);
		UpdateAllTextOnColorRecBtn();
	}

	//ShowColorIndexInButonText(3);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CUpperLevelSoftDlg::OnBnClickedButton2ColorReced2()
{
	if (m_bRecedPic)
	{
		m_cResAdapter.AddMachineIndexOnRule(1);
		UpdateAllTextOnColorRecBtn();
	}

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CUpperLevelSoftDlg::OnBnClickedButton2ColorReced3()
{
	if (m_bRecedPic)
	{
		m_cResAdapter.AddMachineIndexOnRule(2);
		UpdateAllTextOnColorRecBtn();
	}	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CUpperLevelSoftDlg::OnBnClickedButton2ColorReced4()
{
	if (m_bRecedPic)
	{
		m_cResAdapter.AddMachineIndexOnRule(3);
		UpdateAllTextOnColorRecBtn();
	}	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CUpperLevelSoftDlg::OnBnClickedButton2ColorReced5()
{
	if (m_bRecedPic)
	{
		m_cResAdapter.AddMachineIndexOnRule(4);
		UpdateAllTextOnColorRecBtn();
	}	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CUpperLevelSoftDlg::OnBnClickedButton2ColorReced6()
{
	if (m_bRecedPic)
	{
		m_cResAdapter.AddMachineIndexOnRule(5);
		UpdateAllTextOnColorRecBtn();
	}	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

bool CUpperLevelSoftDlg::ShowColorIndexInButonText(unsigned IndexOfRecedColor)
{
	if (IndexOfRecedColor>6)
	{
		return false;
	}
	char* ps=strFromUns(m_cResAdapter.QueryMachineColorIndexByRecedIndex(IndexOfRecedColor)) ;
	CString   ps2(ps);
	switch (IndexOfRecedColor)
	{
	case 0:
		m_btnColor1.SetWindowText((ps2));
		break;
	case 1:
		m_btnColor2.SetWindowText(ps2);
		break;
	case 2:
		m_btnColor3.SetWindowText(ps2);
		break;
	case 3:
		m_btnColor4.SetWindowText(ps2);
		break;
	case 4:
		m_btnColor5.SetWindowText(ps2);
		break;
	case 5:
		m_btnColor6.SetWindowText(ps2);
		break;
	}	
	return true;
}

bool CUpperLevelSoftDlg::UpdateAllTextOnColorRecBtn(void)
{
	bool Res=true;
	Res=Res&ShowColorIndexInButonText(0);
	Res=Res&ShowColorIndexInButonText(1);
	Res=Res&ShowColorIndexInButonText(2);
	Res=Res&ShowColorIndexInButonText(3);
	Res=Res&ShowColorIndexInButonText(4);
	Res=Res&ShowColorIndexInButonText(5);
	return  Res;
}