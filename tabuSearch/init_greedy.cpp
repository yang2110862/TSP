#include "tabu.h"

/*
 *�������ܣ�ʹ��̰�ķ����TSP��Ϊ��ʼ·��
 *��ʼ���ڣ�2020/7/13
 */

void init_greedy()
{
    int f[1111] = { 0 }; //����ѷ��ʵĳ���,���㹻�������

    int sum = 0;//��¼·�̳���
    int num = 0;//��¼��i����
    f[0] = 1;
    int ed;
    initRoute[num++] = 0;
    int rm = cityNum - 1;  //����rm������δ����
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
    //cout << "��·����Ϊ" << sum; 
}

