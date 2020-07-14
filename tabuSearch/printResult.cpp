#include "tabu.h"

/*
 *函数功能：打印路径
 *开始日期：2020/7/13
 */

void printResult()
{
	fstream fout("TSP_AnswerOut.txt", ios::out);
	fout << filename << " result:" << endl;
	cout << "最佳路径长度： " << bestLen << endl;
	fout << "最佳路径长度： " << bestLen << endl;
	cout << "最佳路径：" << endl;
	fout << "最佳路径：" << endl;
	for (int i = 0; i < cityNum; i++) {
		cout << bestRoute[i] + 1 << "->";
		fout << bestRoute[i] + 1 << "->";
	}
	cout << 1 << endl;
	fout << 1 << endl;
	fout.close();
}