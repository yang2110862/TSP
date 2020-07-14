#include "tabu.h"

/*
 *函数功能：找邻居解
 *开始日期：2020/7/13
 *上次更新：
 *更新内容：
 */

void findNeighbor(int* initRoute, int* tempRoute)
{
    int ran1 = rand() % cityNum;
    int ran2 = rand() % cityNum;
    while (ran1 == 0)    ran1 = rand() % cityNum;
    while (ran2 == 0 || ran2 == ran1)    ran2 = rand() % cityNum;
    if (ran1 > ran2) swap(ran1, ran2);

    int ran3 = rand() % 3; //用3种方法来找邻居
    /*找局部最优解*/
    int len = costFunction(initRoute); //初始路径长度
    int flag = 0;//没有找到比最优解更好的解
    for (int i = 1; i < cityNum; ++i) {
        for (int j = i + 1; j < cityNum; ++j) {
            /*用swap找邻居*/
            memcpy(localTempRoute, initRoute, sizeof(int) * cityNum);
            swap(localTempRoute[i], localTempRoute[j]);
            localTempLen = costFunction(localTempRoute);
            if (localTempLen < len && !in_tabuList(localTempRoute)) {
                flag = 1;
                len = localTempLen;
                memcpy(tempRoute, localTempRoute, sizeof(int) * cityNum);
            }
            /*用reverse找邻居*/
            int sum = i + j;
            for (int k = 0; k < cityNum; ++k) {
                if (k >= i && k <= j) {
                    localTempRoute[k] = initRoute[sum - k];
                }
                else {
                    localTempRoute[k] = initRoute[k];
                }
            }
            localTempLen = costFunction(localTempRoute);
            if (localTempLen < len && !in_tabuList(localTempRoute)) {
                flag = 1;
                len = localTempLen;
                memcpy(tempRoute, localTempRoute, sizeof(int) * cityNum);
            }
            /*用replaceSegment找邻居*/
            int index = 0;
            for (int k = 0; k < i; ++k) {
                localTempRoute[index++] = initRoute[k];
            }
            for (int k = j + 1; k < cityNum; ++k) {
                localTempRoute[index++] = initRoute[k];
            }
            for (int k = i; k <= j; ++k) {
                localTempRoute[index++] = initRoute[k];
            }
            localTempLen = costFunction(localTempRoute);
            if (localTempLen < len && !in_tabuList(localTempRoute)) {
                flag = 1;
                len = localTempLen;
                memcpy(tempRoute, localTempRoute, sizeof(int) * cityNum);
            }
        }
    }
    /*没有找到比初始解更好的解，随机选取一断*/
    if (flag == 0) {
        if (ran3 == 0) {//swap(x,i, j): swap the element at index i in permutation x with element at index j
            memcpy(tempRoute, initRoute, sizeof(int) * cityNum);
            swap(tempRoute[ran1], tempRoute[ran2]);
        }
        else if (ran3 == 1) {//reverse(x,i, j): reverse the subsequence between indexes i and j in permutation x
            int sum = ran1 + ran2;
            for (int i = 0; i < cityNum; ++i) {
                if (i >= ran1 && i <= ran2) {
                    tempRoute[i] = initRoute[sum - i];
                }
                else {
                    tempRoute[i] = initRoute[i];
                }
            }
        }
        else {//随机交换一段距离
            int index = 0;
            for (int i = 0; i < ran1; i++) {
                tempRoute[index++] = initRoute[i];
            }
            for (int i = ran2 + 1; i < cityNum; i++) {
                tempRoute[index++] = initRoute[i];
            }
            for (int i = ran1; i <= ran2; i++) {
                tempRoute[index++] = initRoute[i];
            }
        }
    }
}