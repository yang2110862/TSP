#include "tabu.h"

/*
 *�������ܣ����·���ܳ���
 *��ʼ���ڣ�2020/7/13
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