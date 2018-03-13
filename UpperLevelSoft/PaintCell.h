#pragma once
//#include "Parm.h"
#include "atltypes.h"
#include <vector>
#include <algorithm>
/********************************************************************
	created:	2011/09/02
	created:	2:9:2011   23:33
	filename: 	f:\�ҵ���Ŀ\SoftProj\UpperLevelSoft\UpperLevelSoft\PaintCell.h
	file path:	f:\�ҵ���Ŀ\SoftProj\UpperLevelSoft\UpperLevelSoft
	file base:	PaintCell
	file ext:	h
	author:		YangGAO
	
	purpose:	�Ӿ����м̳ж�������ʾ��Ϳ����С��λ����ĿǰĬ���Ǿ��Σ��ڲ���λ��Ϊ����
*********************************************************************/
/**
* @class 
* @brief ����ͼƬ�ϲ��������������ԣ���ʵ�����ǰ���������Ҫ��Ϳ�������С����
*
* ���ڶ����������ĳ����,��λΪ���أ�ʵ�ʾ���Ļ���λΪmm
*/
struct PaintAreaTemplate 
{
	long StartPointX;///<��ʼ��X����
	long StartPointY;///<��ʼ��Y����

	long EndPointX;///<�յ�X����
	long EndPointY;///<�յ�Y����

	long WidthInPixel;///<��ȣ���λ����
	long HeightInPixel;///<�߶ȣ���λ����

	double WidthInMM;///<��ȣ���λMM
	double HeightInMM;///<�߶ȣ���λMM
	int Width()
	{
		return EndPointX-StartPointX;
	}
	int Height()
	{
		return EndPointY-StartPointY;
	}
	
};
/**
*@brief ר������ pushBackColor�����е�count ifʹ�ã�ֻ������
*
*
*@parm
*
*@return
*@todo
*/
static bool CountFun (COLORREF& CurColor) { return true; }
typedef std::vector<COLORREF> ColorVec;
class CPaintCell :
	public CRect
{
public:
	CPaintCell(void);
	~CPaintCell(void);
	unsigned m_uColorIndex;///<����Ԫ�ڵ���ɫ����Ӧ�����

/**
*@brief ����ǰ��Ϳ�������ɫ��Ϣ������
*
*��⵱ǰ��ɫ�Ƿ��Ѿ�������ˣ�û�еĻ���������������ɫ���� m_vColorToBePainted��������Ӧ�±긳������Ϳ�����m_uColorIndex�����������
*��ɫ�±긳������Ϳ�����m_uColorIndex
*@parm CurColor��ǰ��Ϳ��Ԫ����ɫ��
*
*@return
*@todo
*/
	void pushBackColor(COLORREF CurColor)
	{
		
		if (m_vColorToBePainted.empty())
		{
			m_vColorToBePainted.push_back(CurColor);
			this->m_uColorIndex=0;
				return;
		}
		ColorVec::iterator iterEnd=m_vColorToBePainted.end();
		ColorVec::iterator iterBeg=m_vColorToBePainted.begin();
		ColorVec::iterator it;
		it = std::find(iterBeg, iterEnd, CurColor);
		if (it!=iterEnd)//��������ɫ
		{
			this->m_uColorIndex=count_if(iterBeg,it,CountFun);//�����������±꣬�±��0��ʼ��count if ǡ�����㣬����-1��
			//this->m_uColorIndex=it-iterBeg;//��֧��iterator֮��ļӼ�
		}
		else//�µ���ɫ��δ������
		{
			m_vColorToBePainted.push_back(CurColor);
			this->m_uColorIndex=m_vColorToBePainted.size()-1;
		}
		//ASSERT(this->m_uColorIndex!=6);
	}
	void InitAll()
	{
		m_vColorToBePainted.clear();
	}
	void operator=(CRect TarRect)
	{
		top=TarRect.top;
		bottom=TarRect.bottom;
		left=TarRect.left;
		right=TarRect.right;
	}
	void operator=(CPaintCell& TarRect)
	{
		top=TarRect.top;
		bottom=TarRect.bottom;
		left=TarRect.left;
		right=TarRect.right;
		m_uColorIndex=TarRect.m_uColorIndex;

	}
	COLORREF& QueryColorByIndex(unsigned ColorIndex)
	{return m_vColorToBePainted[ColorIndex];}
	unsigned QueryNumOfColorToBePainted()
	{return m_vColorToBePainted.size();	}
protected:
	static ColorVec m_vColorToBePainted;///<����ʶ���������ɫ���������뱾���������±꣬���Ǹ���ɫ��Ӧ�����;
};
/**
* @class 
* @brief ��Ϳ�����е�����
*
* ����Ϳ�������н��л��֣��õ��С�Ĭ���п�Ϊ��Ϳ��Ԫ�Ŀ��
*/
class CRow:public CRect
{
public:
	CRect * CellInRow(unsigned Line)
	{
		return &( m_vPaintCellVec[Line]);
	}
	CPaintCell * FindCellInRow(unsigned Line)
	{
		return &( m_vPaintCellVec[Line]);
	}
	long ValidTopOfThisRow()
	{
		return m_vPaintCellVec[0].top;
	}
	long ValidBottomOfThisRow()
	{
		if (m_bNeedPaint)
		{
			std::vector<CPaintCell>::iterator itOfCellVec;
			itOfCellVec=m_vPaintCellVec.end()-1;
			return itOfCellVec->bottom;
		}
		return 0;
	}
public:
	void InitAll()
	{
		m_vPaintCellVec.clear();
	}
	bool m_bNeedPaint;///<���а�����Ҫ��Ϳ�ĵ�Ԫ
	std::vector<CPaintCell> m_vPaintCellVec;///<�����а�����������Ϳ��Ԫ
	
	unsigned NumOfCellInRow()
	{
		return  m_vPaintCellVec.size();
	}
};
/**
* @class 
* @brief ����һ���ƶ��Ĺ������򣬾���
*
* 
*/
class CRect_Work_Region: public CRect
{
public:
	CRect_Work_Region(void);
	~CRect_Work_Region(void);
public:
	std::vector<CRow> m_vRowsVec;///<���������а�����������Ҫ��Ϳ����
public:
	
	unsigned NumOfRow;///<���������а���������Ҫ��Ϳ����
	unsigned m_uNumOfPaintCell;///<���������а�������Ϳ��Ԫ����
	bool m_bNeedPaint;///<����������Ҫ��Ϳ�ĵ�Ԫ
	void InitAll()
	{
		m_bNeedPaint=false;
		 NumOfRow=0;
		 m_uNumOfPaintCell=0;
		 m_vRowsVec.clear();
		WidthOfWorkRegion=LineNumOfWorkRegion=RowNumOfWorkRegion=NumOfWorkRegion=0;
		 InRowIndex=HeightofWorkRegion=0;
	}
/**
*@brief ��������Ƿ�λ��ͼ��ı߽���
*
*
*@parm BorderPixelVal �߽��Ӧ������ֵ������
*@parm BorderPixelVal ��ǰҪ�����Ƿ�X���ϵı߽�?�ǣ�Ϊ��
*
*@return ����Ϊ��
*@todo
*/
	bool IsBorder(unsigned BorderPixelVal,bool bCheckingBorderOfX)
	{
		if (bCheckingBorderOfX)
		{return BorderPixelVal==right;}
		return BorderPixelVal==bottom;
	}
	CRect * RecedCell(unsigned Line,unsigned Row)
	{
		return m_vRowsVec[Row].CellInRow(Line);
	}
	CPaintCell * FindRecedCell(unsigned Line,unsigned Row)
	{
		return m_vRowsVec[Row].FindCellInRow(Line);
	}
	int NumOfCellInGivenRow(unsigned Row)
	{
		return m_vRowsVec[Row].NumOfCellInRow();
	}
	long NumOfCell()
	{
		return m_uNumOfPaintCell;
	}
	bool GivenRowNeedPaint(unsigned Row)
	{
		return m_vRowsVec[Row].m_bNeedPaint;
	}
/**
*@brief ��һ����Ч��Ϳ��ɫ����ʼ����
*
*
*@parm
*
*@return
*@todo
*/
	long ValidTopOfGivenRow(unsigned Row)
	{
		return m_vRowsVec[Row].ValidTopOfThisRow();
	}
	long ValidBottomOfGivenRow(unsigned Row)
	{
		return m_vRowsVec[Row].ValidBottomOfThisRow();
	}
public:
	static unsigned NumOfWorkRegion;///<ȫͼ�л��ֵĹ���������
	static unsigned RowNumOfWorkRegion;///<ȫͼ�л��ֵĹ������е���Ŀ
	static unsigned LineNumOfWorkRegion;///<ȫͼ�л��ֵĹ������е���Ŀ
	static unsigned WidthOfWorkRegion;///<һ�����������׼�Ŀ�ȣ��ر�ע����CRect������������Width������ͬ������ǹ��е����ʣ�������ĳһ�������ʵ�ʿ�ȡ�
	static unsigned HeightofWorkRegion;///<һ�����������׼�ĸ߶ȣ��ر�ע����CRect������������Height������ͬ������ǹ��е����ʣ�������ĳһ�������ʵ�ʸ߶ȡ�
	unsigned InRowIndex;///<�����������ڵ������

};
