#include "tabu.h"

/*
 *�������ܣ���������ʼ��
 *��ʼ���ڣ�2020/7/13
 *�������ڣ�2020/7/16
 *�������ݣ����϶Խ��ɱ�ĳ�ʼ��
 */

void init(int argc, char** argv)
{
    filename = (argc >= 2) ? (string)argv[1] : "att48.txt";
    int textMode = (argc >= 3) ? atoi(argv[2]) : 0;   //�ж϶����ı��ĸ�ʽ����textMode == 0 ������������㣬��textMode == 1��������Ǿ������
    iterationNum = (argc >= 4) ? atoi(argv[3]) : 20000;
    tabuListLen = (argc >= 6) ? atoi(argv[4]) : 20;

    fstream fin(filename, ios::in); //���ļ�
    if (!fin.is_open()) {
        cerr << "can not open the file " << filename << endl;
        exit(0);
    }
    fin >> cityNum;
    //�������������ռ�
    distanceMatri = new int* [cityNum];
    for (int i = 0; i < cityNum; ++i)
        distanceMatri[i] = new int[cityNum];
    //�����ı����ݣ����������ֵ
    int num;
    if (textMode == 0) {
        double* x, * y;
        x = new double[cityNum];
        y = new double[cityNum];
        for (int i = 0; i < cityNum; ++i)
            fin >> num >> x[i] >> y[i];
        for (int i = 0; i < cityNum; ++i) {
            distanceMatri[i][i] = 0;
            for (int j = i + 1; j < cityNum; ++j) {
                distanceMatri[i][j] = distanceMatri[j][i] = ceil(sqrt(pow(x[i] - x[j], 2) / 10 + pow(y[i] - y[j], 2) / 10));//�����������룻
            }
        }
        delete[] x;
        delete[] y;
    }
    else if (textMode == 1) {
        for (int i = 0; i < cityNum; ++i) {
            for (int j = 0; j < cityNum; ++j)
                fin >> distanceMatri[i][j];
        }
    }
    else {
        cerr << "mode error" << endl;
    }
    //����ռ�,��ʼ��·������Ϊ�����
    initRoute = new int[cityNum];       //·�������������ַ�ֱ�������ͷ��β���·������λ����������߶ν���
    localRoute = new int[cityNum];
    bestRoute = new int[cityNum];
    tempRoute = new int[cityNum];
    tabuList = new int[tabuListLen];
    for (int i = 0; i < tabuListLen; ++i)    tabuList[i] = 0;   //�Խ��ɱ��ʼ��
    localLen = INT_MAX;
    bestLen = INT_MAX;
    tempLen = INT_MAX;

    srand((unsigned int)time(0));//�������������
}