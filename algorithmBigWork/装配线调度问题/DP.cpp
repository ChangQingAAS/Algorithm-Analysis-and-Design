#include <stdio.h>
#include <stdlib.h>

/*
下面的公共数据是对配件站的模拟，f_star对应于文章中的f*,l_star对应于l*
其余路径均一数组形式存放，所有的数据都是从1开始计算，所以数组第0号位置全部存放0
*/

int f_star, l_star;
int f[2 + 1][6 + 1];
int l[2 + 1][6 + 1];
int a[2 + 1][6 + 1] = {{0, 0, 0, 0, 0, 0, 0}, {0, 7, 9, 3, 4, 8, 4}, {0, 8, 5, 6, 4, 5, 7}};
int t[2 + 1][5 + 1] = {{0, 0, 0, 0, 0, 0}, {0, 2, 3, 1, 3, 4}, {0, 2, 1, 2, 2, 1}};
int e[2 + 1] = {0, 2, 4};
int x[2 + 1] = {0, 3, 2};

void FASTEST_WAY()
{
    int j;
    f[1][1] = e[1] + a[1][1];
    f[2][1] = e[2] + a[2][1];
    for (j = 2; j <= 6; j++)
    {
        if (f[1][j - 1] + a[1][j] <= f[2][j - 1] + t[2][j - 1] + a[1][j])
        {
            f[1][j] = f[1][j - 1] + a[1][j];
            l[1][j] = 1;
        }
        else
        {
            f[1][j] = f[2][j - 1] + t[2][j - 1] + a[1][j];
            l[1][j] = 2;
        }
        if (f[2][j - 1] + a[2][j] <= f[1][j - 1] + t[1][j - 1] + a[2][j])
        {
            f[2][j] = f[2][j - 1] + a[2][j];
            l[2][j] = 2;
        }
        else
        {
            f[2][j] = f[1][j - 1] + t[1][j - 1] + a[2][j];
            l[2][j] = 1;
        }
    }
    if (f[1][6] + x[1] <= f[2][6] + x[2])
    {
        f_star = f[1][6] + x[1];
        l_star = 1;
    }
    else
    {
        f_star = f[2][6] + x[2];
        l_star = 2;
    }
}

void PRINT_STATIONS()
{
    int j;
    int i = l_star;
    // printf("line %d,station %d\n", i, 6);
    printf("%d <- ", i);
    for (j = 6; j >= 2; j--)
    {
        i = l[i][j];
        // printf("line %d,station %d\n", i, j - 1);
        if(j == 2)
            printf("%d", i);
        else
            printf("%d <- ",i);
    }
}

int main()
{
    FASTEST_WAY();
    printf("最短路线f_star=%d\n", f_star);
    printf("以下是每个配件站的位置：\n");
    PRINT_STATIONS();
    return 0;
}
