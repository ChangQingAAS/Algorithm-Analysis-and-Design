#include <stdio.h>

// #define max 20

#define M 30
#define N 7

int w[N] = {0};
int x[N] = {0,5,10,12,13,15,18};
int flag = 0;

//回溯算法实现
void sumOfSub(int s, int k, int r);
//首先对这些正数排序
void InsertionSort(int a[], int low, int high);
//每产生一个解向量就打印出来，同时清零。准备下一个解向量
void print();

int main()
{
    int sum = 0;
    //先判断所有数的和是否小于M，如果小于M则不会有解向量
    for (int i = 1; i < N; i++)
    {
        sum += w[i];
    } //for

    if (sum < M)
    {
        printf("没有解向量满足条件\n");
        return 0;
    } //if

    //如果要用回溯算法，首先对数据排序。因为数据的规模不大，用InsertionSort搞定
    InsertionSort(w, 1, N - 1);

    if (w[0] > M)
    {
        printf("没有解向量满足条件\n");
        return 0;
    } //if

    //回溯算法的准备工作完毕，下面开始调用
    sumOfSub(0, 1, sum);

    //通过flag的值判断print()函数有没有被调用过，从而确定是否存在解向量
    if (!flag)
    {
        printf("不存在满足条件的序列\n");
    }

    return 0;
}
void sumOfSub(int s, int k, int r)
{
    //生成左子树
    x[k] = 1;
    if (s + w[k] == M)
    {
        print();
    } //if
    else
    {
        if (k < N - 1 && s + w[k] + w[k + 1] <= M)
        {
            sumOfSub(s + w[k], k + 1, r - w[k]);
        } //if

    } //else

    //生成右子树
    x[k] = 0;
    if (k < N - 1 && s + r - w[k] >= M && s + w[k + 1] <= M)
    {
        sumOfSub(s, k + 1, r - w[k]);
    } //if
}

void print()
{
    for (int i = 1; i < N; i++)
    {
        printf("%d ", x[i]);
    }
    printf("\n");
    flag = 1;
}

void InsertionSort(int a[], int low, int high)
{
    int unsort = low + 1;
    int j;
    for (; unsort <= high; ++unsort)
    {
        int temp = a[unsort];
        j = unsort - 1;
        while (j >= 0 && temp < a[j])
        {
            a[j + 1] = a[j];
            j--;
        } //while
        a[j + 1] = temp;

    } //for
}