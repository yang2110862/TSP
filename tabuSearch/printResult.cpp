#include "tabu.h"

/*
 *�������ܣ���ӡ·��
 *��ʼ���ڣ�2020/7/13
 */

void printResult()
{
	fstream fout("TSP_AnswerOut.txt", ios::out);
	fout << filename << " result:" << endl;
	cout << "���·�����ȣ� " << bestLen << endl;
	fout << "���·�����ȣ� " << bestLen << endl;
	cout << "���·����" << endl;
	fout << "���·����" << endl;
	for (int i = 0; i < cityNum; i++) {
		cout << bestRoute[i] + 1 << "->";
		fout << bestRoute[i] + 1 << "->";
	}
	cout << 1 << endl;
	fout << 1 << endl;
	fout.close();
}