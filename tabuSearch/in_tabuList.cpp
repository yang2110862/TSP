#include "tabu.h"

/*
 *�������ܣ��ж�tempRoute�Ƿ���tabulist����
 *��ʼ���ڣ�2020/7/13
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
    if (flag == 0)   return true;        //����tempRoute��tabuList���棻
    else return false;
}