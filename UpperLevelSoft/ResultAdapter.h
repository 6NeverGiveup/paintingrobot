#pragma once
/** @file 
*@brief ���ļ����ڴ�Ÿ��ִ���ʶ�����������࣬�󲿷���ǹ����Ϊ���õȲ����йص������ڱ��ļ���ʶ�𲿷���ʵ��󲿷��˹������޹�
* @author Yang GAO
* @date 
* @version 1.0
*
* 
*/
/**
* @class 
* @brief ��ʶ��������������ɫ˳��Ӱ��Ϊ������Ҫ��˳��
*
* ����ָ������ţ�Ҫ��ʶ�������ɫһһƥ�����������ṩ����ƥ��Ľ�ڡ�
*/
#include <vector>
#include <map>
#include <algorithm>
#include "gyMath.h"
#include <math.h>
#define MAX_COLOR_MACHINE_INDEX 6 //������Ϳ��ɫ��ΪMAX_COLOR_MACHINE_INDEX������ɫ��ŷ�ΧΪ��0~MAX_COLOR_MACHINE_INDEX-1��MAX_COLOR_MACHINE_INDEX����Ϊ��ɫ
/**
*@brief ר�����ڱȽ�m_ColorIndexRecedMap�еĵ�2���������ƺ�����һ������,�º�����.����findif�����У����ҵ�ָ���Ķ�����ô����Stl��findifҪ��ġ�Ҳ���ּ���
*
*
*@parm
*
*@return
*@todo
*/
template<class T>
class map_finder
{
public:
	map_finder(unsigned &cmp):Compaer(cmp){};
		const unsigned Compaer;
	bool operator ()(const T &pair)
	{   return pair.second == Compaer;} 

};
/**
* @class 
* @brief �������ڽ�ʶ�����ɫ�洢��ӳ�䵽��ɫ���,ע��:�����еĻ�����ţ�ʵ����Ҳ�Ǻ������ǹģʽ�е�������
*
* 
*/
class CColorResAdapter
{
public:
	typedef std::map<unsigned,unsigned> ColorResMapType;	
	typedef std::map<unsigned,unsigned>::value_type MValType;

	typedef std::map<unsigned,int> ColorResHexMapType;///<������ŵ�PLC�е�2����ӳ��ͼ����
	typedef std::map<unsigned,int>::value_type HexMValType;///<ColorResHexMapType�����ݶ�Ӧ������
	CColorResAdapter( );
	~CColorResAdapter();
public:
/**
*@brief ��ɫӳ�����ĩβ���һ��ӳ��
*
*��ɫӳ�����ĩβ���һ��ӳ�䣬Ĭ��ӳ��ǰ���ֵ��һ���ģ�û��ӳ����ֵ�����ظ�����������Ҫע��
*
*@parm
*
*@return
*@todo
*/
	bool pushback(unsigned Index)
	{
		std::pair< ColorResMapType::iterator,bool > InserReslt;//map��������Ľ��
		InserReslt=m_ColorIndexRecedMap.insert(MValType(Index,Index));
		return InserReslt.second;
	}
	unsigned size()
	{
		return m_ColorIndexMachineHexMap.size();
	}
	/**
	*@brief ��ɫ��PLC2���Ʊ���ӳ�����ĩβ���һ��ӳ��
	*
	*��ɫӳ�����ĩβ���һ��ӳ�䣬Ĭ��ӳ��ǰ���ֵ��һ���ģ�û��ӳ����ֵ�����ظ�����������Ҫע��
	*0����ǹ��Ӧֵ0x01,1�Ŷ�Ӧ0x02,....
	*@parm
	*
	*@return
	*@todo
	*/
	bool pushback_HexMap(unsigned Index)
	{
		std::pair<ColorResHexMapType::iterator,bool > InserReslt;//map��������Ľ��
		int Val=1;		
		if (Index==MAX_COLOR_MACHINE_INDEX)
		{Val=0;	}
		else
		{Val<<=Index;}
		InserReslt=m_ColorIndexMachineHexMap.insert(HexMValType(Index,Val));
		return InserReslt.second;
	}
	unsigned Compaer;

	
	
	
	
/**
*@brief �Ը�����ʶ��ɫ���ı����Ӧ��ʵ����ɫ���(����1��ʽ)��
*
*�����+1����������һ����������ı��Ϊͼ��ʶ���еı�ţ�������Ӧ�Ļ�����ɫӳ��ֵ+1�����ǣ�
*ǰ���ǣ������ȵ�ͼ������ռ�õ�ӳ��ֵ�������������Ա��������ܻ���ı��MapRecedIndex���ȶȸ��͵�
*��ɫ����Ӧ�Ļ�����ɫֵ����Щ��ŵ����ȶ��ǰ��ո�С�ı�Ÿ����ȵķ�ʽ��
*@parm  MapRecedIndex ͼ��ʶ���и������ɫ�������
*
*@return �ɹ��Ļ�������
*@todo
*/
	bool AddMachineIndexOnRule(unsigned MapRecedIndex)
	{
		ColorResMapType::iterator iter;
		iter = m_ColorIndexRecedMap.find(MapRecedIndex);
		if (iter==m_ColorIndexRecedMap.end())
		{	return false;	}//���������û���ҵ��ñ��
		unsigned AddedNum=1;
		ColorResMapType::iterator it;
		do 
		{
			unsigned AddedRes=RoundAddColorIndex(iter->second,AddedNum);
			iter->second=AddedRes;
			it = std::find_if(m_ColorIndexRecedMap.begin(),iter,map_finder<MValType>(AddedRes));
		} while (it!=iter);
		InfluenceLessImportanters(iter,m_ColorIndexRecedMap.end());
		
		return true;
	}
/**
*@brief ����ʶ���������ɫ��ţ���ѯ����ɫ��Ӧ��ǹ�ţ�Ҳ���ǻ������
*
*
*@parm  MColorIndex ʶ���������ɫ���
*
*@return
*@todo
*/
	unsigned QueryMachineColorIndexByRecedIndex(unsigned MColorIndex)
	{
		if (MColorIndex>6)
		{
			MColorIndex=6;
		}
		ColorResMapType::iterator iter=m_ColorIndexRecedMap.find(MColorIndex);     //����ֵ���Ϊ6
		//std::find_if(m_ColorIndexRecedMap.begin(),m_ColorIndexRecedMap.end(),map_finder<MValType>(AddedRes));
		//ColorResHexMapType::iterator iterHex=m_ColorIndexMachineHexMap.find(iter->second);
		return iter->second;               //���ش洢����
	}
	/**
	*@brief ����ǹ�ţ�Ҳ���ǻ�����ţ���ѯ��ǹ��PLC�еĶ�Ӧ���ƶ����Ʊ���
	*
	*
	*@parm  MColorIndex ������ţ��������Ϊÿ����ɫ���õ�����
	*
	*@return
	*@todo
	*/
	unsigned QueryMachineHexMapByMachineColorIndex(unsigned MColorIndex)
	{
			ColorResHexMapType::iterator iterHex=m_ColorIndexMachineHexMap.find(MColorIndex);
			return iterHex->second;
	}
	unsigned QueryMachineHexMapByRecedIndex(unsigned MColorIndex)
	{
		unsigned MechineColor=QueryMachineColorIndexByRecedIndex( MColorIndex);
		return QueryMachineHexMapByMachineColorIndex( MechineColor);
	}
	/**
	*@brief ����PLC�еĶ�Ӧ���ƶ����Ʊ��룬��������ѯ������ţ��������Ϊÿ����ɫ���õ�����,ע��:�����еĻ�����ţ�ʵ����Ҳ�Ǻ������ǹģʽ�е�������
	*
	*
	*@parm  MhexValue ����ɫ�Ķ����Ʊ���
	*
	*@return �ҵ����ظ���ɫ�Ļ������룬���˹����õ����֡����򷵻�-1
	*@todo
	*/
	unsigned QueryMachineColorIndexByMachineHexValue(unsigned MhexValue)
	{
		ColorResHexMapType::iterator iterFound = std::find_if(m_ColorIndexMachineHexMap.begin(),m_ColorIndexMachineHexMap.end(),map_finder<MValType>(MhexValue));//�ҳ��ö�����ֵ��Ӧ�Ļ������
		return iterFound==m_ColorIndexMachineHexMap.end()?-1:iterFound->first;
	}
protected:
	/**
	*@brief ��ɫ ComparedIt��CurIt�����ȶȸ�����
	*
	*
	*@parm
	*
	*@return
	*@todo
	*/
	bool LessImportant(ColorResMapType::iterator CurIt,ColorResMapType::iterator ComparedIt)
	{return CurIt->first<ComparedIt->first;}
	
/**
*@brief �����յ�Ӱ��ĵ���Ҫ��ֵ�����ڵݹ����
*
*
*@parm
*
*@return
*@todo
*/
	void InfluenceLessImportanters(ColorResMapType::iterator ChangedIter,ColorResMapType::iterator IterEnd)
	{
		if (ChangedIter==IterEnd)
		{return;}
		ColorResMapType::iterator CurIter=ChangedIter;
		CurIter++;
		while ( CurIter!=IterEnd)
		{
			CurIter= std::find_if(CurIter,IterEnd,map_finder<MValType>(ChangedIter->second));
			if (CurIter!=IterEnd)
			{
				AddMachineIndexOnRule(CurIter->first);///<�ݹ����
			}		
		}
	}
/**
*@brief ѭ��������ɫ���
*
*�ñ�ż��˺���� m_MaxColorNum�Ļ������ص���������m_MaxColorNum�������
*@parm
*
*@return
*@todo
*/
	unsigned RoundAddColorIndex(unsigned MapRecedIndex,unsigned AddNum=1)
	{
		unsigned res=MapRecedIndex+AddNum;
		return res>m_MaxColorNum?((res%m_MaxColorNum)-1):res;/*-*/;
	}
protected:
	ColorResMapType m_ColorIndexRecedMap;///<ʶ�����������������ӵ���ɫ˳��֮���Ӱ�䣬��һ��Ԫ��Ϊʶ�����˳�򣬵�2��Ԫ��Ϊ���������˳�򣬴��ȥ����Զ����ؼ��ִ�С���������
	unsigned m_MaxColorNum;					///<������ɫ���
	ColorResHexMapType m_ColorIndexMachineHexMap;///<�ɻ������ӵ���ɫ˳���ţ���PLC��2���Ƹ�ʽ��ǹ��ŵ�ӳ�䡣�����PLC�������Ļ�����ɫ��ţ���һ��Ԫ��Ϊ���������˳�򣬵�2��Ԫ��ΪPLC����ɫ��Ӧ��2����ֵ
private:
};
typedef std::vector<float>::iterator MotionParm_It_TYPE;
/**
* @class 
* @brief ����ר������ʶ�����γ��˶������������
*
* 
*/
template<class RecResType>
class MotionParmAdapter
{
public:
	MotionParmAdapter()
	{
		m_uGunNum=2;
		m_fGunDis=2000;
	};
	~MotionParmAdapter(){};
	typedef MotionParm_It_TYPE Parm_It_TYPE;
/**
*@brief ����ͼƬ��ʵ�ʵı�����
*
*
*@parm Ratio Ϊ1�����ض�Ӧ����mm
*
*@return
*@todo
*/
	//void SetRatioOfPiexl(float Ratio)
	//{
	//	m_fRatioOfPixel=Ratio;
	//}
	/**
	 *@brief ������Ĳ�����ʽ��Ϊ���������г�����������ĸ�ʽ
	 *
	 *������Ĳ�����ʽ��Ϊ���������г�����������ĸ�ʽ,�������贫������г��Ȳ�����λΪ(������)ʱ������Ҫ����
	 *@parm
	 *
	 *@return
	 *@todo
	 */
	float FormatLengthParm(float parm,bool JudgeXOrY)             //2016��12��10�ո�
	{
		if (JudgeXOrY==true)         //X��
		{
			return parm*m_fRatioOfPixel;
		}
		if (JudgeXOrY==false)      //Y��
		{
			return parm*m_fRatioOfYPixel;
		}
		
	}
	/**
	*@brief ʵ���ٶȣ�
	*
	*
	*@parm Vel ʵ�������ٶ� ת/s
	*
	*@return
	*@todo
	*/
	void SetRealVel(float Vel)
	{
		m_sHeaderInfo.Vel=Vel;
	}
	void SetRealRatio(float RealRatio,float RealYRatio)
	{		
		m_fRatioOfPixel=RealRatio;	
		m_fRatioOfYPixel=RealYRatio;
	}
	void SetCellSizeReal()            //�γɵ�Ԫ���ʵ��ֵ
	{
		m_sHeaderInfo.PaintWidth=FormatLengthParm(gRowWidth,true);
		m_sHeaderInfo.PaintHeigth=FormatLengthParm(gHeightOfEveryPaintCell,false);
	}
	/**
	*@brief ����ӿں�����������������
	*
	*
	*@parm WorkRegNum ��Ҫ�����ĸ��������еĲ���>=0,����ֵС��0ʱ����ȫ���������Ĳ�����
	*
	*@return �ɹ���Ϊ��
	*@todo
	*/
	Parm_It_TYPE ExportMotionParmVec(int WorkRegNum)
	{
		
		Formheader(pRecRes->NumOfRowInGivenWorkReg(WorkRegNum),m_sHeaderInfo.PaintHeigth,m_sHeaderInfo.PaintWidth,m_sHeaderInfo.Vel);
		if (WorkRegNum>=0)	{
			return QueryParmVec(WorkRegNum,m_fRatioOfPixel,m_fRatioOfYPixel);
		}
		else	{
			return  QueryAllRegParmVec(m_fRatioOfPixel);
		}
	
		//Formheader()
	}
	Parm_It_TYPE ExportMotionParmVecEnd(int WorkRegNum)
	{	 return QueryParmVecEnd(WorkRegNum);	}
/**
*@brief Ϊ���������ļ�ͷ������Ҳ�ǲ�����������ȫ�ֵ�һЩ����
*
*
*@parm
*
*@return
*@todo
*/
	Parm_It_TYPE  InsertParmHeader()
	{
		m_vParmVec.insert(m_vParmVec.begin(),m_vParmHeader.begin(),m_vParmHeader.end());
		return m_vParmVec.begin();
	}
protected:
	/**
	*@brief ������ǹ������ǹ���
	*
	*
	*@parm GunNum ��ǹ�� <100
	*@parm GunDis ��ǹ��� ��λ����,<2000
	*
	*@return ������ȷ�򷵻���
	*@todo
	*/
	bool SetPaintGunParm(unsigned GunNum,float GunDis)
	{
		if (GunNum>100||GunDis>2000)
		{return false;	}
		m_uGunNum=GunNum;
		m_fGunDis=GunDis;
		return true;
	}
	/**
	*@brief ����ʶ����
	*
	*
	*@parm
	*
	*@return �ɹ���Ϊ��
	*@todo
	*/
	bool ImportRecRes(RecResType* RecRes)
	{
		if (RecRes){	
			pRecRes=RecRes;            //pRecRes��ӵ���βε�һ��
			return true;
		}		
		return false;
	}
	/**
	*@brief �Եõ����˶���Χ��������
	*
	*�Եõ����˶���Χ�������䣬�Բ�������ǹ��װ,���µĲ�����ǹ�޷�����ȫ����Ϳ��Χ������
	*���ﲻ�����˶���Χ������Ƿ񳬳�����������г�����,����Ҫ�ⲿԤ�ȿ��ǵ�
	*@parm BorderTobeExtend ��Ҫ������˶���Χ�߽�,mm
	*@parm ExtendDirect ����ķ���+����Ϊ1��-����Ϊ-1
	*
	*@return �������˶���Χ�߽�,mm
	*@todo
	*/
	float ExtendMotionRange(float BorderTobeExtend,int ExtendDirect)
	{
		return BorderTobeExtend+ExtendDirect*(m_uGunNum-1)*m_fGunDis;
	}
	/**
	*@brief ��ָ���Ĺ������γ�����������������������ָ��
	*
	*�Ȳ�ѯ���ʶ������ÿ�е������أ�Ȼ������ǹ��װģʽ�Ĳ�ͬ��������
	*
	*@parm BorderTobeExtend ��Ҫ������˶���Χ�߽�,mm
	*@parm ExtendDirect ����ķ���+����Ϊ1��-����Ϊ-1
	*
	*@return �������˶���Χ�߽�,mm
	*@todo
	*/
	Parm_It_TYPE QueryParmVec(int WorkRegNum,float RatioOfPixel=m_fRatioOfPixel,float RatioOfYPixel=m_fRatioOfYPixel,bool bNewQuery=true)
	{
		unsigned StartY;
		unsigned EndY;
		if (bNewQuery)
		{	m_vParmVec.clear();	}
		
		bool bReserve=false;
		int Low=pRecRes->NumOfRowInGivenWorkReg(WorkRegNum);         //��ǰ���������
		for (unsigned i=0;i<pRecRes->NumOfRowInGivenWorkReg(WorkRegNum);i++)
		{
			if(pRecRes->QueryStartEndParmOfRow(i,WorkRegNum,StartY,EndY,RatioOfPixel,RatioOfYPixel))  //i�����У�WorkRegNumΪ�����������е�ǰ����ڼ�����
			{
				m_vParmVec.push_back(i);//ֻ�е�ǰ������Ҫ��Ϳ��С��Ԫ�ż�¼
				if (bReserve) {
					EndY=ExtendMotionRange(EndY,1);//��Ӧ������StartY�ģ���StartY=0ʱ�޷����䣬ֻ��EndY��ǡ�ý��һ��
					m_vParmVec.push_back(EndY);
					m_vParmVec.push_back(StartY);				
				}
				else{		
					EndY=ExtendMotionRange(EndY,1);
					m_vParmVec.push_back(StartY);
					m_vParmVec.push_back(EndY);
				}
			}
			bReserve=!bReserve;
		}
		return m_vParmVec.begin();
	}
	Parm_It_TYPE QueryParmVecEnd(int WorkRegNum)
	{
		return m_vParmVec.end();
	}
/**
*@brief �γɹ������ֲ���������m_vParmHeader���ظò��ֵ�ָ�롣
*
*
*@parm 
*
*@return
*@todo
*/
	Parm_It_TYPE Formheader(unsigned NumOfRowToBePaint,float PaintHeight,float PaintWidth,float Vel)
	{
		m_vParmHeader.clear();
		m_vParmHeader.push_back(NumOfRowToBePaint);
		m_vParmHeader.push_back(Vel);
		m_vParmHeader.push_back(PaintHeight);
		m_vParmHeader.push_back(PaintWidth);
		return m_vParmHeader.begin();
	}
	Parm_It_TYPE QueryHeader()
	{
		m_vParmHeader.begin();
	}
	Parm_It_TYPE QueryAllRegParmVec(float RatioOfPixel)
	{
		Parm_It_TYPE it;
		for (int i=0;i<pRecRes->NumOfRecedPic();i++)
		{	it=QueryParmVec(i,RatioOfPixel,false);	}
		return it;
	}
	RecResType* pRecRes;
protected:
public:
	std::vector<float>m_vParmVec;
	std::vector<float>m_vParmHeader;
	unsigned m_uGunNum;///<ǹ��
	float m_fGunDis;///<ǹ����mm
	struct HeaderInfo
	{
		float Vel;///<�ƶ�ʵ���ٶ�
		float PaintWidth;///<��Ϳ��Ԫʵ�ʿ��
		float PaintHeigth;///<��Ϳ��Ԫʵ�ʸ߶�
	}m_sHeaderInfo;///<�洢����ͷ�е���Ϣ����m_vParmHeader�е���ϢӦ��ȫһ��
	float m_fRatioOfPixel;///<���ص�ʵ��mm�ı�����
	float m_fRatioOfYPixel;
};


#define PARM_USE_COLOR_INDEX_ONLY //���ƺ꣬���屾���������ʽ�н�������ɫ��ţ���û�е�Ԫ���š���ɫ�Ĳ�����ɫ��Ԫ
/**
* @class 
* @brief ��ʶ����ת��ΪPLC��Ҫ�ĸ�ʽ���Է���ͨѶ
*
* 
*/
template<class RecResType,class PaintCellType>
//����ģ��������һ���������ݳ�Ա���������Ͳ���ȷ����������ĳ����Ա�����Ĳ����򷵻�ֵ�����Ͳ���ȷ����
//�ͱ��뽫��������Ϊģ�壬���Ĵ��ڲ��Ǵ���һ������ġ�ʵ�ʵ��࣬���Ǵ�����һ���ࡣ
class CPLC_Parm_Adapter:public VirtualGunMapperForMultiColoGun// public CColorResAdapter
{

	
public:
	typedef std::vector<int>::iterator PLC_Parm_It_TYPE;
	typedef std::vector<int> PLC_Parm_TYPE;
	/**
	*@brief ������������
	*
	*
	*@parm WorkRegNum ��Ҫ�����ĸ��������еĲ���>=0,����ֵС��0ʱ����ȫ���������Ĳ�����
	*
	*@return �ɹ���Ϊ��
	*@todo
	*/
	 PLC_Parm_It_TYPE ExportPLC_ParmVec(int WorkRegNum)
	{
		Formheader(FormatLengthParm(gHeightOfEveryPaintCell));
		if (WorkRegNum>0)	{
			return QueryParmVec(WorkRegNum);
		}
		else	{
			return  QueryAllRegParmVec();
		}		
	}
	 PLC_Parm_It_TYPE ExportPLC_ParmVecEnd(int WorkRegNum)
	{	 return QueryParmVecEnd(WorkRegNum);	}
	 PLC_Parm_It_TYPE  InsertParmHeader()
	 {
		 m_vParmVec.insert(m_vParmVec.begin(),m_vParmHeader.begin(),m_vParmHeader.end());
		 return m_vParmVec.begin();
	 }
	 /**
	 *@brief ����ʶ����
	 *
	 *
	 *@parm pRec ʶ������
	 *
	 *@return �ɹ���Ϊ��
	 *@todo
	 */
	 bool ImportRecRes(RecResType* pRec)                //�ββ�ȷ������
	 {	if (pRec){
			 pRecRes=pRec;
			 return true;
		}
		return false;
	 }
	 RecResType * QueryMapRecResPointer(void)
	 {
		 return pRecRes;
	 }
	 void SetRealRatio(float Ratio,float YRatio)
	 {
		 m_fRealRatio=Ratio;
		 m_fRealYRatio=YRatio;
	 }
protected:
	

	
	PLC_Parm_It_TYPE QueryAllRegParmVec()
	{
		PLC_Parm_It_TYPE it;
		for (int i=0;i<pRecRes->NumOfRecedPic();i++)
		{	it=QueryParmVec(i);	}
		return it;
	}
	/**
	*@brief ���ɲ���ͷ
	*
	*
	*@parm PaintCellHeight ��Ԫ�ĸ߶� ��λ���ף���ȡ����
	*
	*@return
	*@todo
	*/
	PLC_Parm_It_TYPE Formheader(unsigned PaintCellHeight)
	{
		//m_vParmHeader.push_back();
		m_vParmHeader.clear();
		m_vParmHeader.push_back(PaintCellHeight);
		return m_vParmHeader.begin();
	}
	PLC_Parm_TYPE m_vParmHeader;///<����������ɵĲ�����ͷ�����ΰ�����Ԫ��߶ȡ�
/**
*@brief ���ݱ�׼ֵ���жϸ����ķ����Ƿ��Ǹ��������飬
*
*������߶ȳ�������ֵһ����Χ����Ϊ�٣�����Ϊ��
*@parm CurCellHeight�����ʵ�ʸ߶�
*@parm StandardCellHeight ����߶ȵıȽϻ�׼
*
*@return ����Ϊ��
*@todo
*/
	bool IsRegularCell(float CurCellHeight, float StandardCellHeight)
	{
		static float Torerant=(BIGEST_SIZE_RATIO_OF_ONE_CELL-1)*StandardCellHeight;
		return fabs(CurCellHeight-StandardCellHeight)<Torerant;
	}
/**
*@brief ��¼ָ���ĵ�Ԫ
*
*����ʶ����Ľ����ֻ��¼����Ҫ��Ϳ�ĵ�Ԫ���������Ԫ�����г��ֿհ��������⴦��
*���յ�Ԫ����Ա�������λ��ȷ�������ţ�����������ͻȻ���ֿհ׵ķ���λ�ã��������жϳ��������ڲ��������в���հ׸�
*�Ա���������һ�еĵ�Ԫ����ǰ��ȫ����հ׸�
*@parm WorkRegNum ��ǰ��Ԫ���ڹ�������
*@parm i ��ǰ��Ԫ����к�
*@parm j ��ǰ��Ԫ����к�
*@parm bfirstCellInRow ��ǰ��Ԫ���ڱ������ǵ�һ��
*@parm bfirstCellInRow ��ǰ��Ԫ���ڱ������ǵ�һ��
*@parm PreIndexOfGrid ǰһ��Ԫ���ڱ����еı��
*@parm bFirstRow ��ǰ��Ԫ���������ǹ������ڵĵ�һ��
*
*@return
*@todo
*/
	void RecordExactCellToParmVec(int WorkRegNum,unsigned i,unsigned j,bool& bfirstCellInRow,long& PreIndexOfGrid,bool & bFirstRow)
	{
		unsigned StartY;
		unsigned EndY;
		CRect* pRegRectParm;
		PaintCellType* pCell=pRecRes->QueryPaintCell(i,j,WorkRegNum);  //���ص�ǰС��Ԫ���λ��
		pRegRectParm=pRecRes->QueryRegRectParm(WorkRegNum);
		StartY=(pCell->top)-(pRegRectParm->top);     //ÿһ�е���Ϳ��ʼλ��
		long IndexOfGrid=Floor4_Ceil5((float)StartY/gHeightOfEveryPaintCell);//���ڱ��
		if (bfirstCellInRow)		//ÿ�еĵ�һ��Ԫ��Ҫ���ǳ�ʼ��PreIndexOfGrid
		{	
			PreIndexOfGrid=IndexOfGrid;
			bfirstCellInRow=false;
			if (bFirstRow)//��Ϳ��ʼ��һ�У����ĵ�һ��Ԫ��֮ǰȫ����հ׸�
			{
				for (int i=0;i<IndexOfGrid;i++)	{
					//m_vParmVec.push_back(QueryMachineHexMapByRecedIndex(MAX_COLOR_MACHINE_INDEX));//����հ�ɫ���ؼ�ֻ�ڵ�һ�в���0
					;
				}
				bFirstRow=false;
			}
		}
#ifdef PARM_USE_COLOR_INDEX_ONLY
		long IndexDif=abs(IndexOfGrid-PreIndexOfGrid);//��Ų�
		if (IndexDif>1)	{
			for (int i=0;i<IndexDif-1;i++)	{
				m_vParmVec.push_back(QueryMachineHexMapByRecedIndex(MAX_COLOR_MACHINE_INDEX));//����հ�ɫ
			}
		}
		PreIndexOfGrid=IndexOfGrid;
#else
		if (!IsRegularCell(pCell->Height(), gHeightOfEveryPaintCell))//���ߴ�ķ��񣬱߽紦���ܳ���
		{
			EndY=(pCell->bottom)-(pRegRectParm->top);
			m_vParmVec.push_back(-1);//���ڱ��
			m_vParmVec.push_back(FormatLengthParm(StartY));
			m_vParmVec.push_back(FormatLengthParm(EndY));
		}
		else
		{m_vParmVec.push_back(IndexOfGrid);}//���ڱ��}		
#endif	
	m_vParmVec.push_back(QueryMachineHexMapByRecedIndex(pCell->m_uColorIndex));//��ɫ���
	}
/**
*@brief ��ѯ��Ҫ����Ĳ�����������ɫ�飬δ����ǹ��������
*
*������˳�����£�����ͷ�������ݡ���ÿ�бȶ���ǰ���е����ݣ�������Ҫ�Ľ����˲岹��
*���������ΰ���������������Ϳ�ĵ�Ԫ�������������������Ԫ��Ϣ��ע�⣬ÿ��Ϳ����ĵ�һ�У��ѿհ׿ո�������
*��Ԫ��Ϣ�������ָ�ʽ��PARM_USE_COLOR_INDEX_ONLY�����
*1��Ϊֻ����ɫ��ţ�ĿǰĬ��Ϊ����ʽ
*2��Ϊ������Ԫ��ţ��ǳ���Ļ�����Ԫ���Ϊ-1�����ҽ����õ�Ԫ����ֹλ�ã�+��ɫ��š�
*��������У�4��0��0,1,1,2,1,2
*           ����ʾ�����У�
*                  ��һ����4����Ԫ��ǰ������ɫΪ0����������ɫΪ1.���е�һ�аѿհ׵Ķ���������ɫ0��ɫ�顣
*                  �ڶ�����2����Ԫ����ɫ�ֱ�Ϊ1��2
*����ٶ�����ֳ�����Ϳ��Ԫ����õ�Ԫ��Ϊ�������һ��
*@parm
*
*@return
*@todo
*/
	PLC_Parm_It_TYPE QueryParmVec(int WorkRegNum)
	{
		bool bReserveOrder=false;///<�Ƿ��������¼˳��
		m_vParmVec.clear();
		long PreIndexOfGrid;///<����ǰһ����Ԫ�������еı��
		bool bFirstRow=true;//�Ƿ����㵽�ô��ĵ�һ��
		m_vInsertedNullCellInRows.clear();
		std::vector<int>NumOfInsertedNullTmp;
		for (unsigned j=0;j<pRecRes->NumOfRowInGivenWorkReg(WorkRegNum);j++)//ע����ܴ��ڿհ���,jΪ��Ϳ������
		{
			NumOfInsertedNullTmp.clear();
			NumOfInsertedNullTmp.push_back(j);//�ȼ����кţ��������û�еĻ����ܻ�ɾ��			
			//unsigned SizeOfInsertedNullCellVec=NumOfInsertedNullTmp.size();
		/*	pRecRes->QueryStartEndParmOfRow(i,WorkRegNum,StartY,EndY,RatioOfPixel);*/
			unsigned LinMax=pRecRes->NumOfCellInGivenRowOfGivenReg(WorkRegNum,j);//���ܱ��浱ǰ������Ҫ��Ϳ�ĵ�Ԫ	
			//////////////////////////////////////////////////////////////////////////
			int InsertedNum=0;
			//if (j!=pRecRes->NumOfRowInGivenWorkReg(WorkRegNum)-1){
			//	InsertedNum=CheckCurRowIfInsertNullColor(bReserveOrder,WorkRegNum,j,false,true);//����β�Ƿ���Ҫ�岹����������
			//}
			//if (j!=0){
			//	InsertedNum+=CheckCurRowIfInsertNullColor(bReserveOrder,WorkRegNum,j,false,false);//�������Ƿ���Ҫ�岹����ʵ����
			//}
			if (LinMax<=0)//�հ��еĻ�����
			{continue;}
			//////////////////////////////////////////////////////////////////////////
#ifdef PARM_USE_COLOR_INDEX_ONLY
			unsigned CurStartY;               //��ǰ�е���Ϳ��ʼλ��
			unsigned CurEndY;                 //��ǰ�е���Ϳ��ֹλ��
			pRecRes->QueryStartEndParmOfRow(j,WorkRegNum,CurStartY,CurEndY,1,1);
			unsigned NumOfCell=Floor4_Ceil5(float(CurEndY-CurStartY)/gHeightOfEveryPaintCell);     //��ǰ��Ҫ��Ϳ�ĵ�Ԫ
			m_vParmVec.push_back(NumOfCell);		//ѹ����������Ϳ��Ԫ����,����ֵ��������
			unsigned IndexOfTotal=m_vParmVec.size();		// ���е�Ԫ������λ��
#else			
			m_vParmVec.push_back(LinMax);			//ѹ����������Ϳ��Ԫ����,����ֵ��������
			unsigned IndexOfTotal=m_vParmVec.size();//���е�Ԫ������λ��
#endif			
			//if (j!=0&&(((j%2)==1)?true:false))//������һ�飬����ǰһ��ȥ�Ƚ�
			if (j!=0)//������һ�飬����ǰһ��ȥ�Ƚϣ��޸�����һ��
			{    
				//InsertedNum+=CheckCurRowIfInsertNullColor_FixBlankRow(bReserveOrder,WorkRegNum,j,true,false);//�Ƕ����У����һ����Ƚϵļ���Ƿ���Ҫ�岹����ʵ����
				InsertedNum=CheckCurRowIfInsertNullColor_FixBlankRow(bReserveOrder,WorkRegNum,j,true,false);//�Ƕ����У����һ����Ƚϵļ���Ƿ���Ҫ�岹����ʵ����
				if (InsertedNum!=0)
				{
					NumOfInsertedNullTmp.push_back(InsertedNum);
				}				
				//SaveInsertedNullCell(InsertedNum);
			}
			bool bFirstCellInRow=true;			
			if (bReserveOrder)	{        //���������ż�¼����												
				if (LinMax>0){					
					for (int i=LinMax-1;i>=0;i--)//���м�¼,����Ԫ��
					{						
						RecordExactCellToParmVec(WorkRegNum,i,j,bFirstCellInRow,PreIndexOfGrid,bFirstRow);
					}
				}				
			}
			else           //������˳�ż�¼����	
			{				
				for (unsigned i=0;i<LinMax;i++)//���������м�¼
				{
					RecordExactCellToParmVec(WorkRegNum,i,j,bFirstCellInRow,PreIndexOfGrid,bFirstRow);
				}
			}
			InsertedNum=0;
			if (j!=pRecRes->NumOfRowInGivenWorkReg(WorkRegNum)-1)	//ǰ����һ��
			{
				InsertedNum=CheckCurRowIfInsertNullColor_FixBlankRow(bReserveOrder,WorkRegNum,j,true,true);////�Ƕ�β�У����һ����Ƚϵ�ǰ�����Ƿ���Ҫ�岹����ʵ����
				//SaveInsertedNullCell(InsertedNum);
				if (InsertedNum!=0)
				{
					NumOfInsertedNullTmp.push_back(InsertedNum);
				}
			}
			if (NumOfInsertedNullTmp.size()>1)//�������µĿհ׸�
			{
				SaveInsertedNullCell(NumOfInsertedNullTmp);
			}
			unsigned RealSize=m_vParmVec.size();
			m_vParmVec[IndexOfTotal-1]=RealSize-IndexOfTotal;//��������
			bReserveOrder=!bReserveOrder;//��Ч��			
			bFirstRow=false;
		}
		return m_vParmVec.begin();
	}
/**
*@brief ��鱾���Ƿ���Ҫ�岹�հ׸�ע�⣬Ҫ��ǰ�еıȽ��в����ǿհ��У����е�ǰ�����пհ��У����汾���������ϳ�
*
*��鱾���Ƿ���Ҫ�岹�հ׸񣬼���������Ҫ���򷵻���Ҫ�岹�Ŀհ׸����������Ƿ������岹�� bInsertλ����
*�����Ҫ����ǰ����ǰһ�бȽϣ���ʱ��Ҫ��ӵĿհ׸�λ�ã�һ���ǵ�ǰ�����ݶ��еĶ��ס�
*�����Ҫ����һ�бȽϣ���ʱ��Ҫ��ӵĿհ׸�λ�ã�һ���ǵ�ǰ�еĶ�β��
*@parm bLookForward ������һ�űȽϻ�������һ�űȽ�
*
*@return �����в���ĵ�Ԫ�����
*@todo ��������֮����ڿհ��У���ʱ���ڱȽϾͻ�����⣬������ѭ������Ϊ��հ��бȽ�ʱ���հ��о�û�ж�����ʼ�����ֵ
*/
	unsigned CheckCurRowIfInsertNullColor(bool bReserveOrder,unsigned WorkRegNum,unsigned CurRowNum,bool bInsert,bool bLookForward)
	{
		unsigned StartY;
		unsigned EndY;
		unsigned StartY0;
		unsigned EndY0;
		pRecRes->QueryStartEndParmOfRow(CurRowNum,WorkRegNum,StartY,EndY,1);
		unsigned InsertedNum=0;
		int AddNum=bLookForward?1:-1;
		if (bLookForward){	//������һ�бȽϣ���ʱҪ��ӵ�λ�þ�Ϊ��ǰ���е�ĩβ
			if (bReserveOrder)		{
				pRecRes->QueryStartEndParmOfRow(CurRowNum+AddNum,WorkRegNum,StartY0,EndY0,1);
				if (StartY<StartY0)	{//���м���ڲ�࣬����ǰ�б���һ�г���Ӧ�üӵ���һ����
					return 0;
				}
				InsertedNum=InsertNULLColor(StartY,StartY0,bInsert);				
			}
			else {			
				pRecRes->QueryStartEndParmOfRow(CurRowNum+AddNum,WorkRegNum,StartY0,EndY0,1);
				if (EndY>EndY0)	{//���м���ڲ�࣬����ǰ�б���һ�г���Ӧ�üӵ���һ����
					return 0;
				}
				InsertedNum=InsertNULLColor(EndY,EndY0,bInsert);	
			}
		}
		else{//������һ�бȽϣ���ʱҪ��ӵ�λ�þ�Ϊ��ǰ���еĿ�ͷ��
			if (bReserveOrder)		{
				pRecRes->QueryStartEndParmOfRow(CurRowNum+AddNum,WorkRegNum,StartY0,EndY0,1);
				if (EndY>EndY0)	{//���м���ڲ�࣬����ǰ�б���һ�г���Ӧ�üӵ���һ����
					return 0;
				}
				InsertedNum=InsertNULLColor(EndY,EndY0,bInsert);//EndY��������ݶ�����				
			}
			else {
				pRecRes->QueryStartEndParmOfRow(CurRowNum+AddNum,WorkRegNum,StartY0,EndY0,1);
				if (StartY<StartY0)	{//���м���ڲ�࣬����ǰ�б���һ�г���Ӧ�üӵ���һ����
					return 0;
				}				
				InsertedNum=InsertNULLColor(StartY,StartY0,bInsert);	
			}
		}
		return InsertedNum;
	}
	void SaveInsertedNullCell(std::vector<int>& itNum)
	{
		if (itNum.size()>0)
		{
			m_vInsertedNullCellInRows.push_back(itNum);
		}
	}
	bool IsNullCellInserted()
	{
		if (m_vInsertedNullCellInRows.size()>0)
		{
			return true;
		}
		return false;
	}
	std::vector<int>::iterator ReturnInsertedNullCell()
	{
		return m_vInsertedNullCellInRows.begin();
	}
	/**
	*@brief ��鱾���Ƿ���Ҫ�岹�հ׸񣬵�2�ַ�ʽ������е�ǰ�����пհ��е�����
	*
	*��鱾���Ƿ���Ҫ�岹�հ׸񣬼���������Ҫ���򷵻���Ҫ�岹�Ŀհ׸����������Ƿ������岹�� bInsertλ����
	*�����Ҫ����ǰ����ǰһ�бȽϣ���ʱ��Ҫ��ӵĿհ׸�λ�ã�һ���ǵ�ǰ�����ݶ��еĶ��ס�
	*�����Ҫ����һ�бȽϣ���ʱ��Ҫ��ӵĿհ׸�λ�ã�һ���ǵ�ǰ�еĶ�β��
	*�������Ľ����£�
	*@parm bLookForward ������һ�űȽϻ�������һ�űȽ�
	*
	*@return �����в���ĵ�Ԫ�����,���еĿ�ͷ��Ϊ�������е�ĩβΪ��
	*@todo
	*/
	int CheckCurRowIfInsertNullColor_FixBlankRow(bool bReserveOrder,unsigned WorkRegNum,unsigned CurRowNum,bool bInsert,bool bLookForward)
	{
		/*unsigned StartY;
		unsigned EndY;
		unsigned StartY0;
		unsigned EndY0;*/
		//pRecRes->QueryStartEndParmOfRow(CurRowNum,WorkRegNum,StartY,EndY,1);
		unsigned TotalRowNum=pRecRes->NumOfRowInGivenWorkReg(WorkRegNum);//������
		unsigned CompRow;//Ҫ��֮�Ƚϵ���
		int NumofInserted=0;
		//unsigned InsertedNum=0;
		int AddNum=bLookForward?1:-1;
		if (bLookForward){	//������һ�бȽϣ���ʱҪ��ӵ�λ�þ�Ϊ��ǰ���е�ĩβ
			if (bReserveOrder)		{
				NumofInserted=CheckAndInsertNullCell(WorkRegNum,TotalRowNum, CurRowNum,AddNum,bInsert,true);				
			}
			else {	
				NumofInserted=CheckAndInsertNullCell(WorkRegNum,TotalRowNum, CurRowNum,AddNum,bInsert,false);	
			}
			return NumofInserted;
		}
		else{//������һ�бȽϣ���ʱҪ��ӵ�λ�þ�Ϊ��ǰ���еĿ�ͷ��
			if (bReserveOrder)		{
				NumofInserted=CheckAndInsertNullCell(WorkRegNum,TotalRowNum, CurRowNum,AddNum,bInsert,false);			
			}
			else {
				NumofInserted=CheckAndInsertNullCell(WorkRegNum,TotalRowNum, CurRowNum,AddNum,bInsert,true);	
			}			
			return -NumofInserted;
		}
		return NumofInserted;
	}
	/**
	*@brief �������ķ������Ƿ���Ҫ����հ׸�
	*
	*��鱾���Ƿ���Ҫ�岹�հ׸񣬼���������Ҫ���򷵻���Ҫ�岹�Ŀհ׸����������Ƿ������岹�� bInsertλ����
	*����ǰ����Ŀ���бȽϣ�Ŀ�����ǣ�����Ч��������Χ�ڣ��ɵ�ǰ�а���ָ���ķ����������õ�����ӽ�����Ч��
	*������������ǰ��������� AddNum�����������ƣ�
	*��ǰ����Ŀ����֮�䣬�ǱȽ���ʼ���꣬�����յ����꣬��bCompareStart���ƣ���Ϊ����Ƚϵ�����ʼ������
	*
	*
	*@parm TotalRowNum ��������Ԫ��������
	*
	*@return �����в���ĵ�Ԫ�����
	*@todo
	*/
	unsigned CheckAndInsertNullCell(unsigned WorkRegNum,unsigned TotalRowNum,unsigned CurRowNum,int AddNum,bool bInsert,bool bCompareStart)
	{
		unsigned CompRow;//Ҫ��֮�Ƚϵ���
		unsigned StartY0;
		unsigned EndY0;
		unsigned StartY;
		unsigned EndY;
		unsigned InsertedNum=0;
		pRecRes->QueryStartEndParmOfRow(CurRowNum,WorkRegNum,StartY,EndY,1,1);
		CompRow=CurRowNum+AddNum;
		if (bCompareStart)	{
			for (CompRow;CompRow<TotalRowNum&&CompRow>=0;CompRow+=AddNum){
			if (pRecRes->QueryStartEndParmOfRow(CompRow,WorkRegNum,StartY0,EndY0,1,1)){
					if (StartY<StartY0)	{//���м���ڲ�࣬����ǰ�б���һ�г���Ӧ�üӵ���һ����
						return 0;
					}
					InsertedNum=InsertNULLColor(StartY,StartY0,bInsert);
					return InsertedNum;
				}//�ҵ����ʵıȽ϶�����Ƚϣ���������
			}	
		}
		else{
			for (CompRow;CompRow<TotalRowNum&&CompRow>=0;CompRow+=AddNum){
				if (pRecRes->QueryStartEndParmOfRow(CompRow,WorkRegNum,StartY0,EndY0,1,1)){
					if (EndY>EndY0)	{//���м���ڲ�࣬����ǰ�б���һ�г���Ӧ�üӵ���һ����
						return 0;
					}
					InsertedNum=InsertNULLColor(EndY,EndY0,bInsert);
					return InsertedNum;
				}//�ҵ����ʵıȽ϶�����Ƚϣ���������
			}	
		}
		return InsertedNum;
	}
/**
*@brief ����Ƿ���Ҫ�岹�հ׵�Ԫ����������Ҫ�岹����Ŀ��bInsert�����Ƿ���Ĳ岹���ǵĻ�����m_vParmVec�еĵ�ǰλ�ò��룬����ʵ�ʲ岹
*
*��ǰ�е���ֹλ������һ�е���ʼλ��������ͬһˮƽ���ϣ���ζ����ǹ��Ҫ�߹�һ�ο��г̣��öο��г̻������ų���
*������ǹ���صļ�����Χ�⡣�����Ҫ����һ���հ׸�����ɫ���ȡ6��������ɫ���Ϊ0~5����ζ����ɫ
*
*@parm CurY  ��ǰ�е�Y����λ��(����)
*@parm CompY  �뵱ǰY�Ƚϵ�Y����λ��(����)
*@parm bInsert �Ƿ���������ո�
*
*@return �ǵĻ����ڵ�ǰλ�ò��벢�����棬���򷵻ؼ�
*@todo
*/
	unsigned InsertNULLColor(unsigned CurY,unsigned CompY,bool bInsert=true)
	{
		const static float ErrorTorence=(unsigned)(gHeightOfEveryPaintCell*0.1);//�ݲ������ڴ˷�Χ��ʱ��Ϊ����岹
		//int Dis=(int)CurEndY-(int)NexStartY;
		float Dis=(float)CurY-(float)CompY;
		float DisOfY=fabs(Dis);
		if (DisOfY<ErrorTorence)
		{return 0;	}
		unsigned NumOfCellToInsert=Floor4_Ceil5((float)DisOfY/gHeightOfEveryPaintCell);
		if (!bInsert)
		{return NumOfCellToInsert;}
		for (unsigned i=0;i<NumOfCellToInsert;i++)//����հ׸�
		{
#ifdef PARM_USE_COLOR_INDEX_ONLY
			m_vParmVec.push_back(QueryMachineHexMapByRecedIndex(MAX_COLOR_MACHINE_INDEX));
#else
			m_vParmVec.push_back(0);
			m_vParmVec.push_back(QueryMachineColorIndexByRecedIndex(MAX_COLOR_MACHINE_INDEX));
#endif
		}
		return NumOfCellToInsert;
	}
	 /**
	 *@brief ������Ĳ�����ʽ��Ϊ���������г�����������ĸ�ʽ
	 *
	 *������Ĳ�����ʽ��Ϊ���������г�����������ĸ�ʽ,Ĭ��Ŀ���ʽΪmm
	 *�������贫������г��Ȳ�����λΪ(������)ʱ������Ҫ����
	 *@parm
	 *
	 *@return
	 *@todo
	 */
	 float FormatLengthParm(float parm)         //��Ԫ�߶�
	 {
		 return parm*/*m_fRealRatio*/m_fRealYRatio;
	 }
	PLC_Parm_It_TYPE QueryParmVecEnd(int WorkRegNum)
	{
		return m_vParmVec.end();
	}
	
	
protected:
	PLC_Parm_TYPE m_vParmVec;///<���������
	std::vector<std::vector<int>>m_vInsertedNullCellInRows;///<Ϊ����б���˶�����Ŀհ׸񣬸�ʽΪ���������Ѳ�����������и���Ϊ����ʾ������β������Ϊ����ʾ������ͷ��������ͬʱ��β�Ͷ�ͷ�岹�Ļ�����Ȼ���ȶ�ͷ�����β��������ͷָ���Ǳ����˶���ʼ�ĵط�
	RecResType * pRecRes;///<ʶ���������ָ��
	float m_fRealRatio;///<ÿ�����ض�Ӧ���׵ı���ֵ
	float m_fRealYRatio; //ÿ�����ض�Ӧ���׵ı���ֵ
};
/**
* @class 
* @brief ����ר��������ǹ��ʵ�ʱ������ɫʶ����֮�����һ��������ǹ��������ʵ�ֶ�ɫ��ǹ��
*CColorResAdapter�����ṩ��������ǹ������Ų�ѯPLC����Ĳ����Ĺ��ܣ�Ȼ��������Ϊ��ɫ��ǹ��ƣ���ÿһ��ǹ��Ӧһɫ��
*�����迼�Ƕ�Ѷ�ɫ��ǹ��������ڴ˼��뱾�࣬���������ⵥɫ��ǹ�ŵĸ������ǹʵ�ʱ��(0��ʼ)��Ӧ���������ǹ��(0��ʼ)������������ǹ�����������CColorResAdapter��ȥ
*��ѯPLC�������
*
* 
*/
class VirtualGunMapperForMultiColoGun: public CColorResAdapter
{
public:
	VirtualGunMapperForMultiColoGun()
	{
		m_uColoPerGun=m_uSeledGunMode=1;
	}
	/**
	*@brief Ϊ�����ɫ��ǹ��Ӧ�ã�������ӳ�䣬������������ɫ�ţ���ѯ����ʵ����ǹ��
	*
	*ʵ����ǹ����һǹ��ɫ�����ⵥ��ǹ��һǹһɫ�������߼����ӳ���ϵ,
	*��ɫʱ��0����ǹ��Ӧǰm_uColoPerGun��������ǹ��1�Ŷ�Ӧ����m_uColoPerGun�����Դ�����...
	*
	*@parm Color ��ɫ��ţ�0����ɫ��Ӧ0��������ǹ��1�Ŷ�Ӧ1�š���������ע�⣬��ɫ��2���Ʊ�ʾ����0����ɫ�����2��0�μ�1,1����ɫ��2��1�μ�2
	*@return ����-1�Ļ���ʾû��ǹ�ܶ�Ӧ�ϣ����򷵻ص��Ƕ�Ӧ����ǹ��
	*@todo
	*/
	unsigned QueryRealGunNumOnColor(unsigned Color)
	{
		int virtualGunNum;
		switch(m_uSeledGunMode)
		{
		case 2://һ�Ѷ�ɫ��ǹ
			if (Color<m_uColoPerGun){
				return 0;
			}
		case 3://��Ѷ�ɫ��ǹ
			virtualGunNum=QueryMachineColorIndexByMachineHexValue(Color);
			return virtualGunNum==-1?-1:floor((float)virtualGunNum/m_uColoPerGun);
		case 1:// ��ѵ�ɫ
			return Color;
		}
		return -1;
	}
	/**
	*@brief ���ָ������ɫ�Ƿ�����ָ������ǹ
	*
	*ʵ����ǹ����һǹ��ɫ�����ⵥ��ǹ��һǹһɫ�������߼����ӳ���ϵ,
	*��ɫʱ��0����ǹ��Ӧǰm_uColoPerGun��������ǹ��1�Ŷ�Ӧ����m_uColoPerGun�����Դ�����...
	*
	*@parm Color ָ����ɫ����ɫ��ţ�����ע�⣬��ɫ��2���Ʊ�ʾ����0����ɫ�����2��0�μ�1,1����ɫ��2��1�μ�2
	*@parm RealGunNum ָ������ʵ��ǹ���
	*@return �ǵĻ������棬���򷵻ؼ�
	*@todo
	*/
	bool IsCurColorBelongToGivenGun(unsigned TheColor, unsigned RealGunNum)
	{
		if (m_uSeledGunMode==1)// ��ѵ�ɫ,ֱ������ǹ�ò�ɫ���Ա���ɫ�Ƿ���ͬ
		{
			return TheColor==QueryMachineHexMapByMachineColorIndex(RealGunNum);
		}
		return RealGunNum==QueryRealGunNumOnColor(TheColor)?true:false;//����������ɫ���������Ƿ���ͬ
	}
	unsigned HowManyVirtualGunUsed()
	{

	}
protected:
	unsigned m_uSeledGunMode;///<ǹ��ģʽ����ѵ�ɫ1��һ�Ѷ�ɫ2�����Ƕ�Ѷ�ɫ3
	unsigned m_uColoPerGun;///<ÿ��ǹ����ɫ��
};

/**
* @class 
* @brief ��ʶ����ת��ΪPLC��Ҫ�ĸ�ʽ���Է���ͨѶ,�����а�������ݵĸ�ʽ���Ӹ���
*���������Ҫ�ı�״̬��λ�ü���ʱ������ǹ��״̬
*
* 
*/
template<class RecResType,class PaintCellType>
class CPLC_Parm_ComplexType_Adapter:public CPLC_Parm_Adapter<RecResType,PaintCellType>
{
public:
	CPLC_Parm_ComplexType_Adapter()
	{
		m_uGunNum=1;
		m_fGunDis=200;
		

	}
	/**
	*@brief �����������У�׼���ò���ͷm_vComplexParmHeaderVec���������Ѳ���ͷ������������������
	*
	*
	*@parm WorkRegNum ��Ҫ�����ĸ��������еĲ���>=0,����ֵС��0ʱ����ȫ���������Ĳ�����
	*
	*@return �ɹ���Ϊ��
	*@todo
	*/
	PLC_Parm_It_TYPE ExportComplexPLC_ParmVec(int WorkRegNum)
	{
		FormComplexheader(FormatLengthParm(gHeightOfEveryPaintCell));
		if (WorkRegNum>=0)	{
			return QueryComplexParmVec(WorkRegNum);
		}
		else	{
			return  QueryAllRegComplexParmVec();
		}		
	}
	PLC_Parm_It_TYPE ExportComplexPLC_ParmVecEnd(int WorkRegNum)
	{
		return m_vComplexParmVec.end();
	}
	/**
	*@brief ���Ѿ��γɲ�����֮����ͷ�������Ѿ�׼���õĲ���ͷ��m_vComplexParmHeaderVec
	*
	*
	*@todo
	*/
	PLC_Parm_It_TYPE  InsertComplexParmHeader()
	{
		m_vComplexParmVec.insert(m_vComplexParmVec.begin(),m_vComplexParmHeaderVec.begin(),m_vComplexParmHeaderVec.end());
		return m_vComplexParmVec.begin();
	}
	
	/**
	*@brief ������ǹ������ǹ���
	*
	*
	*@parm GunNum ��ǹ�� <100
	*@parm GunDis ��ǹ��� ��λ����,<2000
	*
	*@return ������ȷ�򷵻���
	*@todo
	*/
	bool SetPaintGunParm(unsigned GunNum,float GunDis,int GunMod=1,unsigned ColoNumPerGun=1)
	{
		if (GunNum>100||GunDis>2000)
		{return false;	}
		m_uGunNum=GunNum;
		m_fGunDis=GunDis;
		m_uColoPerGun=ColoNumPerGun;
		m_uSeledGunMode=GunMod;
		return true;
	}
	/**
	*@brief ��������п�����Ҫ�ı���ǹ״̬��λ��
	*
	*��������п�����Ҫ�ı���ǹ״̬��λ�ã���Щλ�þ�Ϊ����һ����Ԫ��ߴ��������������ŷ���PLC�ļ�����ʽ
	*�������Ե�һ����ǹ��Ϊ��׼�ġ���һ����ǹ�����������˶�Ϊ�����˶��Ļ����Ƚ������ǹ��
	*@parm
	*
	*@return ��������λ���򷵻��棬���򷵻ؼ�
	*@todo
	*/
	bool CalculateAllPossibleStateChangeCoordinate()
	{
		m_vChangeStateCoordVec.clear();
		m_vChangeStateRoundCoordVec.clear();
		m_fCellHeightInMM=FormatLengthParm(gHeightOfEveryPaintCell);  //��Ԫ���
		if (m_uGunNum>0)
		{
			m_vChangeStateCoordVec.push_back(0);//0Ϊ��Ԫ��ʼ��
			m_vChangeStateRoundCoordVec.push_back(0);
			for (unsigned i=1;i<m_uGunNum;i++)
			{
				float CoodVal=(i*m_fGunDis)/m_fCellHeightInMM;
				m_vChangeStateCoordVec.push_back(CoodVal);
				CoodVal= CoodVal-floor(CoodVal);//	fmod((i*m_fGunDis),m_fCellHeightInMM);
				std::vector<float>::iterator itFindExist=find(m_vChangeStateRoundCoordVec.begin(),m_vChangeStateRoundCoordVec.end(),CoodVal);
				if (itFindExist==m_vChangeStateRoundCoordVec.end())//û�ظ���
				{
					m_vChangeStateRoundCoordVec.push_back(CoodVal);
				}				
			}
			//std::sort(m_vChangeStateCoordVec.begin(),m_vChangeStateCoordVec.end());
			std::sort(m_vChangeStateRoundCoordVec.begin(),m_vChangeStateRoundCoordVec.end());
		}
		return false;
	}
	/**
	*@brief ��ѯ��Ҫ����Ĳ���
	*
	*������˳�����£�����ͷ�������ݡ�����ͨ������ QueryParmVec�����γ��˼򵥻��ı��������б�Ȼ�����ݸú������
	*�����ÿ����ǹ��Ӧ��״̬���Ӷ��γ�PLC��Ҫ�Ĳ�����
	*���������ΰ���������������Ϳ�ĵ�Ԫ�������������������Ԫ��Ϣ��
	*���е�Ԫ��Ϣ����������Ԫ��ţ��ǳ���Ļ�����Ԫ���Ϊ-1�����ҽ����õ�Ԫ����ֹλ�ã�+��ɫ��š�
	*����ٶ�����ֳ�����Ϳ��Ԫ����õ�Ԫ��Ϊ�������һ��
	*@parm
	*
	*@return
	*@todo
	*/
	PLC_Parm_It_TYPE QueryComplexParmVec(int WorkRegNum)
	{
#ifdef PARM_USE_COLOR_INDEX_ONLY//Ŀǰ�������˴�������µ�ʵ��
		m_vComplexParmVec.clear();
		//unsigned CountOfCurCell=0;///<��ǰ��Ԫ�ڱ����еĵڼ�����Ч��Ԫ
		PLC_Parm_It_TYPE SimpleTypeParmVecItBeg= QueryParmVec(WorkRegNum);//���γɼ򵥸�ʽ�������ݣ��������Ա����Ϊ����
		PLC_Parm_It_TYPE SimpleTypeParmVecItEnd= QueryParmVecEnd(WorkRegNum);
		TRACE("�����γ�PLC��������");
		unsigned NumOfCellInRow;
		bool bReverse=false;//�����ƶ�����
		unsigned RowBeginIndex;//��������к�
		for (SimpleTypeParmVecItBeg;SimpleTypeParmVecItBeg!=SimpleTypeParmVecItEnd;SimpleTypeParmVecItBeg++)//���ɫ��
		{		
			NumOfCellInRow=*SimpleTypeParmVecItBeg;//���ڲ�����������ǰ���ж��ٸ���Ԫ��		
			m_vComplexParmVec.push_back(NumOfCellInRow); 
			RowBeginIndex=m_vComplexParmVec.size();//�в����У�����Ϳ�����в����ĸ�������һ���Ӧ�ڱ���λ�����+1��������Ҫ���ݱ���������¸������ֵ��
			//SimpleTypeParmVecItBeg++;
			//SimpleTypeParmVecItBeg=CheckStatusInRowOfParmVec(SimpleTypeParmVecItBeg,NumOfCellInRow,bReverse);
			SimpleTypeParmVecItBeg=CheckStatusInRowOfParmVec_Fix(SimpleTypeParmVecItBeg,NumOfCellInRow,bReverse);
			m_vComplexParmVec.push_back(0);//ÿ�д�����ɺ���Ϊ+��0
			NumOfCellInRow=m_vComplexParmVec.size()-RowBeginIndex;//���¸��±����в������������籾λֵΪ4����ʾ������ŵ�4��������Ϊ���еĲ�����
			m_vComplexParmVec[RowBeginIndex-1]=NumOfCellInRow;
			bReverse=!bReverse;
			//SimpleTypeParmVecItBeg++;
		}
#else//��������ݲ����ǣ�ֱ�ӷ��ؼ򵥰汾�Ľ��
		return QueryParmVec(WorkRegNum);
#endif
		
		return m_vComplexParmVec.begin();
	}
/**
*@brief ���Ѿ�׼���õļ򵥸�ʽ�������У����ֳ�һ�У��������Ԫ�����¼��ǹ״̬��Ȼ��ָ��ͣ����ĩβ�ĵ�Ԫ��
*
*
*@parm CurIt ��ɫ��������е�ָ�룬�Ǽ򵥻�QueryParmVec�����Ľ����
*@parm NumOfCellInRow ��ǰ���е�ɫ�����
*@parm bReverse ��ǹ�ڱ����������ƶ������ǵ�Ϊ�档
*
*@return
*@todo
*/
	//PLC_Parm_It_TYPE CheckStatusInRowOfParmVec(PLC_Parm_It_TYPE CurIt,unsigned NumOfCellInRow,bool bReverse)
	//{
	//	//unsigned MaxIndexOf

	//	std::vector<float>::iterator itBeg=m_vChangeStateRoundCoordVec.begin();
	//	for (unsigned i=0;i<NumOfCellInRow;i++)	{//ע��iΪ��׼�����߹��ĵ�Ԫ����Ŀ0��ʼ����0��ʾ��׼�㻹�ڱ��Ϊ0�ĵ�Ԫ��Χ��
	//		CurIt++;               //��Ԫ�����ǹ״̬
	//		CheckGunStatus(CurIt,i,bReverse,itBeg);			
	//	}
	//	if (m_uGunNum<2)
	//	{return CurIt;}
	//	//���ڶ���ǹ��˵����ĳ���������
	//	/////////////////////////��β���֣���ǹ���в��ֳ�����Χ���赥������/////////////////////////////////////////////////
	//	unsigned NumOfCellOfNewBaseGun=ceil(m_vChangeStateCoordVec[1]-m_vChangeStateCoordVec[0]);//�»�׼��ǹ���ϻ�׼��ǹ(�ϻ�׼��Ϊm_vChangeStateCoordVec[0])���ڷ����ĵڼ���������,ע��Ҫ-1
	//	PLC_Parm_It_TYPE CurCellOfNewBaseGun=CurIt-NumOfCellOfNewBaseGun+1;  //�õ��ڶ�����ǹ������Ϳ��Ԫ��ɫ
	//	unsigned NumOfCellToEnd= NumOfCellOfNewBaseGun;                      //�»�׼������ǡ����һ����������Ļ��ҳ��»�׼��Ӧ��ͻ���
	//	float GunDis=m_vChangeStateCoordVec[1]-m_vChangeStateCoordVec[0];
	//	float BaseGunStartPoint= GunDis-floor( GunDis);//����Ӧͻ���,2017��2��18�ո�
	//	std::vector<float>::iterator StartPointIt=m_vChangeStateRoundCoordVec.begin();
	//	float SecondGunPosition=(*(m_vChangeStateRoundCoordVec.end()-1))-GunDis+floor(m_vChangeStateCoordVec[1]-m_vChangeStateCoordVec[0]);//�ڶ�����ǹ��λ��
	//	//�õ��ڶ�����ǹ��λ�ã��п����ڵ����ڶ�����Ϳ��Ԫ��,������õ�����һ����ǹ����߽��ʱ���ڶ�����ǹ��״̬��
	//	float SecondGunPositionWhenFirstGunArrive=SecondGunPosition+1-(*(m_vChangeStateRoundCoordVec.end()-1));
	//	std::vector<float>::iterator itBegAgain=m_vChangeStateRoundCoordVec.begin();
	//	std::vector<float>::iterator itBegAgainll;
	//	for (itBegAgain;itBegAgain!=m_vChangeStateRoundCoordVec.end();itBegAgain++)
	//	{
	//		if (*itBegAgain-SecondGunPositionWhenFirstGunArrive>0)
	//		{
	//			break;            //�õ�����һ����ǹ���Ｋ��λ��ʱ����һʱ�̵ڶ�����ǹӦ���Ǹ�ͻ��㿪ʼ����
	//		}
	//	}
	//	for (int m_GunIndex=1;m_GunIndex<m_uGunNum;m_GunIndex++)         //ÿ����ǹ��Ҫ����
	//	{
	//		for (int i=0;i<=NumOfCellOfNewBaseGun-1;i++)       //�ж�ÿ����ǹ��Ҫ����������Ԫ��
	//		{
	//			PLC_Parm_It_TYPE m_CurrentSecondGunColor=CurCellOfNewBaseGun+i;     //��ǰ��Ԫ��ɫ
	//			//CheckGunStatus�е�һ����������ǰ��Ϳ��Ԫ����ɫ���ڶ�����������ǰ��Ϳ��Ԫ���кţ���������������
	//			//���򣬵��ĸ���������ӵڼ���ͻ�����𣬵������������ӵڼ���ǹ��ʼ�����״̬
	//			CheckGunStatus(m_CurrentSecondGunColor,NumOfCellInRow-(NumOfCellOfNewBaseGun-1)+i,bReverse,itBegAgain-1,m_GunIndex);
	//		}
	//	}
	//	
	//	return CurIt;
	//}
	/**
	*@brief ���Ѿ�׼���õļ򵥸�ʽ�������У����ֳ�һ�У��������Ԫ�����¼��ǹ״̬��Ȼ��ָ��ͣ����ĩβ�ĵ�Ԫ��
	*
	* CheckStatusInRowOfParmVec�����ĸĽ��汾�����ò�����ɫ��ķ���������ɫ
	*@parm CurIt ��ɫ��������е�ָ�룬�Ǽ򵥻�QueryParmVec�����Ľ����
	*@parm NumOfCellInRow ��ǰ���е�ɫ�����
	*@parm bReverse ��ǹ�ڱ����������ƶ������ǵ�Ϊ�档
	*
	*@return
	*@todo
	*/
	PLC_Parm_It_TYPE CheckStatusInRowOfParmVec_Fix(PLC_Parm_It_TYPE CurIt,unsigned NumOfCellInRow,bool bReverse)
	{
		PLC_Parm_TYPE ExpandedCellVector;//���������ɫ������
		//unsigned MaxIndexOf
		std::vector<float>::iterator itBeg=m_vChangeStateRoundCoordVec.begin();//һ��ɫ���ڵĵ�0��ͻ����ָ��
		for (unsigned i=0;i<NumOfCellInRow;i++)	{//ע��iΪ��׼�����߹��ĵ�Ԫ����Ŀ0��ʼ����0��ʾ��׼�㻹�ڱ��Ϊ0�ĵ�Ԫ��Χ��
			CurIt++;
				CheckGunStatus(CurIt,i,bReverse,itBeg);	
				ExpandedCellVector.push_back(*CurIt);//����
		}
		if (m_uGunNum<2)
		{return CurIt;}
		
		/////////////////////////��β���֣���ǹ���в��ֳ�����Χ���½�һ��ɫ�����У������������ɫ����/////////////////////////////////////////////////
		//unsigned NumOfCellOfNewBaseGun=ceil(m_vChangeStateCoordVec[1]-m_vChangeStateCoordVec[0]);//�ڶ�����ǹ���»�׼��ǹ���ϻ�׼��ǹ(�ϻ�׼��Ϊm_vChangeStateCoordVec[0])���ڷ����ĵڼ���������,ע��Ҫ-1����1��ʼ
		//PLC_Parm_It_TYPE CurCellOfNewBaseGun=CurIt-NumOfCellOfNewBaseGun+1;//��һ���곬����ô��????������
		//unsigned NumOfCellToEnd= NumOfCellOfNewBaseGun;//���ܳ���Ϳ�����ж��ٸ��񣬴�0��ʼ����
		//////�»�׼������ǡ����һ����������Ļ��ҳ��»�׼��Ӧ��ͻ���
		//float GunDis=m_vChangeStateCoordVec[1]-m_vChangeStateCoordVec[0];
		unsigned VirtualExpandedCellNum=ceil(m_fGunDis*(m_uGunNum-1)/m_fCellHeightInMM);//��1��ʼ
		
		for (int i=0;i<VirtualExpandedCellNum;i++)
		{
			ExpandedCellVector.push_back(0);//ѹ����ɫɫ��
		}
		PLC_Parm_It_TYPE itVirtualBorder=ExpandedCellVector.begin()+NumOfCellInRow;//�������ʼ��
		float AllGunDis=m_vChangeStateCoordVec[m_uGunNum-1]-m_vChangeStateCoordVec[0];
		float RoundCoord=fmod(AllGunDis,1);
		std::vector<float>::iterator	itFound;
			itFound=std::find(m_vChangeStateRoundCoordVec.begin(),m_vChangeStateRoundCoordVec.end(),RoundCoord);
		int Num=itFound-m_vChangeStateRoundCoordVec.begin();//���룬����Ԫ��
		unsigned MaxSizeOfComplexParmVecInOneColummn=m_vComplexParmVec.size()+(VirtualExpandedCellNum-1)*m_uGunNum+Num+1;
		for (int i=0;i<VirtualExpandedCellNum;i++)
		{
			CheckGunStatus(itVirtualBorder,NumOfCellInRow+i,bReverse,itBeg,0,false,MaxSizeOfComplexParmVecInOneColummn);	//�������ɫ���ж�
			itVirtualBorder++;
		}
		
		//float BaseGunStartPoint= GunDis-floor( GunDis);//�ڶ�����ǹ��Ϊ����Ӧ��ͻ���
		//PLC_Parm_It_TYPE itEnd=CurIt+1;//ɫ��Ľ�β
		/////////////////////////////��Ҫ���ǵ���ǹ����һ�ѣ��γ��µ�ͻ�������/////////////////////////////////////////////
		
		return CurIt;
	}
	/**
	*@brief ���Ѿ�׼���õļ򵥸�ʽ�������У����ֳ�һ�У��������Ԫ�����¼��ǹ״̬��Ȼ��ָ��ͣ����ĩβ�ĵ�Ԫ��
	*
	*��β���֣���ǹ���в��ֳ�����Χ���赥�������˲�����bug������������!!!!!!!!!!!!!!!!!!!!!
	*@parm CurIt ��ɫ��������е�ָ�룬�Ǽ򵥻�QueryParmVec�����Ľ����
	*@parm NumOfCellInRow ��ǰ���е�ɫ�����
	*@parm bReverse ��ǹ�ڱ����������ƶ������ǵ�Ϊ�档
	*
	*@return
	*@todo
	*/
	PLC_Parm_It_TYPE CheckStatusInRowOfParmVec(PLC_Parm_It_TYPE CurIt,unsigned NumOfCellInRow,bool bReverse)
	{
		//unsigned MaxIndexOf
		std::vector<float>::iterator itBeg=m_vChangeStateRoundCoordVec.begin();//һ��ɫ���ڵĵ�0��ͻ����ָ��
		for (unsigned i=0;i<NumOfCellInRow;i++)	{//ע��iΪ��׼�����߹��ĵ�Ԫ����Ŀ0��ʼ����0��ʾ��׼�㻹�ڱ��Ϊ0�ĵ�Ԫ��Χ��
			CurIt++;
	/*		if (bReverse)
			{CheckGunStatus(CurIt,i,bReverse,itBeg,m_uGunNum-1);	
			}
			else*/
				CheckGunStatus(CurIt,i,bReverse,itBeg);			
		}
		if (m_uGunNum<2)
		{return CurIt;}
		/////////////////////////��β���֣���ǹ���в��ֳ�����Χ���赥������/////////////////////////////////////////////////
		unsigned NumOfCellOfNewBaseGun=ceil(m_vChangeStateCoordVec[1]-m_vChangeStateCoordVec[0]);//�ڶ�����ǹ���»�׼��ǹ���ϻ�׼��ǹ(�ϻ�׼��Ϊm_vChangeStateCoordVec[0])���ڷ����ĵڼ���������,ע��Ҫ-1����1��ʼ
		PLC_Parm_It_TYPE CurCellOfNewBaseGun=CurIt-NumOfCellOfNewBaseGun+1;//��һ���곬����ô��????������
		unsigned NumOfCellToEnd= NumOfCellOfNewBaseGun;//���ܳ���Ϳ�����ж��ٸ��񣬴�0��ʼ����
		////�»�׼������ǡ����һ����������Ļ��ҳ��»�׼��Ӧ��ͻ���
		float GunDis=m_vChangeStateCoordVec[1]-m_vChangeStateCoordVec[0];
		float BaseGunStartPoint= GunDis-floor( GunDis);//�ڶ�����ǹ��Ϊ����Ӧ��ͻ���
		PLC_Parm_It_TYPE itEnd=CurIt+1;//ɫ��Ľ�β
		/////////////////////////////��Ҫ���ǵ���ǹ����һ�ѣ��γ��µ�ͻ�������/////////////////////////////////////////////
		std::vector<float>::iterator StartPointIt=m_vChangeStateCoordVec.begin()+1;//�ڶ�����ǹ������17.8.15�޸�
		//////////////////////////////////////////////////////////////////////////
		//std::vector<float>::iterator StartPointIt=find(m_vChangeStateRoundCoordVec.begin(),m_vChangeStateRoundCoordVec.end(),BaseGunStartPoint);
		
		for (unsigned i=1;i<m_vChangeStateCoordVec.size();i++)//ע��iΪ������Ϳ��Χ��ǹ��Ŀ��������Ϳ��Χ�ڵ�ǹ������Ϊ�µĻ�׼��ǹ��������ǹ����ȥ�ˣ���������
		{
			NumOfCellToEnd=NumOfCellOfNewBaseGun;
			for (PLC_Parm_It_TYPE itNew=CurCellOfNewBaseGun;itNew!=itEnd;itNew++)//��ǰ��׼��ǹ���ڵ�ɫ��Ϊ��ǰɫ�飬�ӵ�ǰ��ɫ�鿪ʼ�������(���ﲻ�ÿ����˶�����)
			{//ע�⣬������ǹ���̶����������İ���ǹ��Ϊ�»�׼�������»�׼ʱ���Ǵ�CurCellOfNewBaseGun���ɫ�飬���ͻ��㿪ʼ�ġ�
				//unsigned CurCellIndex=NumOfCellInRow-1-NumOfCellToEnd;//���˶���ʼ�������𣬵�ǰ���ɫ���ǵڼ���ɫ�飬��0��ʼ���
				
				unsigned CurCellIndex=NumOfCellInRow-NumOfCellToEnd;//���˶���ʼ�������𣬵�ǰ���ɫ���ǵڼ���ɫ�飬��0��ʼ��ţ�17.8.15�޸�
				if (itNew==CurCellOfNewBaseGun)	{//��һ��������ܲ����������м�ĳ��ͻ��㿪ʼ���ᵼ������
					//int FunctionGunNum=m_vChangeStateCoordVec.size()-i;//��ʣ�µ���ǹ��
					//vector<float>NewRoundPointCoord;

					CheckGunStatus(itNew,CurCellIndex,bReverse,StartPointIt,i,true);
				}
				else{
					CheckGunStatus(itNew,CurCellIndex,bReverse,itBeg,i);//�Ե�ǰɫ���ڵ�ͻ��㣬�ж�״̬
				}				
				NumOfCellToEnd--;
			}			
		}
		return CurIt;
	}
	std::vector<float>::iterator ReturnChangedColorPointBegin()
	{
		return m_vChangeStateRoundCoordVec.begin();
	}
	std::vector<float>::iterator ReturnChangedColorPointEnd()
	{
		return m_vChangeStateRoundCoordVec.end();
	}
	/**
	*@brief �γɲ���ͷ��ʵ���ϲ���ͷ��Ϊÿ����Ϳ��Ԫ�ĸ߶ȣ���λmm
	*
	*
	*@parm PaintCellHeight ÿ����Ϳ��Ԫ�ĸ߶ȣ���λmm
	*
	*@return
	*@todo
	*/
	PLC_Parm_It_TYPE FormComplexheader(unsigned PaintCellHeight)
	{
		m_vComplexParmHeaderVec.clear();
		m_vComplexParmHeaderVec.push_back(PaintCellHeight);
		return m_vComplexParmHeaderVec.begin();
	}
	PLC_Parm_It_TYPE QueryAllRegComplexParmVec()
	{
		PLC_Parm_It_TYPE it;
		RecResType *pRecRes2=QueryMapRecResPointer(); 
		for (int i=0;i<pRecRes2->NumOfRecedPic();i++)
		{	it=QueryComplexParmVec(i);	}
		return it;
	}
protected:
	
/**
*@brief �Ը�������Ϳ��Ԫ��ȷ�����ڲ�����״̬�仯�㴦����ǹ״ֵ̬����¼����������
*
*@parm SimpleTypeParmVecItBeg ��������Ϳ��Ԫ(���ٶ���׼��ǹ�ڸ���Ϳ��Ԫ�ڣ�����������п���״̬�仯�㴦����ǹ״̬)
*@parm IndexOfCurCell ����Ϳ��Ԫ��ĿǰΪֹ��׼�����ڵ�λ�ã����˶���ʼ����ĵڼ�����Ϳ��Ԫ��)
*@parm itBeg  �����ɫ���ڵ��ĸ�ͻ��㿪ʼ�жϣ��󲿷�ʱ��Ӧ�ӵ�0��������ʼλ����ɫ����ĳ��λ��ʱ����,��ʱӦ�����ͻ�����û��Բ����ͻ��㼯�еĵ�
*@parm bReverse �����������ƶ�������Ϊ��
*@parm StartOfGunIndex �ӵڼ���ǹ��ʼ�����״̬����������ǹ������Ϳ��Χ��ʱΪ0���м�����ǹ������Ϊ�������˶������޹�,ǹ�Ŵ�0��ʼ
*@return
*@todo
*/
	void CheckGunStatus(PLC_Parm_It_TYPE SimpleTypeParmVecItBeg,unsigned IndexOfCurCell,bool bReverse,std::vector<float>::iterator itBeg,unsigned StartOfGunIndex=0,const bool bStartFromMiddle=false,const unsigned MaxCheckPointNum=99999)
	{
		//SimpleTypeParmVecItBeg��ǰ��Ԫ���е�Ԫ����ɫ��Ӧ����ǹ
		//std::vector<float>::iterator itBeg=m_vChangeStateRoundCoordVec.begin();
		int NumOfValidCell=0;//������ɫ��Χ�ڵ���Ϳ��Ԫ����
		unsigned GunNum=m_vChangeStateCoordVec.size();
		unsigned CurGunIndex;
		int GunAddStep=1;
		//if (bReverse)
		//{GunAddStep=-1;	}//17.8.15�޸�
		std::vector<float>::iterator itBegCopy=itBeg;
		std::vector<float>::iterator itChangPointVecEnd;
		if (bStartFromMiddle)//���м�ĳ��ͻ��㿪ʼ
		{
			itChangPointVecEnd=m_vChangeStateCoordVec.end();
		}
		else
		{
			itChangPointVecEnd=m_vChangeStateRoundCoordVec.end();
		}
		for (itBegCopy;itBegCopy!=itChangPointVecEnd;itBegCopy++)                    //����ʼ״̬�仯�㿪ʼ��������״̬�仯��λ��
		{
			unsigned GunStateResult=0;
			for (unsigned indexOfGun=StartOfGunIndex;indexOfGun<GunNum;indexOfGun=indexOfGun+GunAddStep)    //�ӻ�׼��ǹ��ʼ�������ǹ�ļ��
			{//�����м�ĳ��ͻ��㿪ʼʱ��������������ͻ�����0��0.2��0.6�������0.6��ʼ����ǹ2��0.2ʵ��������ǹ3����Ӧ��ʵ��ͻ�����1.2����ʱ�ͻᵼ�±�����������ǹ3

				//IndexOfGunΪ��ǹ�ı��,StartOfGunIndexΪ0��itBeg��ɫͻ���
				////////////////////////////////NumOfValidCell����bug�����ܳ��ָ���//////////////////////////////////////////
				//NumOfValidCell=ceil(m_vChangeStateCoordVec[indexOfGun]-(*itBeg));//��ǹ�ڻ�׼��ǹ(��׼��Ϊm_vChangeStateCoordVec[StartOfGunIndex])���ڷ����ĵڼ���������
				//NumOfValidCell=ceil(m_vChangeStateCoordVec[indexOfGun]-m_vChangeStateCoordVec[StartOfGunIndex]-(*itBeg));//��ǹ�ڻ�׼��ǹ(��׼��Ϊm_vChangeStateCoordVec[StartOfGunIndex])���ڷ����ĵڼ���������
				float StartRoundCheckPoint;//��ʼ��ǹ��ɫ���ڵ�Բ��ͻ�������
				if (bStartFromMiddle)
				{
					StartRoundCheckPoint=1-((*itBegCopy)-floor(m_vChangeStateCoordVec[StartOfGunIndex]));//��ǰ����������һ��ɫ�����
				}
				else
					StartRoundCheckPoint=(*itBegCopy);
				int NumOfCellOfCurGUN=ceil(m_vChangeStateCoordVec[indexOfGun]-m_vChangeStateCoordVec[StartOfGunIndex]-StartRoundCheckPoint);//��ǹ�ڻ�׼��ǹ(��׼��Ϊm_vChangeStateCoordVec[StartOfGunIndex])���ڷ����ĵڼ���ɫ���ڣ���Ҳ��������׼��ǹ��ɫ����
				//int NumOfCellOfCurGUN=floor(m_vChangeStateCoordVec[indexOfGun]-m_vChangeStateCoordVec[StartOfGunIndex]+StartRoundCheckPoint);//��ǹ�ڻ�׼��ǹ(��׼��Ϊm_vChangeStateCoordVec[StartOfGunIndex])���ڷ����ĵڼ���ɫ���ڣ���Ҳ��������׼��ǹ��ɫ����,��0��ʼ��0����ͬ��һ��ɫ��
				if (NumOfCellOfCurGUN<=IndexOfCurCell)       //�����ǹ������ɫ����Ч��Χ��,�Է�ֹ�����ǹ��Զ�ţ�û������Ϳ������Ҫ�жϣ����˶������޹�
				{//IndexOfCurCells�Ǵ��˶�������������ǰɫ�����ţ������˴ӻ�׼��ǹ���ƻ�ȥ�ж��ٸ�ɫ��������ɫ�ģ�
					//��ǰ��ǹ�����׼��ǹ��ɫ�����ͱ���С��IndexOfCurCell�����������ǹ��û������Ϳ��
					//GunStateResult=0;SimpleTypeParmVecItBegΪ��ɫ
					PLC_Parm_It_TYPE GunInCellColor=SimpleTypeParmVecItBeg-NumOfCellOfCurGUN;   //��ǰ�鿴��ǹ����ɫ��(��Ӧ��PLC���)
					if (bReverse){
						CurGunIndex=GunNum-indexOfGun-1;//��ǰǹ��ʵ�ʺ���
					}
					else
					{
						 CurGunIndex=indexOfGun;//��ǰǹ��ʵ�ʺ���
					}									
					//if (*GunInCel lColor==QueryMachineHexMapByMachineColorIndex(CurGunIndex))//ר���ڶ�ѵ�ɫ��ǹ
					//if()//���ݶ�ɫ��ǹ�ķ���
					//if (IsCurColorBelongToGivenGun(*GunInCellColor,CurGunIndex)) //�Ĺ�,2017��2��18��
					if(GunNum==1)    //��ɫ��ǹ���Զ�
					{
						GunStateResult=GunStateResult|(*GunInCellColor);//����ǹ��λ
					}
					else if(*GunInCellColor==QueryMachineHexMapByMachineColorIndex(CurGunIndex)) //��ǹ�������ɫ
					{
						GunStateResult=GunStateResult|(*GunInCellColor);//����ǹ��λ
					}
				}
			}
			m_vComplexParmVec.push_back(GunStateResult);
			if (m_vComplexParmVec.size()>=MaxCheckPointNum)//��Ŀ����
				return;
			
		}		
	}
	/**
	*@brief �Ը�������Ϳ��Ԫ��ȷ�����ڲ�����״̬�仯�㴦����ǹ״ֵ̬����¼���������У�רΪ���м��ĳ��ͻ��㿪ʼ�����ƣ�����CheckGunStatus
	*
	*@parm SimpleTypeParmVecItBeg ��������Ϳ��Ԫ(���ٶ���׼��ǹ�ڸ���Ϳ��Ԫ�ڣ�����������п���״̬�仯�㴦����ǹ״̬)
	*@parm IndexOfCurCell ����Ϳ��Ԫ��ĿǰΪֹ��׼�����ڵ�λ�ã����˶���ʼ����ĵڼ�����Ϳ��Ԫ��)
	*@parm itBeg  �����ɫ���ڵ��ĸ�ͻ��㿪ʼ�жϣ������ͻ���ָû��Բ����ͻ��㼯�еĵ�
	*@parm bReverse �����������ƶ�������Ϊ��
	*@parm StartOfGunIndex �ӵڼ���ǹ��ʼ�����״̬����������ǹ������Ϳ��Χ��ʱΪ0���м�����ǹ������Ϊ�������˶������޹�,ǹ�Ŵ�0��ʼ
	*@return
	*@todo
	*/
	//void CheckGunStatusForStartGivenPoint(PLC_Parm_It_TYPE SimpleTypeParmVecItBeg,unsigned IndexOfCurCell,bool bReverse,std::vector<float>::iterator itBeg,unsigned StartOfGunIndex=0)
	//{
	//	//SimpleTypeParmVecItBeg��ǰ��Ԫ���е�Ԫ����ɫ��Ӧ����ǹ
	//	//std::vector<float>::iterator itBeg=m_vChangeStateRoundCoordVec.begin();
	//	int NumOfValidCell=0;//������ɫ��Χ�ڵ���Ϳ��Ԫ����
	//	unsigned GunNum=m_vChangeStateCoordVec.size();
	//	unsigned CurGunIndex;
	//	int GunAddStep=1;
	//	if (bReverse)
	//	{GunAddStep=-1;	}//17.8.15�޸�
	//	for (itBeg;itBeg!=m_vChangeStateRoundCoordVec.end();itBeg++)                    //����ʼ״̬�仯�㿪ʼ��������״̬�仯��λ��
	//	{
	//		unsigned GunStateResult=0;
	//		for (unsigned indexOfGun=StartOfGunIndex;indexOfGun<GunNum;indexOfGun=indexOfGun+GunAddStep)    //�ӻ�׼��ǹ��ʼ�������ǹ�ļ��
	//		{//�����м�ĳ��ͻ��㿪ʼʱ��������������ͻ�����0��0.2��0.6�������0.6��ʼ����ǹ2��0.2ʵ��������ǹ3����Ӧ��ʵ��ͻ�����1.2����ʱ�ͻᵼ�±�����������ǹ3

	//			//IndexOfGunΪ��ǹ�ı��,StartOfGunIndexΪ0��itBeg��ɫͻ���
	//			////////////////////////////////NumOfValidCell����bug�����ܳ��ָ���//////////////////////////////////////////
	//			//NumOfValidCell=ceil(m_vChangeStateCoordVec[indexOfGun]-(*itBeg));//��ǹ�ڻ�׼��ǹ(��׼��Ϊm_vChangeStateCoordVec[StartOfGunIndex])���ڷ����ĵڼ���������
	//			//NumOfValidCell=ceil(m_vChangeStateCoordVec[indexOfGun]-m_vChangeStateCoordVec[StartOfGunIndex]-(*itBeg));//��ǹ�ڻ�׼��ǹ(��׼��Ϊm_vChangeStateCoordVec[StartOfGunIndex])���ڷ����ĵڼ���������
	//			int NumOfCellOfCurGUN=ceil(m_vChangeStateCoordVec[indexOfGun]-m_vChangeStateCoordVec[StartOfGunIndex]-(*itBeg));//��ǹ�ڻ�׼��ǹ(��׼��Ϊm_vChangeStateCoordVec[StartOfGunIndex])���ڷ����ĵڼ���ɫ���ڣ���Ҳ��������׼��ǹ��ɫ����
	//			if (NumOfCellOfCurGUN<=IndexOfCurCell)       //�����ǹ������ɫ����Ч��Χ��,�Է�ֹ�����ǹ��Զ�ţ�û������Ϳ������Ҫ�жϣ����˶������޹�
	//			{//IndexOfCurCell������˶�������������ǰɫ�����ţ���ǰ��ǹ�����׼��ǹ��ɫ�����ͱ���С��IndexOfCurCell�����������ǹ��û������Ϳ��
	//				//���NumOfValidCell<=IndexOfCurCell˵����ǰ���ҵ���ǹ��û������Ϳ��Ԫ����
	//				//GunStateResult=0;IndexOfCurCellΪ��Ϳ��Ԫ���к�,SimpleTypeParmVecItBegΪ��ɫ
	//				PLC_Parm_It_TYPE GunInCellColor=SimpleTypeParmVecItBeg-NumOfCellOfCurGUN;   //��ǰ�鿴��ǹ����ɫ��(��Ӧ��PLC���)
	//				if (bReverse){
	//					CurGunIndex=GunNum-indexOfGun-1;//��ǰǹ��ʵ�ʺ���
	//				}
	//				else
	//				{
	//					CurGunIndex=indexOfGun;//��ǰǹ��ʵ�ʺ���
	//				}									
	//				//if (*GunInCel lColor==QueryMachineHexMapByMachineColorIndex(CurGunIndex))//ר���ڶ�ѵ�ɫ��ǹ
	//				//if()//���ݶ�ɫ��ǹ�ķ���
	//				//if (IsCurColorBelongToGivenGun(*GunInCellColor,CurGunIndex)) //�Ĺ�,2017��2��18��
	//				if(GunNum==1)    //��ɫ��ǹ���Զ�
	//				{
	//					GunStateResult=GunStateResult|(*GunInCellColor);//����ǹ��λ
	//				}
	//				else if(*GunInCellColor==QueryMachineHexMapByMachineColorIndex(CurGunIndex)) //��ǹ�������ɫ
	//				{
	//					GunStateResult=GunStateResult|(*GunInCellColor);//����ǹ��λ
	//				}
	//			}
	//		}
	//		m_vComplexParmVec.push_back(GunStateResult);
	//	}		
	//}
	/**
	*@brief �Ը�������Ϳ��Ԫ��ȷ�����ڲ�����״̬�仯�㴦����ǹ״ֵ̬����¼����������,�°汾��רΪ���ݶ�ɫ��ǹ׼��
	*
	*@parm SimpleTypeParmVecItBeg ��������Ϳ��Ԫ(���ٶ���׼��ǹ�ڸ���Ϳ��Ԫ�ڣ�����������п���״̬�仯�㴦����ǹ״̬)
	*@parm IndexOfCurCell ����Ϳ��Ԫ��ĿǰΪֹ��׼�����ڵ�λ��(���˶���ʼ����ĵڼ�����Ϳ��Ԫ��)
	*@parm bReverse �����������ƶ�������Ϊ��
	*@parm StartOfGunIndex �ӵڼ���ǹ��ʼ�����״̬����������ǹ������Ϳ��Χ��ʱΪ0���м�����ǹ������Ϊ�������˶������޹�,ǹ�Ŵ�0��ʼ
	*@return
	*@todo
	*/
	void CheckMultiColoGunStatus(PLC_Parm_It_TYPE SimpleTypeParmVecItBeg,unsigned IndexOfCurCell,bool bReverse,std::vector<float>::iterator itBeg,unsigned StartOfGunIndex=0)
	{
		//std::vector<float>::iterator itBeg=m_vChangeStateRoundCoordVec.begin();
		int NumOfValidCell=0;//������ɫ��Χ�ڵ���Ϳ��Ԫ����
		unsigned GunNum=m_vChangeStateCoordVec.size();
		unsigned CurGunIndex;
		unsigned RealGunNum;
		for (itBeg;itBeg!=m_vChangeStateRoundCoordVec.end();itBeg++)//�����׼��ǹ�����״̬�仯��λ��
		{
			unsigned GunStateResult=0;
			for (unsigned indexOfVirtualGun=StartOfGunIndex;indexOfVirtualGun<this->size();indexOfVirtualGun++)//�����ǹ�ļ��
			{
				//RealGunNum=
				////////////////////////////////NumOfValidCell����bug�����ܳ��ָ���//////////////////////////////////////////
				//NumOfValidCell=ceil(m_vChangeStateCoordVec[indexOfGun]-(*itBeg));//��ǹ�ڻ�׼��ǹ(��׼��Ϊm_vChangeStateCoordVec[StartOfGunIndex])���ڷ����ĵڼ���������
				NumOfValidCell=ceil(m_vChangeStateCoordVec[indexOfVirtualGun]-m_vChangeStateCoordVec[StartOfGunIndex]-(*itBeg));//��ǹ�ڻ�׼��ǹ(��׼��Ϊm_vChangeStateCoordVec[StartOfGunIndex])���ڷ����ĵڼ���������
				if (NumOfValidCell<=IndexOfCurCell)//�����ǹ������ɫ����Ч��Χ��
				{
					PLC_Parm_It_TYPE GunInCellColor=SimpleTypeParmVecItBeg-NumOfValidCell;//����ǹ����ɫ��(��Ӧ��PLC���)
					if (bReverse){
						CurGunIndex=GunNum-indexOfGun-1;//��ǰǹ��ʵ�ʺ���
					}else{
						CurGunIndex=indexOfGun;//��ǰǹ��ʵ�ʺ���
					}									
					//if (*GunInCellColor==QueryMachineHexMapByMachineColorIndex(CurGunIndex))//ר���ڶ�ѵ�ɫ��ǹ
					//if()//���ݶ�ɫ��ǹ�ķ���
					if (IsCurColorBelongToGivenGun(*GunInCellColor,CurGunIndex))
					{
						GunStateResult=GunStateResult|(*GunInCellColor);//����ǹ��λ
					}					
				}
			}
			m_vComplexParmVec.push_back(GunStateResult);
		}		
	}
	std::vector<float>m_vChangeStateCoordVec;///<�п�����Ҫ�ı���ǹ״̬������ֵ������λ����Ҫ�������ǹ״̬����Щλ�þ�Ϊ����һ����Ԫ��ߴ��ĸ��㱶����ͻ�������
	std::vector<float>m_vChangeStateRoundCoordVec;///<�п�����Ҫ�ı���ǹ״̬������ֵ������λ����Ҫ�������ǹ״̬����Щλ�þ�Ϊ����һ����Ԫ��ߴ���������Ե�Ԫ��ߴ�ı���(),ͻ����������������
	PLC_Parm_TYPE m_vComplexParmVec;///<���Ӹ�ʽ�Ĳ��������
	PLC_Parm_TYPE m_vComplexParmHeaderVec;///<����ͷ����
public:
	unsigned m_uGunNum;///<ǹ��Ŀ�������ǵ�ɫ���Ƕ�ɫ�ġ�

	float m_fGunDis;///<ǹ��
	float m_fCellHeightInMM;///<��Ԫ�߶ȣ���λmm
};
#define USE_COMPLEX_PLC_PARM_TYPE
/**
* @class 
* @brief ��ʶ����ת��Ϊ��λ����Ҫ�ĸ�ʽ
*
* 
*/
template<class RecResType,class PaintCellType>
class CResultAdapter:public  MotionParmAdapter<RecResType>,public CPLC_Parm_ComplexType_Adapter<RecResType,PaintCellType>
{
public:
	CResultAdapter(void)
	{	//ImportRecRes(RecRes);	
		m_fRatioOfPixel=1;
	}
	~CResultAdapter(void)
	{	}
	Parm_It_TYPE InsertHeaderOfMotionParm()
	{
		return InsertParmHeader();
	}
	Parm_It_TYPE ExportMotionParmVec(int WorkRegNum)//ע�⣬�ú���������ExporPLCParmVec����ã�����Ͳ��ܿ��ǵ�����Ŀհ׵�������˶���Ӱ��
	{
		
		MotionParmAdapter<RecResType>::ExportMotionParmVec(WorkRegNum);		
		return MotionParmAdapter<RecResType>::InsertParmHeader();
	}
	/*!
 *@brief ��Ϊ׼��PLC����ʱ����Ϊ�˲���б������ͷ��β���岹�˷��飬�����Ҫ��Ӧ�������˶���Χ��Ϣ,������Direction�������������˶��л��Ǹ����˶���
 *
 *@parm RowNum �к�
 *@parm itInserted ���в����դ����Ϣ����ʽΪ�кţ�������դ�������յ����դ������ע������itInserted�����������䶼�Ǹ������յ�����䶼�������������ʾ����
 *@parm itParm �Ѿ�׼���õ��˶����� 
 *@parm Direction ��Y���ӷ����˶�ʱΪ1������Ϊ-1
 *
 *@return
 *@todo
 */
	void ExtendOneRowMotionWithDirection(std::vector<std::vector<int>>::iterator itInserted,MotionParm_It_TYPE itParm,int Direction)
	{
		if ((*itInserted).size()>2)//���������������ȶ�ͷ�����β
		{
			itParm++;
			(*itParm)+=Direction*(*itInserted)[1]*m_sHeaderInfo.PaintHeigth;//�յ�����
			itParm++;//��β
			(*itParm)+=Direction*(*itInserted)[2]*m_sHeaderInfo.PaintHeigth;//�������,
		}
		else//ֻ��һ������
		{
			if ((*itInserted)[1]<0)//������ͷ
			{
				itParm++;				
			}
			else//��β
			{
				itParm=itParm+2;
			}
			(*itParm)+=Direction*(*itInserted)[1]*m_sHeaderInfo.PaintHeigth;//�յ�����
		}
	}
/*!
 *@brief ��Ϊ׼��PLC����ʱ����Ϊ�˲���б������ͷ��β���岹�˷��飬�����Ҫ��Ӧ�������˶���Χ��Ϣ,�������γ��������˶�������������
 *
 *@parm RowNum �к�
 *@parm itInserted ���в����դ����Ϣ����ʽΪ�кţ�������դ�������յ����դ������ע������itInserted�����������䶼�Ǹ������յ�����䶼�������������ʾ����
 *@parm itParm �Ѿ�׼���õ��˶����� 
 *
 *@return
 *@todo
 */
	void ExtendOneRowMotion(std::vector<std::vector<int>>::iterator itInserted,MotionParm_It_TYPE itParm,unsigned DisToFirstRow)
	{
		if (DisToFirstRow%2==0)//0��ʼ������Ϊż�������������ƶ���������������Ǽ�����դ���յ�������+��դ��
		{			
			ExtendOneRowMotionWithDirection(itInserted,itParm,1);			
		}
		else//ż���У��������������+����դ���յ�������-��դ��
		{
			ExtendOneRowMotionWithDirection(itInserted,itParm,-1);
		}
	}
/*!
 *@brief ��Ϊ׼��PLC����ʱ����Ϊ�˲���б������ͷ��β���岹�˷��飬�����Ҫ��Ӧ�������˶���Χ��Ϣ,�������γ��������˶�������������
 *
 *
 *@return
 *@todo
 */
	void ExtendMotionRangeForInsertedNullCell()
	{
		//MotionParmAdapter<RecResType>::m_vParmVec;
		
		if (CPLC_Parm_ComplexType_Adapter<RecResType,PaintCellType>::IsNullCellInserted())
		{
			unsigned HeadSize=MotionParmAdapter<RecResType>::m_vParmHeader.size();
			std::vector<std::vector<int>>::iterator itInserted=CPLC_Parm_ComplexType_Adapter<RecResType,PaintCellType>::m_vInsertedNullCellInRows.begin();
			for (itInserted;itInserted!=CPLC_Parm_ComplexType_Adapter<RecResType,PaintCellType>::m_vInsertedNullCellInRows.end();itInserted++)
			{
				int RowNum=(*itInserted)[0];
				MotionParm_It_TYPE itParm=find(MotionParmAdapter<RecResType>::m_vParmVec.begin(),MotionParmAdapter<RecResType>::m_vParmVec.end(),RowNum);//���������γɵĲ������������кţ����Ҫ���кŲ���ǡ�ú�ĳ�����յ�������ͬ
				/*MotionParm_It_TYPE itEnd=MotionParmAdapter<RecResType>::m_vParmVec.end()--;*/
				//������ˣ������0�У������0���յ�Ҳ�ǣ���һ���յ�Ҳ��0�����ҵ��ǵ�һ�����ϵ�λ�ã�����ȷ��
				int Distance=(itParm-MotionParmAdapter<RecResType>::m_vParmVec.begin()-HeadSize);
				long nDis=Floor4_Ceil5( Distance%3);
				while(nDis!=0&&itParm!=MotionParmAdapter<RecResType>::m_vParmVec.end())//����Ч��Χ�ڣ�������кţ���һ�����ڲ���������λ��3��������λ�á�
				{
					itParm++;
					itParm=find(itParm,MotionParmAdapter<RecResType>::m_vParmVec.end(),RowNum);//���������γɵĲ������������к�
					Distance=(itParm-MotionParmAdapter<RecResType>::m_vParmVec.begin()-HeadSize)%3;
					nDis=Floor4_Ceil5( Distance);
				}
				if (itParm==MotionParmAdapter<RecResType>::m_vParmVec.end())//û�ҵ������
				{
					return;
				}
				int RowDisToFirstRow=Floor4_Ceil5(Distance/3);//�߹��ĵڼ�����
				ExtendOneRowMotion(itInserted,itParm,RowDisToFirstRow);				
			}			
		}
	}
	/*!
	 *@brief ���ɲ����PLC����Ҫ�����ݣ�ע�����
	 *
	 *@parm
	 *@parm
	 *
	 *@return
	 *@todo
	 */
	 PLC_Parm_It_TYPE ExporPLCParmVec(int WorkRegNum)
	 {
		 CPLC_Parm_Adapter<RecResType,PaintCellType>::ExportPLC_ParmVec(WorkRegNum);
		 //ExtendMotionRangeForInsertedNullCell();
		 return CPLC_Parm_Adapter<RecResType,PaintCellType>::InsertParmHeader();
	 }
/**
*@brief ��ͼ��ʶ��Ľ�������������ʶ���˶�������PLC���Ʋ���
*
*@return
*@todo
*/
	 void ImportRecedRes(RecResType* RecRes)
	{
		MotionParmAdapter<RecResType>::ImportRecRes(RecRes);
		CPLC_Parm_Adapter<RecResType,PaintCellType>::ImportRecRes(RecRes);
#ifdef USE_COMPLEX_PLC_PARM_TYPE
		CPLC_Parm_ComplexType_Adapter<RecResType,PaintCellType>::ImportRecRes(RecRes);
#endif
	}
public:
//#ifdef USE_COMPLEX_PLC_PARM_TYPE
	void SetParmOfGunForParm(unsigned GunNum=2,float GunDis=200)
	{
		CPLC_Parm_ComplexType_Adapter<RecResType,PaintCellType>::SetPaintGunParm(GunNum,GunDis);
		CPLC_Parm_ComplexType_Adapter<RecResType,PaintCellType>::CalculateAllPossibleStateChangeCoordinate();
		MotionParmAdapter<RecResType>::SetPaintGunParm(GunNum,GunDis);
	}
	void SetParmOfGunForParm(unsigned GunNum=2,float GunDis=200,int GunMod=1,unsigned ColoNumPerGun=1)
	{
		CPLC_Parm_ComplexType_Adapter<RecResType,PaintCellType>::SetPaintGunParm(GunNum,GunDis,GunMod, ColoNumPerGun);
		CPLC_Parm_ComplexType_Adapter<RecResType,PaintCellType>::CalculateAllPossibleStateChangeCoordinate();
		MotionParmAdapter<RecResType>::SetPaintGunParm(GunNum,GunDis);
	}
	//CPLC_Parm_ComplexType_Adapter<RecResType,PaintCellType> m_cComplexTypePlcParmAdapter;///<���Ӹ�ʽ��PLC����ת����
/**
*@brief ׼����ָ���������ڵĲ�������������ͷ����������¶��ȥ��
*
*
*@parm WorkRegNum ���������
*
*@return ��������ͷ��������
*@todo
*/
	PLC_Parm_It_TYPE ExporComplexPLCParmVec(int WorkRegNum)
	{
		CPLC_Parm_ComplexType_Adapter<RecResType,PaintCellType>::ExportComplexPLC_ParmVec(WorkRegNum);

		return 	CPLC_Parm_ComplexType_Adapter<RecResType,PaintCellType>::InsertComplexParmHeader();
	}
	PLC_Parm_It_TYPE ExportComplexPLC_ParmVecEnd(int WorkRegNum)
	{
		return CPLC_Parm_ComplexType_Adapter<RecResType,PaintCellType>::ExportComplexPLC_ParmVecEnd(WorkRegNum);
	}
//#endif
	/**
	*@brief �����ص�ʵ��mm�ı�����ϵ��
	*
	*
	*@parm
	*
	*@return ���óɹ�������
	*@todo
	*/
	bool SetRatioOfPixel(float RatioOfPixel,float RatioOfYPixel)
	{
		if (RatioOfPixel<=0||RatioOfYPixel<=0)
		{ 
			return false;		
		}
		m_fRatioOfPixel=RatioOfPixel;
		m_fRatioOfYPixel=RatioOfYPixel;
		MotionParmAdapter<RecResType>::SetRealRatio(m_fRatioOfPixel,m_fRatioOfYPixel);
		MotionParmAdapter<RecResType>::SetCellSizeReal();//�������ú�ʵ�ʳߴ�
		CPLC_Parm_Adapter<RecResType,PaintCellType>::SetRealRatio(m_fRatioOfPixel,m_fRatioOfYPixel);
#ifdef USE_COMPLEX_PLC_PARM_TYPE
		CPLC_Parm_ComplexType_Adapter<RecResType,PaintCellType>::SetRealRatio(m_fRatioOfPixel,m_fRatioOfYPixel);
#endif
		return true;
	}
	/**
	*@brief ʵ���ٶȣ�
	*
	*
	*@parm Vel ʵ�������ٶ� ת/s
	*
	*@return
	*@todo
	*/
	void SetRealVel(float Vel)
	{
		//m_sHeaderInfo.Vel=Vel;
		MotionParmAdapter<RecResType>::SetRealVel(Vel);
	}
protected:
	float m_fRatioOfPixel;///<ÿ�����ض�Ӧ���׵ı���ֵ
	float m_fRatioOfYPixel; ///��Y����ÿ�����ض�Ӧ���׵ı���ֵ
	float m_fRealVel;///<ʵ�������ٶȵ�λת/s
};
