#include "StdAfx.h"
#include "Parm.h"

COLORREF gNULLCOLOR=RGB(255,255,255);///<��ɫ��Ӧ��RGB�����������ɫ
long gRowWidth;///<ÿ����Ϳ�еĿ�ȣ���λ���ر��븳ֵ
long gHeightOfEveryPaintCell;///<ÿ����Ϳ��Ԫ�ĸ߶ȣ���λ���أ����븳ֵ����ʵ��ʶ�����ʱ��û�а�����ߣ����ǰ�ʵ�ʸ߶����ģ�ת����Ԥ����С��Ϳ����ĳߴ�ʹ��߽粻���ڴ�����Ϳ��Ԫ
double gMMPerPixel=MM_PER_PIXEL;///<ÿһ���ض�ӦΪ����mm
bool gbOnePixelBetweenWorkReg=false;///<�ڹ�����֮�����һ�����ؿ�ȵļ��
enum AreaPartitionFlag geAreaPartitionFlag=GRID_PARTION_BY_INTELLIGENCE;///<��־λ��������Ԥ�Ȱ��̶����������С�ָ�������ͼΪ���ɸ��������䣻�����Զ�Ѱ�ң��ӵ�һ������Ϳ�ķ���λ��ʼ���л��֣��������ܻ��Զ�����(Ŀǰδ��)
enum CellSizePreRecFlag gCellSizePreRecFlag;///<��־λ�����ƶԵ�Ԫ�Ĳ���Ԥʶ��ʱ�����и��ӵ�ƽ�����㣬���Ǽ򵥵�ֱ��ȡ��Сֵ��

PaintAreaTemplate g_sPaintAreaParm;///<ȫ�ֱ���������������������Ĳ���
//const 
CRect_Work_Region g_cWorkRegionParm;///<���幤������Ĳ���