#include "tabu.h"

/*
 *函数功能：将参数初始化
 *开始日期：2020/7/13
 *更新日期：2020/7/16
 *更新内容：加上对禁忌表的初始化
 */

void init(int argc, char** argv)
{
    filename = (argc >= 2) ? (string)argv[1] : "att48.txt";
    int textMode = (argc >= 3) ? atoi(argv[2]) : 0;   //判断读入文本的格式，若textMode == 0 则读入的是坐标点，若textMode == 1，读入的是距离矩阵
    iterationNum = (argc >= 4) ? atoi(argv[3]) : 20000;
    tabuListLen = (argc >= 6) ? atoi(argv[4]) : 20;

    fstream fin(filename, ios::in); //打开文件
    if (!fin.is_open()) {
        cerr << "can not open the file " << filename << endl;
        exit(0);
    }
    fin >> cityNum;
    //给距离矩阵申请空间
    distanceMatri = new int* [cityNum];
    for (int i = 0; i < cityNum; ++i)
        distanceMatri[i] = new int[cityNum];
    //读入文本数据，给距离矩阵赋值
    int num;
    if (textMode == 0) {
        double* x, * y;
        x = new double[cityNum];
        y = new double[cityNum];
        for (int i = 0; i < cityNum; ++i)
            fin >> num >> x[i] >> y[i];
        for (int i = 0; i < cityNum; ++i) {
            distanceMatri[i][i] = 0;
            for (int j = i + 1; j < cityNum; ++j) {
                distanceMatri[i][j] = distanceMatri[j][i] = ceil(sqrt(pow(x[i] - x[j], 2) / 10 + pow(y[i] - y[j], 2) / 10));//考虑四舍五入；
            }
        }
        delete[] x;
        delete[] y;
    }
    else if (textMode == 1) {
        for (int i = 0; i < cityNum; ++i) {
            for (int j = 0; j < cityNum; ++j)
                fin >> distanceMatri[i][j];
        }
    }
    else {
        cerr << "mode error" << endl;
    }
    //申请空间,初始化路径长度为无穷大
    initRoute = new int[cityNum];       //路径数组多两个地址分别在数组头和尾存放路径的首位，方便进行线段交换
    localRoute = new int[cityNum];
    bestRoute = new int[cityNum];
    tempRoute = new int[cityNum];
    tabuList = new int[tabuListLen];
    for (int i = 0; i < tabuListLen; ++i)    tabuList[i] = 0;   //对禁忌表初始化
    localLen = INT_MAX;
    bestLen = INT_MAX;
    tempLen = INT_MAX;

    srand((unsigned int)time(0));//设置随机数种子
}