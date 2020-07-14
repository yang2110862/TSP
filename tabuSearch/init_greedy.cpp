#include "tabu.h"

/*
 *函数功能：使用贪心法求解TSP作为初始路径
 *开始日期：2020/7/13
 */

void init_greedy()
{
    int f[1111] = { 0 }; //标记已访问的城市,开足够大的数组

    int sum = 0;//记录路程长度
    int num = 0;//记录第i个点
    f[0] = 1;
    int ed;
    initRoute[num++] = 0;
    int rm = cityNum - 1;  //还有rm个城市未访问
    while (rm--) {
        int x = INT_MAX;
        int temp;
        for (int i = 0; i < cityNum; ++i) {
            if (f[i] == 1)   continue;
            temp = distanceMatri[initRoute[num - 1]][i];
            if (temp < x) {
                x = temp;
                ed = i;
            }
        }
        f[ed] = 1;
        initRoute[num++] = ed;
        sum += x;
        //cout << initRoute[num - 1] << ' ';
    }
    //cout << endl;
    sum += distanceMatri[ed][0];
    //cout << "总路径长为" << sum; 
}

