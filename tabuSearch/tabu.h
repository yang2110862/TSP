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
extern int tabuListLen;    //���ɱ�
extern int maxRandNum;	   //�Ҵ��Ž�ʱ��������
extern int cityNum;        //��������
extern int bestValue;      //������������·�����ȣ�

extern int* tabuList;          //���ɱ�
extern int** distanceMatri;    //�������
extern int* initRoute;     //����·������
extern int* localRoute;    //�ֲ�·������
extern int* bestRoute;     //���·������
extern int* tempRoute;     //��ʱ·������
extern int localLen;       //�ֲ�·������
extern int tempLen;        //��ʱ·������
extern int bestLen;        //���·������

void init(int argc, char** argv);
void solve();
void init_greedy();
int costFunction(int* Route);
void findNeighbor(int* initRoute, int* localRoute);
bool in_tabuList(int tempLen);
void pushTabuList(int localLen);
void printResult();

