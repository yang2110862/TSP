#include<iostream>
#include<string>
using namespace std;

/*
 *�ļ����ܣ����ȫ�ֱ���
 *��ʼ���ڣ�2020/7/13
 *�ϴθ���  2020/7/17
 *��������	����һЩ������maxRandNum��bestValue
 */

string filename;    //�ļ���
int iterationNum;   //��������
int tabuListLen;    //���ɱ�
int maxRandNum;		//�Ҵ��Ž�ʱ��������
int cityNum;        //��������
int bestValue;      //������������·�����ȣ�

int* tabuList;          //���ɱ�
int** distanceMatri;    //�������
int* initRoute;     //����·������
int* localRoute;    //�ֲ�·������
int* bestRoute;     //���·������
int* tempRoute;     //��ʱ·������
int localLen;       //�ֲ�·������
int tempLen;        //��ʱ·������
int bestLen;        //���·������