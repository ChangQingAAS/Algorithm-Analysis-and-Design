#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

#include "path.h"
#include "all_pairs.h"

void inputData(string Path)
{
    //将string转为char*
    const char *inpath = Path.c_str();
    int i,j;
    if (freopen(inpath, "r", stdin) == NULL)
        fprintf(stderr, "Wrong input document!\n");
    // cout<<"已经进入inputData()"<<endl;
    cin >> n;
    init_c_kay(n);
    while(scanf("%d", &i) !=EOF)
    {
        cin>>j;
        cin>>c[i][j];
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

    cout<<"运行时间(us)为："<<time<<endl<<endl;
    output_all_path();

    //关闭
    fclose(stdout);
    free(c);
    free(kay);
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
        all_pairs();
        //计时结束
        QueryPerformanceCounter(&time_end);
        //乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
        run_time = 1000000 * (time_end.QuadPart - time_start.QuadPart) / dqFreq;
        //输出
        outputAnswers(answers_path[j], run_time);
    }
    return 0; 
}

