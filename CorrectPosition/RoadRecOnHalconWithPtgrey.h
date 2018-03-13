#pragma once
/*!
 * \class  CRoadRecOnHalconWithPtgrey
 *
 * \brief ������������Halcon�⣬ʵ��pointgrey����ɼ�ͼƬ��ͬʱ����CRoadLineDetect����г�����ʶ�𣬶��װ��һЩ����
 *
 * \author admin
 * \date ���� 2015
 */
#include "StdAfx.h"
#include <windows.h>
#include "RoadLineDetect.h"
//using namespace std;
class CRoadRecOnHalconWithPtgrey
{
public:
	CRoadRecOnHalconWithPtgrey(void);
	~CRoadRecOnHalconWithPtgrey(void);
	void Init(Hlong pParent,CRect RecOfWindowDispLay);      //��ʼ����һ���Ի���
	void InitTwo(Hlong pParent,CRect RecOfWindowDispLay);
	bool CreateGrabThread();///<�����ɼ��̣߳�δ����
	UINT GrabThread(LPVOID lpParam);///<�ɼ��߳���Ӧ����δ����
	bool RecOneGrab()///<ʶ��һ�Σ�δ����
	{
		return false;
	}
	LocationCorrect RecOneGrab(unsigned char* pImgData, long lWidth, long lHeight)   ///<ʶ��һ��
	{
		if ( pImgData!=NULL)
		{
			return m_HalconRoadRec.RoadRec(pImgData, lWidth, lHeight);
			
		}
	}
	LocationCorrect RecOneGrabTwo(unsigned char* pImgData, long lWidth, long lHeight)  //�ڶ������ͼ�������
	{
		if ( pImgData!=NULL)
		{
			return m_HalconRoadRec.RoadRecTwo(pImgData, lWidth, lHeight);

		}
	}
	HalconCpp::HTuple * QueryGreyThreshold()
	{
		return m_HalconRoadRec.QueryGreyThreshold();
	}
	bool ChangeGreyThresholdValue(unsigned MinThres,unsigned MaxThres)///<�ı���ֵ�Ľӿں�����ֵ����0~255
	{
		return m_HalconRoadRec.ChangeGreyThresholdValue(MinThres,MaxThres);
	}
	bool ChangeGreyThresholdMaxValue(unsigned MaxThres)///<�ı���ֵ�Ľӿں�����ֵ����0~255
	{
		return m_HalconRoadRec.ChangeGreyThresholdMaxValue(MaxThres);
	}
	bool ChangeGreyThresholdMinValue(unsigned MinThres)///<�ı���ֵ�Ľӿں�����ֵ����0~255
	{
		return m_HalconRoadRec.ChangeGreyThresholdMinValue(MinThres);
	}


	CRoadLineDetect* QueryRoadLineRecSolid(){
		return &m_HalconRoadRec;
	}
	void ChangeThresholdSlider(ThresholdSlide m_ThresholsSlider)        //�ı���ֵ
	{
		 m_HalconRoadRec.SetThresholdSlider(m_ThresholsSlider);
	}
	void ChangeThresholdSliderTwo(ThresholdSlide m_ThresholsSlider)        //�ı���ֵ
	{
		m_HalconRoadRec.SetThresholdSliderTwo(m_ThresholsSlider);
	}
protected:
	CRoadLineDetect m_HalconRoadRec;


	
};

