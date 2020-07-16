#include "tabu.h"

/*
 *函数功能：求解路径总长度
 *开始日期：2020/7/13
 */

int costFunction(int* Route)
{
    int sum = 0;
    for (int i = 0; i < cityNum - 1; ++i) {
        sum += distanceMatri[Route[i]][Route[i + 1]];
    }
    sum += distanceMatri[Route[cityNum - 1]][Route[0]];
    return sum;
}