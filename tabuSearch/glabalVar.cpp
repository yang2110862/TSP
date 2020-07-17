#include<iostream>
#include<string>
using namespace std;

/*
 *文件功能：存放全局变量
 *开始日期：2020/7/13
 *上次更新  2020/7/17
 *更新内容	增加一些参数，maxRandNum和bestValue
 */

string filename;    //文件名
int iterationNum;   //迭代次数
int tabuListLen;    //禁忌表长
int maxRandNum;		//找次优解时最大随机数
int cityNum;        //城市数量
int bestValue;      //该算例下最优路径长度；

int* tabuList;          //禁忌表
int** distanceMatri;    //距离矩阵
int* initRoute;     //初试路径编码
int* localRoute;    //局部路径编码
int* bestRoute;     //最佳路径编码
int* tempRoute;     //暂时路径编码
int localLen;       //局部路径长度
int tempLen;        //暂时路径长度
int bestLen;        //最好路径长度