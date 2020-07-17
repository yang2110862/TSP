#include "tabu.h"

/*
 *���TSP����
 */

void solve() {
    init_greedy();
    memcpy(bestRoute, initRoute, sizeof(int) * cityNum);
    bestLen = costFunction(bestRoute);

    /*����iterationNum��*/
    int n1 = 0;        //��������
    time_t beg, end;  //for debug
    beg = clock(); //for debug
    while (n1 < iterationNum) {
        localLen = INT_MAX;
        tempLen = INT_MAX;
        findNeighbor(initRoute, localRoute);  //�ҵ�һ���ֲ���
        localLen = costFunction(localRoute);
        if (localLen < bestLen) {  //���Ž����
            memcpy(bestRoute, localRoute, sizeof(int) * cityNum);
            bestLen = localLen;
        }
        end = clock(); //for debug
        double runTime = (double)(end - beg) / CLOCKS_PER_SEC; //for debug
        if(n1 % 10000 == 0)  cout << "iterationNum:" << n1 + 1 << "  localLen:" << localLen << "  bestLen : " << bestLen << "  runTime: " << runTime << " seconds" << endl;  //ÿ1000�β鿴һ�½��
        //cout << "iterationNum:" << n1 + 1 << "  localLen:" << localLen << "  bestLen : " << bestLen << "  runTime: " << runTime << " seconds" << endl;//just for debug
        if (bestLen == bestValue) { //48��������10628��532��������27686
            printResult();
            cout << "runTime: " << runTime << endl;
            cout << "iterationNum: " << n1 + 1;
            exit(1);
        }
        memcpy(initRoute, localRoute, sizeof(int) * cityNum); //���ֲ����Ž⸳ֵ����ʼ�������һ�ε�����������Ҳ�������У�
        pushTabuList(localLen);     //���ֲ����Ž������ɱ�
        ++n1;
    }
}

