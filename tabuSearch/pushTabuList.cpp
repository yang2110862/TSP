#include "tabu.h"

/*
 *更新禁忌表
 */

void pushTabuList(int* localRoute) {
    for (int i = 0; i < tabuListLen - 1; ++i) {       //删除禁忌表中第一组编码
        for (int j = 0; j < cityNum; ++j) {
            tabuList[i][j] = tabuList[i + 1][j];
        }
    }
    for (int i = 0; i < cityNum; ++i) {//在禁忌表中将localRoute插入
        tabuList[tabuListLen - 1][i] = localRoute[i];
    }
}