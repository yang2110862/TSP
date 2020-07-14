#pragma once

/*
 *����ȫ�ֱ�
 ���ͺ���
 */
#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
#include<cmath>
#include<cstdlib>
using namespace std;

extern string filename;    //�ļ���
extern int iterationNum;   //��������
//int neighborNum;    //�ھ�����
extern int tabuListLen;    //������
extern int cityNum;        //��������

extern int** tabuList;          //���ɱ�
extern int** distanceMatri;    //�������
extern int* initRoute;     //����·������
extern int* localRoute;    //�ֲ�·������
extern int* bestRoute;     //���·������
extern int* tempRoute;     //��ʱ·������
extern int localLen;       //�ֲ�·������
extern int tempLen;        //��ʱ·������
extern int bestLen;        //���·������

extern int* localTempRoute;     //�ֲ���ʱ·��
extern int localTempLen;        //�ֲ���ʱ·������

void init(int argc, char** argv);
void solve();
void init_greedy();
int costFunction(int* Route);
void findNeighbor(int* initRoute, int* localRoute);
bool in_tabuList(int* tempRoute);
void pushTabuList(int* localRoute);
void printResult();

