
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS
#define WMU_UpdateStats (WM_USER+1)
#define WMU_SetRealToMapRatioAndVel (WM_USER+2)//������������ͼƬ��ʵ�ʵı�����,�Լ��ٶȵ���Ϣ
#define WMU_SetGunParm (WM_USER+3)			//������������ǹ��ز�������Ϣ
#define WMU_SetWorkRegParm (WM_USER+4)		//���ù���������ز�������Ϣ

#define WMU_BeginWashGun (WM_USER+5)        //�������ڷ��Ϳ�ʼϴ����ǹ�������ڽ�������λ����ָ��
#define WMU_CloseAllGun  (WM_USER+6)        //�ر���������ϴ�ӵ���ǹ

#define WMU_CameraCorrect (WM_USER+7)       //����õ�������ڻ�׼��ƫ��
#define WMU_SAVEPMCDIRECTORY (WM_USER+8)     //��IDD_PAINTDLG�е��������ɳ���ʱ������һ�Ի�����һ���ź�
#define WMU_PUMPPOWEROFF (WM_USER+9)
#define WMU_MOTOROFF (WM_USER+10)
#define WMU_PUMPPOWERON (WM_USER+11)
#define WMU_MOTORON (WM_USER+12)
#define WMU_RETURNZEROPOINT (WM_USER+13)
#define WMU_STOPALLFUNCTION (WM_USER+14)
#define WMU_DOWNLOADFILE (WM_USER+15)
#define WMU_RUN (WM_USER+16)
#define WMU_TEMPORARYSTOP (WM_USER+17)
#define WMU_STOPNOW (WM_USER+18)
#define WMU_AGAINRUN (WM_USER+19)
#define WMU_BEGINWASHGUN (WM_USER+20)
#define WMU_STOPWASHGUN (WM_USER+21)
//����������Ϣ��ʾ�ڶ�����ǹ���ʱ�����¶���+X�ȵ���Ӧ��Ϣ�ͷſ���Ϣ
#define WMU_ALIGNMENTCLICKED (WM_USER+22)
#define WMU_ALIGNMENTLOOSEN (WM_USER+23)
#define WMU_GUN0_DELAY (WM_USER+24)//��ǹ0�ӳٿ������ݴ�����Ϣ
#define WMU_GUN1_DELAY (WM_USER+25)//��ǹ1�ӳٿ������ݴ�����Ϣ
#define WMU_GUN2_DELAY (WM_USER+26)//��ǹ2�ӳٿ������ݴ�����Ϣ
#define WMU_GUN3_DELAY (WM_USER+27)//��ǹ3�ӳٿ������ݴ�����Ϣ
#define WMU_GUN4_DELAY (WM_USER+28)//��ǹ4�ӳٿ������ݴ�����Ϣ
#define WMU_GUN5_DELAY (WM_USER+29)//��ǹ5�ӳٿ������ݴ�����Ϣ
#define WMU_GUN0_REV_DELAY (WM_USER+30)//��ǹ0�����ӳٿ������ݴ�����Ϣ
#define WMU_GUN1_REV_DELAY (WM_USER+31)//��ǹ1�����ӳٿ������ݴ�����Ϣ
#define WMU_GUN2_REV_DELAY (WM_USER+32)//��ǹ2�����ӳٿ������ݴ�����Ϣ
#define WMU_GUN3_REV_DELAY (WM_USER+33)//��ǹ3�����ӳٿ������ݴ�����Ϣ
#define WMU_GUN4_REV_DELAY (WM_USER+34)//��ǹ4�����ӳٿ������ݴ�����Ϣ
#define WMU_GUN5_REV_DELAY (WM_USER+35)//��ǹ5�����ӳٿ������ݴ�����Ϣ
#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


