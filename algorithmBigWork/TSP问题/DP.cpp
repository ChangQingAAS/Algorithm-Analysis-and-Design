#include <string>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <iomanip>
#include <iostream>
using namespace std;

#include "global.h"
#include "path.h"

void TSP()
{
    for (int i = 0; i < binaryOfN; i++)
        for (int j = 0; j < n; j++)
        {
            Route[j][i] = -1.0;
            way[j][i] = -1;
        }
    for (int i = 0; i < n; i++) //初始化第0列
        Route[i][0] = dis[i][0];
    //
    for (int i = 1; i < binaryOfN - 1; i++)
        for (int j = 1; j < n; j++)            //依次进行第i次迭代
            if (((int)pow(2, j - 1) & i) == 0) //子集V[j不包含i
            {
                mincost = inf;
                for (int k = 1; k < n; k++)
                    if ((int)pow(2, k - 1) & i)
                    {
                        temp = dis[j][k] + Route[k][i - (int)pow(2, k - 1)];
                        if (temp < mincost)
                        {
                            mincost = temp;
                            Route[j][i] = mincost;
                            way[j][i] = k; //局部最优决策
                        }
                    }
            }
    //
    mincost = inf;
    for (int k = 1; k < n; k++)
    {
        temp = dis[0][k] + Route[k][(binaryOfN - 1) - (int)pow(2, k - 1)];
        if (temp < mincost)
        {
            mincost = temp;
            Route[0][binaryOfN - 1] = mincost; //最优解
            way[0][binaryOfN - 1] = k;
        }
    }
    return;
}

void inputData(string Path)
{
    //将string转为char*
    const char *inpath = Path.c_str();
    if (freopen(inpath, "r", stdin) == NULL)
        fprintf(stderr, "Wrong input document!\n");
    cin >> n;
    binaryOfN = (int)pow(2, n - 1);
    //初始化将要用到的数组
    init_all_arrays(n, binaryOfN);
    for (int ii = 0; ii < n; ii++)
    {
        for (int jj = 0; jj < n; jj++)
            cin>>dis[ii][jj];
    }
        
    fclose(stdin);
    //在标准C中只定义了输出流、更新流的刷新，而输入流的刷新是未定义的。
    cin.clear(); //特别注意：在读取完一个文件后，使用 cin.clear()清空输入流。否则除第一个文件，其他文件无读入。
    return;
}

void outputAnswers(string Path, float time)
{
    const char *outpath = Path.c_str();
    if (freopen(outpath, "w", stdout) == NULL)
        fprintf(stderr, "Wrong output document!\n");

    //最短路径长度
    cout <<Route[0][binaryOfN - 1] << endl; 
    //输出最短路径
    cout << 1 << endl;
    for (int i = binaryOfN - 1, j = 0; i > 0;)
    {
        j = way[j][i];
        i = i - (int)pow(2, j - 1);
        cout << j + 1 << endl;
    }
    cout << 1 ;
    // cout<<"time(us)："<<time;
    //关闭
    fclose(stdout);
    return;
}

int main()
{
    //有关计时的变量,这部分变量设置放在main函数内较好
    double run_time;
    _LARGE_INTEGER time_start; //开始时间
    _LARGE_INTEGER time_end;   //结束时间
    double dqFreq;             //计时器频率
    LARGE_INTEGER f;           //计时器频率
    QueryPerformanceFrequency(&f);
    dqFreq = (double)f.QuadPart;

    for (int j = 0; j < DataSetNum; j++)
    {
        //输入
        inputData(data_path[j]);
        //计时开始
        QueryPerformanceCounter(&time_start);
        //要计时的运算程序
        TSP();
        //计时结束
        QueryPerformanceCounter(&time_end);
        //乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
        run_time = 1000000 * (time_end.QuadPart - time_start.QuadPart) / dqFreq;
        //输出
        outputAnswers(answers_path[j], run_time);
    }

    return 0;
}
