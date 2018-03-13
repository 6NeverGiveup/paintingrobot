#include "StdAfx.h"
#include "RecognizePicture.h"
extern long gRowWidth;///<ÿ����Ϳ�еĿ�ȣ���λ���ر��븳ֵ
extern long gHeightOfEveryPaintCell;///<ÿ����Ϳ��Ԫ�ĸ߶ȣ���λ���أ����븳ֵ����ʵ��ʶ�����ʱ��û�а�����ߣ����ǰ�ʵ�ʸ߶����ģ�ת����Ԥ����С��Ϳ����ĳߴ�ʹ��߽粻���ڴ�����Ϳ��Ԫ

CPartionPicture::CPartionPicture(void)
{
	m_vWorkRegionPationed.clear();
}

CPartionPicture::~CPartionPicture(void)
{
}
unsigned CRect_Work_Region::NumOfWorkRegion;//��̬��Ա������������ǰ����
unsigned CRect_Work_Region::RowNumOfWorkRegion;//
unsigned CRect_Work_Region::LineNumOfWorkRegion;//
bool  CPartionPicture::PartionThePic(CDC*pPicDC,long Width,long Height)
{
	//������δ���
	//unsigned NumOfWorkRegion,RowNumOfWorkRegion,LineNumOfWorkRegion
	if (!SearchValidatePicBorder(pPicDC,Width,Height))
	{
		return false;
	}
	g_cWorkRegionParm.RowNumOfWorkRegion=ceil((float)g_sPaintAreaParm.Width()/g_cWorkRegionParm.WidthOfWorkRegion);//�л�����
	g_cWorkRegionParm.LineNumOfWorkRegion=ceil((float)g_sPaintAreaParm.Height()/g_cWorkRegionParm.HeightofWorkRegion);
	//CRect_Work_Region Work_Region;
	//long RegionHeight=Work_Region.HeightofWorkRegion;
	//long RegionWidth=Work_Region.WidthOfWorkRegion;//ע�ⲻ����width����
	//unsigned WidthBaseTmp;
	//unsigned HeightBaseTmp;
	//unsigned PixelDisBetweenWorkReg=gbOnePixelBetweenWorkReg?1:0;

	///////////////////////////���ֹ�����///////////////////////////////////////////////
	//for (int j=0;j<g_cWorkRegionParm.LineNumOfWorkRegion;j++)
	//{
	//	HeightBaseTmp=g_sPaintAreaParm.StartPointY+j*RegionHeight;
	//	//Work_Region.top=0+j*g_cWorkRegionParm.HeightofWorkRegion;
	//	//Work_Region.bottom=
	//	PartionBorderCheckAndHandle(j,CRect_Work_Region::LineNumOfWorkRegion-1,Work_Region.top,Work_Region.bottom,
	//		HeightBaseTmp,g_sPaintAreaParm.EndPointY,HeightBaseTmp,HeightBaseTmp+RegionHeight-PixelDisBetweenWorkReg);//
	//	for (int i=0;i<g_cWorkRegionParm.RowNumOfWorkRegion;i++)//��
	//	{
	//		WidthBaseTmp=g_sPaintAreaParm.StartPointX+i*RegionWidth;
	//		PartionBorderCheckAndHandle(i,CRect_Work_Region::RowNumOfWorkRegion-1,Work_Region.left,Work_Region.right,
	//			WidthBaseTmp,g_sPaintAreaParm.EndPointX,WidthBaseTmp,WidthBaseTmp+RegionWidth-PixelDisBetweenWorkReg);//
	//		m_vWorkRegionPationed.push_back(Work_Region);
	//	}
	//}
	////m_vWorkRegionPationed
	//g_cWorkRegionParm.NumOfWorkRegion=m_vWorkRegionPationed.size();
	//return true;
	return Partion();
	///
	
}




bool CPartionPicture::Partion(void)
{
	unsigned WidthBaseTmp;
	unsigned HeightBaseTmp;
	CRect_Work_Region Work_Region;
	unsigned PixelDisBetweenWorkReg=gbOnePixelBetweenWorkReg?1:0;
	long RegionHeight=Work_Region.HeightofWorkRegion;
	long RegionWidth=Work_Region.WidthOfWorkRegion;//ע�ⲻ����width����
	for (int j=0;j<g_cWorkRegionParm.LineNumOfWorkRegion;j++)
	{
		HeightBaseTmp=g_sPaintAreaParm.StartPointY+j*RegionHeight;
		//Work_Region.top=0+j*g_cWorkRegionParm.HeightofWorkRegion;
		//Work_Region.bottom=
		PartionBorderCheckAndHandle(j,CRect_Work_Region::LineNumOfWorkRegion-1,Work_Region.top,Work_Region.bottom,
			HeightBaseTmp,g_sPaintAreaParm.EndPointY,HeightBaseTmp,HeightBaseTmp+RegionHeight-PixelDisBetweenWorkReg);//
		for (int i=0;i<g_cWorkRegionParm.RowNumOfWorkRegion;i++)//��
		{
			WidthBaseTmp=g_sPaintAreaParm.StartPointX+i*RegionWidth;
			PartionBorderCheckAndHandle(i,CRect_Work_Region::RowNumOfWorkRegion-1,Work_Region.left,Work_Region.right,
				WidthBaseTmp,g_sPaintAreaParm.EndPointX,WidthBaseTmp,WidthBaseTmp+RegionWidth-PixelDisBetweenWorkReg);//
			m_vWorkRegionPationed.push_back(Work_Region);
		}
	}
	//m_vWorkRegionPationed
	g_cWorkRegionParm.NumOfWorkRegion=m_vWorkRegionPationed.size();
	return !m_vWorkRegionPationed.empty();
}

bool CPartionPicture::PationPicIntell(CDC*pPicDC,long Width,long Height)
{
	
	g_cWorkRegionParm.WidthOfWorkRegion=g_cWorkRegionParm.WidthOfWorkRegion-g_cWorkRegionParm.WidthOfWorkRegion%gRowWidth;//floor((float)g_cWorkRegionParm.WidthOfWorkRegion/gRowWidth);//��С��������ȣ�ʹ֮�����п�
	g_cWorkRegionParm.HeightofWorkRegion=g_cWorkRegionParm.HeightofWorkRegion-g_cWorkRegionParm.HeightofWorkRegion%gHeightOfEveryPaintCell;//floor((float)g_cWorkRegionParm.HeightofWorkRegion/gHeightOfEveryPaintCell);
	return PartionThePic(pPicDC,Width,Height);
	//int OffsetOfRefine;
	//if (PartionThePic(pPicDC,Width,Height))//Ԥ����һ�Σ��ٿ�������
	//{
	//	//unsigned NumOfWorkReg=m_vWorkRegionPationed.size();
	//	for (unsigned i=0;i<CRect_Work_Region::NumOfWorkRegion;i++)
	//	{
	//		
	//	}
	//}
}
int CPartionPicture::RefineTheBorder(CDC*pPicDC)
{
	return 0;
}
bool CPartionPicture::SearchValidatePicBorder(CDC*pPicDC,long Width,long Height)
{
	bool bStartNotFounded=true;
	bool bExitPaintArea=false;
	bExitPaintArea=bExitPaintArea|ShrinkXBorder(pPicDC,Width,0,0,Height);//X�����Ӧ�߽�+��������
	bExitPaintArea=bExitPaintArea|ShrinkXBorder(pPicDC,0,Width,0,Height);//X�����Ӧ�߽�-��������
	bExitPaintArea=bExitPaintArea|ShrinkYBorder(pPicDC,Height,0,0,Width);//Y�����Ӧ�߽�+��������
	bExitPaintArea=bExitPaintArea|ShrinkYBorder(pPicDC,0,0,Height,Width);//Y�����Ӧ�߽�-��������
	return bExitPaintArea;
}
bool CPartionPicture::ShrinkXBorder(CDC*pPicDC,long BorderVal,long StartX,long StartY,long BiggerBorderOfYaxs)
{
	
		if (StartX>BorderVal)//����������
		{		
			for (long i=StartX;i>BorderVal;i--)//ɨ�軮����ʼ���Y
			{
				for (long j=StartY;j< BiggerBorderOfYaxs;j++)
				{
					if (pPicDC->GetPixel(i,j)!=gNULLCOLOR)
					{
						g_sPaintAreaParm.EndPointX=i;//���ֵ���ʼ��(���Ͻ�)X����
						return true;

					}
				}
				
			}
		}
		else
		{
			for (long i=StartX;i<BorderVal;i++)//ɨ�軮����ʼ���Y
			{
				for (long j=StartY;j< BiggerBorderOfYaxs;j++)
				{
					if (pPicDC->GetPixel(i,j)!=gNULLCOLOR)
					{
						g_sPaintAreaParm.StartPointX=i;//���ֵ���ʼ��(���Ͻ�)X����
						return true;

					}
				}
			}
		}
	
	
	return false;
}
bool CPartionPicture::ShrinkYBorder(CDC*pPicDC,long BorderVal,long StartX,long StartY,long BiggerBorderOfXaxs)
{
	
		if (StartY>BorderVal)//����������
		{		
			for (long j=StartY;j>BorderVal;j--)//ɨ�軮����ʼ���Y
			{
				for (long i=StartX;i< BiggerBorderOfXaxs;i++)
				{
					if (pPicDC->GetPixel(i,j)!=gNULLCOLOR)
					{
						g_sPaintAreaParm.EndPointY=j;//���ֵ���ʼ��(���Ͻ�)X����
						return true;

					}
				}
			}
		}
		else
		{
			for (long j=StartX;j<BorderVal;j++)//ɨ�軮����ʼ���Y
			{
				for (long i=StartX;i< BiggerBorderOfXaxs;i++)
				{
					if (pPicDC->GetPixel(i,j)!=gNULLCOLOR)
					{
						g_sPaintAreaParm.StartPointY=j;//���ֵ���ʼ��(���Ͻ�)X����
						return true;

					}
				}
			}
		}
	
	return false;
}



bool CPartionPicture::PartionThePicRegulaly(CDC*pPicDC,long Width,long Height)
{
	//unsigned NumOfWorkRegion,RowNumOfWorkRegion,LineNumOfWorkRegion;
	g_cWorkRegionParm.RowNumOfWorkRegion=ceil((float)Width/g_cWorkRegionParm.WidthOfWorkRegion);//�л�����
	g_cWorkRegionParm.LineNumOfWorkRegion=ceil((float)Height/g_cWorkRegionParm.HeightofWorkRegion);
	//CRect_Work_Region Work_Region;
	//long RegionHeight=Work_Region.HeightofWorkRegion;
	//long RegionWidth=Work_Region.WidthOfWorkRegion;//ע�ⲻ����width����
	//unsigned WidthBaseTmp;
	//unsigned HeightBaseTmp;
	//unsigned PixelDisBetweenWorkReg=gbOnePixelBetweenWorkReg?1:0;
	/////////////////////////////���ֹ�����///////////////////////////////////////////////
	//for (int j=0;j<g_cWorkRegionParm.LineNumOfWorkRegion;j++)
	//{
	//	HeightBaseTmp=j*RegionHeight;
	//	PartionBorderCheckAndHandle(j,CRect_Work_Region::LineNumOfWorkRegion-1,Work_Region.top,Work_Region.bottom,
	//		HeightBaseTmp,Height,HeightBaseTmp,HeightBaseTmp+RegionHeight-PixelDisBetweenWorkReg);
	//	for (int i=0;i<g_cWorkRegionParm.RowNumOfWorkRegion;i++)//��
	//	{
	//		WidthBaseTmp=i*RegionWidth;
	//		PartionBorderCheckAndHandle(i,CRect_Work_Region::RowNumOfWorkRegion-1,Work_Region.left,Work_Region.right,
	//			WidthBaseTmp,Width,WidthBaseTmp,WidthBaseTmp+RegionWidth-PixelDisBetweenWorkReg);

	//		m_vWorkRegionPationed.push_back(Work_Region);
	//	}
	//}
	////m_vWorkRegionPationed
	//g_cWorkRegionParm.NumOfWorkRegion=m_vWorkRegionPationed.size();
	//return true;
	return Partion();
}
void CPartionPicture::FurtherPartionTheWorkRegIntoRow(CRect_Work_Region& Work_Region)
{
	static CRow RowInReg;
	static unsigned Offset=0;
	unsigned NumOfRow=ceil((float)Work_Region.Width()/gRowWidth); //��ǰ���������
	for (unsigned i=0;i<NumOfRow;i++)
	{
		Offset=(i+1)*gRowWidth;
		RowInReg.top=Work_Region.top;
		RowInReg.left= Work_Region.left+i*gRowWidth;
		RowInReg.right=Work_Region.right<Work_Region.left+Offset?Work_Region.right:Work_Region.left+Offset;
		RowInReg.bottom=Work_Region.bottom;
		
		Work_Region.m_vRowsVec.push_back(RowInReg);
	}
	Work_Region.NumOfRow=NumOfRow;
	//return true;
}
bool CPartionPicture::PartionThePicAccordGivenWidth(CDC*pPicDC,long Width,long Height)
{

	return true;
}
//////////////////////////////////////////////////////////////////////////
CRecognizePicture::CRecognizePicture(void)
{
}

CRecognizePicture::~CRecognizePicture(void)
{
}

bool CRecognizePicture::RecgnizePic(CDC* pDCOfMapToRec,long MapWidth,long MapHeight)
{
	bool bPationedSucces;
	switch (geAreaPartitionFlag)
	{
		case PARTION_BY_WIDTH:
			bPationedSucces=PartionThePicRegulaly(pDCOfMapToRec,MapWidth,MapHeight);
			break;
		case PARTION_BY_FIRST_FOUND :
			 bPationedSucces=PartionThePic(pDCOfMapToRec,MapWidth,MapHeight);
			 break;
		default:
//			PreReggnizeForParm(pDCOfMapToRec,MapWidth,MapHeight);
			bPationedSucces=PationPicIntell(pDCOfMapToRec,MapWidth,MapHeight);
			break;
	}
	if (!bPationedSucces)
	{
		return false;
	}
	
	bool bNeedPaintPic=false;
	static COLORREF CurColor;
	if (m_vWorkRegionPationed.empty())      //���ֵ�����
	{
		return false;
	}
	ItOfRegVec ItWorkRegionVecEnd=m_vWorkRegionPationed.end();
	ItOfRegVec itToWorkRegionVec=m_vWorkRegionPationed.begin();
	unsigned i=0;
	for (itToWorkRegionVec;itToWorkRegionVec!=ItWorkRegionVecEnd;itToWorkRegionVec++)  //�����������Ѱ����Ҫ��Ϳ��С��Ԫ
	{

		FurtherPartionTheWorkRegIntoRow(*itToWorkRegionVec);//������
		if (geAreaPartitionFlag==GRID_PARTION_BY_INTELLIGENCE)
		{
			if (ValidateGridRegionInWorkRegion(CurColor,itToWorkRegionVec->left,itToWorkRegionVec->top,pDCOfMapToRec,itToWorkRegionVec))
			{bNeedPaintPic=true;}			
		}
		else
		{
			if (ValidateRegionInWorkRegion(CurColor,itToWorkRegionVec->left,itToWorkRegionVec->top,pDCOfMapToRec,itToWorkRegionVec))
			{bNeedPaintPic=true;}	
		}
		i++;
		//ASSERT(i!=93);
	}
	
	
	return bNeedPaintPic;
}

bool CRecognizePicture::ValidateRegionInWorkRegion(COLORREF& CurColor,long x,long y,CDC*pPicDC,ItOfRegVec CurReg)
{
	CurReg->m_uNumOfPaintCell=0;
	for (unsigned i=0;i<CurReg->NumOfRow;i++)
	{
		long RowStartX=CurReg->m_vRowsVec[i].left;
		long RowStartY=CurReg->m_vRowsVec[i].top;
		if (SearchValidateRegionInRow(pPicDC,CurReg,i))
		{
			CurReg->m_vRowsVec[i].m_vPaintCellVec=(m_vRowOfPaintCell);
			CurReg->m_vRowsVec[i].m_bNeedPaint=true;
			CurReg->m_uNumOfPaintCell+=m_vRowOfPaintCell.size();
		}
	}
	CurReg->m_bNeedPaint=CurReg->m_uNumOfPaintCell>0;
	return CurReg->m_bNeedPaint;
	/*unsigned i=0;
	do 
	{

		i++;
	} while (i<CurReg->NumOfWorkRegion);*/
	/*if()
	{
	}*/
	
	//m_CurCell.top=x;
	//CurCell.left=y;
	//Height
	/*long i=x;
	long j=y;*/
	//for (long i=0;i<gRowWidth;i++)//��������
	//{
	//	if (pPicDC->GetPixel(i+x,y)!=CurColor)
	//	{
	//		break;
	//	} 
	//	else
	//	{
	//		CurCell.right++;
	//	}
	//}
	//for (long j=0;j<g_sPaintAreaParm.HeightInPixel;j++)
	//{
	//}
	return false;
}
bool CRecognizePicture::ValidateGridRegionInWorkRegion(COLORREF& CurColor,long x,long y,CDC*pPicDC,ItOfRegVec CurReg)//һ������
{
	CurReg->m_uNumOfPaintCell=0;
	unsigned i=0;
	for (i;i<CurReg->NumOfRow;i++)      //ÿ������һ��һ�еĲ鴦,��ǰ���������
	{
		long RowStartX=CurReg->m_vRowsVec[i].left;
		long RowStartY=CurReg->m_vRowsVec[i].top;
		if (SearchValidateRegionInGridRow(pPicDC,CurReg,i))
		{
			CurReg->m_vRowsVec[i].m_vPaintCellVec=(m_vRowOfPaintCell);//m_vRowOfPaintCell��¼�ڵ�ǰ������Ҫ��Ϳ������
			CurReg->m_vRowsVec[i].m_bNeedPaint=true;                  //��ǰ���Ƿ���Ҫ��Ϳ
			CurReg->m_uNumOfPaintCell+=m_vRowOfPaintCell.size();
		}
	}
	CurReg->m_bNeedPaint=CurReg->m_uNumOfPaintCell>0;
	return CurReg->m_bNeedPaint;
}
//bool CRecognizePicture::SearchValidateRegionInRow(CDC*pPicDC,long RowStartX,long RowStartY,ItOfRegVec CurReg)
//{
//
//	long RowHeight=CurReg->Height();
//	static COLORREF CurColor;
//	m_vRowOfPaintCell.clear();
//	for (long j=0;j<RowHeight;j++)
//	{
//		CurColor=pPicDC->GetPixel(RowStartX,j+RowStartY);
//		if (CurColor!=gNULLCOLOR)
//		{
//		
//			RecordPaintCell(CurColor,pPicDC,RowHeight,RowStartX,j+RowStartY);
//			j=m_CurCell.bottom;//��+1
//		}
//	}
//
//	return !m_vRowOfPaintCell.empty();
//}
bool CRecognizePicture::SearchValidateRegionInRow(CDC*pPicDC,ItOfRegVec CurReg,unsigned RowIndex)
{

	long RowHeight=CurReg->Height();
	static COLORREF CurColor;
	/////////////////////////���������������߽���/////////////////////////////////////////////////
	long SearchLineX=CurReg->m_vRowsVec[RowIndex].left+CurReg->m_vRowsVec[RowIndex].Width()*0.5;
	long RowStartY=CurReg->m_vRowsVec[RowIndex].top;
	m_vRowOfPaintCell.clear();
	for (long j=RowStartY;j<CurReg->m_vRowsVec[RowIndex].bottom;j++)
	{
		CurColor=pPicDC->GetPixel(SearchLineX,j);
		if (CurColor!=gNULLCOLOR)
		{
			CRect PaintCell;
			PaintCell.top=j;
			PaintCell.bottom=CurReg->m_vRowsVec[RowIndex].bottom;
			PaintCell.left=CurReg->m_vRowsVec[RowIndex].left;
			PaintCell.right=CurReg->m_vRowsVec[RowIndex].right;
			RecordPaintCell(CurColor,pPicDC,PaintCell,SearchLineX,j);
			j=m_CurCell.bottom;//��+1
		}
	}
	return !m_vRowOfPaintCell.empty();
}
bool  CRecognizePicture::SearchValidateRegionInGridRow(CDC*pPicDC,ItOfRegVec CurReg,unsigned RowIndex)
{
	long RowHeight=CurReg->Height();
	static COLORREF CurColor;
	/////////////////////////���������������߽���/////////////////////////////////////////////////
	long SearchLineX=CurReg->m_vRowsVec[RowIndex].left+CurReg->m_vRowsVec[RowIndex].Width()*0.5;//
	long RowStartY=CurReg->m_vRowsVec[RowIndex].top;
	m_vRowOfPaintCell.clear();
	long HalfGridHeight=0.5*gHeightOfEveryPaintCell;
	for (long j=RowStartY+HalfGridHeight;j<CurReg->m_vRowsVec[RowIndex].bottom;j=j+gHeightOfEveryPaintCell)//ÿ����Ԫ�����ɫ
	{
		
		CurColor=pPicDC->GetPixel(SearchLineX,j);
		if (CurColor!=gNULLCOLOR)
		{
			CRect PaintCell;
			PaintCell.top=j-HalfGridHeight;   //��Ԫ����������ʼ����
			if (j+gHeightOfEveryPaintCell>=CurReg->m_vRowsVec[RowIndex].bottom)//��������դ���ڱ߽紦�Ҹ߶����ڰ������
			{	
				PaintCell.bottom=CurReg->m_vRowsVec[RowIndex].bottom;		
			}
			else
			{	
				PaintCell.bottom=PaintCell.top+gHeightOfEveryPaintCell;
			}	//��Ԫ����������ֹ����,�Ҹо���Ӧ��һ		
			PaintCell.left=CurReg->m_vRowsVec[RowIndex].left;
			PaintCell.right=CurReg->m_vRowsVec[RowIndex].right;
			RecordGridPaintCell(CurColor,pPicDC,PaintCell,SearchLineX,j);
			//j=m_CurCell.bottom;
		}
		//j=j+gHeightOfEveryPaintCell;
	}
	return !m_vRowOfPaintCell.empty();
}
ColorVec  CPaintCell::m_vColorToBePainted;
bool CRecognizePicture::RecordPaintCell(COLORREF& CurColor,CDC*pPicDC,CRect& CurCellRect,long SearchStartX,long SearchStartY)
{
	//CurCell.bottom;
	m_CurCell=CurCellRect;
// 	m_CurCell.top=StartY;
// 	m_CurCell.left=StartX;
// 	m_CurCell.right=StartX+gRowWidth-1;//��0��ʼҪ��1����
// 	m_CurCell.bottom=StartY;
	m_CurCell.pushBackColor(CurColor);
	unsigned MidleLineX=(m_CurCell.left+m_CurCell.right)*0.5;//���������
	//for (long j=0;j<RowHeight;j++)//��������
	//{
	//	if (pPicDC->GetPixel( StartX,j+ StartY)!=CurColor)
	//	{
	//		break;
	//	} 
	//	else
	//	{
	//		m_CurCell.bottom++;
	//	}
	//}
	m_CurCell.bottom=CurCellRect.top+SearchAlongY(CurColor,pPicDC,CurCellRect.bottom, MidleLineX,CurCellRect.top);//���������������
	if (m_CurCell.bottom>CurCellRect.top)//��ֹ��Ϳ����ֻ��һ�����ؿ�Ĵ������
	{
		m_vRowOfPaintCell.push_back(m_CurCell);
		return true;
	}
	return false;
}

bool CRecognizePicture::RecordGridPaintCell(COLORREF& CurColor,CDC*pPicDC,CRect& CurCellRect,long SearchStartX,long SearchStartY)
{
	m_CurCell.pushBackColor(CurColor);
//	unsigned MidleLineX=(m_CurCell.left+m_CurCell.right)*0.5;//���������
	m_CurCell=CurCellRect;
	m_vRowOfPaintCell.push_back(m_CurCell);
	return true;
}
int CMapSearch::SearchAlongX(COLORREF& CurColor,CDC*pPicDC,long Border,long StartX,long StartY)
{
	int lengthFromStartPoint=0;
	if (StartX>Border)//-����
	{
		for (long j=StartX;j>Border;j--)//��������
		{
			if (pPicDC->GetPixel( j,StartY)!=CurColor)
			{
				break;
			} 
			else
			{
				lengthFromStartPoint--;
			}
		}
	}
	else
	{
		for (long j=StartX;j<Border;j++)//��������
		{
			if (pPicDC->GetPixel(j,StartY)!=CurColor)
			{
				break;
			} 
			else
			{
				lengthFromStartPoint++;
			}
		}
	}	
	return lengthFromStartPoint;
}
int  CMapSearch::SearchAlongY(COLORREF& CurColor,CDC*pPicDC,long Border,long StartX,long StartY)
{
	int lengthFromStartPoint=0;
	if (StartY>Border)//-����
	{
		for (long j=StartY;j>Border;j--)//��������
		{
			if (pPicDC->GetPixel( StartX,j)!=CurColor)
			{
				break;
			} 
			else
			{
				lengthFromStartPoint--;
			}
		}
	}
	else
	{
		for (long j=StartY;j<Border;j++)//��������
		{
			if (pPicDC->GetPixel( StartX,j)!=CurColor)
			{
				break;
			} 
			else
			{
				lengthFromStartPoint++;
			}
		}
	}	
	return lengthFromStartPoint;
}
bool CMapSearch::SearchLengthOfNonNuLLColor(CDC* pDCOfMapToRec,long XBorder,long YBorder,long StartX,long StartY)
{
	COLORREF CurColor;
	int iterAlongX;
	int iterAlongY;
	if (StartX<XBorder)
	{iterAlongX=1;}
	else
	{iterAlongX=-1;}
	if (StartY<YBorder)
	{iterAlongY=1;}
	else
	{iterAlongY=-1;}
	//////////////////////////���滹��ֻ��X,Y��+����������δ���-������������////////////////////////////////////////////////
	for (long i= StartX;i<XBorder;i=i+iterAlongX)
	{
		for (long j=StartY;j<YBorder;j=j+iterAlongY)
		{
			CurColor=pDCOfMapToRec->GetPixel(i,j);
			if (CurColor!=gNULLCOLOR)
			{
				m_SearchResRect.top=j;
				m_SearchResRect.left=i;
				m_SearchResRect.bottom=j+SearchAlongY(CurColor,pDCOfMapToRec,YBorder,i,j+1);
				m_SearchResRect.right=i+SearchAlongX(CurColor,pDCOfMapToRec,XBorder,i+1,j);
				if (m_SearchResRect.Width()==0||m_SearchResRect.Height()==0)
				{	return false;}
				return true;
			}
		}
	}
	return false;
}
int CPreRecgnize::LookForParmOfGapBetweenCell(CDC* pDCOfMapToRec,long MapWidth,long MapHeight)
{
	if (SearchLengthOfNonNuLLColor(pDCOfMapToRec,MapWidth,MapHeight,0,0))//0��ʼ���������������
	{
		if (m_SearchResRect.Width()<MINI_CELL_WIDTH_THREAD)//ֻ�м�϶�Ŀ��С��2
		{
			g_sGapBetweenCellParm.m_uWidth=m_SearchResRect.Width()+1;
			g_sGapBetweenCellParm.s_bGapExist=true;
			return 1;
		}
		if (m_SearchResRect.Height()<MINI_CELL_WIDTH_THREAD)//ֻ�м�϶�ĸ߶�С��2���ⷢ�ֵ��Ǹ���ļ�϶���߶�
		{
			g_sGapBetweenCellParm.m_uWidth=m_SearchResRect.Height()+1;
			//g_sGapBetweenCellParm.m_uHeight=m_SearchResRect.Height();
			g_sGapBetweenCellParm.s_bGapExist=true;
			return 1;
		}
		/////////////////////���ֵ��Ǹ���Ϳ��Ԫ,,��û�з��ֿ�϶����Ϣ/////////////////////////////////////////////////////
		if (gCellSizePreRecFlag==AVERAGE_SIZE_OF_CELL)
		{
			m_RecgnizedWidthParmOfPaintCell=SearchWidthOfOneParm(pDCOfMapToRec,MapWidth,MapHeight);
			m_RecgnizedHeightParmOfPaintCell=SearchHeightOfOneParm(pDCOfMapToRec,MapWidth,MapHeight);
		}
		else
		{
			m_RecgnizedWidthParmOfPaintCell=m_SearchResRect.Width()+1;
			m_RecgnizedHeightParmOfPaintCell=m_SearchResRect.Height()+1;
		}
		//������㣬��һ�����ֵ���Ϳ��Ԫ���½Ǵ���Ȼ�п�϶��������ڵĻ�
		if (SearchLengthOfNonNuLLColor(pDCOfMapToRec,MapWidth,MapHeight,m_SearchResRect.right+1,m_SearchResRect.bottom+1))
		{
			if (m_SearchResRect.Width()<MINI_CELL_WIDTH_THREAD||m_SearchResRect.Height()<MINI_CELL_WIDTH_THREAD)//ֻ�м�϶�Ŀ��С��2
			{
				g_sGapBetweenCellParm.m_uWidth=min(m_SearchResRect.Width()+1,m_SearchResRect.Height()+1);
				g_sGapBetweenCellParm.s_bGapExist=true;
				return 2;
			}
			//���ҵ�һ���ǿ�϶
			if (gCellSizePreRecFlag!=AVERAGE_SIZE_OF_CELL)
			{
				m_RecgnizedWidthParmOfPaintCell=min(m_RecgnizedWidthParmOfPaintCell,m_SearchResRect.Width()+1);//��ֹ��һ�����ֵ���������ͬ��ɫ����Ϳ����
				m_RecgnizedHeightParmOfPaintCell=min(m_RecgnizedHeightParmOfPaintCell,m_SearchResRect.Height()+1);
			}
			g_sGapBetweenCellParm.s_bGapExist=false;
			return 3;
		}
		return 3;
	}
	g_sGapBetweenCellParm.s_bGapExist=false;
	return 0;
}
bool CPreRecgnize::PreReggnizeForParm(CDC* pDCOfMapToRec,long MapWidth,long MapHeight)
{
	int GapSearchRes=LookForParmOfGapBetweenCell(pDCOfMapToRec,MapWidth,MapHeight);
	if ( GapSearchRes>=2)//��¼����Ϳ��Ԫ��,�������޼�϶,
	{
		SetParmAccordingly();
		return true;
	}
	else if ( GapSearchRes==1)//�м�϶û��¼����Ϳ��Ԫ
	{
		long NStartX;
		long NStartY;
		if (m_SearchResRect.Height()<MINI_CELL_WIDTH_THREAD)//�ҵ�����ļ�϶
		{
			NStartX=0;
			NStartY=m_SearchResRect.bottom+1;
		}
		else//�ҵ�Y��ļ�϶
		{ 
			NStartX=m_SearchResRect.right+1;
			NStartY=0;
		}
		if (LookForParmOfPaintCell(pDCOfMapToRec,MapWidth, MapHeight,NStartX,NStartY))
		{
			SetParmAccordingly();
			return true;
		}
	}
	if (LookForParmOfPaintCell(pDCOfMapToRec,MapWidth, MapHeight,0,0))//û��϶��û��¼����Ԫ���ƺ������ܣ�����
	{
		SetParmAccordingly();
		return true;
	}
	return false;

}
unsigned CAverageCellSizeRec::Search1LineForAllPossibleParmOfPaintCell(CDC* pDCOfMapToRec,long MapWidth,long MapHeight,long StartX,long StartY,unsigned& MiniSizeOfParm)
{		
	long CurX=StartX;
	std::pair<ResMapType::iterator,bool > InserReslt;//map��������Ľ��
	while(CurX<MapWidth)
	{
		if (SearchLengthOfNonNuLLColor(pDCOfMapToRec,MapWidth,MapHeight,CurX,StartY))
		{
			CurX=m_SearchResRect.right+1;
			if (MiniSizeOfParm>m_SearchResRect.Width())
			{				
				MiniSizeOfParm=m_SearchResRect.Width();
				InserReslt=m_mPossibleWidthOfCell.insert(MValType(MiniSizeOfParm,1));
				if (!InserReslt.second)
				{++InserReslt.first->second;}
				//m_mPossibleWidthOfCell.push_back(MiniSizeOfParm);
			}
			else if (m_SearchResRect.Width()<MiniSizeOfParm*BIGEST_SIZE_RATIO_OF_ONE_CELL)//
			{
				InserReslt=m_mPossibleWidthOfCell.insert(MValType(m_SearchResRect.Width(),1));
				if (!InserReslt.second)
				{++InserReslt.first->second;}
				//m_mPossibleWidthOfCell.push_back(m_SearchResRect.Width());
			}
		}
		else
		{
			return MiniSizeOfParm;
		}			
	}
	return MiniSizeOfParm;		
}
unsigned CAverageCellSizeRec::SearchWidthOfOneParm(CDC* pDCOfMapToRec,long MapWidth,long MapHeight)
{
	unsigned MiniWidth=MapWidth;
	for (long i=0;i<MapHeight;i=i+20)//��Խʽ����ɨ��
	{
		MiniWidth=Search1LineForMiniParmOfPaintCell(pDCOfMapToRec,MapWidth,MapHeight,0,i,MiniWidth);
	}
	m_mPossibleWidthOfCell.clear();
	if (MiniWidth==MapWidth||MiniWidth<MINI_CELL_WIDTH_THREAD)
	{return 0; }
	// m_vPossibleWidthOfCell.push_back(MiniWidth);
	for (long i=0;i<MapHeight;i=i+10)
	{
		MiniWidth=Search1LineForAllPossibleParmOfPaintCell(pDCOfMapToRec,MapWidth,MapHeight,0,i,MiniWidth);
	}
	//ResMapType ItOfWidthVec=m_mPossibleWidthOfCell.begin();
	unsigned Sum=0;
	unsigned Num=0;
	for (ResMapType::iterator ItOfWidthVec=m_mPossibleWidthOfCell.begin();ItOfWidthVec!=m_mPossibleWidthOfCell.end();ItOfWidthVec++)
	{
		Sum+=ItOfWidthVec->first*(ItOfWidthVec->second);
		Num+=ItOfWidthVec->second;
		//Num++;
	}
	if (Num>0)
	{return Floor4_Ceil5((float)Sum/Num);}
	return 0;

}
unsigned CAverageCellSizeRec::Search1LineForMiniParmOfPaintCell(CDC* pDCOfMapToRec,long MapWidth,long MapHeight,long StartX,long StartY,unsigned& MiniSizeOfParm)
{
	CRect MinSizeRect;
	MinSizeRect.left=StartX;
	MinSizeRect.right=MiniSizeOfParm+StartX;
	long CurX=StartX;
	while(CurX<MapWidth)
	{
		if (SearchLengthOfNonNuLLColor(pDCOfMapToRec,MapWidth,MapHeight,CurX,StartY))
		{
			CurX=m_SearchResRect.right+1;
			if (MinSizeRect.Width()>m_SearchResRect.Width())
			{	MinSizeRect=m_SearchResRect;}
		}
		else
		{return MinSizeRect.Width();}			
	}
	return MinSizeRect.Width();	
}
unsigned CAverageCellSizeRec::Search1RowForMiniParmOfPaintCell(CDC* pDCOfMapToRec,long MapWidth,long MapHeight,long StartX,long StartY,unsigned& MiniSizeOfParm)
{
	CRect MinSizeRect;
	MinSizeRect.top=StartY;
	MinSizeRect.bottom=MiniSizeOfParm+StartY;
	long CurY=StartY;
	while(CurY<MapHeight)
	{
		if (SearchLengthOfNonNuLLColor(pDCOfMapToRec,MapWidth,MapHeight,StartX,CurY))
		{
			CurY=m_SearchResRect.bottom+1;
			if (MinSizeRect.Height()>m_SearchResRect.Height())
			{	MinSizeRect=m_SearchResRect;}
		}
		else
		{return MinSizeRect.Height();}		//���ļ��㷽ʽ����Ҫ+1	
	}
	return MinSizeRect.Height();		
}
unsigned CAverageCellSizeRec::Search1RowForAllPossibleParmOfPaintCell(CDC* pDCOfMapToRec,long MapWidth,long MapHeight,long StartX,long StartY,unsigned& MiniSizeOfParm)
{		
	long CurY=StartY;
	std::pair<ResMapType::iterator,bool > InserReslt;//map��������Ľ��
	while(CurY<MapHeight)
	{
		if (SearchLengthOfNonNuLLColor(pDCOfMapToRec,MapWidth,MapHeight,StartX,CurY))
		{
			CurY=m_SearchResRect.bottom+1;
			if (MiniSizeOfParm>m_SearchResRect.Height())
			{				
				MiniSizeOfParm=m_SearchResRect.Height();
				InserReslt=m_mPossibleHeightOfCell.insert(MValType(m_SearchResRect.Height(),1));
				if (!InserReslt.second)
				{++InserReslt.first->second;}
			}
			else if (m_SearchResRect.Height()<MiniSizeOfParm*BIGEST_SIZE_RATIO_OF_ONE_CELL)//
			{
				InserReslt=m_mPossibleHeightOfCell.insert(MValType(m_SearchResRect.Height(),1));
				if (!InserReslt.second)
				{++InserReslt.first->second;}
				//m_vPossibleHeightOfCell.push_back(m_SearchResRect.Height());
			}
		}
		else
		{
			return MiniSizeOfParm;
		}			
	}
	return MiniSizeOfParm;		
}
unsigned CAverageCellSizeRec::SearchHeightOfOneParm(CDC* pDCOfMapToRec,long MapWidth,long MapHeight)
{
	unsigned MiniHeight=MapHeight;
	for (long i=0;i<MapWidth;i=i+20)//��Խʽ����ɨ��
	{
		MiniHeight=Search1RowForMiniParmOfPaintCell(pDCOfMapToRec,MapWidth,MapHeight,i,0,MiniHeight);
	}
	m_mPossibleHeightOfCell.clear();
	if (MiniHeight==MapHeight||MiniHeight<MINI_CELL_WIDTH_THREAD)
	{return 0; }
	// m_vPossibleWidthOfCell.push_back(MiniWidth);
	for (long i=0;i<MapWidth;i=i+10)
	{
		MiniHeight=Search1RowForAllPossibleParmOfPaintCell(pDCOfMapToRec,MapWidth,MapHeight,i,0,MiniHeight);
	}
//	std::vector<unsigned>::iterator ItOfWidthVec=m_mPossibleHeightOfCell.begin();
	unsigned Sum=0;
	unsigned Num=0;
	for (ResMapType::iterator ItOfWidthVec=m_mPossibleHeightOfCell.begin();ItOfWidthVec!=m_mPossibleHeightOfCell.end();ItOfWidthVec++)
	{
		Sum+=ItOfWidthVec->first*(ItOfWidthVec->second);
		Num+=ItOfWidthVec->second;
		//Num++;
	}
	
	if (Num>0)
	{return Floor4_Ceil5((float)Sum/Num);}
	return 0;

}

//int CPreRecgnize::SearchBorderOfCurPaintCell(COLORREF& CurColor,CDC*pPicDC,long Border,long StartX,long StartY,bool bSearchAlongX)
//{
//	
//	if (bSearchAlongX)//��x����
//	{
//		return SearchAlongX(CurColor,pPicDC,Border, StartX, StartY);
//	}
//	else
//		return SearchAlongY(CurColor,pPicDC,Border, StartX, StartY);
//}
