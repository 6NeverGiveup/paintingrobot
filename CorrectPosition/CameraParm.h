#include "stdafx.h"
//��ǹ�����Ϳ��ΧΪ1250*1900
//ÿ��������ϵ��
//ע�⣬������ص��������������겻һ��
//��һ�����������Ҫ��һ��
#define FIRSTCAMERAXAXISWIDTH 1288
#define FIRSTCAMERAYAXISHEIGHT 964
#define SECONDCAMERAXAXISWIDTH 1288
#define SECONDCAMERAYAXISHEIGHT 964
#define FIRSTEVERYPIXELTOEVERYCENTIMETREX 0.411490683   //��һ�������X����һ�����ص��ڶ��ٸ�����
#define FIRSTEVERYPIXELTOEVERYCENTIMETREY 0.399377593   //��һ�������Y����һ�����ص��ڶ��ٸ�����
#define SECONDEVERYPIXELTOEVERYCENTIMETREX 0.489130435   //�ڶ��������X����һ�����ص��ڶ��ٸ�����
#define SECONDEVERYPIXELTOEVERYCENTIMETREY 0.487551867   //�ڶ��������Y����һ�����ص��ڶ��ٸ�����
#define DISTANCEBETWEENCAMERA 170 //���������X��֮���������İ�װ����
//���ڵ�һ�������˵��������ϵͳ��ռ�ݷǳ���Ҫ�����ã�������Ҫȷ���ڵ�ǰλ�ã���ǹ������λ�ã�
//һ������FIRSTCAMERAXORIGINPOINTΪ�ڵ�ǰ����ϵ�е�һ������İ�װλ�ã�X���꣬FIRSTCAMERAYORIGINPOINTΪY���꣬Ҫ��֤�����װ�����뵱ǰ����ϵƽ��

#define FIRSTCAMERAXORIGINPOINT 340
#define FIRSTCAMERAYORIGINPOINT 1230            //��λ���ף������������λ
//�ڶ�������ڵ�ǰ����ϵ�е�λ��
#define SECONDCAMERAXORIGINPOINT 1845               //��λ���ף������������λ
#define SECONDCAMERAYORIGINPOINT 1250
//����Ϳ�����У�ʵ��Ҫ����ͷ���Ķ�׼����Ϳ�ĵ�һ����Ԫ��������λ��������ǹ���������в��
#define FRAMEX 160
#define FRAMEY 10