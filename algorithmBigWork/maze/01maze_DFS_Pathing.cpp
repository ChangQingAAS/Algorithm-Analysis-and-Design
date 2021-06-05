/*
题目描述：
    一个迷宫，其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，要求编程序找出从某点到达某点左上角到右下角的路线。
输入
    一个5 × 5的二维数组，表示一个迷宫。数据保证有唯一解。
输出
    路径数量
*/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;

//最大可能路径数
#define maxPath 10

//迷宫大小
#define maze_x_length 4
#define maze_y_length 4

//迷宫，其中的1表示墙壁，0表示可以走的路
int maze[maze_x_length + 1][maze_y_length + 1];

//用来记录已访问节点
int isvisited[maze_x_length + 1][maze_y_length + 1] = {0};

//代表着在迷宫中怎样移动
int dx[4] = {0, 0, 1, -1};
int dy[4] = {-1, 1, 0, 0};

//路径数量
int pathNum = 0;

//记录结点坐标,默认为(0,0)
struct point{
    int x = 0;
    int y = 0;
};

//记录着路径子节点与父节点的对应关系
struct point path[maze_x_length + 1][maze_y_length + 1];  

void printPath()
{
    
        cout<<"这是第"<< pathNum <<"条路径:"<<endl;
        int num[30][2] = {-1};

        int x = maze_x_length,y = maze_y_length;
        int w = 0;
        while(1)
        {                                //把父子节点关系倒着取出放入数组中以便打印
            int k = x;
            x = path[x][y].x;
            y = path[k][y].y;

            num[w][0]=x;
            num[w][1]=y;  
            w++;
            if(x==0&&y==0)
                break;
        }

        for(int j = w-1;j >= 0;j--)
        {
            printf("(%d, %d)\n",num[j][0],num[j][1]);          //打印路径节点部分
        }
        
        printf("(%d, %d)\n\n",maze_x_length, maze_y_length); 

}


void dfs(int x, int y)
{
    if (x == maze_x_length && y == maze_y_length)
    {
        pathNum++;
        printPath();
        return;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            struct point current_point;
            current_point.x = x + dx[i];
            current_point.y = y + dy[i];
            if(current_point.x < 0|| current_point.x > maze_x_length || current_point.y < 0||current_point.y > maze_y_length|| maze[current_point.x][current_point.y] || isvisited[current_point.x][current_point.y])      //判断是否为合法路径，比如墙和已走过节点都为非法路径
                continue;

            if (isvisited[current_point.x][current_point.y] == 0 && maze[current_point.x][current_point.y] == 0)
            {
                isvisited[current_point.x][current_point.y] = 1;

                //记录着谁走到了它
                path[current_point.x][current_point.y].x = x;
                //现在来说明这个二维数组怎样记录最短路径，首先这个数组里存的是坐标结构体，数组下标代表着子节点坐标，而数组内容存着父节点坐标，这样皆可以通过循环，一级一级找上去，既可以知道最短路径长度，也可以打印所有经过的节点坐标
                path[current_point.x][current_point.y].y = y;

                dfs(current_point.x, current_point.y);

                isvisited[current_point.x][current_point.y] = 0;
            }
        }
    }
}

int main()
{
    for(int m = 0;m < maze_x_length + 1; m++)                  
    {
        for(int n = 0; n < maze_y_length + 1;n++)
        {
            scanf("%d",&maze[m][n]);
        }
    }

    dfs(0, 0);

    cout <<"共有"<<pathNum<<"条路径"<<endl;

    return 0;
}
