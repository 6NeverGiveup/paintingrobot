#pragma once
#ifndef __APPLE__
//#include".\halcon\include\halconcpp\HalconCpp.h"
#include"..\CorrectPosition\halcon\include\halconcpp\HalconCpp.h"
//#include "..\CameraCorrect\halcon\include\halconcpp\HalconCpp.h"
#include <afx.h>
#include "resource.h"
#  if defined(__linux__) && !defined(NO_EXPORT_APP_MAIN)
#    include <X11/Xlib.h>
#  endif
#else

#endif

//#include ".\halcon\include\halconcpp\HalconCpp.h"
#include "..\CameraParm.h"
#include"..\CorrectPosition\halcon\include\halconcpp\HalconCpp.h"
//#pragma comment(lib,".\\halcon\\lib\\x86sse2-win32\\halconcpp.lib")   
#pragma comment(lib,"..\\CorrectPosition\\halcon\\lib\\x86sse2-win32\\halconcpp.lib")
using namespace HalconCpp;
struct LocationCorrect  
{
	double X_Correct;           //ÿ�������⵽�ĵ㵽�������������ʵ�ʾ���
	double Y_Correct;
	bool dignose;
};
struct ThresholdSlide
{
	int MinGreyThreshold;
	int MaxGreyThreshold;
};
class CRoadLineDetect
{
	
public:
	CRoadLineDetect(void);
	~CRoadLineDetect(void);
	void InitHalconRecPointGrey(void);//��ʼ������halcon��PT���
	LocationCorrect RoadRec(unsigned char* pImgData, long lWidth, long lHeight);
	LocationCorrect RoadRecTwo(unsigned char* pImgDataTwo, long lWidthTwo, long lHeightTwo); //ͼ����
protected:
	HalconCpp::HObject /* ho_Image,*/ ho_GrayImage, ho_MapFixed;
	HalconCpp::HObject  ho_ImageMapped, ho_ImageReduced, ho_Regions, ho_RegionErosion;
	HalconCpp::HObject  ho_RegionErosion1, ho_RegionDilation, ho_RegionDilation1;
	HalconCpp::HObject  ho_ConnectedRegions, ho_SelectedRegions1,ho_SelectedRegions2;
// Local control variables
	HalconCpp::HTuple  hv_CameraParameters, hv_CameraPose, hv_Campar;
	HalconCpp::HTuple  hv_CamparVirtualFixed, hv_WindowHandle, hv_Area;
	HalconCpp::HTuple  hv_Row, hv_Column, hv_Area1, hv_Row1, hv_Column1;
	HalconCpp::HTuple  hv_Number, hv_OrnRow, hv_OrnColun, hv_Distance;
	HalconCpp::HTuple  hv_MinDis, hv_i, hv_x, hv_Row2, hv_Column2, hv_MinRow;
	HalconCpp::HTuple  hv_j, hv_y, hv_Mincolumn, hv_k, hv_z, hv_A, hv_B;
	HalconCpp::HTuple  hv_C, hv_D, hv_ATan, hv_ATan1;
	HalconCpp::HTuple hv_WindowID,hv_Width,hv_Height,hv_ContLength,hv_AnswerLength;
	
protected:
	HalconCpp::HObject  ho_Image;///<�ɼ���ͼƬ
	// Local control variables
	HalconCpp::HTuple  hv_AcqHandle;///<PointGrey���
	LocationCorrect m_LocationCorrect;
	LocationCorrect m_LocationCorrectTwo;
	ThresholdSlide m_ThresholdSlide;
	ThresholdSlide m_ThresholdSlideTwo;
private:
	HalconCpp::HTuple m_GreyThreshold[2] ;///<�Ҷ���ֵ��[0]Ϊ���ޣ�[1]Ϊ����
protected:           //�ڶ�������Ĳ���
	HalconCpp::HObject  ho_GrayImageTwo, ho_MapFixedTwo;
	HalconCpp::HObject  ho_ImageMappedTwo, ho_ImageReducedTwo, ho_RegionsTwo, ho_RegionErosionTwo;
	HalconCpp::HObject  ho_RegionErosion1Two, ho_RegionDilationTwo, ho_RegionDilation1Two;
	HalconCpp::HObject  ho_ConnectedRegionsTwo, ho_SelectedRegions1Two,ho_SelectedRegions2Two;
	// Local control variables
	HalconCpp::HTuple  hv_CameraParametersTwo, hv_CameraPoseTwo, hv_CamparTwo;
	HalconCpp::HTuple  hv_CamparVirtualFixedTwo, hv_WindowHandleTwo, hv_AreaTwo;
	HalconCpp::HTuple  hv_RowTwo, hv_ColumnTwo, hv_Area1Two, hv_Row1Two, hv_Column1Two;
	HalconCpp::HTuple  hv_NumberTwo, hv_OrnRowTwo, hv_OrnColunTwo, hv_DistanceTwo;
	HalconCpp::HTuple  hv_MinDisTwo, hv_iTwo, hv_xTwo, hv_Row2Two, hv_Column2Two, hv_MinRowTwo;
	HalconCpp::HTuple  hv_jTwo, hv_yTwo, hv_MincolumnTwo, hv_kTwo, hv_zTwo, hv_ATwo, hv_BTwo;
	HalconCpp::HTuple  hv_CTwo, hv_DTwo, hv_ATanTwo, hv_ATan1Two;
	HalconCpp::HTuple hv_WindowIDTwo,hv_WidthTwo,hv_HeightTwo,hv_ContLengthTwo,hv_AnswerLengthTwo;
	HalconCpp::HObject  ho_ImageTwo;///<�ɼ���ͼƬ
	// Local control variables
	HalconCpp::HTuple  hv_AcqHandleTwo;///<PointGrey���
public:
	HalconCpp::HTuple * QueryGreyThreshold()
	{
		return m_GreyThreshold;
	}
	bool ChangeGreyThresholdValue(unsigned MinThres,unsigned MaxThres)///<�ı���ֵ�Ľӿں�����ֵ����0~255
	{
		if (MinThres>255||MinThres<0||MaxThres>255||MaxThres<0)
		{
			return false;
		}		
		m_GreyThreshold[0]=(HalconCpp::HTuple)(long)MinThres;
		m_GreyThreshold[1]=(HalconCpp::HTuple)(long)MaxThres;
		return true;
	}
	bool ChangeGreyThresholdMinValue(unsigned MinThres)///<�ı���ֵ�Ľӿں�����ֵ����0~255
	{
		if (MinThres>255||MinThres<0)
		{
			return false;
		}		
		m_GreyThreshold[0]=(HalconCpp::HTuple)(long)MinThres;		
		return true;
	}
	bool ChangeGreyThresholdMaxValue(unsigned MaxThres)///<�ı���ֵ�Ľӿں�����ֵ����0~255
	{
		if (MaxThres>255||MaxThres<0)
		{
			return false;
		}		
		m_GreyThreshold[1]=(HalconCpp::HTuple)(long)MaxThres;		
		return true;
	}
public:
	bool InitHalconDisp(Hlong FatherWndID,CRect RecOfWindowDispLay );///<��ʼ��halcon�Ľ����ʾ����
	bool InitHalconDispTwo(Hlong FatherWndID,CRect RecOfWindowDispLay);
	bool GrabPictrueFromPointGrey(void);///<����halcon�������ȡͼƬ����δ����
	bool DisplayRecResu( );///<��ʾʶ����
	void SetThresholdSlider(ThresholdSlide m_ThresholsSlider);
	void SetThresholdSliderTwo(ThresholdSlide m_ThresholsSlider);
public: 
    bool ChoseCloseCameraThread();
	void TranstheImagetoWord(HalconCpp::HTuple Row,HalconCpp::HTuple Column);
	void InitParmFirstCamera();
	void InitParmSecondCamera();
};
 

