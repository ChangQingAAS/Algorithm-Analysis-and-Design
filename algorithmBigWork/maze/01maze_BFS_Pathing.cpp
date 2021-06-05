/*
题目描述：
    一个迷宫，其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，要求编程序找出从左上角到右下角的最短路线。
输入
    一个5 × 5的二维数组，表示一个迷宫。数据保证有唯一解。
输出
    左上角到右下角的最短路径，格式如样例所示。
*/


#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;

//迷宫大小
#define maze_x_length 4
#define maze_y_length 4

//迷宫，其中的1表示墙壁，0表示可以走的路
int maze[maze_x_length + 1 ][maze_y_length + 1]; 

//用来记录已访问节点
int isvisited[maze_x_length + 1][maze_y_length + 1];

//记录结点坐标,默认为(0,0)
struct point{
    int x = 0;
    int y = 0;
};

//记录着路径子节点与父节点的对应关系
struct point path[maze_x_length + 1][maze_y_length + 1];  

//代表着在迷宫中怎样移动
int xx[4]={1,-1,0,0};
int yy[4]={0,0,-1,1};


// 注意：凡是写到背下的，说明其基本可以完全复用，而且处于此模板(bfs)的核心部分
void BFS()
{
    memset(isvisited,0,sizeof(isvisited));       //初始化已访问数组
    queue<point>q;                              //背下,初始化队列
    struct point A;                             //把第一个结点压入队列里
    isvisited[0][0]=1;                         //初始化首已访问节点，说明自己已被访问
    path[0][0].x=0;                          //初始化对应关系底层结点  下面将详细解释
    path[0][0].y=0;

    //特别注意:千万不要死板，此题是走迷宫，所以首节点是左上角，其他题可不一定，千万不要一堆0就上去了

    q.push(A);                              //将首节点压入队列                 
    while(!q.empty())                       //只要队列里还有东西就继续
    {
        struct point current_point = q.front();             //这两句背下
        q.pop();
        struct point moved_point;

        if(current_point.x == maze_x_length && current_point.y == maze_y_length)                //找到答案后退出 
            return;

        //特别注意:不一定都需要退出条件，如果题目要求我们对单节点进行移动（后面会提到）

        for(int i = 0; i < 4; i++)                //把各个方向都试着走一遍,共四个方向，左右上下
        {
            moved_point.x = current_point.x+xx[i];              //zx,zy为移动后节点坐标
            moved_point.y = current_point.y+yy[i];

            if(moved_point.x < 0|| moved_point.x > 4||moved_point.y < 0||moved_point.y > 4|| maze[moved_point.x][moved_point.y] || isvisited[moved_point.x][moved_point.y])      //判断是否为合法路径，比如墙和已走过节点都为非法路径
                continue;

            isvisited[moved_point.x][moved_point.y]=1;              //将已访问节点标志为1  下标对应当前节点

            //将合法子节点压入队列
            q.push(moved_point);

            //记录着谁走到了它
            path[moved_point.x][moved_point.y].x=current_point.x;
            //现在来说明这个二维数组怎样记录最短路径，首先这个数组里存的是坐标结构体，数组下标代表着子节点坐标，而数组内容存着父节点坐标，这样皆可以通过循环，一级一级找上去，既可以知道最短路径长度，也可以打印所有经过的节点坐标
            path[moved_point.x][moved_point.y].y=current_point.y;
        }
    }          
}

int main(void)                   
{
    //初始化迷宫地图
    for(int m = 0;m < maze_x_length + 1; m++)                  
    {
        for(int n = 0; n < maze_y_length + 1;n++)
        {
            scanf("%d",&maze[m][n]);
        }
    }

    BFS();  
    
    int num[30][2];

    int x = maze_x_length,y = maze_y_length;
    int i=0;
    while(1)
    {                                //把父子节点关系倒着取出放入数组中以便打印
        int k;
        k=x;
        x=path[x][y].x;
        y=path[k][y].y;

        num[i][0]=x;
        num[i][1]=y;  
        i++;
        if(x==0&&y==0)
            break;
    }

    for(int j=i-1;j>=0;j--)
    {
        printf("(%d, %d)\n",num[j][0],num[j][1]);          //打印路径节点部分
    }
    printf("(%d, %d)",maze_x_length, maze_y_length);     

    return 0;
}