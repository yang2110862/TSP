#include "tabu.h"

/*
 *���½��ɱ�
 *��ʼ���ڣ�2020/7/16
 *�������ݣ����ɱ��ɽ���·����Ϊ����·������
 */

void pushTabuList(int localLen) {
    for (int i = 0; i < tabuListLen - 1; ++i) {       //ɾ�����ɱ��е�һ�����
        tabuList[i] = tabuList[i + 1];
    }
    tabuList[tabuListLen - 1] = localLen;
}