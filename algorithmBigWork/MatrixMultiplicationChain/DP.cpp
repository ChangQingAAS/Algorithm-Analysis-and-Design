// 动态规划算法求矩阵连乘积问题...
//进阶要求1：改进算法使复杂度n*lgn
//进阶要求2：输出为括号的形式:((0, 1), 2)
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <string.h>
#include <iomanip>
#include <math.h>
#include <windows.h>
#include <unistd.h>
#include <iostream>
using namespace std;
//引入输入输出的路径
#include "path.h"

#define MAX_SIZE 200

int p[MAX_SIZE];           //矩阵连乘积A1A2...An中矩阵的位数一维数组，其中Ai的维数为Pi-1*Pi，i=1,2,..,n
int n;                     //矩阵个数
int m[MAX_SIZE][MAX_SIZE]; //最少数乘次数
int s[MAX_SIZE][MAX_SIZE]; //A[i,j]的 最佳断开位置

//计算过程
void DPMatrixChain(int p[MAX_SIZE], int n, int m[MAX_SIZE][MAX_SIZE], int s[MAX_SIZE][MAX_SIZE])
{
    int i, j, r;
    int t;
    int k;
    for (i = 1; i < n; i++) //初始化对角线，因为m[i][j]的值位于上三角区域，当i=j时为单一矩阵，无需计算
    {
        m[i][i] = 0;
        m[i][i + 1] = p[i] * p[i + 1] * p[i + 2];
        s[i][i + 1] = i;
    }
    m[n][n] = 0; 

    for (r = 2; r <= n; r++)             //变量r表示矩阵链长的递增，如r=2，表示AiA(i+1)，此处处理2~n的所有矩阵链
    {                                    //上边的对角线初始化相当于r=1
        for (i = 1; i <= n - r + 1; i++) //此处取矩阵子链，长度为r的矩阵子链共有n-r+1中组合方式
        {
            j = i + r - 1;
            m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
            s[i][j] = i;
            for (k = i + 1; k < j; k++)
            {
                t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (t < m[i][j])
                {
                    m[i][j] = t;
                    s[i][j] = k;
                }
            }
        }
    }
    return;
}

//输出数组
void print_array(int a[MAX_SIZE][MAX_SIZE], int n)
{
    printf("         |");
    for(int i = 1; i <= n; i++)
        printf("%5d    ", i);
    printf("\n");
    printf("-----");
    for(int i = 1; i <= n; i++)
        printf("----------");
    printf("\n");
    for (int i = 1; i <= n; i++)
    {
        printf("%5d    ", i);
        printf("|");
        for (int j = 1; j <= n; j++)
        {
            printf("%5d    ", a[i][j]);
        }
        printf("\n");
    }
    return;
}

//输出最优解
void PRINT_OPTIMAL_PARENS(int q[MAX_SIZE][MAX_SIZE], int i, int j)
{
    if (i == j)
        cout << " A" << i << " ";
    else
    {
        cout << "(";
        PRINT_OPTIMAL_PARENS(q, i, q[i][j]);
        cout << ",";
        PRINT_OPTIMAL_PARENS(q, q[i][j] + 1, j);
        cout << ")";
    }
    return;
}

void outputAnswers(string Path, float time)
{
    const char *outpath = Path.c_str();
    if (freopen(outpath, "w", stdout) == NULL)
        fprintf(stderr, "Wrong output document!\n");
    cout << "计算时间(us)：" << time << "\n\n";
    cout << "最优解为: " << m[1][n] << "\n\n";
    cout << "括号化方案为：" << endl;
    PRINT_OPTIMAL_PARENS(s, 1, n);

    cout << "\n\n最少数乘次数矩阵：" << endl;
    print_array(m, n);
    cout << "\n最佳断开位置矩阵:" << endl;
    print_array(s, n);
    //关闭
    fclose(stdout);

    return;
}

int inputData(string Path)
{
    //将string转为char*
    const char *inpath = Path.c_str();
    if (freopen(inpath, "r", stdin) == NULL)
        fprintf(stderr, "Wrong input document!\n");
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i] >> p[i + 1];
    }

    fclose(stdin);
    //在标准C中只定义了输出流、更新流的刷新，而输入流的刷新是未定义的。
    cin.clear(); //特别注意：在读取完一个文件后，使用 cin.clear()清空输入流。否则除第一个文件，其他文件无读入。
    return 0;
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
    //初始化，排除DPMatrixChain函数初始化对计时的影响
        //输入
        inputData(DataSetPath[DataSetNumber - 1]);
        //要计时的运算程序
        DPMatrixChain(p, n, m, s);

    for (int j = 0; j < DataSetNumber; j++)
    {
        //输入
        inputData(DataSetPath[j]);
        //计时开始
        QueryPerformanceCounter(&time_start);
        //要计时的运算程序
        DPMatrixChain(p, n, m, s);
        //计时结束
        QueryPerformanceCounter(&time_end);
        //乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
        run_time = 1000000 * (time_end.QuadPart - time_start.QuadPart) / dqFreq;
        //输出
        outputAnswers(AnswersPath[j], run_time);
    }
    return 0;
}