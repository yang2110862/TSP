#include "tabu.h"

/*
 *�������ܣ��ж�tempLen�Ƿ���tabulist����
 *��ʼ���ڣ�2020/7/13
 *�ϴθ��£�2020/7/16
 *�������ݣ����ɱ��ɽ���·����Ϊ���ɳ���
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
    if (flag == 1)   return true;        //����tempLen��tabuList���棻
    else return false;
}