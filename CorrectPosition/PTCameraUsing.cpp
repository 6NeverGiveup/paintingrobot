#include "stdafx.h"
#include "PTCameraUsing.h"


CPTCameraUsing::CPTCameraUsing(void)
{
}


CPTCameraUsing::~CPTCameraUsing(void)
{
}
bool  CPTCameraUsing::InitCameraSetting(void)
{
	if (m_pCamera==NULL)
	{
		//ror error;
		return  false;
	}
	Format7ImageSettings FormatSetting;
	//Format7Info Format7InforSetting;
	unsigned upackgeSize;
	float  Percent;
		Error error;
		//GigECamera* pCurCamera=(GigECamera *)m_pCamera;
		Camera* pCurCamera=(Camera *)m_pCamera;
//	GigEImageSettings m_GigimageSettings; //�������Format7 ��������
		
	//	error = pCurCamera->GetGigEImageSettings(&m_GigimageSettings); //��ȡ��ǰ��Format7 ����
		//��������Format7 ����
	/*	m_GigimageSettings.offsetX = 0;
		m_GigimageSettings.offsetY = 0;
		m_GigimageSettings.pixelFormat = PIXEL_FORMAT_MONO8 ;
		m_GigimageSettings.height = 640;
		m_GigimageSettings.width = 480;*/
	//	error =  pCurCamera->SetGigEImageSettings( &m_GigimageSettings );
	/*error =pCurCamera->GetFormat7Configuration(&FormatSetting,&upackgeSize,&Percent);
	if (error== PGRERROR_FAILED)
	{
		return false;
	}
	FormatSetting.pixelFormat=PIXEL_FORMAT_BGR;
	error =pCurCamera->SetFormat7Configuration(&FormatSetting,upackgeSize);*/

}
