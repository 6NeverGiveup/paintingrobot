#pragma once
#include "Parm.h"
#include <atltypes.h>
//#include "PaintCell.h"
#include <math.h>
#include <vector>
#include <map>
#include "gyMath.h"
/********************************************************************
	created:	2011/08/31
	created:	31:8:2011   11:14
	filename: 	f:\�ҵ���Ŀ\SoftProj\UpperLevelSoft\UpperLevelSoft\RecognizePicture.h
	file path:	f:\�ҵ���Ŀ\SoftProj\UpperLevelSoft\UpperLevelSoft
	file base:	RecognizePicture
	file ext:	h
	author:		YangGao
	
	purpose:	�Զ����ͼƬ����ͼ������ʱ��Ҫ��Թ����ͼ�Σ��̶���������Ϊ���Σ���Ϳ����ҲΪ���Ρ���ƫб

*********************************************************************/
//#define AVERAGE_SIZE_OF_CELL ///<�Ե�Ԫ�Ĳ���Ԥʶ��ʱ�����и��ӵ�ƽ�����㣬����
/** @file 
*@brief  �Զ����ͼƬ����ͼ����
* @author YangGao
* @date 2011/08/31
* @version 1.0
*
* �Զ����ͼƬ����ͼ������ʱ��Ҫ��Թ����ͼ�Σ��̶���������Ϊ���Σ���Ϳ����ҲΪ���Ρ���ƫб���Ƚ�����ͼƬ����Ϊ���ɹ��������ٽ�����������Ϊÿһ����Ϳ��Ԫ����ʶ��
*/
/**
* @class 
* @brief ����ר�����ڽ�ͼƬ���ֳ�һ��������Ϳ��������
*
* 
*/
class CPartionPicture
{
public:
	CPartionPicture(void);
	~CPartionPicture(void);
	/**
	*@brief ������ͼƬ����
	*
	*������X,Y�᷽���һ�η�������Ϳ�ķ���λ�ý�����ͼƬ����
	*@parm pPicDC ��ͼDC
	*@parm Width ��ͼ���
	*@parm Height ��ͼ�߶�
	*
	*@return ����ͼƬ��������Ҫ��Ϳ�ĵط��򷵻���
	*@todo
	*/
	bool PartionThePic(CDC*pPicDC,long Width,long Height);
/**
*@brief ���ܻ��Ļ���ͼƬ
*
*��PartionThePic��ȣ������˶�ÿ�����ֵĹ�����������б߽�����ܻ���������߽罫��С��Ϳ��Ԫ��1��Ϊ2
*@parm
*
*@return
*@todo
*/
	bool PationPicIntell(CDC*pPicDC,long Width,long Height);
	/**
	*@brief ����΢���������ı߽磬ʹ֮���ָ���Ϳ��Ԫ
	*
	*�ڽ�����һ�λ��ֺ�����΢���������ı߽磬ʹ֮���ָ���Ϳ��Ԫ
	*@parm
	*
	*@return
	*@todo
	*/
	int RefineTheBorder(CDC*pPicDC);
protected:
	/**
	*@brief ������ͼƬ����
	*
	*���԰���Ԥ������п�ȡ�ͼƬ�ߴ绮�֡���������п�Ϊÿ��PaintCell�ÿ�ȡ�ֱ��������ͼƬ����С�������
	*��С���Ըð�����ν��зָ������ʵ�ֶ�����ͼƬ�ķ���.�������к��е�˳�򽫷�������洢��m_vWorkRegionPationed
	*@parm
	*
	*@return û�ҵ����ʵı߽磬����û�ҵ���Ϳ�����򷵻ؼٷ��򷵻���
	*@todo
	*/
	bool PartionThePicRegulaly(CDC*pPicDC,long Width,long Height);
/**
*@brief ���ֹ��������һ��������������Ϊһ������
*
*���ֹ�������,��ÿһ�������������п��򵥵ģ�������ÿһ�����������Ƿ񻮳����ж�����Ϳ��Ԫ���м�⡣
*��һ��������������Ϊһ������,�൱�ڻ�����
*@parm
*
*@return
*@todo
*/
	void FurtherPartionTheWorkRegIntoRow(CRect_Work_Region& Work_Region);
	/**
	*@brief �����������Ƚ�����ͼƬ����
	*
	*���԰���Ԥ������п�ȡ�ͼƬ�ߴ绮�֡�
	*@parm
	*
	*@return
	*@todo
	*/
	bool PartionThePicAccordGivenWidth(CDC*pPicDC,long Width,long Height);
/**
*@brief �����ڻ�������ʱ�����߽粢����ñ߽��ϵ��������Խ��д���
*
*ר�� ���ֺ������ã������ֵ��߽�ʱ������һ���������򲢲���������Ҫ���⴦��
*@parm CurRowOrLine      ��ǰ��Ҫ�жϵ��С�������
*@parm BorderVal         �߽紦����ֵ
*@parm AttributeL        ��Ҫ��ֵ������L
*@parm BorderAttributeR  �߽紦��Ҫ����������R����ֵ
*@parm AttributeLVal     �Ǳ߽紦��Ҫ������L����ֵ
*
*@return ��ȷ�����⴦��ı߽��򷵻�ֵ��
*@todo   ������ֻ�����˱߽紦�����������쳣������Ҳֻ�����˻���ʱ���һ�������һ�е��쳣��������ǵ�һ�л��һ�еĳ����쳣�Ļ���δ����
*/
	bool PartionBorderCheckAndHandle(unsigned CurRowOrLine,unsigned BorderVal,long& AttributeL,long&AttributeR,
									long BorderAttributeLVal,long BorderAttributeRVal,
									long AttributeLVal,long AttributeRVal)
	{
		if (CurRowOrLine==BorderVal)
		{
			AttributeL=BorderAttributeLVal;
			AttributeR=BorderAttributeRVal;
			return true;
		}
		else
		{
			AttributeL=AttributeLVal;
			AttributeR=AttributeRVal;
		}
		return false;
	}
	public:
/**
*@brief ��������ͼƬ����Ч�߽�
*
*�����Ǽ򵥵İ��չ�������ȶ�����ͼƬ���зָ�ʱ�����뿼�ǵ�ͼƬ�������п����пհ��������á���˽�����������ѹ��ֱ����С����ͼƬ�ڲ�ͼ��
*�����洢��g_sPaintAreaParm��
*@parm 
*
*@return ����С��������Ǵ��ڵģ�ͼƬ�ڲ�������Ϳͼ��ģ��򷵻���
*@todo
*/
	bool SearchValidatePicBorder(CDC*pPicDC,long Width,long Height);
/**
*@brief ������ͼƬ����С�������ʱ����,��X��������
*
*������ͼƬ����С�������ʱ����,��X�����������������ĵ�һ������Ϳ�����X���꣬��Ϊ����ͼ�µ�X����߽硣�ú������� StartX����߽� BorderVal֮��Ĵ�С�ж�����X���ӷ���
*������������-��������
*@parm pPicDC  ��ͼDC
*@parm BorderVal X�����Ӧ���������ޣ�
*@parm StartX  ��X������������ʼ������
*@parm StartY  ������Ч��ͼ��Y������Сֵ
*@parm BiggerBorderOfYaxs  ������Ч��ͼ��Y�������ֵ
*
*@return �ҵ�����Ϳ�������򷵻���
*@todo
*/
	bool ShrinkXBorder(CDC*pPicDC,long BorderVal,long StartX,long StartY,long BiggerBorderOfYaxs);
	/**
	*@brief ������ͼƬ����С�������ʱ����,��Y��������
	*
	*������ͼƬ����С�������ʱ����,��X�����������������ĵ�һ������Ϳ�����X���꣬��Ϊ����ͼ�µ�X����߽硣�ú������� StartY����߽� BorderVal֮��Ĵ�С�ж�����Y���ӷ���
	*������������-��������
	*@parm pPicDC  ��ͼDC
	*@parm BorderVal Y�����Ӧ���������ޣ�
	*@parm StartX  ������Ч��ͼ��X������Сֵ
	*@parm StartY  ��Y������������ʼ������
	*@parm BiggerBorderOfYaxs  ������Ч��ͼ��X�������ֵ
	*
	*@return �ҵ�����Ϳ�������򷵻���
	*@todo
	*/
	bool ShrinkYBorder(CDC*pPicDC,long BorderVal,long StartX,long StartY,long BiggerBorderOfXaxs);
	/**
	*@brief ���ã�����˵��ʼ������
	*
	*���ã�����˵��ʼ������,�����г�Ա����������ֵ�����������������ֹ����
	*@parm
	*
	*@return
	*@todo
	*/
	void InitAll()
	{
		m_vWorkRegionPationed.clear();
	}
public:
	std::vector<CRect_Work_Region>m_vWorkRegionPationed;///<���ֺ�õ��Ĺ��������У��洢˳��Ϊ�������к���
	//m_vWorkRegionPationed.size_type
	/**
	*@brief �������еķ�ʽ������ͼƬ����
	*
	*�������еķ�ʽ������ͼƬ����,�ⲿ��ָ���÷����Ĳ���������ߴ硣��������Ϊ�ߴ硣��������m_vWorkRegionPationed
	*@parm
	*
	*@return
	*@todo
	*/
	bool Partion(void);
	
};
class CMapSearch
{
protected:
	/**
	*@brief �����ǿ���ɫ����ĳ���
	*
	*�Ӹ����㿪ʼ��ͬʱ��x,y���������ǿ���ɫ���飬������Ϣ�������m_SearchResRect
	*@parm
	*
	*@return
	*@todo
	*/
	bool SearchLengthOfNonNuLLColor(CDC* pDCOfMapToRec,long XBorder,long YBorder,long StartX,long StartY);
	CRect m_SearchResRect;///<SearchLengthOfNonNuLLColor�����������ķǿ���ɫ����
	/**
	*@brief ��X����������Ϳ����ı߽�
	*
	*��һ�е������У��Ѿ��ҵ�����Ϳ�����ҵ��˸���Ϳ�������ʼ��(����)��X�᷽��������ռ�Ĵ�С
	*
	*@parm CurColor ��ǰ�����������ɫ
	*@parm pPicDC ����ͼ��DC������ȡ��ͼ
	*@parm Border �÷���ı߽磬��X�����С
	*@parm StartX ����Ϳ��Ԫ����ʼ���x����
	*@parm StartY ����Ϳ��Ԫ����ʼ���Y����
	*
	*@return ����Ϳ������ڵ���1�����صĿ���򷵻���
	*@todo
	*/
	int SearchAlongX(COLORREF& CurColor,CDC*pPicDC,long Border,long StartX,long StartY);
	/**
	*@brief ��Y����������Ϳ����ı߽�
	*
	*��һ�е������У��Ѿ��ҵ�����Ϳ�����ҵ��˸���Ϳ�������ʼ��(����)��X�᷽��������ռ�Ĵ�С
	*
	*@parm CurColor ��ǰ�����������ɫ
	*@parm pPicDC ����ͼ��DC������ȡ��ͼ
	*@parm Border �÷���ı߽磬��Y�����С
	*@parm StartX ����Ϳ��Ԫ����ʼ���x����
	*@parm StartY ����Ϳ��Ԫ����ʼ���Y����
	*
	*@return ����Ϳ������ڵ���1�����صĿ���򷵻���
	*@todo
	*/
	int SearchAlongY(COLORREF& CurColor,CDC*pPicDC,long Border,long StartX,long StartY);
};
typedef std::map<unsigned,unsigned>::value_type MValType;
typedef std::map<unsigned,unsigned> ResMapType;
/**
* @class 
* @brief ��ͼƬ����Ԥʶ��,ʶ���ͼƬ�ڵ�Ԫ��ƽ���ߴ����
*
* 
*/
class CAverageCellSizeRec:public CMapSearch
{
protected:
#define BIGEST_SIZE_RATIO_OF_ONE_CELL 1.5//��ͼƬ���Σ���������Ԫ�ߴ�仯��ϵ��
	/**
	*@brief ��1��������Ϳ��Ԫ�Ŀ�Ȳ���,�����п��ܽ������m_vPossibleSizeOfCell
	*
	*��x����1��������Ϳ��Ԫ�Ŀ�Ȳ���,�����п��ܽ������m_vPossibleSizeOfCell,Ҫ�����һ�����ܵ���С���ֵ�����ֵ�������ڲ������ı䣬���Ѱ�ҵ���С�Ļ�
	*@parm 
	*
	*@return �����ҵ�����С���ֵ����û�ҵ��򷵻ص���ͼƬ�Ŀ�ȡ�
	*@todo
	*/
	unsigned Search1LineForAllPossibleParmOfPaintCell(CDC* pDCOfMapToRec,long MapWidth,long MapHeight,long StartX,long StartY,unsigned& MiniSizeOfParm);

	std::map<unsigned,unsigned> m_mPossibleWidthOfCell;//���п�����һ����Ԫ�ĳߴ�ֵ,������Ϊֵ��ֵΪ����
	/**
	*@brief ��1��������Ϳ��Ԫ����С��Ȳ���
	*
	*��x�������ȷ���
	*@parm 
	*
	*@return �����ҵ�����С���ֵ����û�ҵ��򷵻ص����Ѿ��ҵ�����С��ȡ�
	*@todo
	*/
	unsigned Search1LineForMiniParmOfPaintCell(CDC* pDCOfMapToRec,long MapWidth,long MapHeight,long StartX,long StartY,unsigned& MiniSizeOfParm);
	/**
	*@brief ����������Ϳ��Ԫ����С��Ȳ���
	*
	*��x���ȴ�����������С���ֵ���ٽ����п��ܵĿ��ֵ����������ƽ����Ϊ�����ȷ���
	*@parm 
	*
	*@return �����ҵ��ĵ�����Ԫ������ֵ����û�ҵ��򷵻ص�0��
	*@todo
	*/
	unsigned SearchWidthOfOneParm(CDC* pDCOfMapToRec,long MapWidth,long MapHeight);
protected:
	/**
	*@brief ��1��������Ϳ��Ԫ����С�߶Ȳ���
	*
	*��x�������ȷ���
	*@parm 
	*
	*@return �����ҵ�����С���ֵ����û�ҵ��򷵻ص����Ѿ��ҵ�����С�߶ȡ�
	*@todo
	*/
	unsigned Search1RowForMiniParmOfPaintCell(CDC* pDCOfMapToRec,long MapWidth,long MapHeight,long StartX,long StartY,unsigned& MiniSizeOfParm);
	/**
	*@brief ��1��������Ϳ��Ԫ�Ŀ�Ȳ���,�����п��ܽ������m_vPossibleSizeOfCell
	*
	*��x����1��������Ϳ��Ԫ�Ŀ�Ȳ���,�����п��ܽ������m_vPossibleSizeOfCell,Ҫ�����һ�����ܵ���С���ֵ�����ֵ�������ڲ������ı䣬���Ѱ�ҵ���С�Ļ�
	*@parm 
	*
	*@return �����ҵ�����С�߶�ֵ����û�ҵ��򷵻ص���ͼƬ�ĸ߶ȡ�
	*@todo
	*/
	unsigned Search1RowForAllPossibleParmOfPaintCell(CDC* pDCOfMapToRec,long MapWidth,long MapHeight,long StartX,long StartY,unsigned& MiniSizeOfParm);
	/**
	*@brief ����������Ϳ��Ԫ����С��Ȳ���
	*
	*��x���ȴ�����������С���ֵ���ٽ����п��ܵĿ��ֵ����������ƽ����Ϊ�����ȷ���
	*@parm 
	*
	*@return �����ҵ��ĵ�����Ԫ������ֵ����û�ҵ��򷵻ص�0��
	*@todo
	*/
	unsigned SearchHeightOfOneParm(CDC* pDCOfMapToRec,long MapWidth,long MapHeight);
	ResMapType m_mPossibleHeightOfCell;
};
/**
* @class CPreRecgnize
* @brief ��ͼƬ����Ԥ����ʶ��ͼƬ����Ϳ��Ԫ�ĳߴ磬��ʶ��Ԫ֮��ļ��
*
* 
*/
class CPreRecgnize:public CAverageCellSizeRec
{
public:
	/**
 *@brief ��Ľӿں���������ʶ��ͼƬ����
 *
 *
 *@parm pDCOfMapToRec��Ҫʶ���ͼƬ���ڵ�DC
 *@parm MapWidth ͼƬ�Ŀ�ȣ���λ����
 *@parm MapHeight ͼƬ�ĸ߶ȣ���λ����
 *
 *@return �ɹ��򷵻���
 *@todo
 */
	bool PreReggnizeForParm(CDC* pDCOfMapToRec,long MapWidth,long MapHeight);
protected:

	/*unsigned m_uHeightResult;
	unsigned m_uWidthResult;*/
	/**
	*@brief ������Ϳ��Ԫ�ĳ��������
	*
	*ͬʱ��x,y�����������������m_RecgnizedWidthParmOfPaintCell��m_RecgnizedHeightParmOfPaintCell
	*@parm 
	*
	*@return
	*@todo
	*/
	bool LookForParmOfPaintCell(CDC* pDCOfMapToRec,long MapWidth,long MapHeight,long StartX,long StartY)
	{
		if (gCellSizePreRecFlag==AVERAGE_SIZE_OF_CELL)
		{
			m_RecgnizedWidthParmOfPaintCell=SearchWidthOfOneParm(pDCOfMapToRec,MapWidth,MapHeight);
			m_RecgnizedHeightParmOfPaintCell=SearchHeightOfOneParm(pDCOfMapToRec,MapWidth,MapHeight);
			if (m_RecgnizedWidthParmOfPaintCell!=0&&m_RecgnizedHeightParmOfPaintCell!=0)
			{return true;}
			return false;			
		}		
		if (SearchLengthOfNonNuLLColor(pDCOfMapToRec,MapWidth,MapHeight, StartX, StartY))
		{
			m_RecgnizedWidthParmOfPaintCell=m_SearchResRect.Width();
			m_RecgnizedHeightParmOfPaintCell=m_SearchResRect.Height();
			return true;
		}		
		return false;
	}
	void SetParmAccordingly()
	{
		gRowWidth=m_RecgnizedWidthParmOfPaintCell+1;
		gHeightOfEveryPaintCell= m_RecgnizedHeightParmOfPaintCell+1;//�㷨�������õ�Width�����ȣ���������+1
	}
/**
*@brief �Զ�ʶ��Ԫ֮���϶�Ŀ�ȣ�Ĭ��������߶���һ����
*
*�Զ�ʶ��Ԫ֮���϶�Ŀ�ȡ�����Կ�϶���м���ģ���϶�������Ϊ MINI_CELL_WIDTH_THREAD��һ�����ֵ���Ϳ��Ԫ���½Ǵ���Ȼ�п�϶,�����û��϶
*���ڵ�Ԫ�ߴ��ʶ�����������������϶ʱ��������Ҳ����д���
*@parm
*
*@return ����һ�����ֵ���ɫ��������Ϳ��Ԫ���Һ��������˼�϶�򷵻�2������һ�����ֵ�����Ϳ��Ԫ������û���ֿ�϶�򷵻�3������һ�����ֵ��Ǹ���϶���򷵻�1�����򷵻�0
*
*@todo
*/
	int LookForParmOfGapBetweenCell(CDC* pDCOfMapToRec,long MapWidth,long MapHeight);
	
	unsigned m_RecgnizedWidthParmOfPaintCell;
	unsigned m_RecgnizedHeightParmOfPaintCell;
	
	int SearchBorderOfCurPaintCell(COLORREF& CurColor,CDC*pPicDC,long Border,long StartX,long StartY,bool bSearchAlongX);

//Average ( ) 



};
typedef std::vector<CRect_Work_Region>::iterator  ItOfRegVec;
class CRecognizePicture:public CPartionPicture,public CPreRecgnize
{
public:
	CRecognizePicture(void);
	~CRecognizePicture(void);
/**
*@brief ��Ľӿں���������ʶ��ͼƬ����
*
*
*@parm pDCOfMapToRec��Ҫʶ���ͼƬ���ڵ�DC
*@parm MapWidth ͼƬ�Ŀ�ȣ���λ����
*@parm MapHeight ͼƬ�ĸ߶ȣ���λ����
*
*@return �ɹ��򷵻���
*@todo
*/
	bool RecgnizePic(CDC* pDCOfMapToRec,long MapWidth,long MapHeight);
/**
*@brief ���ػ����˶��ٸ����򣬲���������������ɫ��
*
*
*@parm
*
*@return
*@todo
*/
	unsigned NumOfRecedPic()
	{
		return m_vWorkRegionPationed.size();
	}
	long NumOfRecedCell()
	{
		long NumOfCell=0;
		for (std::vector<CRect_Work_Region>::iterator itReg=m_vWorkRegionPationed.begin();
			itReg!=m_vWorkRegionPationed.end();itReg++)
		{
			if (itReg->m_bNeedPaint)
			{
				NumOfCell+=itReg->NumOfCell();
			}			
		}
		return NumOfCell;
	}
	CPoint TopLeftOfWorkRegion(unsigned indexOfReg)
	{
		return m_vWorkRegionPationed[indexOfReg].TopLeft();
	}
	CPoint BottomRighttOfWorkRegion(unsigned indexOfReg)
	{
		return m_vWorkRegionPationed[indexOfReg].BottomRight();
	}
	unsigned TopOfReg(unsigned indexOfReg)
	{
		return m_vWorkRegionPationed[indexOfReg].top;
	}
	unsigned BottomOfReg(unsigned indexOfReg)
	{
		return m_vWorkRegionPationed[indexOfReg].bottom;
	}
	unsigned LeftOfReg(unsigned indexOfReg)
	{
		return  m_vWorkRegionPationed[indexOfReg].left;
	}
	unsigned RightOfReg(unsigned indexOfReg)
	{
		return m_vWorkRegionPationed[indexOfReg].right;
	}
	CRect* RectOfReg(unsigned indexOfReg) 
	{
		return &(m_vWorkRegionPationed[indexOfReg]);
	}
	CRect* RectOfCell(unsigned Line,unsigned Row,unsigned indexOfReg)
	{
		return (m_vWorkRegionPationed[indexOfReg].RecedCell(Line,Row));
	}
/**
*@brief ��ѯָ������Ϳ��Ԫ������ָ��
*
*
*@parm
*
*@return
*@todo
*/
	CPaintCell* QueryPaintCell(unsigned Line,unsigned Row,unsigned indexOfReg)
	{
		return (m_vWorkRegionPationed[indexOfReg].FindRecedCell(Line,Row));
	}
	/**
	*@brief ��ѯָ���е���ʼ��ֹλ��,��ѯ����ʶ��������δ������ǹ��װ���µ���������
	*
	*����Ҫ��Ϳ�򷵻��棬����ͨ���������StartY EndY���ؽ������λΪmm��δ������ǹ��װ���µ�����
	*@parm StartY ����
	*
	*@return
	*@todo
	*/
	//Row�����������,indexOfReg����������
	bool QueryStartEndParmOfRow(unsigned Row,unsigned indexOfReg,unsigned& StartY,unsigned& EndY,float RatioOfPiexel,float RatioOfYPiexel)
	{
		if (m_vWorkRegionPationed[indexOfReg].GivenRowNeedPaint(Row))//ֻ�е�ǰ������Ҫ��Ϳ�ĵ�Ԫ�Ż�ΪTRUE
		{
			StartY=(m_vWorkRegionPationed[indexOfReg].ValidTopOfGivenRow(Row))-m_vWorkRegionPationed[indexOfReg].top;//�˶���������ڹ��������ϱ��أ��������겻ͬ
			StartY*=RatioOfYPiexel;
			EndY=m_vWorkRegionPationed[indexOfReg].ValidBottomOfGivenRow(Row)-m_vWorkRegionPationed[indexOfReg].top;
			EndY*=/*RatioOfPiexel*/RatioOfYPiexel;
			return true;
		}		
		return false;
	}
/**
*@brief ��ѯ�������ľ��β���
*
*
*@parm
*
*@return
*@todo
*/
	CRect* QueryRegRectParm(unsigned indexOfReg)
	{
		return &m_vWorkRegionPationed[indexOfReg];
	}
	unsigned NumOfRowInGivenWorkReg(unsigned WorkReg)
	{
		return m_vWorkRegionPationed[WorkReg].NumOfRow;        //���ص�ǰ���������
	}
	unsigned NumOfCellInGivenRowOfGivenReg(unsigned WorkReg,unsigned Row)
	{
		return m_vWorkRegionPationed[WorkReg].NumOfCellInGivenRow(Row);
	}
//bool CheckLocationInReg()
	/**
	*@brief �Ը����㣬������������������������������ı��
	*
	*
	*@parm  point ����������
	*
	*@return ���������������ı��
	*@todo
	*/
	unsigned LocGivenPointInRegs(CPoint & point)
	{
		unsigned PixelDisBetweenWorkReg=gbOnePixelBetweenWorkReg?1:0;
		unsigned LineNum=point.y/(CRect_Work_Region::HeightofWorkRegion+PixelDisBetweenWorkReg);//��-1��ָ��ǰ��Partion������һ��
		unsigned RowNum=point.x/(CRect_Work_Region::WidthOfWorkRegion+PixelDisBetweenWorkReg);
		return RowNum+LineNum*(CRect_Work_Region::RowNumOfWorkRegion);
		//ItOfRegVec ItofRegs=m_vWorkRegionPationed.begin();
		//while (ItofRegs!=m_vWorkRegionPationed.end())
		//{
		//	ItofRegs++;
		//}
	}
	

protected:
/**
*@brief �ڵ�ͼ��ָ�����������ҵ��Ϸ��ķ������򣬲������ǵ���Ϣ��¼
*
*�ڵ�ͼ���ҵ��Ϸ��ķ��������͵�paintCell���������ǵ���Ϣ��¼,�ⲿ���ñ�������ÿ���е�һ������ֻ����һ�Ρ�
*Ҫ��֤�״ε���ʱ����ǰ������Ϊ���Ͻǣ���������ϵԭ�����������ε����Ͻǣ�
*@parm CurColor ��ǰ�����ɫ
*@parm x  ��ǰ���x
*@parm y  ��ǰ���y����
*@parm pPicDC ͼƬ
*@parm CurReg �����������еĹ�����
*
*@return
*@todo
*/
	bool ValidateRegionInWorkRegion(COLORREF& CurColor,long x,long y,CDC*pPicDC,ItOfRegVec CurReg);
	/**
	*@brief �ڵ�ͼ��ָ�����������ҵ��Ϸ��ķ������򣬲������ǵ���Ϣ��¼,�ر��������̶����гߴ����Ϳդ��gridդ��
	*
	*�ڵ�ͼ���ҵ��Ϸ��Ĺ̶��ߴ�ķ��������͵�paintCell���������ǵ���Ϣ��¼��
	*Ҫ��֤�״ε���ʱ����ǰ������Ϊ���Ͻǣ���������ϵԭ�����������ε����Ͻǣ�
	*@parm CurColor ��ǰ�����ɫ
	*@parm x  ��ǰ���x
	*@parm y  ��ǰ���y����
	*@parm pPicDC ͼƬ
	*@parm CurReg �����������еĹ�����
	*
	*@return
	*@todo
	*/
	bool ValidateGridRegionInWorkRegion(COLORREF& CurColor,long x,long y,CDC*pPicDC,ItOfRegVec CurReg);
public:
	/**
	*@brief ���ã�����˵��ʼ������
	*
	*���ã�����˵��ʼ������,�����г�Ա����������ֵ�����������������ֹ����
	*@parm
	*
	*@return
	*@todo
	*/
	void InitAll()
	{
		CPartionPicture::InitAll();
		m_vRowOfPaintCell.clear();
		m_CurCell.InitAll();
	}
protected:
	
	std::vector<CPaintCell> m_vRowOfPaintCell;///<��Ϳ��Ԫ�У���¼һ��֮�����е���Ϳ��Ԫ
	CPaintCell m_CurCell;

public:
	COLORREF& QueryColorByIndex(unsigned ColorIndex)
	{return m_CurCell.QueryColorByIndex(ColorIndex);}
	unsigned QueryNumOfColorToBePainted()
	{return m_CurCell.QueryNumOfColorToBePainted();	}
	bool FoundCellToBePaint()
	{
		ItOfRegVec ItofRegs=m_vWorkRegionPationed.begin();
		while (ItofRegs!=m_vWorkRegionPationed.end())
		{
			if (ItofRegs->m_bNeedPaint)
			{
				return true;
			}
			ItofRegs++;
		}
		return false;
	}
/**
*@brief �Ӹ��������������������Ϊ�е����Ͻǣ���һ��������������Ϳ����
*
*�Ӹ��������������������Ϊ�е����Ͻǣ���һ��������������Ϳ���򣬽��þ�����Ϣ��¼����������һ���е�������Ϳ��Ϣ��¼��m_vRowOfPaintCell
*�������У���δ�����п�ȿ��ܵĲ�ͬ������ֱ����Ϊ����gRowWidth,���������е���ʼ�б߽��У����Ҫ��֤�п��
*@parm pPicDC ����ͼ��DC������ȡ��ͼ
*@parm RowStartX ���е���ʼ��(����)X����
*@parm RowStartY ���е���ʼ��(����)Y����
*@parm CurReg    �������ڵĹ��������ָ��Iterator����
*
*@return  �ҵ��Ϸ�����Ϳ�����򷵻��棬���򷵻ؼ�
*@todo
*/
	//bool SearchValidateRegionInRow(CDC*pPicDC,long RowStartX,long RowStartY,ItOfRegVec CurReg);
	/**
	*@brief ��һ��������������Ϳ����
	*
	*��ָ���У���һ��������������Ϳ���򣬽��þ�����Ϣ��¼����������һ���е�������Ϳ��Ϣ��¼��m_vRowOfPaintCell
	*�������У�����Ϣ����RowIndex��ָ�������������е���ֱ���߽���
	*@parm pPicDC ����ͼ��DC������ȡ��ͼ
	*@parm RowIndex �����ڹ��������е�����
	*@parm CurReg    �������ڵĹ��������ָ��Iterator����
	*
	*@return  �ҵ��Ϸ�����Ϳ�����򷵻��棬���򷵻ؼ�
	*@todo
	*/
bool SearchValidateRegionInRow(CDC*pPicDC,ItOfRegVec CurReg,unsigned RowIndex);
/**
*@brief ��һ��դ�񻯵����������̶���С�ľ�����Ϳ����
*
*��ָ���У���һ��������������Ϳ���򣬽��þ�����Ϣ��¼����������һ���е�������Ϳ��Ϣ��¼��m_vRowOfPaintCell
*�������У�����Ϣ����RowIndex��ָ�������������е���ֱ���߽��У���SearchValidateRegionInRow��ͬ�����ڱ��������е�դ���ǹ̶���С����Ԫ��
*@parm pPicDC ����ͼ��DC������ȡ��ͼ
*@parm RowIndex �����ڹ��������е�����
*@parm CurReg    �������ڵĹ��������ָ��Iterator����
*
*@return  �ҵ��Ϸ�����Ϳ�����򷵻��棬���򷵻ؼ�
*@todo
*/

bool SearchValidateRegionInGridRow(CDC*pPicDC,ItOfRegVec CurReg,unsigned RowIndex);

/**
*@brief �ҵ���Ϳ���󣬼�¼
*
*��һ�е������У��Ѿ��ҵ�����Ϳ�����ҵ��˸���Ϳ�������ʼ��(����)��Y�᷽��������ռ�Ĵ�С��X����Ĭ��Ϊ�п��������¼����Ա����m_CurCell������ٽ���ѹ��m_vRowOfPaintCell
*
*@parm CurColor ��ǰ�����������ɫ
*@parm pPicDC ����ͼ��DC������ȡ��ͼ
*@parm CurCellRect ����Ԫ����Ϣ
*@parm StartX ����Ϳ��Ԫ����ʼ���x����
*@parm StartY ����Ϳ��Ԫ����ʼ���Y����
*
*@return ����Ϳ������ڵ���1�����صĿ���򷵻���
*@todo
*/
	bool RecordPaintCell(COLORREF& CurColor,CDC*pPicDC,CRect& CurCellRect,long SearchStartX,long SearchStartY);
	/**
	*@brief �ҵ���Ϳ���󣬼�¼
	*
	*��һ�е������У��Ѿ��ҵ�����Ϳ�����ҵ��˸���Ϳ�������ʼ��(����)
	*��Ϳ����ʵ�����ǹ̶��������դ����ˣ�������������Y�����ϵĴ�С����ֵΪ�̶�ֵ
	*
	*@parm CurColor ��ǰ�����������ɫ
	*@parm pPicDC ����ͼ��DC������ȡ��ͼ
	*@parm CurCellRect ����Ԫ����Ϣ
	*@parm StartX ����Ϳ��Ԫ����ʼ���x����
	*@parm StartY ����Ϳ��Ԫ����ʼ���Y����
	*
	*@return ����Ϳ������ڵ���1�����صĿ���򷵻���
	*@todo
	*/
	bool RecordGridPaintCell(COLORREF& CurColor,CDC*pPicDC,CRect& CurCellRect,long SearchStartX,long SearchStartY);
};
/**
* @class 
* @brief �������ڶ�ͼƬ����Ԥʶ��ʶ������������������Ϳ��Ԫ�ĳߴ�
*
* 
*/
