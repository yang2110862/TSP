#include "tabu.h"

/*
 *求解TSP问题
 */

void solve() {
    init_greedy();
    memcpy(bestRoute, initRoute, sizeof(int) * cityNum);
    bestLen = costFunction(bestRoute);

    /*迭代iterationNum次*/
    int n1 = 0;        //迭代次数
    time_t beg, end;  //for debug
    beg = clock(); //for debug
    while (n1 < iterationNum) {
        localLen = INT_MAX;
        tempLen = INT_MAX;
        findNeighbor(initRoute, localRoute);  //找到一个局部解
        localLen = costFunction(localRoute);
        if (localLen < bestLen) {  //最优解更新
            memcpy(bestRoute, localRoute, sizeof(int) * cityNum);
            bestLen = localLen;
        }
        end = clock(); //for debug
        double runTime = (double)(end - beg) / CLOCKS_PER_SEC; //for debug
        if(n1 % 10000 == 0)  cout << "iterationNum:" << n1 + 1 << "  localLen:" << localLen << "  bestLen : " << bestLen << "  runTime: " << runTime << " seconds" << endl;  //每1000次查看一下结果
        //cout << "iterationNum:" << n1 + 1 << "  localLen:" << localLen << "  bestLen : " << bestLen << "  runTime: " << runTime << " seconds" << endl;//just for debug
        if (bestLen == bestValue) { //48算例最优10628，532算例最优27686
            printResult();
            cout << "runTime: " << runTime << endl;
            cout << "iterationNum: " << n1 + 1;
            exit(1);
        }
        memcpy(initRoute, localRoute, sizeof(int) * cityNum); //将局部最优解赋值给初始解进行下一次迭代，结果变差也继续进行；
        pushTabuList(localLen);     //将局部最优解存入禁忌表；
        ++n1;
    }
}

