#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
#include<cmath>
#include<cstdlib>
using namespace std;
/*禁忌法求解TSP*/
/*对比tabu_4尝试找ATT532的最优解，记录每一次迭代后的路径长度，找迭代合适的次数*/
string filename;    //文件名
int iterationNum;   //迭代次数
//int neighborNum;    //邻居数量
int tabuListLen;    //紧急表长
int cityNum;        //城市数量

int **tabuList;          //禁忌表
int **distanceMatri;    //距离矩阵
int *initRoute;     //初试路径编码
int *localRoute;    //局部路径编码
int *bestRoute;     //最佳路径编码
int *tempRoute;     //暂时路径编码
int localLen;       //局部路径长度
int tempLen;        //暂时路径长度
int bestLen;        //最好路径长度

int *localTempRoute;     //局部暂时路径
int localTempLen;        //局部暂时路径长度

void init(int argc,char **argv);
void solve();
void init_greedy();
int costFunction(int *Route);
void findNeighbor(int *initRoute,int *localRoute);
bool in_tabuList(int *tempRoute);
void pushTabuList(int *localRoute);
void printResult();

int main(int argc,char **argv){
    init(argc,argv);
    time_t beg,end;
    beg = clock();
    solve();
    end = clock();
    double runTime = (double)(end - beg) / CLOCKS_PER_SEC;
    printResult();
    cout << "runTime: " << runTime << " seconds" << endl;
	system("pause");
    return 0;
}

/*初始化*/
void init(int argc,char **argv){
    filename = (argc >= 2) ? (string)argv[1] : "att532.txt";
    int textMode = (argc >= 3) ? atoi(argv[2]) : 0;   //判断读入文本的格式，若textMode == 0 则读入的是坐标点，若textMode == 1，读入的是距离矩阵
    iterationNum = (argc >= 4) ? atoi(argv[3]) : 100000;
    tabuListLen = (argc >= 6) ? atoi(argv[4]) : 20;

    fstream fin(filename,ios::in); //打开文件
    if(!fin.is_open()){
        cerr << "can not open the file " << filename << endl;
        exit(0);
    }
    fin >> cityNum;
    //给距离矩阵申请空间
    distanceMatri = new int*[cityNum];
    for(int i = 0; i < cityNum; ++i)
        distanceMatri[i] = new int[cityNum];
    //读入文本数据，给距离矩阵赋值
    int num;
    if(textMode == 0){      
        double *x,*y;
        x = new double[cityNum];
        y = new double[cityNum];
        for(int i = 0; i < cityNum; ++i)
            fin >> num >> x[i] >> y[i];
        for(int i = 0; i < cityNum; ++i){
            distanceMatri[i][i] = 0;
            for(int j = i + 1; j < cityNum; ++j){
                distanceMatri[i][j] = distanceMatri[j][i] = ceil(sqrt(pow(x[i] - x[j], 2) / 10 + pow(y[i] - y[j], 2) / 10));//考虑四舍五入；
            }
        }
        delete[] x;
        delete[] y;
    }else if(textMode == 1){
        for(int i = 0; i < cityNum; ++i){
            for(int j = 0; j < cityNum; ++j)
                fin >> distanceMatri[i][j];
        }
    }else{
        cerr << "mode error" << endl;
    }  
    //申请空间,初始化路径长度为无穷大
    initRoute = new int[cityNum];
    localRoute = new int[cityNum];
    bestRoute = new int[cityNum];
    tempRoute = new int[cityNum];
    tabuList = new int*[tabuListLen];

    localTempRoute = new int[cityNum];
    for(int i = 0; i < tabuListLen; ++i)
        tabuList[i] = new int[cityNum];
    localLen = INT_MAX;
    bestLen = INT_MAX;
    tempLen = INT_MAX;
    localTempLen = INT_MAX;
    
    srand((unsigned int)time(0));//设置随机数种子
}

/*求解TSP问题*/
void solve(){
    init_greedy();
    memcpy(bestRoute,initRoute,sizeof(int) * cityNum);
    bestLen = costFunction(bestRoute);

    //cout << bestLen;           //可输出贪心解的距离

    /*迭代iterationNum次*/
    int n1 = 0;        //迭代次数
    time_t beg,end;  //for debug
    beg = clock(); //for debug
    while(n1 < iterationNum){
        localLen = INT_MAX;
        tempLen = INT_MAX;
        findNeighbor(initRoute,tempRoute);  //找到一个邻居解
        memcpy(localRoute,tempRoute,sizeof(int) * cityNum);
        tempLen = costFunction(tempRoute);
        localLen = tempLen;
        
        if(localLen < bestLen){  //最优解更新
            memcpy(bestRoute,localRoute,sizeof(int) * cityNum);
            bestLen = localLen;
        }

        end = clock(); //for debug
        double runTime = (double)(end - beg) / CLOCKS_PER_SEC; //for debug
        cout << "iterationNum:" << n1 + 1<< "  localLen:" << localLen << "  bestLen : " << bestLen <<  "  runTime: " << runTime << " seconds" << endl;//just for debug
        if(bestLen == 27686){
            printResult();
            exit(1);
        }
        memcpy(initRoute,localRoute,sizeof(int) * cityNum); //将局部最优解赋值给初始解进行下一次迭代，结果变差也继续进行；
        pushTabuList(localRoute);     //将局部最优解存入紧急表；
        ++n1;
    }
}

/*贪心法求解TSP作为初始路径*/
void init_greedy(){
    int f[cityNum] = {0}; //标记已访问的城市

    int sum = 0;//记录路程长度
    int num = 0;//记录第i个点
    f[0] = 1;
    int ed;   
    initRoute[num++] = 0;
    //cout << initRoute[num - 1] << ' ';
    int rm = cityNum - 1;  //还有rm个城市未访问
    while(rm--){
        int x = INT_MAX;
        int temp;
        for(int i = 0; i < cityNum; ++i){
            if(f[i] == 1)   continue;
            temp = distanceMatri[initRoute[num - 1]][i];
            if(temp < x){
                x = temp;
                ed = i;
            }
        }
        f[ed] = 1;
        initRoute[num++] = ed;
        sum += x;
        //cout << initRoute[num - 1] << ' ';
    }
    //cout << endl;
    sum += distanceMatri[ed][0];
    //cout << "总路径长为" << sum; 
}

/*求解路径总长度*/
int costFunction(int *Route){
    int sum = 0;
    for(int i = 0; i < cityNum - 1; ++i){
        sum += distanceMatri[Route[i]][Route[i + 1]] + 0.5;
    }
    sum += distanceMatri[Route[cityNum - 1]][Route[0]] + 0.5;
    return sum;
}

/*找邻居解*/
void findNeighbor(int *initRoute,int *tempRoute){
    int ran1 = rand() % cityNum;
    int ran2 = rand() % cityNum;
    while(ran1 == 0)    ran1 = rand() % cityNum;
    while(ran2 == 0 || ran2 == ran1)    ran2 = rand() % cityNum;
    if(ran1 > ran2) swap(ran1,ran2);

    int ran3 = rand() % 3; //用3种方法来找邻居
    /*找局部最优解*/
    int len = costFunction(initRoute); //初始路径长度
    int flag = 0;//没有找到比最优解更好的解
    for(int i = 1; i < cityNum; ++i){
        for(int j = i + 1;j < cityNum; ++j){
            /*用swap找邻居*/
            memcpy(localTempRoute,initRoute,sizeof(int) * cityNum);
            swap(localTempRoute[i],localTempRoute[j]);
            localTempLen = costFunction(localTempRoute);
            if(localTempLen < len && !in_tabuList(localTempRoute)){
                flag = 1;
                len = localTempLen;
                memcpy(tempRoute,localTempRoute,sizeof(int) * cityNum);
            }
            /*用reverse找邻居*/
            int sum = i + j;
            for(int k = 0; k < cityNum; ++k){
                if(k >= i && k <= j){
                    localTempRoute[k] = initRoute[sum - k];
                }else{
                    localTempRoute[k] = initRoute[k];
                }
            }
            localTempLen = costFunction(localTempRoute);
            if(localTempLen < len && !in_tabuList(localTempRoute)){
                flag = 1;
                len = localTempLen;
                memcpy(tempRoute,localTempRoute,sizeof(int) * cityNum);
            }
            /*用replaceSegment找邻居*/
            int index = 0;
		    for(int k = 0; k < i; ++k){
		    	localTempRoute[index++] = initRoute[k];
	    	}
		    for(int k = j + 1; k < cityNum; ++k){
		    	localTempRoute[index++] = initRoute[k];
		    }
	    	for(int k = i; k <= j; ++k){
		    	localTempRoute[index++] = initRoute[k];
		    }
            localTempLen = costFunction(localTempRoute);
            if(localTempLen < len && !in_tabuList(localTempRoute)){
                flag = 1;
                len = localTempLen;
                memcpy(tempRoute,localTempRoute,sizeof(int) * cityNum);
            }
        }
    }
    /*没有找到比初始解更好的解，随机选取一断*/
    if(flag == 0){
        if(ran3 == 0){//swap(x,i, j): swap the element at index i in permutation x with element at index j
             memcpy(tempRoute,initRoute,sizeof(int) * cityNum);
             swap(tempRoute[ran1],tempRoute[ran2]);
        }else if(ran3 == 1){//reverse(x,i, j): reverse the subsequence between indexes i and j in permutation x
            int sum = ran1 + ran2;
            for(int i = 0; i < cityNum; ++i){
                if(i >= ran1 && i <= ran2){
                tempRoute[i] = initRoute[sum - i];
            }else{
                tempRoute[i] = initRoute[i];
            }
            }
        }else{//随机交换一段距离
            int index = 0;
		    for(int i = 0; i < ran1; i++){
		    	tempRoute[index++] = initRoute[i];
		    }
		    for(int i = ran2 + 1; i < cityNum; i++){
		    	tempRoute[index++] = initRoute[i];
		    }
		    for(int i = ran1; i <= ran2; i++){
			    tempRoute[index++] = initRoute[i];
		    }
        }
    }
}
/*判断tempRoute是否在tabulist里面*/
bool in_tabuList(int *tempRoute){
    int flag = 0;
    for(int i = 0; i < tabuListLen; ++i){
        flag = 0;
        for(int j = 0; j < cityNum; ++j){
            if(tempRoute[j] != tabuList[i][j]){
                flag = 1;
                break;
            }
        }
        if(flag == 0)   break;
    }
    if(flag == 0)   return true;        //表明tempRoute在tabuList里面；
    else return false;
}

/*更新紧急表*/
void pushTabuList(int *localRoute){
    for(int i = 0; i < tabuListLen - 1; ++i){       //删除禁忌表中第一组编码
        for(int j = 0; j < cityNum; ++j){
            tabuList[i][j] = tabuList[i + 1][j];
        }
    }
    for(int i = 0; i < cityNum; ++i){//在禁忌表中将localRoute插入
        tabuList[tabuListLen - 1][i] = localRoute[i];
    }      
}

/*打印路径*/
void printResult(){
    fstream fout("TSP_AnswerOut.txt", ios::out);
	fout << filename << " result:" << endl;
	cout << "最佳路径长度： " << bestLen << endl;
	fout << "最佳路径长度： " << bestLen << endl;
	cout << "最佳路径：" << endl;
	fout << "最佳路径：" << endl;
	for(int i = 0; i < cityNum; i++){
		cout << bestRoute[i] + 1 << "->";
		fout << bestRoute[i] + 1 << "->";
	}
	cout << 1 << endl;
	fout << 1 << endl;
	fout.close();
}