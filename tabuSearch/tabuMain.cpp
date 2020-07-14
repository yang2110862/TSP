#include "tabu.h"

/*
 *�������ܣ�ʹ�ý����������TSP
 *��ʼ���ڣ�2020/7/13
 *�ϴθ��£�2020/7/13
 *�������ݣ�
 */

int main(int argc, char** argv)
{
    init(argc, argv); //��ʼ������
    time_t beg, end;
    beg = clock();
    solve(); //�������
    end = clock();
    double runTime = (double)(end - beg) / CLOCKS_PER_SEC;
    printResult(); //���
    cout << "runTime: " << runTime << " seconds" << endl;
    system("pause");
    return 0;
}