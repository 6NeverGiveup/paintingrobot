#pragma once
/**
*���ֶ������ѧ���㣬Ŀǰ����������������
*/
#define ONEHALF 0.5
static long Floor4_Ceil5(float NumTobeOperate)
{
	return long(NumTobeOperate+0.5);
}
static int Floor4_Ceil5Float(int Business,int Denominator)              //�������룬����0.5����1��С��0.5������0
{
	float Result=(float)Business/Denominator;
	if (Result>=ONEHALF)
	{
		return 1;
	}
	else
		return 0;
}