#include "tabu.h"

/*
 *更新禁忌表
 *开始日期：2020/7/16
 *更新内容：禁忌表由禁忌路径改为禁忌路径长度
 */

void pushTabuList(int localLen) {
    for (int i = 0; i < tabuListLen - 1; ++i) {       //删除禁忌表中第一组编码
        tabuList[i] = tabuList[i + 1];
    }
    tabuList[tabuListLen - 1] = localLen;
}