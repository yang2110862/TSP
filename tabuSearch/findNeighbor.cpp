#include "tabu.h"
#include<stack>
/*
 *函数功能：找邻居解
 *开始日期：2020/7/13
 *上次更新：2020/7/16
 *更新内容：用7种找邻居的方法，并优化
 */

struct record {       //每次迭代时，当没有找到更优解时，记录次优解的求解类型；
    int first;
    int second;
    int type;
};

void findNeighbor(int* initRoute, int* localRoute)
{
    stack<record> candidate;    //存放次优解

    /*找局部最优解*/
    int len = costFunction(initRoute); //初始路径长度
    int temp; //存放delta的暂时值
    int delta = INT_MAX;//存放新路径相较初始路径的差值

    /*7种找邻居的type，特别注意i = 0，j = cityNum - 1以及i，j相邻的特殊情况*/
    for (int i = 0; i < cityNum - 1; ++i) {
        for (int j = i + 1; j < cityNum; ++j) {
            record rrd;//记录找到暂时路径的i，j和type
            int add1, add2, add3, add4;      //记录增加边长,最多4-opt move
            int delete1, delete2, delete3, delete4;        //记录删除边长

            /* swap(x,i,j): swap the element at index i in permutation x with 
            element at index j, possible 4-opt move */
            /*  x = (A,B,C,D,E,F,G,H,I), swap(x, 3, 7) = (A,B,G,D,E,F,C,H,I)    */
            if (i == 0 && j == cityNum - 1) {
                add1 = 0;
                add2 = distanceMatri[initRoute[j]][initRoute[i + 1]];
                add3 = distanceMatri[initRoute[j - 1]][initRoute[i]];
                add4 = 0;
                delete1 = 0;
                delete2 = distanceMatri[initRoute[i]][initRoute[i + 1]];
                delete3 = distanceMatri[initRoute[j - 1]][initRoute[j]];
                delete4 = 0;
            }
            else {
                add1 = (i == 0) ? distanceMatri[initRoute[cityNum - 1]][initRoute[j]] : distanceMatri[initRoute[i - 1]][initRoute[j]];
                add2 = (i == j - 1) ? 0 : distanceMatri[initRoute[j]][initRoute[i + 1]];
                add3 = (i == j - 1) ? 0 : distanceMatri[initRoute[j - 1]][initRoute[i]];
                add4 = (j == cityNum - 1) ? distanceMatri[initRoute[i]][initRoute[0]] : distanceMatri[initRoute[i]][initRoute[j + 1]];
                delete1 = (i == 0) ? distanceMatri[initRoute[cityNum - 1]][initRoute[i]] : distanceMatri[initRoute[i - 1]][initRoute[i]];
                delete2 = (i == j - 1) ? 0 : distanceMatri[initRoute[i]][initRoute[i + 1]];
                delete3 = (i == j - 1) ? 0 : distanceMatri[initRoute[j - 1]][initRoute[j]];
                delete4 = (j == cityNum - 1) ? distanceMatri[initRoute[j]][initRoute[0]] : distanceMatri[initRoute[j]][initRoute[j + 1]];
            }
            temp = add1 + add2 + add3 + add4 - delete1 - delete2 - delete3 - delete4;
            if (temp < delta) {
                memcpy(tempRoute, initRoute, sizeof(int) * (cityNum));
                swap(tempRoute[i], tempRoute[j]);
                tempLen = costFunction(tempRoute);
                if ((len + temp) != tempLen) cout << "type1 error,i = " << i << ", j = "<< j << endl;
                if (!in_tabuList(tempLen)) {//判断是否在禁忌表中
                    delta = temp;//更新delta值
                    rrd.first = i;
                    rrd.second = j;
                    rrd.type = 1;
                    candidate.push(rrd);//存放候选解
                }
            }

            /* Two ways to reverse(x, i, j) : reverse the subsequence between indexes i and
            j in permutation x，Possible 2-opt move */
            /*  x = (A,B,C,D,E,F,G,H,I), reverse1(x, 3, 7) = (A,B,G,F,E,D,C,H,I) */
            if (i == 0 && j == cityNum - 1) {
                add1 = add2 = delete1 = delete2 = 0;
            }
            else {
                add1 = (i == 0) ? distanceMatri[initRoute[cityNum - 1]][initRoute[j]] : distanceMatri[initRoute[i - 1]][initRoute[j]];
                add2 = (j == cityNum - 1) ? distanceMatri[initRoute[i]][initRoute[0]] : distanceMatri[initRoute[i]][initRoute[j + 1]];
                delete1 = (i == 0) ? distanceMatri[initRoute[cityNum - 1]][initRoute[i]] : distanceMatri[initRoute[i - 1]][initRoute[i]];
                delete2 = (j == cityNum - 1) ? distanceMatri[initRoute[j]][initRoute[0]] : distanceMatri[initRoute[j]][initRoute[j + 1]];
            }
            temp = add1 + add2 - delete1 - delete2;
            if (temp < delta) {
                int sum = i + j;
                for (int k = 0; k < cityNum; ++k) {
                    if (k >= i && k <= j) {
                        tempRoute[k] = initRoute[sum - k];
                    }
                    else {
                        tempRoute[k] = initRoute[k];
                    }
                }
                tempLen = costFunction(tempRoute);
                if ((len + temp) != tempLen) cout << "type2 error,i = " << i << ", j = " << j << endl;
                if (!in_tabuList(tempLen)) {//判断是否在禁忌表中
                    delta = temp;//更新delta值
                    rrd.first = i;
                    rrd.second = j;
                    rrd.type = 2;
                    candidate.push(rrd);//存放候选解
                }
            }

            /*  x = (A,B,C,D,E,F,G,H,I), reverse2(x, 3, 7) = (I,H,G,D,E,F,C,B,A) */
            add1 = (i == j - 1) ? 0 : distanceMatri[initRoute[j]][initRoute[i + 1]];
            add2 = (i == j - 1) ? 0 : distanceMatri[initRoute[j - 1]][initRoute[i]];
            delete1 = (i == j - 1) ? 0 : distanceMatri[initRoute[i]][initRoute[i + 1]];
            delete2 = (i == j - 1) ? 0 : distanceMatri[initRoute[j - 1]][initRoute[j]];
            temp = add1 + add2 - delete1 - delete2;
            if (temp < delta) {
                int sum = i + j;
                int num = 0;
                for (int k = cityNum - 1; k >= j; --k)  tempRoute[num++] = initRoute[k];
                for (int k = i + 1; k > i && k < j; ++k)  tempRoute[num++] = initRoute[k];
                for (int k = i; k >= 0; k--)  tempRoute[num++] = initRoute[k];
                tempLen = costFunction(tempRoute);
                if ((len + temp) != tempLen) cout << "type3 error,i = " << i << ", j = " << j << endl;
                if (!in_tabuList(tempLen)) {//判断是否在禁忌表中
                    delta = temp;//更新delta值
                    rrd.first = i;
                    rrd.second = j;
                    rrd.type = 3;
                    candidate.push(rrd);//存放候选解
                }
            }

            /*rotateLeft(x,i, j): Two ways to rotate the subsequence between indexes i and
            j in permutation x one step to the left，Possible 3-opt move*/
            /* (A,B,C,D,E,F,G,H,I)， rotateLeft1(x, 3, 7) = (A,B,D,E,F,G,C,H,I) */
            if (i == 0 && j == cityNum - 1) {

            }
            if (i == 0 && j == cityNum - 1) {
                add1 = add2 = add3 = delete1 = delete2 = delete3 = 0;
            }
            else {
                add1 = (i == 0) ? distanceMatri[initRoute[cityNum - 1]][initRoute[i + 1]] : distanceMatri[initRoute[i - 1]][initRoute[i + 1]];
                add2 = (i == j - 1) ? 0 : distanceMatri[initRoute[j]][initRoute[i]];
                add3 = (j == cityNum - 1) ? distanceMatri[initRoute[i]][initRoute[0]] : distanceMatri[initRoute[i]][initRoute[j + 1]];
                delete1 = (i == 0) ? distanceMatri[initRoute[cityNum - 1]][initRoute[i]] : distanceMatri[initRoute[i - 1]][initRoute[i]];
                delete2 = (i == j - 1) ? 0 : distanceMatri[initRoute[i]][initRoute[i + 1]];
                delete3 = (j == cityNum - 1) ? distanceMatri[initRoute[j]][initRoute[0]] : distanceMatri[initRoute[j]][initRoute[j + 1]];
            }
            temp = add1 + add2 + add3 - delete1 - delete2 - delete3;
            if (temp < delta) {
                int num = 0;
                for (int k = 0; k < i; ++k)  tempRoute[num++] = initRoute[k];
                for (int k = i + 1; k <= j; ++k) tempRoute[num++] = initRoute[k];
                tempRoute[num++] = initRoute[i];
                for (int k = j + 1; k < cityNum; ++k)  tempRoute[num++] = initRoute[k];
                tempLen = costFunction(tempRoute);
                if ((len + temp) != tempLen) cout << "type4 error,i = " << i << ", j = " << j << endl;
                if (!in_tabuList(tempLen)) {//判断是否在禁忌表中
                    delta = temp;//更新delta值
                    rrd.first = i;
                    rrd.second = j;
                    rrd.type = 4;
                    candidate.push(rrd);//存放候选解
                }
            }

            /* x = (A,B,C,D,E,F,G,H,I), rotateLeft2(x, 3, 7) = (A,B,C,G,D,E,F,H,I) */
            add1 = (i == j - 1) ? 0 : distanceMatri[initRoute[i]][initRoute[j]];
            add2 = (i == j - 1) ? 0 : distanceMatri[initRoute[j]][initRoute[i + 1]];
            add3 = (i == j - 1) ? 0 : (j == cityNum - 1) ? distanceMatri[initRoute[j - 1]][initRoute[0]] : distanceMatri[initRoute[j - 1]][initRoute[j + 1]];
            delete1 = (i == j - 1) ? 0 : distanceMatri[initRoute[i]][initRoute[i + 1]];
            delete2 = (i == j - 1) ? 0 : distanceMatri[initRoute[j - 1]][initRoute[j]];
            delete3 = (i == j - 1) ? 0 : (j == cityNum - 1) ? distanceMatri[initRoute[j]][initRoute[0]] : distanceMatri[initRoute[j]][initRoute[j + 1]];
            temp = add1 + add2 + add3 - delete1 - delete2 - delete3;
            if (temp < delta) {
                int num = 0;
                for (int k = 0; k <= i; ++k)  tempRoute[num++] = initRoute[k];
                tempRoute[num++] = initRoute[j];
                for (int k = i + 1; k < j; ++k) tempRoute[num++] = initRoute[k];
                for (int k = j + 1; k < cityNum; ++k)  tempRoute[num++] = initRoute[k];
                tempLen = costFunction(tempRoute);
                if ((len + temp) != tempLen) cout << "type4 error,i = " << i << ", j = " << j << endl;
                if (!in_tabuList(tempLen)) {//判断是否在禁忌表中
                    delta = temp;//更新delta值
                    rrd.first = i;
                    rrd.second = j;
                    rrd.type = 5;
                    candidate.push(rrd);//存放候选解
                }
            }

            /* rotateRight(x,i, j): rotate the subsequence between indexes i and 
            j in permutation x one step to the right,Possible 3-opt move */
            /* (A,B,C,D,E,F,G,H,I), rotateRight1(x, 3, 7) = (A,B,G,C,D,E,F,H,I) */
            if (i == 0 && j == cityNum - 1) {
                add1 = add2 = add3 = delete1 = delete2 = delete3 = 0;
            }
            else {
                add1 = (i == 0) ? distanceMatri[initRoute[cityNum - 1]][initRoute[j]] : distanceMatri[initRoute[i - 1]][initRoute[j]];
                add2 = (i == j - 1) ? 0 : distanceMatri[initRoute[j]][initRoute[i]];
                add3 = (j == cityNum - 1) ? distanceMatri[initRoute[j - 1]][initRoute[0]] : distanceMatri[initRoute[j - 1]][initRoute[j + 1]];
                delete1 = (i == 0) ? distanceMatri[initRoute[cityNum - 1]][initRoute[i]] : distanceMatri[initRoute[i - 1]][initRoute[i]];
                delete2 = (i == j - 1) ? 0 : distanceMatri[initRoute[j - 1]][initRoute[j]];
                delete3 = (j == cityNum - 1) ? distanceMatri[initRoute[j]][initRoute[0]] : distanceMatri[initRoute[j]][initRoute[j + 1]];
            }
            temp = add1 + add2 + add3 - delete1 - delete2 - delete3;
            if (temp < delta) {
                int num = 0;
                for (int k = 0; k < i; ++k)  tempRoute[num++] = initRoute[k];
                tempRoute[num++] = initRoute[j];
                for (int k = i; k < j; ++k) tempRoute[num++] = initRoute[k];
                for (int k = j + 1; k < cityNum; ++k)  tempRoute[num++] = initRoute[k];
                tempLen = costFunction(tempRoute);
                if ((len + temp) != tempLen) cout << "type6 error,i = " << i << ", j = " << j << endl;
                if (!in_tabuList(tempLen)) {//判断是否在禁忌表中
                    delta = temp;//更新delta值
                    rrd.first = i;
                    rrd.second = j;
                    rrd.type = 6;
                    candidate.push(rrd);//存放候选解
                }
            }

            /* x = (A,B,C,D,E,F,G,H,I), rotateRight2(x, 3, 7) = (I,A,B,D,E,F,C,G,H) */
            add1 = (i == j - 1) ? 0 : (i == 0) ? distanceMatri[initRoute[cityNum - 1]][initRoute[i + 1]] : distanceMatri[initRoute[i - 1]][initRoute[i + 1]];
            add2 = (i == j - 1) ? 0 : distanceMatri[initRoute[j - 1]][initRoute[i]];
            add3 = (i == j - 1) ? 0 : distanceMatri[initRoute[i]][initRoute[j]];
            delete1 = (i == j - 1) ? 0 : (i == 0) ? distanceMatri[initRoute[cityNum - 1]][initRoute[i]] : distanceMatri[initRoute[i - 1]][initRoute[i]];
            delete2 = (i == j - 1) ? 0 : distanceMatri[initRoute[i]][initRoute[i + 1]];
            delete3 = (i == j - 1) ? 0 : distanceMatri[initRoute[j - 1]][initRoute[j]];
            temp = add1 + add2 + add3 - delete1 - delete2 - delete3;
            if (temp < delta) {
                int num = 0;
                for (int k = 0; k < i; ++k)  tempRoute[num++] = initRoute[k];
                for (int k = i + 1; k < j; ++k) tempRoute[num++] = initRoute[k];
                tempRoute[num++] = initRoute[i];
                for (int k = j; k < cityNum; ++k)  tempRoute[num++] = initRoute[k];
                tempLen = costFunction(tempRoute);
                if ((len + temp) != tempLen) cout << "type7 error,i = " << i << ", j = " << j << endl;
                if (!in_tabuList(tempLen)) {//判断是否在禁忌表中
                    delta = temp;//更新delta值
                    rrd.first = i;
                    rrd.second = j;
                    rrd.type = 7;
                    candidate.push(rrd);//存放候选解
                }
            }
        }
    }

    /*判断是否找到了比初始解更好的解，若delta < 0,则找到更好的解，则将局部最优解赋值给局部解，反之，找一个次优解赋值给局部解*/
    if (delta < 0) {
        auto ans = candidate.top();         //candidate至少有一个候选解，故不需要考虑candidate为空的情况
        if (ans.type == 1) {
            memcpy(localRoute, initRoute, sizeof(int) * (cityNum));
            swap(localRoute[ans.first], localRoute[ans.second]);
        }
        else if(ans.type == 2){
            int sum = ans.first + ans.second;
            for (int k = 0; k < cityNum; ++k) {
                if (k >= ans.first && k <= ans.second) {
                    localRoute[k] = initRoute[sum - k];
                }
                else {
                    localRoute[k] = initRoute[k];
                }
            }
        }
        else if (ans.type == 3) {
            int sum = ans.first + ans.second;
            int num = 0;
                for (int k = cityNum - 1; k >= ans.second; --k) {
                    localRoute[num++] = initRoute[k];
                }
            for (int k = ans.first + 1; k > ans.first && k < ans.second; ++k) {
                localRoute[num++] = initRoute[k];
            }
            for (int k = ans.first; k>= 0; k--) {
                localRoute[num++] = initRoute[k];
            }
        }
        else if (ans.type == 4) {
            int num = 0;
            for (int k = 0; k < ans.first; ++k)  localRoute[num++] = initRoute[k];
            for (int k = ans.first + 1; k <= ans.second; ++k) localRoute[num++] = initRoute[k];
            localRoute[num++] = initRoute[ans.first];
            for (int k = ans.second + 1; k < cityNum; ++k)  localRoute[num++] = initRoute[k];
        }
        else if (ans.type == 5) {
            int num = 0;
            for (int k = 0; k <= ans.first; ++k)  localRoute[num++] = initRoute[k];
            localRoute[num++] = initRoute[ans.second];
            for (int k = ans.first + 1; k < ans.second; ++k) localRoute[num++] = initRoute[k];
            for (int k = ans.second + 1; k < cityNum; ++k)  localRoute[num++] = initRoute[k];
        }
        else if (ans.type == 6) {
            int num = 0;
            for (int k = 0; k < ans.first; ++k)  localRoute[num++] = initRoute[k];
            localRoute[num++] = initRoute[ans.second];
            for (int k = ans.first; k < ans.second; ++k) localRoute[num++] = initRoute[k];
            for (int k = ans.second + 1; k < cityNum; ++k)  localRoute[num++] = initRoute[k];
        }
        else if (ans.type == 7) {
            int num = 0;
            for (int k = 0; k < ans.first; ++k)  localRoute[num++] = initRoute[k];
            for (int k = ans.first + 1; k < ans.second; ++k) localRoute[num++] = initRoute[k];
            localRoute[num++] = initRoute[ans.first];
            for (int k = ans.second; k < cityNum; ++k)  localRoute[num++] = initRoute[k];
        }
    }
    else {
        record ans;
        int ran = rand() % maxRandNum + 1;  // n不能取0；
        int n = ran;//避免陷入局部最优解，随机找倒数第n优解,暂时设置最多倒数第10优。
        while (!candidate.empty() && n) {
            --n;
            ans = candidate.top();
            candidate.pop();
        }
        if (ans.type == 1) {
            memcpy(localRoute, initRoute, sizeof(int) * (cityNum));
            swap(localRoute[ans.first], localRoute[ans.second]);
        }
        else if (ans.type == 2) {
            int sum = ans.first + ans.second;
            for (int k = 0; k < cityNum; ++k) {
                if (k >= ans.first && k <= ans.second) {
                    localRoute[k] = initRoute[sum - k];
                }
                else {
                    localRoute[k] = initRoute[k];
                }
            }
        }
        else if (ans.type == 3) {
            int sum = ans.first + ans.second;
            int num = 0;
            for (int k = cityNum - 1; k >= ans.second; --k)  localRoute[num++] = initRoute[k];
            for (int k = ans.first + 1; k > ans.first && k < ans.second; ++k)  localRoute[num++] = initRoute[k]; 
            for (int k = ans.first; k>= 0; k--)  localRoute[num++] = initRoute[k]; 
        }
        else if (ans.type == 4) {
            int num = 0;
            for (int k = 0; k < ans.first; ++k)  localRoute[num++] = initRoute[k];
            for (int k = ans.first + 1; k <= ans.second; ++k) localRoute[num++] = initRoute[k];
            localRoute[num++] = initRoute[ans.first];
            for (int k = ans.second + 1; k < cityNum; ++k)  localRoute[num++] = initRoute[k];
        }
        else if (ans.type == 5) {
            int num = 0;
            for (int k = 0; k <= ans.first; ++k)  localRoute[num++] = initRoute[k];
            localRoute[num++] = initRoute[ans.second];
            for (int k = ans.first + 1; k < ans.second; ++k) localRoute[num++] = initRoute[k];
            for (int k = ans.second + 1; k < cityNum; ++k)  localRoute[num++] = initRoute[k];
        }
        else if (ans.type == 6) {
            int num = 0;
            for (int k = 0; k < ans.first; ++k)  localRoute[num++] = initRoute[k];
            localRoute[num++] = initRoute[ans.second];
            for (int k = ans.first; k < ans.second; ++k) localRoute[num++] = initRoute[k];
            for (int k = ans.second + 1; k < cityNum; ++k)  localRoute[num++] = initRoute[k];
        }
        else if (ans.type == 7) {
            int num = 0;
            for (int k = 0; k < ans.first; ++k)  localRoute[num++] = initRoute[k];
            for (int k = ans.first + 1; k < ans.second; ++k) localRoute[num++] = initRoute[k];
            localRoute[num++] = initRoute[ans.first];
            for (int k = ans.second; k < cityNum; ++k)  localRoute[num++] = initRoute[k];
        }
    }
}