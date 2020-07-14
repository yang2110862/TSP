#include "tabu.h"

/*
 *求解TSP问题
 */
void solve() {
    init_greedy();
    memcpy(bestRoute, initRoute, sizeof(int) * cityNum);
    bestLen = costFunction(bestRoute);

    //cout << bestLen;           //可输出贪心解的距离

    /*迭代iterationNum次*/
    int n1 = 0;        //迭代次数
    time_t beg, end;  //for debug
    beg = clock(); //for debug
    while (n1 < iterationNum) {
        localLen = INT_MAX;
        tempLen = INT_MAX;
        findNeighbor(initRoute, tempRoute);  //找到一个邻居解
        memcpy(localRoute, tempRoute, sizeof(int) * cityNum);
        tempLen = costFunction(tempRoute);
        localLen = tempLen;

        if (localLen < bestLen) {  //最优解更新
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
        memcpy(initRoute, localRoute, sizeof(int) * cityNum); //将局部最优解赋值给初始解进行下一次迭代，结果变差也继续进行；
        pushTabuList(localRoute);     //将局部最优解存入紧急表；
        ++n1;
    }
}

