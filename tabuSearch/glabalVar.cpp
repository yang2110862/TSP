#include<iostream>
#include<string>
using namespace std;

/*
 *�ļ����ܣ����ȫ�ֱ���
 *��ʼ���ڣ�2020/7/13
 */

string filename;    //�ļ���
int iterationNum;   //��������
//int neighborNum;    //�ھ�����
int tabuListLen;    //������
int cityNum;        //��������

int** tabuList;          //���ɱ�
int** distanceMatri;    //�������
int* initRoute;     //����·������
int* localRoute;    //�ֲ�·������
int* bestRoute;     //���·������
int* tempRoute;     //��ʱ·������
int localLen;       //�ֲ�·������
int tempLen;        //��ʱ·������
int bestLen;        //���·������

int* localTempRoute;     //�ֲ���ʱ·��
int localTempLen;        //�ֲ���ʱ·������