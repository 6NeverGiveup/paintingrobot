#pragma once
/*!
 * \class CPTCameraUsing
 *
 * \brief ��scPTGrab2���������������Ҫ�ĳ�ʼ���������
 *
 * \author admin
 * \date ���� 2015
 */
#include "svptgrab2.h"
class CPTCameraUsing :
	public scPTGrab2
{
public:
	CPTCameraUsing(void);
	~CPTCameraUsing(void);
public:

	bool  InitCameraSetting(void);///<������������ظ�ʽΪBGR
};

