#pragma once
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include "Parm.h"
/*!
 * \file DownParmValueHead.h
 *
 * \author gy
 * \date ʮ���� 2017
 *
 * ���ļ�����DownParmValue,DownParmAdjust��Ҫ�õ���һЩ�������͵�����
 */
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
	void operator()(const int X, const float Y){
		XPoint=X;
		YPoint=Y;
	}

};
typedef std::vector<CornerPoint> VectorTypePoint;
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