#include "tabu.h"

/*
 *���TSP����
 */
void solve() {
    init_greedy();
    memcpy(bestRoute, initRoute, sizeof(int) * cityNum);
    bestLen = costFunction(bestRoute);

    //cout << bestLen;           //�����̰�Ľ�ľ���

    /*����iterationNum��*/
    int n1 = 0;        //��������
    time_t beg, end;  //for debug
    beg = clock(); //for debug
    while (n1 < iterationNum) {
        localLen = INT_MAX;
        tempLen = INT_MAX;
        findNeighbor(initRoute, tempRoute);  //�ҵ�һ���ھӽ�
        memcpy(localRoute, tempRoute, sizeof(int) * cityNum);
        tempLen = costFunction(tempRoute);
        localLen = tempLen;

        if (localLen < bestLen) {  //���Ž����
            memcpy(bestRoute, localRoute, sizeof(int) * cityNum);
            bestLen = localLen;
        }

        end = clock(); //for debug
        double runTime = (double)(end - beg) / CLOCKS_PER_SEC; //for debug
        cout << "iterationNum:" << n1 + 1 << "  localLen:" << localLen << "  bestLen : " << bestLen << "  runTime: " << runTime << " seconds" << endl;//just for debug
        if (bestLen == 10628) {
            printResult();
            exit(1);
        }
        memcpy(initRoute, localRoute, sizeof(int) * cityNum); //���ֲ����Ž⸳ֵ����ʼ�������һ�ε�����������Ҳ�������У�
        pushTabuList(localRoute);     //���ֲ����Ž���������
        ++n1;
    }
}

