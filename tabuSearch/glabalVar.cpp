#include<iostream>
#include<string>
using namespace std;

/*
 *文件功能：存放全局变量
 *开始日期：2020/7/13
 */

string filename;    //文件名
int iterationNum;   //迭代次数
//int neighborNum;    //邻居数量
int tabuListLen;    //紧急表长
int cityNum;        //城市数量

int** tabuList;          //禁忌表
int** distanceMatri;    //距离矩阵
int* initRoute;     //初试路径编码
int* localRoute;    //局部路径编码
int* bestRoute;     //最佳路径编码
int* tempRoute;     //暂时路径编码
int localLen;       //局部路径长度
int tempLen;        //暂时路径长度
int bestLen;        //最好路径长度

int* localTempRoute;     //局部暂时路径
int localTempLen;        //局部暂时路径长度