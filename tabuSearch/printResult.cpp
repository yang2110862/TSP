#include "tabu.h"

/*
 *�������ܣ���ӡ·��
 *��ʼ���ڣ�2020/7/13
 */

void printResult()
{
	fstream fout("answerOut.txt", ios::out);
	fout << filename << " result:" << endl;
	cout << "���·�����ȣ� " << bestLen << endl;
	fout << "���·�����ȣ� " << bestLen << endl;
	cout << "���·����" << endl;
	fout << "���·����" << endl;
	for (int i = 0; i < cityNum; i++) {          //�洢ʱ�ѵ�һ�����б�ǳ�0�����ʱ+1
		cout << bestRoute[i] + 1 << "->";
		fout << bestRoute[i] + 1 << "->";
	}
	cout << bestRoute[0] + 1 << endl;
	fout << bestRoute[0] + 1 << endl;
	fout.close();
}