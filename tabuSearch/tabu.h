#pragma once

/*
 *声明全局变
 量和函数
 */
#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
#include<cmath>
#include<cstdlib>
using namespace std;

extern string filename;    //文件名
extern int iterationNum;   //迭代次数
//int neighborNum;    //邻居数量
extern int tabuListLen;    //紧急表长
extern int cityNum;        //城市数量

extern int** tabuList;          //禁忌表
extern int** distanceMatri;    //距离矩阵
extern int* initRoute;     //初试路径编码
extern int* localRoute;    //局部路径编码
extern int* bestRoute;     //最佳路径编码
extern int* tempRoute;     //暂时路径编码
extern int localLen;       //局部路径长度
extern int tempLen;        //暂时路径长度
extern int bestLen;        //最好路径长度

extern int* localTempRoute;     //局部暂时路径
extern int localTempLen;        //局部暂时路径长度

void init(int argc, char** argv);
void solve();
void init_greedy();
int costFunction(int* Route);
void findNeighbor(int* initRoute, int* localRoute);
bool in_tabuList(int* tempRoute);
void pushTabuList(int* localRoute);
void printResult();

