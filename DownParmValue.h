#pragma once
#include "iostream"
#include <vector>
#include <utility>
#include "ResultAdapter.h"
#include "afx.h"
#include ".\pmac\runtime.h"
#include "gyMath.h"
#include "Parm.h"
#define LINESPEED 24000        //����ǹֱ������ʱ���ٶ�
#define SPEEDTRANSLATE 600
#define MAXPOINT 1400
typedef std::vector<int> VectorType;

struct GunModelAndDistance
{
	int GunNember;
	float BetweenGunDistance;
};
struct GunCondition
{
	bool OneCondition;
	bool TwoCondition;
	bool ThreeCondition;
	bool FourCondition;
	bool FiveCondition;
	bool SixCondition;
};
struct CameraParm
{
	float Angle_Correct;
	float X_Correct;
	float Y_Correct;
};
struct PerGunCondition
{
	int Index;
	GunCondition EveryPerGunCondition;
};
struct GunPerBeginAndEnd
{
	int Index;
	int Begin;
	int End;
};
struct CornerPoint          //��¼ÿһ��ת�ǵ�XY����
{
	int XPoint;
	float YPoint;
};
struct CoordinateFrame
{
	bool IsRequireCanGet;  //�ܲ�����Ϳ
	float BeginXPoint;
	float BeginYPoint;
	float FrameRange;
};
typedef std::vector<std::pair<int,float>> CheckPointPairVecType;
class CheckPointMap_finder
{
	public:
		CheckPointMap_finder(const float &cmp_string):m_s_cmp(cmp_string){}
		bool operator ()(const std::map<float, int>::value_type &pair)
		{
		      return pair.first == m_s_cmp;
		}
		private:
		const float &m_s_cmp;                    
};
class DownValue
{
public:
	DownValue();
	~DownValue();
	void GetDownValueMotion(MotionParm_It_TYPE MotionBegin,MotionParm_It_TYPE MotionEnd);
	void GetDownValuePlc(std::vector<int> StoragePlc,std::vector<float>::iterator ChangedColorPointHead,std::vector<float>::iterator ChangedColorPointEnd,unsigned m_uGunNum,float m_fGunDis);
	
	void GetDownValuePlc2(std::vector<int> StoragePlc,std::vector<float>::iterator ChangedColorPointHead,std::vector<float>::iterator ChangedColorPointEnd,unsigned m_uGunNum,float m_fGunDis);

	void GetDownCameraValue(CString CameraParm);
	/*void GetDownMotionSpeed(int MotionSpeed);*/
	CString CompileGunCondition(int Parm);
	CString GetStringPaser_star(CString gps_str,int num);
	void StartOpen(CString Directory);
	void StartOpenPlc(CString Directory,CoordinateFrame m_CoordinateFrame,float GunDelay[][2]);
	void CheckHeight(float Height);
	void GetGunModelAndGunDistance(int GunNember,float BetweenGunDistance);//�õ���ǹģʽ����ǹ֮��ľ���
	void TranslateEveryChangeColor(int BeginPoint,int EndPoint);  //������ɫͻ��������
	void TranslateEveryChangePoint(unsigned m_uGunNum,float m_fGunDis);                             //����ÿһ��λ��ͻ���
	//////////////////////////////////////////////////////////////////////////
	void TranslateOneColumm(unsigned CurColumIndex,float MoveRangeEnd,float MoveRangeBegin,int CellToBeRun,bool bisForward);
	void TranslateEveryChangePoint2(unsigned m_uGunNum,float m_fGunDis);                             //����ÿһ��λ��ͻ���

private:
	GunCondition m_Gundition;
	int PerLaw;      //����ǰ���������м���
	std::vector<PerGunCondition> m_EveryPerCondition;
	std::vector<GunPerBeginAndEnd> m_GunPerBeginAndEnd;
	std::map<int,VectorType> GunColorAll;        //��map����ʾ��ǹ״̬�Ķ�ά���飬�д����У��д�����е���ǹ״̬
	typedef std::vector<CornerPoint> VectorTypePoint;
	VectorTypePoint m_VectorTypePoint;
	std::map<int,VectorTypePoint> AllChangeColorPosition;
	VectorType m_EveryColumnGunColor;               //ÿ����ǹ��״̬
	CornerPoint m_CornerPoint;                   //��¼ÿһ��ת������
	int m_CornerPointColor;                      //��¼ÿһ��ת�ǵ���ǹ״̬
	bool JudgeIsFirstCorner;
	float Speed;
	int PerWidth;
	int PerHeight;
	int m_MotionSpeed;
	bool JudgeReturn;
	bool JudgeChangeDirection;
	int HeightPer;       //ÿ�еĸ߶�
	int LastRemberY;
	bool JudgeFirstLow;
	CameraParm m_CameraParm;
	int m_JudgeOneChoice;
	GunModelAndDistance m_GunModelAndDistance;
	std::vector<int> m_ColumnXYPointEverySholdJudgeColor; //��ÿһ���д洢ÿһ����Ҫ�����ǹ��ɫͻ��������
	int GunMenber; //��ѡ�����ǹģʽʱ������ǹ��
	std::vector<float>::iterator m_ChangedColorPointHead;
	std::vector<float>::iterator m_ChangedColorPointHeadCopy;
	std::vector<float>::iterator m_ChangedColorPointHeadCopyl;
	std::vector<float>::iterator m_ChangedColorPointEnd;
	int OldColor;      //��¼��һ��ɫͻ������ɫֵ
	bool JudgeIsOrFirstPer;
protected:
	bool WriteDelayParm(float OpenDelay, float CloseDelay,FILE* fp);
	bool WriteAllDelayParm(float GunDelay[][2],FILE*fp,unsigned GunNum=4)
	{
		
		for (unsigned i=0;i<GunNum;i++)
		{
			//float fopen=GunDelay[i][0];

			WriteDelayParm( GunDelay[i][0], GunDelay[i][1],fp);
		}
		return true;
	}
/*!
 *@brief ���ı��ļ�д������ͻ��㼰��Ϣ
 *
 *@parm
 *@parm
 *
 *@return
 *@todo
 */
	void WriteCheckPointsAndStatus(unsigned GunNum,int CheckPointX,float CheckPintY,float GunDelay[][2],FILE*fp,VectorType::iterator m_ColumnUnitColor);
	void CompareString(unsigned GunNum,int CheckPintY, float GunDelay[][2]);
/*!
 *@brief ��һ��ԭʼͻ���������䡢��д�µ���ɫ״̬
 *
 *@parm CheckPoint ���е�ԭʼͻ��㼯��
 *@parm CheckPointColorList ����ԭʼͻ����Ӧ����ɫ״̬
 *@parm GunDelay ���е��ӳ�
 *
 *@return
 *@todo
 */	
	bool CheckEveryGunDelayAndAddCheckPoint(VectorTypePoint CheckPoint,VectorType CheckPointColorList,float GunDelay[][2],unsigned GunNum,bool bReverse);
/*!
 *@brief �Ը���ԭʼͻ���������䡢��д�µ���ɫ״̬
 *
 *@parm itCurColor ԭʼͻ����Ӧ��ɫ
 *@parm itCheckPoint ԭʼͻ���
 *@parm PreColor ǰһԭʼͻ������ɫ
 *@parm GunDelay ���е��ӳ�
 *
 *@return
 *@todo ������ʱδ������Ҫ������ٵ�һ�Σ�һ��ͻ����ͬһ����ǹ״̬Ҫô�ɿ�����Ҫô��֮��Ҫôά��ԭ״��ֻ�����֡���������ɼ�������ì��
 */		
	bool CheckOneCheckPoint(VectorType::iterator itCurColor,VectorTypePoint::iterator itCheckPoint,int PreColor,float GunDelay[][2],unsigned GunNum,bool bReverse);
/*!
 *@brief �Ը���������ͻ���������䡢��д�µ���ɫ״̬�����ո�����ͻ��㼰����ͻ���ǹ�ţ���ԭ����ɫPreColor������������Ӧǹλ����ɫ״̬��
 *
 *@parm itCurColor ԭʼͻ����Ӧ��ɫ
 *@parm itSortedOpenCheckSets �����˵Ŀ���ͻ��㼯������
 *@parm itSortedCloseCheckSets �����˵Ĺر�ͻ��㼯������
  *@parm itAllDelayedCheckSets δ��������ͻ�����ĵ�����
  *@parm PreColor ǰһԭʼͻ������ɫ
 *@parm 
 *
 *@return
 *@todo ������ʱδ������Ҫ������ٵ�һ�Σ�һ��ͻ����ͬһ����ǹ״̬Ҫô�ɿ�����Ҫô��֮��Ҫôά��ԭ״��ֻ�����֡���������ɼ�������ì��
 */		
	bool CheckOneExpandedCheckPoint(VectorType::iterator itCurColor,std::map< float,int>::iterator itSortedOpenCheckSets,
		std::map< float,int>::iterator itSortedCloseCheckSets,std::map< float,int>::iterator itAllDelayedCheckSets,
		std::map< float,int>& DelayMap,//�ӳ�֮���ͻ���,���¿����ӳٵ�ǹ��,
		std::map< float,int>& CloseDelayMap,//�ӳ�֮���ͻ���,���¹ر��ӳٵ�ǹ��,
		CheckPointPairVecType RepeatedOpenCheckPoints, CheckPointPairVecType RepeatedCloseCheckPoints,
		int& PreColor,bool bReverse);
	VectorTypePoint m_CheckPointListWithDelay;//�����ӳٺ���µ�ͻ���
	VectorType m_CheckPointColorListWithDelay;//�����ӳٺ���µ�ͻ��㴦����ɫ
	VectorTypePoint OneCheckPointExpandTmp;//�������������ļ��㼯,�ӳ�����������GunNum��ͻ���
	VectorType ColorOfExpandedCheckPointsTmp;//�����ļ��㼯��Ӧ����ɫ����
	std::vector<int>GunNumValue;//����ǹǹ�Ŷ�Ӧ��ʮ��������
	//��ʼ������ǹ�Ŷ�Ӧ�Ķ�������
	void InitGunNumValue(int GunNum)
	{		
		GunNumValue.clear();
		for (int i=0;i<GunNum;i++)
		{
			GunNumValue.push_back(pow((float)2,i));//����ǹ��Ӧ�ĺ���ֵ,Ŀǰ����4����ǹ
		}
	}
	/*!
	 *@brief ����ظ���ͻ��㣬���������ظ��ĵ㵥���ó���������ͻ���λ�ô�С��������
	 *
	 *@parm Delay ͻ��������
	 *@parm
	 *
	 *@return
	 *@todo
	 */
	CheckPointPairVecType CheckGetRepeatedDelay(std::vector<float> Delay);
	/*!
	 *@brief ��ÿһ��������ͻ��㣬�Ը�����ǹ�������γɸõ���е���ɫ״̬������ǹ��״̬�������������ӳٿ��������ӳٹر�ͻ������ֱ���,��������ظ���ͻ��㴦��
	 *
	 *@parm itCurColor ��ǰԭʼͻ��㴦����ɫ״̫
	 *@parm GunIndex ��Ҫ�жϵ�ǹ�ţ�����������ͻ������ɼ���ǹ���ӳ��ճɵ�
	 *@parm PreColor �����ͻ���ǰ����ɫ״̬
	 *@parm RepeatedCheckPoints �뱾ͻ����غϵ�����ͻ��㣬ע�⿪���͹ر����µ������������غϵ�Ҫ�ֱ��
	 *@parm NeedOpen ���Ǹ��ӳٿ���ͻ���ô��
	 *
	 *@return
	 *@todo
	 */
	bool SetExpandedCheckPointsForEachGun(VectorType::iterator itCurColor,int GunIndex,
		float CheckPointPose,// CornerPoint& GunCheckPointTmp, 
		int& PreColor,CheckPointPairVecType& RepeatedCheckPoints,
		bool NeedOpen);
	/*!
	 *@brief ��ΪҪ������������ӳٵ�ͳһ���ǣ�ȴ�ֱ�����������Ҫ�ӳٿ��������ӳٹرշֱ�������Ҫ�ж����ǿ����ǹص��ӳٵ�
	 *
	 *@parm 
	 *@parm
	 *
	 *@return ���ظ�ͻ����Ƿ�Ϊ��������ͣ���Ϊ��
	 *@todo
	 */
	bool JudgeExpandedCheckPointType(std::map< float,int>::iterator itAllDelayedCheckSets,
		std::map< float,int>::iterator itSorteTypeCheckSets,std::map< float,int>::iterator itSorteTypeCheckSetsEnd)
	{
		for (itSorteTypeCheckSets;itSorteTypeCheckSets!=itSorteTypeCheckSetsEnd;itSorteTypeCheckSets++)	{	//����ǰ�����жϵĻ� 
			//float a=itAllDelayedCheckSets->first;
			//float b=itSorteTypeCheckSets->first;
			if (itAllDelayedCheckSets->first==itSorteTypeCheckSets->first){
				return true;
			}
		}
		return false;
	}
/*!
 *@brief ����һ��ԭʼͻ���������ܵ�ǰ��ĳ��ԭʼͻ���������λ��֮ǰ�ˣ�������ͻ����Ҫ���⴦��
 *�ڲ����������������m_vStackOfAllDelayPointMapInRow��m_vStackOfAllRepeatedOpenCheckPoints���ڲ���ͻ��㼯�ϣ����
 *������it_CurCheckPoint��itRepeatedCheckPoints��itRepeatedCloseCheckPoints��������Щ�����ϸ�һһ��Ӧ
 *�����ӳ�ͻ�����໥��ͻ������һ��ԭʼͻ���������ӳ�ͻ��㣬�ܵ�ǰĳ��ԭʼͻ����ӳ������ķ�Χ�ڵ����������˼·�ǣ��ҵ����������ͻ��ͻ��㣬�����ͻ������ɼ�����ǹ����ʱ��ɵģ����⼸����ǹ��Ӧ����ɫλ��ֵȡ������
 *�ٰ����µ��⼸λ��ֵ���ǻ�ȥ������֮��ͻ��ͻ����Ӧ����ɫλ
 *�����ı�m_CheckPointColorListWithDelay�д����ɫ
 *@parm fCurCheckPoint ��ǰҪ����Ƿ�����ͻ��ͻ���Y����
 *@parm StackOfAllDelayPointMapInRow ��������������ͻ������У���ͻ������б���û�о����������򣬻��ǰ���ԭʼͻ����˳������
 *
 *@return 
 *@todo
 */
	bool CheckConflictFromDifferentOriginCheckPoint(std::vector<std::pair<float,int>>::iterator it_CurCheckPoint,std::vector<std::pair<float,int>>& StackOfAllDelayPointMapInRow
		,CheckPointPairVecType::iterator& itRepeatedCheckPoints,CheckPointPairVecType::iterator& itRepeatedCloseCheckPoints
		,bool bReverse);
	void ClearAllCheckPointsBackUpVecInRow()
	{
		m_CheckPointListWithDelay.clear();
		m_CheckPointColorListWithDelay.clear();
		m_vStackOfAllDelayPointMapInRow.clear();//ÿ������һ��

		m_vStackOfAllRepeatedCloseCheckPoints.clear();
		m_vStackOfAllRepeatedOpenCheckPoints.clear();
	}
	float m_fMaxRange;//������Ϳ������˶���Χֵ
	void LimitCheckPoint(float& OpenCheckPointAfterDelay,float& CloseCheckPointAfterDelay,float MaxRange)
	{
		OpenCheckPointAfterDelay=OpenCheckPointAfterDelay<0?0:OpenCheckPointAfterDelay;
		CloseCheckPointAfterDelay=CloseCheckPointAfterDelay<0?0:CloseCheckPointAfterDelay;
		OpenCheckPointAfterDelay=OpenCheckPointAfterDelay>MaxRange?MaxRange:OpenCheckPointAfterDelay;
		CloseCheckPointAfterDelay=CloseCheckPointAfterDelay>MaxRange?MaxRange:CloseCheckPointAfterDelay;

		//if (OpenCheckPointAfterDelay<0)		{
		//	OpenCheckPointAfterDelay=0;
		//}
		//if (CloseCheckPointAfterDelay<0)	{
		//	CloseCheckPointAfterDelay=0;
		//}
		//if (OpenCheckPointAfterDelay>MaxRange)		{
		//	OpenCheckPointAfterDelay=MaxRange;
		//}
		//if (CloseCheckPointAfterDelay)		{
		//	CloseCheckPointAfterDelay=MaxRange;
		//}
	}
	std::vector<std::pair<float,int>> m_vStackOfAllDelayPointMapInRow;//�����ӳ�֮���ͻ���,�����ӳٵ�ǹ��,���ڴ�������ͻ����ͻ����
	
	CheckPointPairVecType m_vStackOfAllRepeatedOpenCheckPoints;//�����ӳ�֮���ظ��Ŀ���ͻ���,�����ӳٵ�ǹ��,���ڴ�������ͻ����ͻ����
	CheckPointPairVecType m_vStackOfAllRepeatedCloseCheckPoints;//�����ӳ�֮���ظ��Ĺر�ͻ���,�����ӳٵ�ǹ��,���ڴ�������ͻ����ͻ����
 /*!
 *@brief ���и�������ɫ��λ���������ڰѵ�ǰ�����ɫ�в�����ͻ��ǹ�Ŷ�Ӧ����ɫλ���ǻ�ȥ������ͻ�����ɫλ
 *
 *@parm BackPosIndex Ҫ�����ǵĳ�ͻ����±�
 *@parm GunIndex ����ǹ��
 *
 *@return
 *@todo
 */
	void CoverGivenBitColorForGivenPoint(int BackCheckPoint,int CurCheckPoint,int GunIndex);
 /*!
 *@brief ����Ҫ���ǵĳ�ͻ�����ɫ���ѵ�ǰ�����ɫ�в�����ͻ��ǹ�Ŷ�Ӧ��λ�ø��ǻ�ȥ������ͻ�����ɫλ
 *
 *@parm BackPosIndex Ҫ�����ǵĳ�ͻ����±�
 *@parm CurIndex ��ǰ�������±�
 *@parm  itRepeatedCheckPoints �ڿ���ͻ��㼯�еĻ�׼λ�ã������ڿ����ƶ�����������
 *
 *@return
 *@todo
 */
	void BackSetConflictPointColor(std::vector<std::pair<float,int>>::iterator itvPreCheckPoint,
		std::vector<std::pair<float,int>>::iterator itvCurCheckPoint,	
		CheckPointPairVecType::iterator& itRepeatedCheckPoints, CheckPointPairVecType::iterator& itRepeatedCloseCheckPoints);
 /*!
 *@brief �жϵ�ǰ������λ���Ƿ�������ͻ��㷢�����ظ��������ظ���λ����itRepeatedCheckPoints����
 *
 *@parm CheckPointPose Ҫ�жϵ�ͻ���λ��
 *@parm itRepeatedCheckPoints ��ǰҪ�жϵ�λ��
 *
 *@return
 *@todo
 */
	bool JudgeRepeatedCheckPoint(float CheckPointPose,CheckPointPairVecType::iterator& itRepeatedCheckPoints,CheckPointPairVecType::iterator itRepeatedCheckPointsEnd)
	{
		for (itRepeatedCheckPoints;itRepeatedCheckPoints!=itRepeatedCheckPointsEnd;itRepeatedCheckPoints++)
		{
			if (CheckPointPose==itRepeatedCheckPoints->second)//ȷʵ�ظ���
			{
				return true;
			}
		}
		return false;
	}
};
