#include "tabu.h"

/*
 *函数功能：打印路径
 *开始日期：2020/7/13
 */

void printResult()
{
	fstream fout("answerOut.txt", ios::out);
	fout << filename << " result:" << endl;
	cout << "最佳路径长度： " << bestLen << endl;
	fout << "最佳路径长度： " << bestLen << endl;
	cout << "最佳路径：" << endl;
	fout << "最佳路径：" << endl;
	for (int i = 0; i < cityNum; i++) {          //存储时把第一座城市标记成0，输出时+1
		cout << bestRoute[i] + 1 << "->";
		fout << bestRoute[i] + 1 << "->";
	}
	cout << bestRoute[0] + 1 << endl;
	fout << bestRoute[0] + 1 << endl;
	fout.close();
}