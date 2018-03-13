#pragma once
#include "iostream"
#include <vector>
#include <utility>
#include "ResultAdapter.h"
#include "afx.h"
#include ".\pmac\runtime.h"
#include "DownParmAdjust.h"
#include "gyMath.h"

#include "DownParmValueHead.h"
#define LINESPEED 24000        //����ǹֱ������ʱ���ٶ�
#define SPEEDTRANSLATE 600
#define MAXPOINT 1400
#define  TOLERANCE_OF_SAME_POINT 0.02//�����ٺ��׿�����Ϊ��ͬһ��ͻ���


//struct ChecPointIteratorSet
//{
//
//	std::vector<std::pair<float,int>>::iterator itCheckPoint;
//	void operator ()(const std::vector<std::pair<float,int>>::iterator &iter)
//	{
//		itCheckPoint = iter;
//	}
//	bool operator <(const ChecPointIteratorSet & rhs) const // ��������ʱ����д�ĺ���
//	{
//		return itCheckPoint->first < rhs.itCheckPoint->first;
//	}
//	bool operator >(const ChecPointIteratorSet & rhs) const // ��������ʱ����д�ĺ���
//	{
//		return itCheckPoint->first > rhs.itCheckPoint->first;
//	}
//};
class DownValue
{
public:
	DownValue();
	~DownValue();
	void GetDownValueMotion(MotionParm_It_TYPE MotionBegin,MotionParm_It_TYPE MotionEnd);
	/*!
 *@brief ��ԭ�����˶����ƿ�����������µĿ��ƿ�����Ҫ�İ汾
 *
 *@parm
 *@parm
 *
 *@return
 *@todo
 */
	//void GetDownValueMotion2(MotionParm_It_TYPE MotionBegin,MotionParm_It_TYPE MotionEnd);
	void GetDownValuePlc(std::vector<int> StoragePlc,std::vector<float>::iterator ChangedColorPointHead,std::vector<float>::iterator ChangedColorPointEnd,unsigned m_uGunNum,float m_fGunDis);
	
	//void GetDownValuePlc2(std::vector<int> StoragePlc,std::vector<float>::iterator ChangedColorPointHead,std::vector<float>::iterator ChangedColorPointEnd,unsigned m_uGunNum,float m_fGunDis);

	//void GetDownValuePlc(std::vector<int> StoragePlc,std::vector<float>::iterator ChangedColorPointHead,std::vector<float>::iterator ChangedColorPointEnd,unsigned m_uGunNum,float m_fGunDis);

	void GetDownCameraValue(CString CameraParm);
	/*void GetDownMotionSpeed(int MotionSpeed);*/
	CString CompileGunCondition(int Parm);
	CString GetStringPaser_star(CString gps_str,int num);
	void StartOpen(CString Directory);
/*!
 *@brief
 *
 *@parm
 *@parm
 *
 *@return �򲻿�д���ļ���Ϊ�٣�����Ϊ��
 *@todo
 */
	bool StartOpenPlc(CString Directory,CoordinateFrame m_CoordinateFrame,double GunDelay[][2],double GunDelayInReverse[][2]);
	void CheckHeight(float Height);
	void GetGunModelAndGunDistance(int GunNember,float BetweenGunDistance);//�õ���ǹģʽ����ǹ֮��ľ���
	void TranslateEveryChangeColor(int BeginPoint,int EndPoint);  //������ɫͻ��������
	void TranslateEveryChangePoint(unsigned m_uGunNum,float m_fGunDis);                             //����ÿһ��λ��ͻ��㣬׼���������Ϳ��������Ϊԭ���汾��ֻ����ͻ��㴦����ɫ�����������ͻ������������������Ӧ�ú���ɫ�ĸ���һ��
	//////////////////////////////////////////////////////////////////////////
	void TranslateOneColumm(unsigned CurColumIndex,float MoveRangeEnd,float MoveRangeBegin,int CellToBeRun,bool bisForward);///<׼��һ�е�����ͻ��㣬��Ϊԭ���汾��ֻ����ͻ��㴦����ɫ�����������ͻ������������������Ӧ�ú���ɫ�ĸ���һ��
	void TranslateEveryChangePoint2(unsigned m_uGunNum,float m_fGunDis);                             ///<����ÿһ��λ��ͻ��㣬׼���������Ϳ����,TranslateEveryChangePoint������ģ�黯�汾

private:
	GunCondition m_Gundition;
	int PerLaw;      //����ǰ���������м���
	std::vector<PerGunCondition> m_EveryPerCondition;
	std::vector<GunPerBeginAndEnd> m_GunPerBeginAndEnd;
	std::map<int,VectorType> GunColorAll;        //��map����ʾ��ǹ״̬�Ķ�ά���飬�д����У��д�����е���ǹ״̬
	
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
	bool WriteAllDelayParm(double GunDelay[][2],FILE*fp,unsigned GunNum=DEFAULT_NUM_OF_GUN)
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
	void WriteCheckPointsAndStatus(unsigned GunNum,int CheckPointX,float CheckPintY,double GunDelay[][2],FILE*fp,VectorType::iterator m_ColumnUnitColor);
/************************************************************************/
/*         ׼��ɾ��                                                             */
/************************************************************************/
	void WriteCheckPointsAndStatus2(unsigned GunNum,int CheckPointX,float CheckPintY,double GunDelay[][2],FILE*fp,VectorType::iterator m_ColumnUnitColor,VectorType::iterator m_PreColumnUnitColor);
	bool BitCheckFor1Change(VectorType::iterator m_PreColumnUnitColor,VectorType::iterator m_ColumnUnitColor,int GunNum=DEFAULT_NUM_OF_GUN);
	/***/
	void CompareString(unsigned GunNum,int CheckPintY, double GunDelay[][2]);
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
	bool CheckEveryGunDelayAndAddCheckPoint(VectorTypePoint CheckPoint,VectorType CheckPointColorList,double GunDelay[][2],unsigned GunNum,bool bReverse);
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
	bool CheckOneCheckPoint(VectorType::iterator itCurColor,VectorTypePoint::iterator itCheckPoint,int PreColor,double GunDelay[][2],unsigned GunNum,bool bReverse);
/*!
 *@brief �Ը���������ͻ���������䡢��д�µ���ɫ״̬�����ո�����ͻ��㼰����ͻ���ǹ�ţ���ԭ����ɫPreColor������������Ӧǹλ����ɫ״̬��
 *
 *@parm itCurColor ��ǰԭʼͻ����Ӧ��ɫ
 *@parm itSortedOpenCheckSets �����˵Ŀ���ͻ��㼯������
 *@parm itSortedCloseCheckSets �����˵Ĺر�ͻ��㼯������
  *@parm itAllDelayedCheckSets δ��������ͻ�����ĵ�����,ָ��ǰ��ͻ���
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
 *@brief Ϊÿһ��������ͻ������õ����ɫ״̬ʱ����Ҫ��Ū��ǰһ����ɫ״̬��ʲô��������ʵ������
 *ԭ��ֱ����Ϊ��һ��ԭʼͻ������ɫ�����Ǳ�������ͻ���������ԭʼ��ɫ,�ڱ��������ڲ���ʼ�հ���������ϵ�ǰһ�仯��Ϊ��precolor
 *�����������⣬������Ȼ������һ���ܣ�bSearchNewPreColorΪ��ʱ��ֱ�ӷ���PreColor
 *
 *@parm CurCheckPointPos ��ǰ�������
 *@parm PreColor ��bSearchNewPreColorΪ��ʱ��ֱ�ӷ��ر�ֵ
 *@parm bSearchNewPreColor �Ƿ���Ҫ������������ʵ��ǰһ��ɫ״̬������Ϊ��
 *
 *@return
 *@todo
 */
	int findPreColorAfterPreExpand(float CurCheckPointPos,int PreColor,bool bSearchNewPreColor,bool bReverse);
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
			if (*itAllDelayedCheckSets==*itSorteTypeCheckSets){
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
		PoseAndIndex.clear();
		m_StackOfAllCloseDelayMap.clear();
		m_StackOfAllOpenDelayMap.clear();
		AllDelayPointMap.clear();
		m_mExpandedPointAndOriginCheckPointIndexMap.clear();

		OneCheckPointExpandTmp.clear();
		ColorOfExpandedCheckPointsTmp.clear();
		m_vStackOfAllDelayPointIndexByGun.clear();
		m_vStackOfAllColorsIndexByGun.clear();
	}
	double m_fMaxRange;//������Ϳ������˶���Χֵ
	void LimitCheckPoint(double& OpenCheckPointAfterDelay,double& CloseCheckPointAfterDelay,double MaxRange)
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
	VectorTypePoint::iterator m_itChecPointVecEnd;///<��������ԭʼͻ����ĩβ
	std::vector<int>KeepRemainedBitNumVec;///<û�ִ����������ͻ����У�����Щλ��û����ģ�0��ʼ,SetExpandedCheckPointsForEachGun�����и�ֵ������CheckAndSetRemainColor�����ĵ���
	bool CheckAndSetRemainColor(VectorTypePoint::iterator itCurOriginCheckPoint,VectorTypePoint::iterator itOriginCheckPointVecEnd,//CornerPoint& GunCheckPointTmp, 
		VectorType::iterator itCurOriginCheckPointColor,int ToBeCheckedGunIndex,
		float CurExpandedCheckPointPose, double GunDelay[][2],
		int& ColorStatus,//����ǹλ��Ӧ��ǰһ״̬��Ҳ����Ӧ�ñ��ֵ�״̬��
		bool bReverse);

	//////////////////////ԭ��������bug��������˼·,����2������3////////////////////////////////////////////////////
	/*!
 *@brief ��Ҫ�ӿں��������÷���3
 *1.���Ȱ����е������ͻ����ҵ��������������С�
 *2.��ÿ����ǹ����ԭʼͻ��㴦��ʼ����һ�飬�ҵ�û����ǹ�÷���״̬�仯��ͻ��㣬Ҳ�ͱ�Ȼ�ǿ�����һ��һ�Ե�ͻ��㡣����¼��Щͻ��㴦����ɫ״̬��ֻ��һ����ǹ��״̬�����γ�һ������ǹ��Ϊ�У�ÿ��ͻ���Ϊ�еĶ�άvector����m_vStackOfAllDelayPointIndexByGun���Լ���ɫ��ά����m_vStackOfAllColorsIndexByGun
 *3.�ع�ͷ������m_vStackOfAllDelayPointIndexByGun�е���ǹ���ص㣬���ź��������ͻ��㼯m_CheckPointListWithDelay�С��ҵ�ÿһ����ǹ���ص��Ӧ��λ�á�
 *����m_CheckPointColorListWithDelay�У���������ǹ����ɫ��һд�롣�γ����յĸ������ͻ������ɫ����
 *
 *@parm 
 *@parm 
 *
 *@return �ɹ������棬���е����ս������m_CheckPointListWithDelay��m_CheckPointColorListWithDelay�У�ǰ��Ϊͻ��㣬����Ϊ��Ӧ����ɫ״̬
 *@todo
 */
	bool CalculateAllDelayedCheckPointInRow(VectorTypePoint CheckPoint,VectorType CheckPointColorList,double GunDelay[][2],unsigned GunNum,bool bReverse);
/*!
 *����һ��ԭʼͻ��㣬����������¼��	m_mExpandedPointAndOriginCheckPointIndexMap��һϵ�б����У�ֻ������ͻ����λ�ã����漰��ɫ
 *
 *@parm 
 *@parm 
 *
 *@return
 *@todo
 */
	void ExpandOneOriginCheckPoint(
		std::map< float,int>& DelayMap,//�ӳ�֮���ͻ���,���¿����ӳٵ�ǹ��,
		std::map< float,int>& CloseDelayMap,//�ӳ�֮���ͻ���,���¹ر��ӳٵ�ǹ��,<
		std::map<float,int>&AllDelayPointMap,//�����ӳ�֮���ͻ���,�����ӳٵ�ǹ��,<
		std::vector<float>& OpenDelayPoints,
		std::vector<float>& CloseDelayPoints,
		const VectorTypePoint::iterator itCheckPoint,const int OriginPointIndex,//0��ʼ
		const double GunDelay[][2],const unsigned GunNum,const bool bReverse	
		);
 /*!
 *����һ���е�����ԭʼͻ��㣬����������¼��	m_mExpandedPointAndOriginCheckPointIndexMap��һϵ�б����У�ֻ������ͻ����λ�ã����漰��ɫ
 *
 *@parm 
 *@parm 
 *
 *@return
 *@todo
 */
	void ExpandAllOriginCheckPointInRow( VectorTypePoint& CheckPointVec, const double GunDelay[][2],const unsigned GunNum,const bool bReverse)
	{
		std::map< float,int> DelayMap;//�ӳ�֮���ͻ���,���¿����ӳٵ�ǹ��,
		std::map< float,int> CloseDelayMap;//�ӳ�֮���ͻ���,���¹ر��ӳٵ�ǹ��,<
		
		std::vector<float> OpenDelayPoints;
		std::vector<float> CloseDelayPoints;
		int OriginPointIndex=0;//
		for (VectorTypePoint::iterator itCheckPointVec=CheckPointVec.begin();itCheckPointVec!=CheckPointVec.end();itCheckPointVec++)//������ԭʼͻ������䣬�洢
		{
			ExpandOneOriginCheckPoint( DelayMap,CloseDelayMap,AllDelayPointMap,OpenDelayPoints, CloseDelayPoints,itCheckPointVec,OriginPointIndex,GunDelay,GunNum,bReverse);
			OriginPointIndex++;
		}
		
	}
	void CalCulateOneExpandedCheckPointStatues(const VectorType::iterator itCurOriginColor,std::map< float,int>::iterator itCurDelayedCheckPoint,int& PreColor,bool bReverse);
	/*!
 *������������ͻ������򣬰����Ⱥ�˳�����򣬿������������ظ�ͻ��������
 *
 *@parm 
 *@parm 
 *
 *@return
 *@todo
 */
	void SortAllExpandedCheckPoint(bool bReverse,int XCoord);
	CheckPointPairVecType CheckGetRepeatedDelay2(std::vector<float> Delay,int GunNum);
	std::map<float,int> PoseAndIndex;//��ͻ��㴦���������Ӧ�ı�ţ����ͻ�����m_vStackOfAllDelayPointMapInRow�еĶ�Ӧ�±�,
	std::map< float,int> m_StackOfAllOpenDelayMap;//�ӳ�֮���ͻ���,���¿����ӳٵ�ǹ��,
	std::map< float,int> m_StackOfAllCloseDelayMap;//�ӳ�֮���ͻ���,���¹ر��ӳٵ�ǹ��,<
	std::map<float,int>AllDelayPointMap;//�����ӳ�֮���ͻ���,�����ӳٵ�ǹ��,<map��ʽ�����Զ�����
	std::map<float,int>m_mExpandedPointAndOriginCheckPointIndexMap;///<�ӳ�֮���ͻ��㣬������Ӧ��ԭʼͻ�����ԭʼͻ��㼯���е��±�
	int m_UnReapeatedCheckPointNumOfExpanded;
	int m_iGunNum;//��ǹ��
	/*!
 *@brief �Ը�������ǹ������ԭʼͻ������У���������һ����Ը���ǹ���µ�ͻ������в���������ǹ�ӳ�����
 *��Ӧÿ����ǹ�������ͻ��㣬һ�����ȿ���ص�ͻ��㣬һ��һ�ԡ��������ݳ��ֵ��Ⱥ�˳������˳��ġ��������
 *m_vStackOfAllDelayPointIndexByGun��m_vStackOfAllColorsIndexByGun
 *@parm 
 *@parm 
 *
 *@return
 *@todo
 */
	bool RecheckEveryOriginCheckPointToSetExpandCheckPointForOneGun(int GunIndex,VectorTypePoint& CheckPoint,VectorType& CheckPointColorList,double GunDelay[][2],bool bReverse);
	/*!
 *@brief �����е���ǹ������ԭʼͻ������У���������һ����Ը���ǹ���µ�ͻ������в���������ǹ�ӳ�����
 *��Ӧÿ����ǹ�������ͻ��㣬һ�����ȿ���ص�ͻ��㣬һ��һ�ԡ��������ݳ��ֵ��Ⱥ�˳������˳��ġ��������
 *m_vStackOfAllDelayPointIndexByGun��m_vStackOfAllColorsIndexByGun��������RecheckEveryOriginCheckPointToSetExpandCheckPointForOneGun
 *@parm 
 *@parm 
 *
 *@return
 *@todo
 */
	bool RecheckOriginCheckPointForAllGun(int GunNum,VectorTypePoint CheckPoint,VectorType CheckPointColorList,double GunDelay[][2],bool bReverse=false)
	{
		for (int i=0;i<GunNum;i++)
		{
			RecheckEveryOriginCheckPointToSetExpandCheckPointForOneGun(i,CheckPoint,CheckPointColorList,GunDelay,bReverse);
		}
		if (m_vStackOfAllColorsIndexByGun.size()!=m_vStackOfAllDelayPointIndexByGun.size())
		{ 
			return false;
		}
		return true;
	}
/*!
 *@brief ����m_vStackOfAllDelayPointIndexByGun m_vStackOfAllColorsIndexByGun,�������պ�������ǹ״̬������ɫ״̬��ͻ�������
 *δ��ɣ�������MergeAllSortedCheckPointAndColor
 *
 *@parm 
 *@parm 
 *
 *@return
 *@todo
 */
	void MergeAllCheckPointAndColor(int GunNum,bool bReverse);
	void MergeAllSortedCheckPointAndColor(int GunNum);
/*!
 *@brief ���ź����m_CheckPointListWithDelay�����У���BeginIter��EndIter֮���ҵ���Pose��Ӧ��ͻ��㣬���ƶ�������BeginIter����ͻ��㡣
 *
 *@parm 
 *@parm 
 *
 *@return ���ͨ��BeginIter����,ͬʱ�������Pose��m_CheckPointListWithDelay�ж�Ӧ����±꣬0��ʼ����
 *@todo
 */
	int FindPoseInSortedVec(float Pose,VectorTypePoint::iterator& BeginIter,VectorTypePoint::iterator EndIter);
	void DownValue::AddColor( int Index ,int ColorOfGun)
	{

		m_CheckPointColorListWithDelay[Index]|=ColorOfGun;
	}
	/*!
 *@brief �������Ѿ�����õ�����ͻ������У�ɾ��״̬�ظ��ĵ㡣ʵ�������������������λ�������ٶ�
 *
 *@parm 
 *@parm 
 *
 *@return ȷʵ�������������򷵻��棬���򷵻ؼ�
 *@todo
 */
	bool ShrinkCheckPointVec(unsigned NumOfOriginCheckPoint);
	CDownParmAdjust m_ParmAdjust;///<����������
	std::vector<std::vector<float>> m_vStackOfAllDelayPointIndexByGun;///����ͻ��㣬��άvector����Ϊǹ�ţ���Ϊÿ��ǹ��Ӧ��ͻ���,�����ͻ���һ����ż����һ���ǿ�����һ��һ��
	std::vector<VectorType> m_vStackOfAllColorsIndexByGun;///����ͻ��㴦����ɫ����άvector����Ϊǹ�ţ���Ϊÿ��ǹ��Ӧ��ͻ��㴦����ɫ
};
