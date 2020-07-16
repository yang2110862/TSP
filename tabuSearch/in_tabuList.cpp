#include "tabu.h"

/*
 *函数功能：判断tempLen是否在tabulist里面
 *开始日期：2020/7/13
 *上次更新：2020/7/16
 *更新内容：禁忌表由禁忌路径改为禁忌长度
 */
bool in_tabuList(int tempLen)
{
    int flag = 0;
    for (int i = 0; i < tabuListLen; ++i) {
        if (tempLen == tabuList[i]) {
            flag = 1;
            break;
        }
    }
    if (flag == 1)   return true;        //表明tempLen在tabuList里面；
    else return false;
}