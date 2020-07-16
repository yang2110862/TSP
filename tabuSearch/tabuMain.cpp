#include "tabu.h"

/*
 *函数功能：使用禁忌搜索求解TSP
 *开始日期：2020/7/13
 *上次更新：2020/7/13
 *更新内容：
 */

int main(int argc, char** argv)
{
    init(argc, argv); //初始化参数
    time_t beg, end;
    beg = clock();
    solve(); //求解问题
    end = clock();
    double runTime = (double)(end - beg) / CLOCKS_PER_SEC;
    printResult(); //输出
    cout << "runTime: " << runTime << " seconds" << endl;
    system("pause");
    return 0;
}