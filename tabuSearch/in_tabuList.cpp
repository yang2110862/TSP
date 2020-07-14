#include "tabu.h"

/*
 *函数功能：判断tempRoute是否在tabulist里面
 *开始日期：2020/7/13
 */
bool in_tabuList(int* tempRoute)
{
    int flag = 0;
    for (int i = 0; i < tabuListLen; ++i) {
        flag = 0;
        for (int j = 0; j < cityNum; ++j) {
            if (tempRoute[j] != tabuList[i][j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0)   break;
    }
    if (flag == 0)   return true;        //表明tempRoute在tabuList里面；
    else return false;
}