#include "tabu.h"
#include<stack>
/*
 *�������ܣ����ھӽ�
 *��ʼ���ڣ�2020/7/13
 *�ϴθ��£�2020/7/16
 *�������ݣ���7�����ھӵķ��������Ż�
 */

struct record {       //ÿ�ε���ʱ����û���ҵ����Ž�ʱ����¼���Ž��������ͣ�
    int first;
    int second;
    int type;
};

void findNeighbor(int* initRoute, int* localRoute)
{
    stack<record> candidate;    //��Ŵ��Ž�

    /*�Ҿֲ����Ž�*/
    int len = costFunction(initRoute); //��ʼ·������
    int temp; //���delta����ʱֵ
    int delta = INT_MAX;//�����·����ϳ�ʼ·���Ĳ�ֵ

    /*7�����ھӵ�type���ر�ע��i = 0��j = cityNum - 1�Լ�i��j���ڵ��������*/
    for (int i = 0; i < cityNum - 1; ++i) {
        for (int j = i + 1; j < cityNum; ++j) {
            record rrd;//��¼�ҵ���ʱ·����i��j��type
            int add1, add2, add3, add4;      //��¼���ӱ߳�,���4-opt move
            int delete1, delete2, delete3, delete4;        //��¼ɾ���߳�

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
                if (!in_tabuList(tempLen)) {//�ж��Ƿ��ڽ��ɱ���
                    delta = temp;//����deltaֵ
                    rrd.first = i;
                    rrd.second = j;
                    rrd.type = 1;
                    candidate.push(rrd);//��ź�ѡ��
                }
            }

            /* Two ways to reverse(x, i, j) : reverse the subsequence between indexes i and
            j in permutation x��Possible 2-opt move */
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
                if (!in_tabuList(tempLen)) {//�ж��Ƿ��ڽ��ɱ���
                    delta = temp;//����deltaֵ
                    rrd.first = i;
                    rrd.second = j;
                    rrd.type = 2;
                    candidate.push(rrd);//��ź�ѡ��
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
                if (!in_tabuList(tempLen)) {//�ж��Ƿ��ڽ��ɱ���
                    delta = temp;//����deltaֵ
                    rrd.first = i;
                    rrd.second = j;
                    rrd.type = 3;
                    candidate.push(rrd);//��ź�ѡ��
                }
            }

            /*rotateLeft(x,i, j): Two ways to rotate the subsequence between indexes i and
            j in permutation x one step to the left��Possible 3-opt move*/
            /* (A,B,C,D,E,F,G,H,I)�� rotateLeft1(x, 3, 7) = (A,B,D,E,F,G,C,H,I) */
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
                if (!in_tabuList(tempLen)) {//�ж��Ƿ��ڽ��ɱ���
                    delta = temp;//����deltaֵ
                    rrd.first = i;
                    rrd.second = j;
                    rrd.type = 4;
                    candidate.push(rrd);//��ź�ѡ��
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
                if (!in_tabuList(tempLen)) {//�ж��Ƿ��ڽ��ɱ���
                    delta = temp;//����deltaֵ
                    rrd.first = i;
                    rrd.second = j;
                    rrd.type = 5;
                    candidate.push(rrd);//��ź�ѡ��
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
                if (!in_tabuList(tempLen)) {//�ж��Ƿ��ڽ��ɱ���
                    delta = temp;//����deltaֵ
                    rrd.first = i;
                    rrd.second = j;
                    rrd.type = 6;
                    candidate.push(rrd);//��ź�ѡ��
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
                if (!in_tabuList(tempLen)) {//�ж��Ƿ��ڽ��ɱ���
                    delta = temp;//����deltaֵ
                    rrd.first = i;
                    rrd.second = j;
                    rrd.type = 7;
                    candidate.push(rrd);//��ź�ѡ��
                }
            }
        }
    }

    /*�ж��Ƿ��ҵ��˱ȳ�ʼ����õĽ⣬��delta < 0,���ҵ����õĽ⣬�򽫾ֲ����Ž⸳ֵ���ֲ��⣬��֮����һ�����Ž⸳ֵ���ֲ���*/
    if (delta < 0) {
        auto ans = candidate.top();         //candidate������һ����ѡ�⣬�ʲ���Ҫ����candidateΪ�յ����
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
        int ran = rand() % maxRandNum + 1;  // n����ȡ0��
        int n = ran;//��������ֲ����Ž⣬����ҵ�����n�Ž�,��ʱ������൹����10�š�
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