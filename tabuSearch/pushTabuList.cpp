#include "tabu.h"

/*
 *���½��ɱ�
 */

void pushTabuList(int* localRoute) {
    for (int i = 0; i < tabuListLen - 1; ++i) {       //ɾ�����ɱ��е�һ�����
        for (int j = 0; j < cityNum; ++j) {
            tabuList[i][j] = tabuList[i + 1][j];
        }
    }
    for (int i = 0; i < cityNum; ++i) {//�ڽ��ɱ��н�localRoute����
        tabuList[tabuListLen - 1][i] = localRoute[i];
    }
}